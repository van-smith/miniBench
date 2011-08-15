#include "cSha1.h"

static unsigned8BitInt sha1Padding[64] =
{
   0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

cSha1::cSha1()
{
   cerr << "cSha1 constructor called." << endl;
   detectPadlock();
} // cSha1::cSha1()

cSha1::~cSha1()
{
   cerr << "cSha1 destructor called." << endl;
} // cSha1::~cSha1()

void cSha1::detectPadlock()
{
   mboolCentaurPadlockHashEngineAvailable = isCentaurPadlockHashEngineAvailable();
} // bool cSha1::detectPadlock()

void cSha1::forceSoftwareCodePath()
{
   mboolCentaurPadlockHashEngineAvailable = false;
} // void cSha1::forceSoftwareCodePath()

void cSha1::forcePadlockCodePath()
{
   mboolCentaurPadlockHashEngineAvailable = true;
} // void cSha1::forcePadlockCodePath()


void cSha1::sha1Starts()
{
   mSha1Context.total[0] = 0;
   mSha1Context.total[1] = 0;

   mSha1Context.state[0] = 0x67452301;
   mSha1Context.state[1] = 0xEFCDAB89;
   mSha1Context.state[2] = 0x98BADCFE;
   mSha1Context.state[3] = 0x10325476;
   mSha1Context.state[4] = 0xC3D2E1F0;
}

void cSha1::sha1Process( unsigned8BitInt data[64] )
{
   unsigned32BitInt temp, W[16], A, B, C, D, E;
   for( int i = 0; i <= 15; i++)
   {
      W[i]   = getInt32FromInt8Array(data, 4*i);
   }
   A = mSha1Context.state[0];
   B = mSha1Context.state[1];
   C = mSha1Context.state[2];
   D = mSha1Context.state[3];
   E = mSha1Context.state[4];

#define S(x,n) (((x) << (n)) | (((x) & 0xFFFFFFFF) >> (32 - (n))))

#define R(t)                                            \
(                                                       \
    temp = (W[(t -  3) & 0x0F]) ^ (W[(t - 8) & 0x0F]) ^     \
           (W[(t - 14) & 0x0F]) ^ (W[ t      & 0x0F]),      \
    ( W[t & 0x0F] = S(temp,1) )                         \
)

#define P(a,b,c,d,e,x)                                  \
{                                                       \
    e += S((a),5) + F((b),(c),(d)) + (K) + (x);			\
	b = S((b),30);       								\
}

#define F(x,y,z) ((z) ^ ((x) & ((y) ^ (z))))
#define K 0x5A827999

   for( int i = 0; i <= 14; i += 5 )
   {
      P( A, B, C, D, E, W[i]  );
      P( E, A, B, C, D, W[i + 1]  );
      P( D, E, A, B, C, W[i + 2]  );
      P( C, D, E, A, B, W[i + 3]  );
      P( B, C, D, E, A, W[i + 4]  );
   } // for

   P( A, B, C, D, E, W[15] );
   P( E, A, B, C, D, R(16) );
   P( D, E, A, B, C, R(17) );
   P( C, D, E, A, B, R(18) );
   P( B, C, D, E, A, R(19) );

#undef K
#undef F

#define F(x,y,z) ((x) ^ (y) ^ (z))
#define K 0x6ED9EBA1

   for( int i = 20; i <= 39; i += 5 )
   {
      P( A, B, C, D, E, R(i) );
      P( E, A, B, C, D, R(i + 1) );
      P( D, E, A, B, C, R(i + 2) );
      P( C, D, E, A, B, R(i + 3) );
      P( B, C, D, E, A, R(i + 4) );
   } // for

#undef K
#undef F

#define F(x,y,z) (((x) & (y)) | ((z) & ((x) | (y))))
#define K 0x8F1BBCDC

   for( int i = 40; i <= 59; i += 5 )
   {
      P( A, B, C, D, E, R(i) );
      P( E, A, B, C, D, R(i + 1) );
      P( D, E, A, B, C, R(i + 2) );
      P( C, D, E, A, B, R(i + 3) );
      P( B, C, D, E, A, R(i + 4) );
   } // for 

#undef K
#undef F

#define F(x,y,z) ((x) ^ (y) ^ (z))
#define K 0xCA62C1D6

   for( int i = 60; i <= 79; i += 5 )
   {
      P( A, B, C, D, E, R(i) );
      P( E, A, B, C, D, R(i + 1) );
      P( D, E, A, B, C, R(i + 2) );
      P( C, D, E, A, B, R(i + 3) );
      P( B, C, D, E, A, R(i + 4) );
   } // for

#undef K
#undef F

   mSha1Context.state[0] += A;
   mSha1Context.state[1] += B;
   mSha1Context.state[2] += C;
   mSha1Context.state[3] += D;
   mSha1Context.state[4] += E;
}

void cSha1::sha1Update( unsigned8BitInt aUnsigned8BitArray[], unsigned32BitInt length )
{
   unsigned32BitInt left, fill, i;

   if( !length ) return;

   left = mSha1Context.total[0] & 0x3F;
   fill = 64 - left;

   mSha1Context.total[0] += length;
   mSha1Context.total[0] &= 0xFFFFFFFF;

   if( mSha1Context.total[0] < length )
   {
      mSha1Context.total[1]++;
   }
   i = 0;
   if( left && length >= fill )
   {
      memcpy( (void *)(&mSha1Context.buffer[left]), (void *)&aUnsigned8BitArray[ i ], fill );
      sha1Process( mSha1Context.buffer );
      length -= fill;
      i += fill;
      left = 0;
    }
    while( length >= 64 )
    {
      sha1Process( &aUnsigned8BitArray[ i ] );
      length -= 64;
      i  += 64;
    }
   if( length )
   {
      memcpy
      (
         (void *)(&mSha1Context.buffer[left]), (void *)&aUnsigned8BitArray[ i ], length
      );
   }
} // void cSha1::sha1Update()

void cSha1::sha1Finish()
{
   unsigned32BitInt last, padn;
   unsigned32BitInt high, low;
   unsigned8BitInt msglen[8];
   high = ( mSha1Context.total[0] >> 29 ) | ( mSha1Context.total[1] <<  3 );
   low  = ( mSha1Context.total[0] <<  3 );
   putInt32IntoInt8Array( high, msglen, 0 );
   putInt32IntoInt8Array( low,  msglen, 4 );
   last = mSha1Context.total[0] & 0x3F;
   padn = ( last < 56 ) ? ( 56 - last ) : ( 120 - last );
   sha1Update( sha1Padding, padn );
   sha1Update( msglen, 8 );
   putInt32IntoInt8Array( mSha1Context.state[0], sha1Result,  0 );
   putInt32IntoInt8Array( mSha1Context.state[1], sha1Result,  4 );
   putInt32IntoInt8Array( mSha1Context.state[2], sha1Result,  8 );
   putInt32IntoInt8Array( mSha1Context.state[3], sha1Result, 12 );
   putInt32IntoInt8Array( mSha1Context.state[4], sha1Result, 16 );
} // void cSha1::sha1Finish()

void cSha1::hashThisString( string &aStringToHash )
{
   sha1Starts();
   mByteArrayLength = aStringToHash.length();
   mUnsigned8BitArray = (unsigned8BitInt*)aStringToHash.c_str();
   if( mboolCentaurPadlockHashEngineAvailable )
   {
      memcpy( (void *)sha1Result ,(void *)(mSha1Context.state), 20 );
      padlockHashTheArray();
   }
   else
   {
      sha1Update( mUnsigned8BitArray, mByteArrayLength );
      sha1Finish();
   }
} // void cSha1::hashThisString( string aStringToHash )

void cSha1::padlockHashTheArray()
{
   centaurPadlockSha1(mByteArrayLength, mUnsigned8BitArray, sha1Result);
   // reorder bytes
   int temp;
   for( int j = 0; j <= 16; j += 4 )
   {
      temp = getInt32FromInt8Array(sha1Result, j);
      sha1Result[j + 3] = (unsigned8BitInt) (temp >> 24);
      sha1Result[j + 2] = (unsigned8BitInt) (temp >> 16);
      sha1Result[j + 1] = (unsigned8BitInt) (temp >> 8);
      sha1Result[j    ] = (unsigned8BitInt) (temp);
   }
} // void cSha1::padlockHashThisString()

void cSha1::hashThisTextFile( string astrFileName )
{
   stringToHash = readTextFileIntoString( astrFileName );
   hashThisString( stringToHash );
} // void cSha1::hashThisFile( string astrFileName )

string cSha1::getSha1ResultAsHex()
{
   string lstrSha1HexResult = "";
   for( int j = 0; j < 20; j++ )
   {
      lstrSha1HexResult += byte2HexString( sha1Result[j] );
   } // for
   return lstrSha1HexResult;
} // string cSha1::getSha1ResultAsHex()

