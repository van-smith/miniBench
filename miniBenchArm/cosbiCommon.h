#pragma once
//#define windowos
//#define amd64

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
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdexcept>
//#ifdef windowsos
//  #include "..\common\cosbiDefine.h"
//#else
  #include "cosbiDefine.h"
//#endif

using namespace std;

//necessary call Padlock ACE ECB encrypt/decrypt (__asm _emit 0xF3 is the "rep" prefix):
#ifdef vs2005
  #define XCRYPT_ECB  __asm _emit 0xF3 __asm _emit 0x0F __asm _emit 0xA7 __asm _emit 0xC8
  #define XCRYPT_CBC  __asm _emit 0xF3 __asm _emit 0x0F __asm _emit 0xA7 __asm _emit 0xD0
  #define NEW_KEYS    __asm pushfd __asm popfd
  // VIA Padlock RNG instruction
  #define REPXSTORE   __asm _emit 0xF3 __asm _emit 0x0F __asm _emit 0xA7 __asm _emit 0xC0
#else
  #define XCRYPT_ECB  ".byte 0xF3; .byte 0x0F; .byte 0xA7; .byte 0xC8;"
  #define XCRYPT_CBC  ".byte 0xF3; .byte 0x0F; .byte 0xA7; .byte 0xD0;"
  #ifdef amd64
    #define NEW_KEYS
  #else
    #define NEW_KEYS    "pushfl; popfl;"
  #endif
  // VIA Padlock RNG instruction
  #define REPXSTORE   ".byte 0xF3; .byte 0x0F; .byte 0xA7; .byte 0xC0;"
#endif
// Various control words for Padlock AES engine:
#define HWKEY        0x000
#define KEYSIZE_128  0x000 + 0x00a
#define ENCRYPT      0x000
#define DECRYPT      0x200

#ifndef unsigned8BitInt
#define unsigned8BitInt  unsigned char
#endif

#ifndef unsigned32BitInt
#define unsigned32BitInt unsigned long int
#endif

inline int getInt32FromInt8Array(unsigned8BitInt b[], int i)
{
   return   (   (unsigned32BitInt) b[i    ] << 24 )
            | ( (unsigned32BitInt) b[i + 1] << 16 )
            | ( (unsigned32BitInt) b[i + 2] <<  8 )
            | ( (unsigned32BitInt) b[i + 3]       );
} // inline int getInt32FromInt8Array(unsigned8BitInt b[], int i)

inline void RDTSC( int &upperWord, int &lowerWord )
{
#ifdef vs2005
  __asm rdtsc
  __asm mov lowerWord, eax
  __asm mov upperWord, edx
#else
  asm __volatile__
  (
    "rdtsc;"
    :"=a" (lowerWord), "=d" (upperWord)
  );
#endif
} // inline void RDTSC( int &upperWord, int &lowerWord )

inline void putInt32IntoInt8Array(unsigned32BitInt n, unsigned8BitInt b[], int i)
{
    b[i    ] = (unsigned8BitInt) ( n >> 24 );
    b[i + 1] = (unsigned8BitInt) ( n >> 16 );
    b[i + 2] = (unsigned8BitInt) ( n >>  8 );
    b[i + 3] = (unsigned8BitInt) ( n       );
} // inline void putInt32IntoInt8Array(unsigned32BitInt n, unsigned8BitInt b[], int i)

inline void Copy32BitIntArray(unsigned32BitInt aSourceArray[], unsigned32BitInt aDestinationArray[], int aCount)
{
   throw("Copy32BitIntArray: Not available on ARM CPU");
/*
#ifdef vs2005
   __asm mov esi, aSourceArray
   __asm mov edi, aDestinationArray
   __asm mov ecx, aCount
   __asm rep movsd
#else
   asm
   (
        "movl %[aSourceArray], %%esi;"
        "movl %[aDestinationArray], %%edi;"
        "rep movsd;"
        : // no output variables
        :[aSourceArray] "r" (aSourceArray), [aDestinationArray] "r" (aDestinationArray), "c" (aCount)
        :"esi", "edi", "ecx"
    ); // asm
#endif
*/
} // inline void Copy32BitIntArray(unsigned32BitInt aSourceArray[], unsigned32BitInt aDestinationArray[], int aCount)

inline bool IsAddress16ByteAligned( void *aBufferAddress )
{
   return (unsigned long)aBufferAddress % 16 == 0;
} // inline bool IsAddress16ByteAligned( void * aBufferAddress )

//inline int round(double x)
//{
//  return int(x > 0.0 ? x + 0.5 : x - 0.5);
//} // inline int round(double x)

string booleanToYesNo( bool aBoolean );
string booleanToTrueFalse( bool aBoolean );
string int2String(const int& number);
string int2HexString(const unsigned int& aInt);
string byte2HexString(const unsigned char& aByte);
string doubleToString( double aDouble, int aintWidth );
string dumpIntArrayToString( int aiIntegerArray[], int aiNumberOfElementsToDump, bool abHex );
string dumpByteArrayToString( unsigned char* aucByteArray, int aiNumberOfElementsToDump, bool abHex );
int getCentaurRandomInteger( int aiQualityFactor  = 3 ); // default to highest quality
string readTextFileIntoString( string astrFileName );

