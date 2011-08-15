#pragma once
//#define windowsos
//#define vs2005
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
#include <cstring> //strcmp

#ifdef windowsos
  #ifdef vs2005
    #include "..\..\crypto\cSha256.h"
  #else
    #include "..\crypto\cSha256.h"
  #endif
#else
  #include "cSha256.h"
#endif


using namespace std;

/**
	@author Van Smith <van@vanshardware.com>
*/

typedef struct
{
   string stringToHash;
   string sha256Hash;
} sha256TestVectors;

class cSha256Bench{
// a few of the standard FIPS-180-1 test vectors plus others:
  private:
    sha256TestVectors mSha256TestVectors[9];
    static const int INDEX_50_THOUSAND_A = 6;
    static const int INDEX_1_MILLION_A = 7;
    static const int INDEX_10_MILLION_A = 8;
    cSha256 mSha256;
  protected:
    double mdSmallStringTime;
    double md50kStringTime;
    double md1MStringTime;
    double md10MStringTime;
    double mdOverallTime;
  public:
    cSha256Bench();
    ~cSha256Bench();
    int mintRepeatCount;
    string mstrNameOfFileToHash;
    bool centaurPadlockRandomNumberGeneratorAvailable;
    bool centaurPadlockAesAvailable;
    bool centaurPadlockAes2Available;
    bool centaurPadlockHashEngineAvailable;
    bool centaurPadlockMontgomeryMultiplierAvailable;
    void copySha256HashArray( unsigned8BitInt aSource[], unsigned8BitInt aDestination[] );
    bool processCommandLine(int argc, char **argv);
    string runPadlockChecks();
    bool runSha256ValidationTests( bool aboolShowStatus );
    string sha256ResultAsHex;
    double runBenchmark( bool aboolShowStatus );
    double runBenchmarkHashSmallStrings( int aiIterations );
    double runBenchmarkHashString( string &aStringToHash,
                                   int aiIterations,
                                   string strExpectedHexHash );
    double runFileHashBenchmark();
    void forceSoftwareCodePath();
    void forcePadlockCodePath();
    double getScoreForSmallStrings();
    double getScoreFor50kString();
    double getScoreFor1MString();
    double getScoreFor10MString();
    double getScoreOverall();
}; // class cSha256Bench
