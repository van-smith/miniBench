#include "cSha256.h"

static unsigned8BitInt sha256Padding[64] =
{
   0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

cSha256::cSha256()
{
   cerr << "cSha256 constructor called." << endl;
   detectPadlock();
} // cSha256::cSha256()

cSha256::~cSha256()
{
   cerr << "cSha256 destructor called." << endl;
} // cSha256::~cSha256()

void cSha256::detectPadlock()
{
   mboolCentaurPadlockHashEngineAvailable = isCentaurPadlockHashEngineAvailable();
} // bool cSha256::detectPadlock()

void cSha256::forceSoftwareCodePath()
{
   mboolCentaurPadlockHashEngineAvailable = false;
} // void cSha256::forceSoftwareCodePath()

void cSha256::forcePadlockCodePath()
{
   mboolCentaurPadlockHashEngineAvailable = true;
} // void cSha256::forcePadlockCodePath()


void cSha256::sha256Starts()
{
   mSha256Context.total[0] = 0;
   mSha256Context.total[1] = 0;

   mSha256Context.state[0] = 0x6A09E667;
   mSha256Context.state[1] = 0xBB67AE85;
   mSha256Context.state[2] = 0x3C6EF372;
   mSha256Context.state[3] = 0xA54FF53A;
   mSha256Context.state[4] = 0x510E527F;
   mSha256Context.state[5] = 0x9B05688C;
   mSha256Context.state[6] = 0x1F83D9AB;
   mSha256Context.state[7] = 0x5BE0CD19;
}

void cSha256::sha256Process( unsigned8BitInt data[64] )
{
   unsigned32BitInt temp1, temp2, W[64];
   unsigned32BitInt A, B, C, D, E, F, G, H;

   for( int i = 0; i <= 15; i++)
   {
      W[i]   = getInt32FromInt8Array(data, 4*i);
   }

#define  SHR(x,n) ((x & 0xFFFFFFFF) >> n)
#define ROTR(x,n) (SHR(x,n) | (x << (32 - n)))

#define S0(x) (ROTR(x, 7) ^ ROTR(x,18) ^  SHR(x, 3))
#define S1(x) (ROTR(x,17) ^ ROTR(x,19) ^  SHR(x,10))

#define S2(x) (ROTR(x, 2) ^ ROTR(x,13) ^ ROTR(x,22))
#define S3(x) (ROTR(x, 6) ^ ROTR(x,11) ^ ROTR(x,25))

#define F0(x,y,z) ((x & y) | (z & (x | y)))
#define F1(x,y,z) (z ^ (x & (y ^ z)))

#define R(t)                                    \
(                                               \
    W[t] = S1(W[t -  2]) + W[t -  7] +          \
           S0(W[t - 15]) + W[t - 16]            \
)

#define P(a,b,c,d,e,f,g,h,x,K)                  \
{                                               \
    temp1 = h + S3(e) + F1(e,f,g) + K + x;      \
    temp2 = S2(a) + F0(a,b,c);                  \
    d += temp1; h = temp1 + temp2;              \
}

    A = mSha256Context.state[0];
    B = mSha256Context.state[1];
    C = mSha256Context.state[2];
    D = mSha256Context.state[3];
    E = mSha256Context.state[4];
    F = mSha256Context.state[5];
    G = mSha256Context.state[6];
    H = mSha256Context.state[7];

    P( A, B, C, D, E, F, G, H, W[ 0], 0x428A2F98 );
    P( H, A, B, C, D, E, F, G, W[ 1], 0x71374491 );
    P( G, H, A, B, C, D, E, F, W[ 2], 0xB5C0FBCF );
    P( F, G, H, A, B, C, D, E, W[ 3], 0xE9B5DBA5 );
    P( E, F, G, H, A, B, C, D, W[ 4], 0x3956C25B );
    P( D, E, F, G, H, A, B, C, W[ 5], 0x59F111F1 );
    P( C, D, E, F, G, H, A, B, W[ 6], 0x923F82A4 );
    P( B, C, D, E, F, G, H, A, W[ 7], 0xAB1C5ED5 );
    P( A, B, C, D, E, F, G, H, W[ 8], 0xD807AA98 );
    P( H, A, B, C, D, E, F, G, W[ 9], 0x12835B01 );
    P( G, H, A, B, C, D, E, F, W[10], 0x243185BE );
    P( F, G, H, A, B, C, D, E, W[11], 0x550C7DC3 );
    P( E, F, G, H, A, B, C, D, W[12], 0x72BE5D74 );
    P( D, E, F, G, H, A, B, C, W[13], 0x80DEB1FE );
    P( C, D, E, F, G, H, A, B, W[14], 0x9BDC06A7 );
    P( B, C, D, E, F, G, H, A, W[15], 0xC19BF174 );
    P( A, B, C, D, E, F, G, H, R(16), 0xE49B69C1 );
    P( H, A, B, C, D, E, F, G, R(17), 0xEFBE4786 );
    P( G, H, A, B, C, D, E, F, R(18), 0x0FC19DC6 );
    P( F, G, H, A, B, C, D, E, R(19), 0x240CA1CC );
    P( E, F, G, H, A, B, C, D, R(20), 0x2DE92C6F );
    P( D, E, F, G, H, A, B, C, R(21), 0x4A7484AA );
    P( C, D, E, F, G, H, A, B, R(22), 0x5CB0A9DC );
    P( B, C, D, E, F, G, H, A, R(23), 0x76F988DA );
    P( A, B, C, D, E, F, G, H, R(24), 0x983E5152 );
    P( H, A, B, C, D, E, F, G, R(25), 0xA831C66D );
    P( G, H, A, B, C, D, E, F, R(26), 0xB00327C8 );
    P( F, G, H, A, B, C, D, E, R(27), 0xBF597FC7 );
    P( E, F, G, H, A, B, C, D, R(28), 0xC6E00BF3 );
    P( D, E, F, G, H, A, B, C, R(29), 0xD5A79147 );
    P( C, D, E, F, G, H, A, B, R(30), 0x06CA6351 );
    P( B, C, D, E, F, G, H, A, R(31), 0x14292967 );
    P( A, B, C, D, E, F, G, H, R(32), 0x27B70A85 );
    P( H, A, B, C, D, E, F, G, R(33), 0x2E1B2138 );
    P( G, H, A, B, C, D, E, F, R(34), 0x4D2C6DFC );
    P( F, G, H, A, B, C, D, E, R(35), 0x53380D13 );
    P( E, F, G, H, A, B, C, D, R(36), 0x650A7354 );
    P( D, E, F, G, H, A, B, C, R(37), 0x766A0ABB );
    P( C, D, E, F, G, H, A, B, R(38), 0x81C2C92E );
    P( B, C, D, E, F, G, H, A, R(39), 0x92722C85 );
    P( A, B, C, D, E, F, G, H, R(40), 0xA2BFE8A1 );
    P( H, A, B, C, D, E, F, G, R(41), 0xA81A664B );
    P( G, H, A, B, C, D, E, F, R(42), 0xC24B8B70 );
    P( F, G, H, A, B, C, D, E, R(43), 0xC76C51A3 );
    P( E, F, G, H, A, B, C, D, R(44), 0xD192E819 );
    P( D, E, F, G, H, A, B, C, R(45), 0xD6990624 );
    P( C, D, E, F, G, H, A, B, R(46), 0xF40E3585 );
    P( B, C, D, E, F, G, H, A, R(47), 0x106AA070 );
    P( A, B, C, D, E, F, G, H, R(48), 0x19A4C116 );
    P( H, A, B, C, D, E, F, G, R(49), 0x1E376C08 );
    P( G, H, A, B, C, D, E, F, R(50), 0x2748774C );
    P( F, G, H, A, B, C, D, E, R(51), 0x34B0BCB5 );
    P( E, F, G, H, A, B, C, D, R(52), 0x391C0CB3 );
    P( D, E, F, G, H, A, B, C, R(53), 0x4ED8AA4A );
    P( C, D, E, F, G, H, A, B, R(54), 0x5B9CCA4F );
    P( B, C, D, E, F, G, H, A, R(55), 0x682E6FF3 );
    P( A, B, C, D, E, F, G, H, R(56), 0x748F82EE );
    P( H, A, B, C, D, E, F, G, R(57), 0x78A5636F );
    P( G, H, A, B, C, D, E, F, R(58), 0x84C87814 );
    P( F, G, H, A, B, C, D, E, R(59), 0x8CC70208 );
    P( E, F, G, H, A, B, C, D, R(60), 0x90BEFFFA );
    P( D, E, F, G, H, A, B, C, R(61), 0xA4506CEB );
    P( C, D, E, F, G, H, A, B, R(62), 0xBEF9A3F7 );
    P( B, C, D, E, F, G, H, A, R(63), 0xC67178F2 );

    mSha256Context.state[0] += A;
    mSha256Context.state[1] += B;
    mSha256Context.state[2] += C;
    mSha256Context.state[3] += D;
    mSha256Context.state[4] += E;
    mSha256Context.state[5] += F;
    mSha256Context.state[6] += G;
    mSha256Context.state[7] += H;
}

void cSha256::sha256Update( unsigned8BitInt aUnsigned8BitArray[], unsigned32BitInt length )
{
   unsigned32BitInt left, fill, i;

   if( !length ) return;

   left = mSha256Context.total[0] & 0x3F;
   fill = 64 - left;

   mSha256Context.total[0] += length;
   mSha256Context.total[0] &= 0xFFFFFFFF;

   if( mSha256Context.total[0] < length )
   {
      mSha256Context.total[1]++;
   }
   i = 0;
   if( left && length >= fill )
   {
      memcpy( (void *)(&mSha256Context.buffer[left]), (void *)&aUnsigned8BitArray[ i ], fill );
      sha256Process( mSha256Context.buffer );
      length -= fill;
      i += fill;
      left = 0;
    }
    while( length >= 64 )
    {
      sha256Process( &aUnsigned8BitArray[ i ] );
      length -= 64;
      i  += 64;
    }
   if( length )
   {
      memcpy
      (
         (void *)(&mSha256Context.buffer[left]), (void *)&aUnsigned8BitArray[ i ], length
      );
   }
} // void cSha256::sha256Update()

void cSha256::sha256Finish()
{
   unsigned32BitInt last, padn;
   unsigned32BitInt high, low;
   unsigned8BitInt msglen[8];
   high = ( mSha256Context.total[0] >> 29 ) | ( mSha256Context.total[1] <<  3 );
   low  = ( mSha256Context.total[0] <<  3 );
   putInt32IntoInt8Array( high, msglen, 0 );
   putInt32IntoInt8Array( low,  msglen, 4 );
   last = mSha256Context.total[0] & 0x3F;
   padn = ( last < 56 ) ? ( 56 - last ) : ( 120 - last );
   sha256Update( sha256Padding, padn );
   sha256Update( msglen, 8 );
   putInt32IntoInt8Array( mSha256Context.state[0], sha256Result,  0 );
   putInt32IntoInt8Array( mSha256Context.state[1], sha256Result,  4 );
   putInt32IntoInt8Array( mSha256Context.state[2], sha256Result,  8 );
   putInt32IntoInt8Array( mSha256Context.state[3], sha256Result, 12 );
   putInt32IntoInt8Array( mSha256Context.state[4], sha256Result, 16 );
   putInt32IntoInt8Array( mSha256Context.state[5], sha256Result, 20 );
   putInt32IntoInt8Array( mSha256Context.state[6], sha256Result, 24 );
   putInt32IntoInt8Array( mSha256Context.state[7], sha256Result, 28 );

} // void cSha256::sha256Finish()

void cSha256::hashThisString( string &aStringToHash )
{
   sha256Starts();
   mByteArrayLength = aStringToHash.length();
   mUnsigned8BitArray = (unsigned8BitInt*)aStringToHash.c_str();
   if( mboolCentaurPadlockHashEngineAvailable )
   {
      memcpy( (void *)sha256Result ,(void *)(mSha256Context.state), 32 );
      padlockHashTheArray();
   }
   else
   {
      sha256Update( mUnsigned8BitArray, mByteArrayLength );
      sha256Finish();
   }
} // void cSha256::hashThisString( string aStringToHash )

void cSha256::padlockHashTheArray()
{
   centaurPadlockSha256(mByteArrayLength, mUnsigned8BitArray, sha256Result);
   // reorder bytes
   int temp;
   for( int j = 0; j <= 28; j += 4 )
   {
      temp = getInt32FromInt8Array(sha256Result, j);
      sha256Result[j + 3] = (unsigned8BitInt) (temp >> 24);
      sha256Result[j + 2] = (unsigned8BitInt) (temp >> 16);
      sha256Result[j + 1] = (unsigned8BitInt) (temp >> 8);
      sha256Result[j    ] = (unsigned8BitInt) (temp);
   }
} // void cSha256::padlockHashThisString()

void cSha256::hashThisTextFile( string astrFileName )
{
   stringToHash = readTextFileIntoString( astrFileName );
   hashThisString( stringToHash );
} // void cSha256::hashThisFile( string astrFileName )

string cSha256::getSha256ResultAsHex()
{
   string lstrSha256HexResult = "";
   for( int j = 0; j < 32; j++ )
   {
      lstrSha256HexResult += byte2HexString( sha256Result[j] );
   } // for
   return lstrSha256HexResult;
} // string cSha256::getSha256ResultAsHex()

