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

#include <iostream>
#include <iomanip>  // needed for setiosflags, etc.
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#ifdef windowsos
  #ifdef vs2005
    #include "..\..\common\cosbiDefine.h"
    #include "..\..\common\cosbiCommon.h"
    #include "..\..\crypto\cAes.h"
  #else
    #include "..\common\cosbiDefine.h"
    #include "..\common\cosbiCommon.h"
    #include "..\crypto\cAes.h"
  #endif
#else
  #include "cosbiDefine.h"
  #include "cosbiCommon.h"
  #include "cAes.h"
#endif

using namespace std;

class cAesBench
{
  private:
    // conversion constants:
    static const int KB_TO_BLOCKS = 64; // 1024B/kB / (16B / Block) = 64 Blocks / kB
    static const int BLOCKS_TO_INT = 4; // (1 int / 4B) / (1 block / 16B) = 4 ints/block
    double BLOCKS_TO_KB;
    static const int BLOCKS_TO_BITS = 16 * 8;
    static const int ONE_BILLION = 1000000000;
    double BPS_TO_GBPS;
  protected:
    // specified buffer size that is set via command line:
    int bufferSizeIn16ByteBlocks;
    unsigned int miRepeatCount;
    double mdEncryptScore;
    double mdEncryptTime;
    double mdEncryptRateGbPerSec;
    double mdDecryptScore;
    double mdDecryptTime;
    double mdDecryptRateGbPerSec;
    string mstrVersion;
  public:
    cAesBench();
    ~cAesBench();
    cAes mAes;
    // data
    bool mboolRunPadlockChecks;
    bool centaurPadlockRandomNumberGeneratorAvailable;
    bool centaurPadlockAesAvailable;
    bool centaurPadlockAes2Available;
    bool centaurPadlockHashEngineAvailable;
    bool centaurPadlockMontgomeryMultiplierAvailable;
    // miRepeatCount specifies the number of test iterations and is set via commandline:
    string mstrFileName;
    // === methods ===
    // process_command_line(int argc, char **argv): parse commandline arguments.
    // Returns TRUE if the Padlock flag is overridden by user.
    bool processCommandLine(int argc, char **argv);
    void initializeBuffer();
    string outputBuffer(int aiNumberOfIntToOutput);
    string dumpBufferToString(int aiNumberToOutput, bool abHex);
    bool CentaurPadlockAesAvailable();
    // Software module key : ciphertext : plaintext (NIST Appendix 3 p35-38)
    // Initial hardware key
    int getBufferSizeInKB();
    int getIterations();
    double getEncryptScore();
    double getEncryptTime();
    double getEncryptRateGbPerSec();
    double getDecryptScore();
    double getDecryptTime();
    double getDecryptRateGbPerSec();
    string getVersion();
    void setBufferSizeInKB( int aiBufferSizeInKB );
    void setIterations( int aiIterations );
    void setKey( int aKey[] );
    void setKeyToDefault();
    void runEncryptionTest();
    void runDecryptionTest();
    void runEncryptBenchmark( bool aboolShowStatus = true );
    // sets flags to indicate presence of VIA Padlock hardware engine features:
    string runPadlockChecks();
    double runEncryptBenchmark8KB( bool aboolShowStatus = true );
    double runEncryptBenchmark16KB( bool aboolShowStatus = true );
    double runEncryptBenchmark32KB( bool aboolShowStatus = true );
    double runEncryptBenchmark64KB( bool aboolShowStatus = true );
    double runEncryptBenchmark128KB( bool aboolShowStatus = true );
    double runEncryptBenchmark256KB( bool aboolShowStatus = true );
    double runEncryptBenchmark512KB( bool aboolShowStatus = true );
    double runEncryptBenchmark1024KB( bool aboolShowStatus = true );
    double runEncryptBenchmark2048KB( bool aboolShowStatus = true );
    double runEncryptBenchmark4096KB( bool aboolShowStatus = true );
    double runEncryptBenchmark8192KB( bool aboolShowStatus = true );
    double runEncryptBenchmark16384KB( bool aboolShowStatus = true );
    void runDecryptBenchmark( bool aboolShowStatus = true );
    double runDecryptBenchmark8KB( bool aboolShowStatus = true );
    double runDecryptBenchmark16KB( bool aboolShowStatus = true );
    double runDecryptBenchmark32KB( bool aboolShowStatus = true );
    double runDecryptBenchmark64KB( bool aboolShowStatus = true );
    double runDecryptBenchmark128KB( bool aboolShowStatus = true );
    double runDecryptBenchmark256KB( bool aboolShowStatus = true );
    double runDecryptBenchmark512KB( bool aboolShowStatus = true );
    double runDecryptBenchmark1024KB( bool aboolShowStatus = true );
    double runDecryptBenchmark2048KB( bool aboolShowStatus = true );
    double runDecryptBenchmark4096KB( bool aboolShowStatus = true );
    double runDecryptBenchmark8192KB( bool aboolShowStatus = true );
    double runDecryptBenchmark16384KB( bool aboolShowStatus = true );
    double runEncryptTextFileBenchmark( string &asFileName, string asKey );
};

