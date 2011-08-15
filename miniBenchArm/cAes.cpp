#include "cAes.h"

/*
  COSBI: Comprehensive Open Source Benchmarking Initiative
  Copyright (c) 2007 Van Smith

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  The current web address of the GNU General Public License is:
  http://www.gnu.org/licenses/gpl.html

  You can contact the authors of this software at:
  cosbi@vanshardware.com
  See www.vanshardware.com or www.cosbi.org for more contact details.
*/

cAes::cAes(void)
{
  //setKeyToDefault();
  cerr << "cAes constructor called" << endl;
  initializeData();
  mboolCentaurPadlockAesAvailable = false;
  detectPadlock();
  cerr << "cAes constructor completed" << endl;
}

void cAes::initializeData()
{
   // Various control words for Padlock AES engine for encryption:
   cerr << "cAes initializeData() called" << endl;
   HwkyEncrypt128[0] = ENCRYPT + HWKEY + KEYSIZE_128;
   HwkyEncrypt128[1] = 0;
   HwkyEncrypt128[2] = 0;
   HwkyEncrypt128[3] = 0;
   // Various control words for Padlock AES engine for decryption:
   HwkyDecrypt128[0] = DECRYPT + HWKEY + KEYSIZE_128;
   HwkyDecrypt128[1] = 0;
   HwkyDecrypt128[2] = 0;
   HwkyDecrypt128[3] = 0;
   boolBufferAllocated = false;
   cerr << "cAes initializeData() completed" << endl;
}

cAes::~cAes(void)
{
  // we need to free the allocatated buffer
  if( boolBufferAllocated == true )
  {
#ifdef vs2005
    _aligned_free( mpucBuffer );
#else
    free( mpucBuffer );
#endif
  }
}

void cAes::setKey( int aKey[] )
{
   for (int i = 0; i <= 3; i++)
   {
      softwareKey[i] = aKey[i];
      ViaPadlockAesKey[i] = aKey[i];
   }
   for (int i = 4; i<= 7; i++ )
   {
      ViaPadlockAesKey[i] = 0;
   }
} // void cAes::setKey( int aKey[] )

void cAes::setKeyToDefault()
{
  int liAesKey[] =  {0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c};
  setKey( liAesKey );
} // void cAes::setKeyToDefault()

void cAes::createFilledAlignedBuffer( unsigned char* aucBuffer, size_t aBufferSize )
{
  createEmptyAlignedBuffer( aBufferSize );
  memcpy( mpucBuffer, aucBuffer, miBufferLength );
  // pad the end of the buffer:
  padBuffer();
} // void cAes::createFilledAlignedBuffer( unsigned char* aucBuffer, size_t aBufferSize )

void cAes::createEmptyAlignedBuffer( size_t aBufferSize )
{
  setBufferSize( aBufferSize );
  size_t lstBufferAllocation = miBufferLengthIn16BBlocks * 16;
  if( boolBufferAllocated == true )
  {
	free( mpucBuffer );
    mpucBuffer = (unsigned char*)valloc( lstBufferAllocation );
  } else
  {
	mpucBuffer = (unsigned char*)valloc( lstBufferAllocation );
    boolBufferAllocated = true;
  }
  if( ( (unsigned long)mpucBuffer % 16 ) != 0 )
  {
    cerr << "_aligned_malloc failed to create an aligned buffer." << endl;
//    exit(1);
  } // if
}

void cAes::padBuffer()
{
  size_t lstBufferAllocation = miBufferLengthIn16BBlocks * 16;
  // pad the end of the buffer:
  size_t lstPadValue = lstBufferAllocation - miBufferLength;
  for( size_t i = miBufferLength; i < lstBufferAllocation; i++ )
  {
    mpucBuffer[ i ] = lstPadValue;
  } // for
} // void cAes::padBuffer()

void cAes::createAlignedBufferFromString( string &aStringToEncrypt )
{
  createFilledAlignedBuffer( (unsigned char*)aStringToEncrypt.c_str(), aStringToEncrypt.length() );
} // void cAes::createAlignedBufferFromString( string &aStringToEncrypt )

