#pragma once
#define windowsos

//  cAes encrypt/decrypt class with hardware support for VIA Padlock
//
//  This class incorporates the C language implementation of the AES algorithm from Brian Gladman.
//
//  http://fp.gladman.plus.com/cryptography_technology/rijndael/
//
//  Brian Gladman's code is distruted as follows:
//
// "I am happy for this code to be used without payment provided that I don't carry
//  any risks as a result.  I would appreciate an appropriate acknowledgement of the
//  source of the code if you do use it in a product or activity provided to third
//  parties. I would also be grateful for feedback on how the code is being used, any
//  problems you encounter, any changes or additions that are desirable for particular
//  processors and any more general improvements you would like to see (no promises mind!)."

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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
/*
#ifdef windowsos
  #include "..\common\cosbiDefine.h"
  #include ".\gladman\aes.h"
  #include "..\common\cosbiCpuid.h"
  #include "..\common\cosbiCommon.h"
#else
*/
  #include "cosbiDefine.h"
  #include "./gladman/aes.h"
  #include "cosbiCpuid.h"
  #include "cosbiCommon.h"
//#endif

using namespace std;

class cAes
{
private:
  // Key structures for Gladman's software AES implementation
  vs2005align16 aes_encrypt_ctx ECTX gccAlign16;
  vs2005align16 aes_decrypt_ctx DCTX gccAlign16;
  // VIA Padlock data structures:
  vs2005align16 int HwkyEncrypt128[4] gccAlign16;
  vs2005align16 int HwkyDecrypt128[4] gccAlign16;
  void setKeyToDefault();
  int miBufferLengthIn16BBlocks;
  bool boolBufferAllocated;
public:
  cAes(void);
  ~cAes(void);
  bool mboolCentaurPadlockAesAvailable;
  int softwareKey[ 4 ];
  vs2005align16 int ViaPadlockAesKey[8] gccAlign16;
  unsigned char* mpucBuffer gccAlign16;
  size_t miBufferLength;
  // main encryption and decryption methods:
  void initializeData();
  void ecbDecrypt();
  void ecbEncrypt();
  void ecbEncryptThisString( string &aStringToEncrypt, string asKey );
  void ecbDecryptThisString( string &aStringToEncrypt, string asKey );
  string ecbEncryptThisTextFile( string astrFileName, string astrKey );
  string ecbDecryptThisTextFile( string astrFileName, string astrKey );
  void forceSoftwareCodePath();
  void forcePadlockCodePath();
  // Padlock AES encrypt and decrypt functions:
  //void padlockEcbEncrypt();
  void padlockEcbEncrypt( int aHwkyEncrypt128[],
                          unsigned char* apucBuffer,
                          int aViaPadlockAesKey[],
                          int aBufferSizeIn16ByteBlocks);
  void padlockEcbDecrypt( int aHwkyDecrypt128[],
                          unsigned char* apucBuffer,
                          int aViaPadlockAesKey[],
                          int aBufferSizeIn16ByteBlocks);
  void detectPadlock();
  void setBufferSize( int aiBufferSize );
  void setBuffer( unsigned char aucBufferToEncrypt[], int aiBufferLength );
  void setKey( int aKey[] );
  void setKeyFromString( string aKey );
  void getResultAsString(string &astrResult);
  void returnResultAsString(string &astrResult, int aiBufferLength );
  bool runEncryptDecryptValidationTest( string &asResult );
  void createAlignedBufferFromString( string &aStringToEncrypt );
  void createEmptyAlignedBuffer( size_t aBufferSize );
  void createFilledAlignedBuffer( unsigned char* aucBuffer, size_t aBufferSize );
  void padBuffer();
};
