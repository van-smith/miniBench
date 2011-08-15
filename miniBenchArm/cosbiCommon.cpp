#include "cosbiCommon.h"
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

#define XSTORE(SIZE, DIVIDER, DATA, X, Y, Z ) \
    asm __volatile__ (".byte 0xF3, 0x0F, 0xA7, 0xC0\n" \
    : "=c" (X), "=a" (Y), "=D" (Z) \
    : "c" (SIZE), "d" (DIVIDER), "D" (DATA));

int getCentaurRandomInteger( int aiQualityFactor )
{
  throw("getCentaurRandomInteger: Not available on ARM CPUs");
  int liResult[2] = {1, 2};
/*
#ifdef vs2005
  __asm lea edi, liResult // move address of result variable into edi
  __asm mov edx, aiQualityFactor  // random bit rate (accumulate every 2^n bits)
  __asm mov ecx, 4  // number of bytes that we need
  REPXSTORE
#else
  asm __volatile__
  (
    "movl $4, %%ecx;" // number of bytes that we need
    REPXSTORE
    : // no output
    :"d" (aiQualityFactor), "D" (liResult)
    :"memory", "cc"// clobber list
  ); //asm
#endif
*/
  return liResult[0];
}// int GetRandomCentaurInteger( int aiQualityFactor );

string booleanToYesNo( bool aBoolean )
{
   if ( aBoolean )
   {
      return "Yes";
   }
   else
   {
      return "No";
   }
} // string BooleanToYesNo( bool aBoolean )

string booleanToTrueFalse( bool aBoolean )
{
   if ( aBoolean )
   {
      return "True";
   }
   else
   {
      return "False";
   }
} // string BooleanToTrueFalse( bool aBoolean );

string int2String(const int& number)
{
   ostringstream oss;
   oss << number;
   return oss.str();
} // string int2string(const int& number)

string byte2HexString(const unsigned char& aByte)
{
   ostringstream oss;
   oss << hex << setfill('0') << setw(2) << (int)aByte;
   return oss.str();
} // string byte2HexString(const unsigned char& aByte)

string int2HexString(const unsigned int& aInt)
{
   ostringstream oss;
   oss << hex << setfill('0') << setw(8) << aInt;
   return oss.str();
} // string int2HexString(const unsigned int& aInt)

string doubleToString( double aDouble, int aintWidth )
{
   ostringstream oss;
   oss << setw( aintWidth ) << aDouble;
   return oss.str();
} // string doubleToString( double aDouble, int aintWidth )

string dumpIntArrayToString( int* aiIntegerArray, int aiNumberOfElementsToDump, bool abHex )
{
   string lsResult;
   string lsTemp;
   stringstream lssTemp;
   if( abHex )
   {
      for( int i = 0; i <= aiNumberOfElementsToDump - 2; i++ )
      {
         lssTemp << hex << aiIntegerArray[ i ] << ", ";
         lssTemp >> lsTemp;
         lsResult = lsResult + lsTemp + " ";
      }
      lssTemp << hex << aiIntegerArray[ aiNumberOfElementsToDump - 1 ];
      lssTemp >> lsTemp;
      lsResult = lsResult + lsTemp;
   }
   else
   {
      for( int i = 0; i <= aiNumberOfElementsToDump - 2; i++ )
      {
         lssTemp << aiIntegerArray[ i ] << ", ";
         lssTemp >> lsTemp;
         lsResult = lsResult + lsTemp + " ";
      }
      lssTemp << aiIntegerArray[ aiNumberOfElementsToDump - 1 ];
      lssTemp >> lsTemp;
      lsResult = lsResult + lsTemp;
   }
   return lsResult;
}

string dumpByteArrayToString( unsigned char* aucByteArray, int aiNumberOfElementsToDump, bool abHex )
{
   string lsResult;
   string lsTemp;
   stringstream lssTemp;
   if( abHex )
   {
      for( int i = 0; i <= aiNumberOfElementsToDump - 2; i++ )
      {
         lssTemp << hex << aucByteArray[ i ] << ", ";
         lssTemp >> lsTemp;
         lsResult = lsResult + lsTemp + " ";
      }
      lssTemp << hex << aucByteArray[ aiNumberOfElementsToDump - 1 ];
      lssTemp >> lsTemp;
      lsResult = lsResult + lsTemp;
   }
   else
   {
      for( int i = 0; i <= aiNumberOfElementsToDump - 2; i++ )
      {
         lssTemp << (int)aucByteArray[ i ] << ", ";
         lssTemp >> lsTemp;
         lsResult = lsResult + lsTemp + " ";
      }
      lssTemp << (int)aucByteArray[ aiNumberOfElementsToDump - 1 ];
      lssTemp >> lsTemp;
      lsResult = lsResult + lsTemp;
   }
   return lsResult;
}

string readTextFileIntoString( string astrFileName )
{
   ifstream inFile(astrFileName.c_str(), ifstream::in);
   string lstrResult, lstrReadLine;
   while(getline(inFile, lstrReadLine))
   {
      lstrResult += lstrReadLine + "\n";  // be sure to add back the "\n"
   }
   return lstrResult;
} // string readFileIntoString( string &astrFileName )