void cAes::setKeyFromString( string asKey )
{
  int liKey[4] = {0};
  size_t lstKeyLength = asKey.length();
  if( lstKeyLength < 16 )
  {
    memcpy( liKey, asKey.c_str(), lstKeyLength );
  } else
  {
    memcpy( liKey, asKey.c_str(), 16 );
  }
  setKey( liKey );
} // void cAes::setKeyFromString( string astrKey )

// ecbEncrypt(): this is the main encryption function
void cAes::ecbEncrypt()
{
  if (mboolCentaurPadlockAesAvailable)
  {
    padlockEcbEncrypt( HwkyEncrypt128, mpucBuffer, ViaPadlockAesKey, miBufferLengthIn16BBlocks );
  }
  else
  {
    aes_encrypt_key128(softwareKey, &ECTX);
    for( int i=0; i < miBufferLengthIn16BBlocks; i++ )
    {
      aes_encrypt( &mpucBuffer[i*16], &mpucBuffer[i*16], &ECTX );
    }
  }
} // void cAes::ecbEncrypt()

// ecbDecryptTest(): this is the main decryption function
void cAes::ecbDecrypt()
{
  if (mboolCentaurPadlockAesAvailable)
  {
    padlockEcbDecrypt( HwkyDecrypt128, mpucBuffer, ViaPadlockAesKey, miBufferLengthIn16BBlocks );
  }
  else
  {
    aes_decrypt_key128(softwareKey, &DCTX);
    for( int i=0; i < miBufferLengthIn16BBlocks; i++ )
    {
      aes_decrypt( &mpucBuffer[i*16], &mpucBuffer[i*16], &DCTX );
    }
  }
} // void cAes::ecbDecrypt()

void cAes::padlockEcbDecrypt( int aHwkyDecrypt128[],
                              unsigned char* apucBuffer,
                              int aViaPadlockAesKey[],
                              int aBufferSizeIn16ByteBlocks)
{
  throw("padlockEcbDecrypt: Not available on ARM CPU");
/*
#ifdef vs2005
  NEW_KEYS
  __asm mov edx, aHwkyDecrypt128
  __asm mov esi, apucBuffer
  __asm mov edi, apucBuffer
  __asm mov ebx, aViaPadlockAesKey
  __asm mov ecx, aBufferSizeIn16ByteBlocks
  XCRYPT_ECB
#else
  asm __volatile__
  (
    NEW_KEYS
    "movl %%esi, %%edi;"
    XCRYPT_ECB
    : // no output variables
    : [aHwkyEncrypt128] "d" (aHwkyDecrypt128),
      [apucBuffer] "S" (apucBuffer),
      "b" (aViaPadlockAesKey),
      "c" (aBufferSizeIn16ByteBlocks)
    : "memory", "cc"
  ); // asm
#endif
*/
}

void cAes::padlockEcbEncrypt( int aHwkyEncrypt128[],
                              unsigned char* apucBuffer,
                              int aViaPadlockAesKey[],
                              int aBufferSizeIn16ByteBlocks)
{
  throw("padlockEcbEncrypt: Not available on ARM CPU");
/*
#ifdef vs2005
  NEW_KEYS
  __asm mov edx, aHwkyEncrypt128
  __asm mov esi, apucBuffer
  __asm mov edi, apucBuffer
  __asm mov ebx, aViaPadlockAesKey
  __asm mov ecx, aBufferSizeIn16ByteBlocks
  XCRYPT_ECB
#else
  asm __volatile__
  (
    NEW_KEYS
    "movl %%esi, %%edi;"
    XCRYPT_ECB
    : // no output variables
    : [aHwkyEncrypt128] "d" (aHwkyEncrypt128),
      [apucBuffer] "S" (apucBuffer),
      "b" (aViaPadlockAesKey),
      "c" (aBufferSizeIn16ByteBlocks)
    : "memory", "cc"
  ); // asm
#endif
*/
}

void cAes::ecbEncryptThisString( string &aStringToEncrypt, string asKey )
{
  setKeyFromString( asKey );
  createAlignedBufferFromString( aStringToEncrypt );
  ecbEncrypt();
  returnResultAsString( aStringToEncrypt, miBufferLengthIn16BBlocks * 16 );
} // void cAes::ecbEncryptThisString()

