#pragma once
//#define windowsos

/*
  COSBI: Comprehensive Open Source Benchmarking Initiative
  Copyright (c) 2004 Van Smith

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

  cSha256 software code path is based on Christophe Devine's work found here:
  http://www.cr0.net:8040/code/crypto/
*/
#include <string>
#include <malloc.h>
#include <cstring> //memcpy

#ifdef windowsos
  #include "..\common\cosbiDefine.h"
  #include "..\common\cosbiCpuid.h"
  #include "..\common\cosbiCommon.h"
#else
  #include "cosbiDefine.h"
  #include "cosbiCpuid.h"
  #include "cosbiCommon.h"
#endif
using namespace std;

#ifndef unsigned8BitInt
  #define unsigned8BitInt  unsigned char
#endif

#ifndef unsigned32BitInt
  #define unsigned32BitInt unsigned long int
#endif

inline void centaurPadlockSha256(unsigned32BitInt aBufferSizeInBytes,
                          unsigned8BitInt aBuffer[],
                          unsigned8BitInt aSha256Result[])
{
   throw("centaurPadlockSha256: Not available on ARM CPU");
/*
   if( IsAddress16ByteAligned( (void *)aSha256Result) )  // if buffer is 16-byte aligned
   {
#ifdef vs2005
      __asm mov eax, 0
      __asm mov ecx, aBufferSizeInBytes
      __asm mov esi, aBuffer
      __asm mov edi, aSha256Result
      __asm _emit 0xF3 __asm _emit 0x0F __asm _emit 0xA6 __asm _emit 0xD0 //REP XSHA256
#else
      asm __volatile__
      (
         "movl $0, %%eax;"
         ".byte 0xF3; .byte 0x0F; .byte 0xA6; .byte 0xD0;" //REP XSHA256
         : // no output variables
         : "c" (aBufferSizeInBytes), [buffer] "S" (aBuffer), [result] "D" (aSha256Result)
         : "memory", "cc"// clobber list
      );
#endif
   }
   else
   {
      throw( "centaurPadlockSha256: You passed me a result buffer that is not 16-byte aligned." );
   }
*/
} // inline void centaurPadlockSha256

vs2005align16 typedef struct
{
   unsigned8BitInt buffer[64];
   unsigned32BitInt total[2];
   vs2005align16 unsigned32BitInt state[8] gccAlign16;
} sha256Context gccAlign16;

vs2005align16 class cSha256
{
   private:
      sha256Context mSha256Context;
      unsigned32BitInt mByteArrayLength;
      unsigned8BitInt *mUnsigned8BitArray;
      void sha256Finish();
      void sha256Process( unsigned8BitInt data[64] );
      void sha256Starts();
      void sha256Update( unsigned8BitInt aUnsigned8BitArray[],
                         unsigned32BitInt length );
      void padlockHashTheArray();
   protected:
      string stringToHash;
   public:
      cSha256();
      ~cSha256();
      bool mboolCentaurPadlockHashEngineAvailable;
      void hashThisString( string &aStringToHash );
      void hashThisTextFile( string astrFileName );
      string getSha256ResultAsHex();
      // The Centaur Padlock Hash Engine requires 128 byte (32 ints) versus 20 ints:
      vs2005align16 unsigned8BitInt sha256Result[128] gccAlign16;
      void detectPadlock();
      void forceSoftwareCodePath();
      void forcePadlockCodePath();
} gccAlign16; // class cSha256