void cAes::ecbDecryptThisString( string &aStringToDecrypt, string asKey )
{
  setKeyFromString( asKey );
  createAlignedBufferFromString( aStringToDecrypt );
  ecbDecrypt();
  size_t lstPadCount = mpucBuffer[ miBufferLength - 1 ];
  returnResultAsString( aStringToDecrypt, miBufferLength - lstPadCount );
} // void cAes::ecbEncryptThisString()

void cAes::detectPadlock()
{
   cerr << "cAes detectPadlock() called" << endl;

   mboolCentaurPadlockAesAvailable = isCentaurPadlockAesAvailable();

   cerr << "cAes detectPadlock() completed" << endl;

} // bool cSha256::detectPadlock()

void cAes::forceSoftwareCodePath()
{
  mboolCentaurPadlockAesAvailable = false;
} // void cSha256::forceSoftwareCodePath()

void cAes::forcePadlockCodePath()
{
  mboolCentaurPadlockAesAvailable = true;
} // void cSha256::forcePadlockCodePath()

void cAes::setBufferSize( int aiBufferSize )
{
  // this routine will set the miBufferLengthIn16BBlocks to >= the length
  // of the input buffer / 16.  It will add 1 if the length is a multiple of 16 in order
  // to accomidate a buffer terminator that indicates where the last buffer element ends
  // within the last block.
  miBufferLength = aiBufferSize;
  miBufferLengthIn16BBlocks = ( int )ceil( ( double )miBufferLength / 16 );
  if( ( miBufferLength % 16 ) == 0 )
  {
    miBufferLengthIn16BBlocks++;
  } // if
} // int cAes::setBufferSizeIn16ByteBlocks()

void cAes::setBuffer( unsigned char aucBufferToEncrypt[], int aiBufferLength )
{
  // note that aucBufferToEncrypt needs to be aligned to 16 bytes
  setBufferSize( aiBufferLength );
  mpucBuffer = &aucBufferToEncrypt[ 0 ];
  padBuffer();
} // void cAes::setBuffer( int aiBufferToEncrypt[] )

void cAes::getResultAsString(string &astrResult )
{
  astrResult.assign( (char*)mpucBuffer, miBufferLength );
}

void cAes::returnResultAsString(string &astrResult, int aiBufferLength )
{
  astrResult.assign( (char*)mpucBuffer, aiBufferLength );
} // void cAes::returnResultAsString(string &astrResult, int aiBufferLength )

string cAes::ecbEncryptThisTextFile( string astrFileName, string astrKey )
{
  string lFileContents = readTextFileIntoString( astrFileName );
  ecbEncryptThisString( lFileContents, astrKey );
  return lFileContents;
}

string cAes::ecbDecryptThisTextFile( string astrFileName, string astrKey )
{
  string lFileContents = readTextFileIntoString( astrFileName );
  ecbDecryptThisString( lFileContents, astrKey );
  return lFileContents;
}

bool cAes::runEncryptDecryptValidationTest( string &asResult )
{
  bool lbResult = false;
  ostringstream ossResult;
  string lsKey = "My test key";
  string lstrEncryptMe = "This is a test string to encrypt.";
  string lstrOriginalKey = lstrEncryptMe;
  ossResult << "== Encrypt/Decrypt Validation Test ==" << endl;
  ossResult << "I'm going to try to encrypt \"" << lstrEncryptMe << "\"" << endl;
  ecbEncryptThisString( lstrEncryptMe, lsKey );
  ossResult << "The string is now \"" << lstrEncryptMe << "\"" << endl;
  ossResult << "Now decrypting \"" << lstrEncryptMe << "\"..." << endl;
  ecbDecryptThisString( lstrEncryptMe, lsKey );
  ossResult << "The string is now \"" << lstrEncryptMe << "\"" << endl << endl;
  if( lstrEncryptMe == lstrOriginalKey )
  {
    ossResult << "The resultant string is identical to the original string." << endl;
    ossResult << "== Encrypt/decrypt validation PASSED. ==" << endl;
    lbResult = true;
  } else
  {
    ossResult << "The resultant string is different from the original string." << endl;
    ossResult << "== Encrypt/decrypt validation FAILED. ==" << endl;
    lbResult = false;
  }
  asResult = ossResult.str();
  return lbResult;
} // bool cAes::runEncryptDecryptValidationTest( string &asResult )

