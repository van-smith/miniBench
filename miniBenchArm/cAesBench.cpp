#include "cAesBench.h"
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
*/

cAesBench::cAesBench()
{
  BLOCKS_TO_KB = 1 / (double) KB_TO_BLOCKS;
  BPS_TO_GBPS = 1 / (double)ONE_BILLION;
  miRepeatCount = 0;
  // flag to indicate presence of VIA Padlock AES hardware engine:
  mboolRunPadlockChecks = false;
  mstrFileName = "";
  setBufferSizeInKB( 0 );
  // default loop counter to 1 iterations if no value passed in commandline:
  miRepeatCount = 1;
  mstrVersion = "1.0";
};

cAesBench::~cAesBench()
{
  cerr << "destructor called" << endl;
};

void cAesBench::setKeyToDefault()
{
  int lintAesKey[] =  { 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c };
  mAes.setKey( lintAesKey );
} // void cAesBench::setKeyToDefault()

// process_command_line(int argc, char **argv): parse commandline arguments.
// Returns TRUE if the HasAce flag is overridden by user.
bool cAesBench::processCommandLine(int argc, char **argv)
{
  int i;
  char *c;
  bool lbResult = false;
  for (i = 1; i < argc; i++)
  {
    c = argv[i];
    if (!strcmp(c,"-soft"))
    {
      mAes.mboolCentaurPadlockAesAvailable = false;
      lbResult = true;
    }
    else if (!strcmp(c,"-ace"))
    {
      mAes.mboolCentaurPadlockAesAvailable = true;
      lbResult = true;
    }
    else if (!strcmp(c,"-check"))
    {
      mboolRunPadlockChecks = true;
    }
    else if (!strcmp(c,"-file"))
    {
      mstrFileName = argv[++i];
      // set iterations to reasonable value:
      if( getIterations() == 1) setIterations( 100 );
    }
    else if (!strcmp(c,"-rep"))
    {
      setIterations( atoi(argv[++i]) );
    }
    else if (!strcmp(c,"-ver"))
    {
      cerr << "cAesBench version: " << getVersion() << endl
           << "Copyright 2007, Van Smith" << endl
           << "Comprehensive OpenSource Benchmarking Initiative (COSBI)" << endl
           << "https://sourceforge.net/projects/opensourcemark/" << endl
           << "This program and its code is distributed under the" << endl
           << "GNU General Public License Version 2." << endl
           << "Scores are normalized against a 3.4GHz Intel Core 2 Duo E6600 with a single thread." << endl;
      exit( 0 );
    }
    else if (!strcmp(c,"-kb"))
    {
      setBufferSizeInKB( atoi(argv[++i]) );
      // set iterations to a reasonable number:
      if( getIterations() == 1)
      {
        int liGetBufferSizeInKB = getBufferSizeInKB();
        if( liGetBufferSizeInKB <= 100000 )
        {
          setIterations( 5 * ( 100000 / getBufferSizeInKB() ) );
        } else
        {
          setIterations( 1 );
        } // if.. else
      } //if
    } // else.. if
    else //if (!strcmp(c,"-?"))
    {
       cerr << "-soft   : Force software (Dr. Gladman) code path." << endl
            << "-ace    : Force VIA Padlock AES hardware code path." << endl
            << "          WARNING: -ace will crash on systems without Padlock support." << endl
            << "-rep n  : Set iteration count to n." << endl
            << "-kb n   : Set buffer size to n kilobytes." << endl
            << "-check  : Run Padlock checks." << endl
            << "-file s : Time encryption of text file s" << endl
            << "-ver    : Display program version." << endl
            << "-?      : Display this help message." << endl;
       exit(0);
    } // if..else
  }
  // Don't let buffer get bigger than 256MB (arbitrary limit)
  if ( getBufferSizeInKB() > 256000 )
  {
   cerr << "Setting buffersize to max size (256MB)." << endl;
   setBufferSizeInKB ( 256000 );
  } // if
  return lbResult;
}

void cAesBench::setBufferSizeInKB( int aiBufferSizeInKB )
{
  // convert kB to number of 128-bit (16-byte) blocks
  bufferSizeIn16ByteBlocks = KB_TO_BLOCKS * aiBufferSizeInKB;
} // void cAesBench::setBufferSizeInKB( int aiBufferSizeInKB )

void cAesBench::setIterations( int aiIterations )
{
  miRepeatCount = aiIterations;
} // void cAesBench::setIterations( int aiIterations )

int cAesBench::getIterations()
{
  return miRepeatCount;
} // int cAesBench::getIterations()

int cAesBench::getBufferSizeInKB()
{
   return (int)(bufferSizeIn16ByteBlocks * BLOCKS_TO_KB);
}

// runEncryptionTest(): this is the timed encryption test that uses whatever buffer size and
// buffer contents that have already been set.  All the encryption benchmarks call this routine.
void cAesBench::runEncryptionTest()
{
  clock_t start;
  unsigned int j;
  // Do the test once to fill the cache before starting the clock:
  mAes.ecbEncrypt(); // prime cache
  // start timed encryption test:
  start = clock();
  for (j=0; j < miRepeatCount; j++)
  {
    mAes.ecbEncrypt();;
  }
  mdEncryptTime = ((double) (clock() - start)) / ( (double)CLOCKS_PER_SEC);
  mdEncryptRateGbPerSec = ( (double)j * (bufferSizeIn16ByteBlocks * BLOCKS_TO_BITS) / mdEncryptTime ) * BPS_TO_GBPS;
} // void cAesBench::runEncryptionTest()

// runDecryptionTest(): this is the timed decryption test uses whatever buffer size and
// buffer contents that have already been set.  All the decryption benchmarks call this routine.
void cAesBench::runDecryptionTest()
{
  clock_t start;
  unsigned int j;
  mAes.ecbDecrypt(); // prime cache
  // start timed decryption test:
  start = clock();
  for (j=0; j < miRepeatCount; j++)
  {
    mAes.ecbDecrypt();
  }
  mdDecryptTime = ((double) (clock() - start)) / ( (double)CLOCKS_PER_SEC);
  mdDecryptRateGbPerSec =( (double)j * (bufferSizeIn16ByteBlocks * BLOCKS_TO_BITS) / mdDecryptTime )* BPS_TO_GBPS;
} // void cAesBench::runEncryptionTest()

// intialize_buffer(): fills the buffer to be encrypted with sequential integers
void cAesBench::initializeBuffer()
{
  int* lpiBufferElement;
  size_t lBufferSize = 16 * bufferSizeIn16ByteBlocks;
  // create buffer:
  mAes.createEmptyAlignedBuffer( lBufferSize );
  // fill the array with 4-byte integers:
  for( size_t i = 0; i < lBufferSize; i += 4 )
  {
    lpiBufferElement = ( int *)&mAes.mpucBuffer[ i ];
    *(lpiBufferElement) = i / 4;
  } // for
  mAes.padBuffer();
}

string cAesBench::dumpBufferToString(int aiNumberToOutput, bool abHex)
{
  return dumpIntArrayToString( (int *)mAes.mpucBuffer, aiNumberToOutput, abHex);
}

// output_buffer(int numberToOutput): will output the first numberToOutput members of buffer
string cAesBench::outputBuffer(int aiNumberOfIntToOutput)
{
  ostringstream ossResult;
  int liBufferSizeIn4ByteIntegers = bufferSizeIn16ByteBlocks * BLOCKS_TO_INT;
  if( aiNumberOfIntToOutput > liBufferSizeIn4ByteIntegers )
    aiNumberOfIntToOutput = liBufferSizeIn4ByteIntegers;
  ossResult << dumpBufferToString(aiNumberOfIntToOutput, false);
  ossResult << endl;
  return ossResult.str();
}

bool cAesBench::CentaurPadlockAesAvailable()
{
  return mAes.mboolCentaurPadlockAesAvailable;
} // bool cAesBench::CentaurPadlockAesAvailable()

string cAesBench::runPadlockChecks()
{
  ostringstream ossResult;
  if( isCentaurPadlockRandomNumberGeneratorAvailable() )
  {
    centaurPadlockRandomNumberGeneratorAvailable = true;
    ossResult << "Centaur Random Number Generator was detected and is available." << endl;
    ossResult << endl << "Here are ten random integers:" << endl;
    for(int n = 1; n <= 10; n++)
    {
      ossResult << "Random integer " << n << ": " << getCentaurRandomInteger() << endl;
    }
    cerr << endl;
  } else
  {
    centaurPadlockRandomNumberGeneratorAvailable = false;
    ossResult << "Centaur Random Number Generator is NOT available." << endl;
  }
  if( isCentaurPadlockAesAvailable() )
  {
    centaurPadlockAesAvailable = true;
    ossResult << "Centaur Padlock AES Engine was detected and is available." << endl;
  } else
  {
    centaurPadlockAesAvailable = false;
    ossResult << "Centaur Padlock AES Engine is NOT available." << endl;
  }
  if( isCentaurPadlockAes2Available() )
  {
    centaurPadlockAes2Available = true;
    ossResult << "Centaur Padlock AES Engine 2 was detected and is available." << endl;
  } else
  {
    centaurPadlockAes2Available = false;
    ossResult << "Centaur Padlock AES Engine 2 is NOT available." << endl;
  }
  if( isCentaurPadlockHashEngineAvailable() )
  {
    centaurPadlockHashEngineAvailable = true;
    ossResult << "Centaur Padlock Hash Engine was detected and is available." << endl;
  } else
  {
    centaurPadlockHashEngineAvailable = false;
    ossResult << "Centaur Padlock Hash Engine is NOT available." << endl;
  }
  if( isCentaurPadlockMontgomeryMultiplierAvailable() )
  {
    centaurPadlockMontgomeryMultiplierAvailable = true;
    ossResult << "Centaur Padlock Montgomery Multiplier was detected and is available." << endl;
  } else
  {
    centaurPadlockMontgomeryMultiplierAvailable = false;
    ossResult << "Centaur Padlock Montgomery Multiplier is NOT available." << endl;
  }
  return ossResult.str();
} // string cAesBench::runPadlockChecks()

double cAesBench::runEncryptTextFileBenchmark( string &asFileName, string asKey )
{
  size_t i;
  string lStringToEncrypt = readTextFileIntoString( asFileName );
  mAes.setKeyFromString( asKey );
  mAes.createAlignedBufferFromString( lStringToEncrypt );
  clock_t endTime;
  clock_t startTime = clock();
  for( i = 1; i <= miRepeatCount; i++ )
  {
    mAes.ecbEncrypt();
  } // for
  endTime = clock();
  mdEncryptTime = ((double) (endTime - startTime)) / ( (double)CLOCKS_PER_SEC);
  mdEncryptRateGbPerSec = ( (double)i * (mAes.miBufferLength * 8) / mdEncryptTime ) * BPS_TO_GBPS;
  cerr << "\"" << asFileName << "\" is " << mAes.miBufferLength << " bytes long." << endl;
  mAes.getResultAsString( asFileName );
  return mdEncryptTime;
} // double RunFileHashBenchmark( string astrFileName )

void cAesBench::runEncryptBenchmark( bool aboolShowStatus )
{
  if( aboolShowStatus )
  {
    cerr << "Here are the first 100 elements in the buffer before encryption: " << endl;
    cerr << outputBuffer( 100 );
    cerr << endl;
    cerr << "Encrypting " << getBufferSizeInKB()  << " kB block " << getIterations() << " times." << endl;
  }
  runEncryptionTest();
  if( aboolShowStatus )
  {
    cerr << endl;
    cerr << "Here are the first 100 elements in the buffer after encryption: " << endl;
    cerr << outputBuffer( 100 );
    cerr << endl;
    cerr << "Encryption completed in " << mdEncryptTime << " seconds with "
         << mdEncryptRateGbPerSec << " Gb/s encryption bandwidth." << endl;
    cerr << endl;
  }
} // void cAesBench::runEncryptBenchmark( str &asResult )

double cAesBench::runEncryptBenchmark8KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 8 )
  {
    setBufferSizeInKB( 8 );
    setIterations( 50000 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark8KB( string &asResult )

double cAesBench::runEncryptBenchmark16KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 16 )
  {
    setBufferSizeInKB( 16 );
    setIterations( 25000 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark16KB( string &asResult )

double cAesBench::runEncryptBenchmark32KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 32 )
  {
    setBufferSizeInKB( 32 );
    setIterations( 12500 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark32KB( string &asResult )

double cAesBench::runEncryptBenchmark64KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 64 )
  {
    setBufferSizeInKB( 64 );
    setIterations( 6250 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark64KB( string &asResult )

double cAesBench::runEncryptBenchmark128KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 128 )
  {
    setBufferSizeInKB( 128 );
    setIterations( 3125 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark128KB( string &asResult )

double cAesBench::runEncryptBenchmark256KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 256 )
  {
    setBufferSizeInKB( 256 );
    setIterations( 1500 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark256KB( string &asResult )

double cAesBench::runEncryptBenchmark512KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 512 )
  {
    setBufferSizeInKB( 512 );
    setIterations( 750 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark512KB( string &asResult )

double cAesBench::runEncryptBenchmark1024KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 1024 )
  {
    setBufferSizeInKB( 1024 );
    setIterations( 360 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark1024KB( string &asResult )

double cAesBench::runEncryptBenchmark2048KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 2048 )
  {
    setBufferSizeInKB( 2048 );
    setIterations( 180 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark2048KB( string &asResult )

double cAesBench::runEncryptBenchmark4096KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 4096 )
  {
    setBufferSizeInKB( 4096 );
    setIterations( 90 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.831 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark4096KB( string &asResult )

double cAesBench::runEncryptBenchmark8192KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 8192 )
  {
    setBufferSizeInKB( 8192 );
    setIterations( 45 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.831 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark8192KB( string &asResult )

double cAesBench::runEncryptBenchmark16384KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 16384 )
  {
    setBufferSizeInKB( 16384 );
    setIterations( 20 );
    initializeBuffer();
  }
  runEncryptBenchmark( aboolShowStatus );
  mdEncryptScore = ( mdEncryptRateGbPerSec / 0.831 ) * 1000;
  return ( mdEncryptScore );
} // double cAesBench::runEncryptBenchmark8KB( string &asResult )

void cAesBench::runDecryptBenchmark( bool aboolShowStatus )
{
  if( aboolShowStatus )
  {
    cerr << "Decrypting " << getBufferSizeInKB() << "kB block "
         << getIterations() << " times." << endl;
  }
  runDecryptionTest();
  if( aboolShowStatus )
  {
    cerr << endl;
    cerr << "Here are the first 100 elements in the buffer after decryption: " << endl;
    cerr << outputBuffer( 100 );
    cerr << endl;
    cerr << "Decryption completed in " << mdDecryptTime << " seconds with "
         << mdEncryptRateGbPerSec << " Gb/s decryption bandwidth." << endl;
    cerr << endl;
  }
} // void cAesBench::runDecryptBenchmark( str &asResult )

double cAesBench::runDecryptBenchmark8KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 8 )
  {
    setBufferSizeInKB( 8 );
    setIterations( 50000 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark8KB( string &asResult )

double cAesBench::runDecryptBenchmark16KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 16 )
  {
    setBufferSizeInKB( 16 );
    setIterations( 25000 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark16KB( string &asResult )

double cAesBench::runDecryptBenchmark32KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 32 )
  {
    setBufferSizeInKB( 32 );
    setIterations( 12500 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark32KB( string &asResult )

double cAesBench::runDecryptBenchmark64KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 64 )
  {
    setBufferSizeInKB( 64 );
    setIterations( 6250 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark64KB( string &asResult )

double cAesBench::runDecryptBenchmark128KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 128 )
  {
    setBufferSizeInKB( 128 );
    setIterations( 3125 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark128KB( string &asResult )

double cAesBench::runDecryptBenchmark256KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 256 )
  {
    setBufferSizeInKB( 256 );
    setIterations( 1500 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark256KB( string &asResult )

double cAesBench::runDecryptBenchmark512KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 512 )
  {
    setBufferSizeInKB( 512 );
    setIterations( 750 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark512KB( string &asResult )

double cAesBench::runDecryptBenchmark1024KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 1024 )
  {
    setBufferSizeInKB( 1024 );
    setIterations( 360 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark1024KB( string &asResult )

double cAesBench::runDecryptBenchmark2048KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 2048 )
  {
    setBufferSizeInKB( 2048 );
    setIterations( 180 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.837 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark2048KB( string &asResult )

double cAesBench::runDecryptBenchmark4096KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 4096 )
  {
    setBufferSizeInKB( 4096 );
    setIterations( 90 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.831 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark4096KB( string &asResult )

double cAesBench::runDecryptBenchmark8192KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 8192 )
  {
    setBufferSizeInKB( 8192 );
    setIterations( 45 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.831 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark8192KB( string &asResult )

double cAesBench::runDecryptBenchmark16384KB( bool aboolShowStatus )
{
  if( getBufferSizeInKB() != 16384 )
  {
    setBufferSizeInKB( 16384 );
    setIterations( 20 );
    initializeBuffer();
  }
  runDecryptBenchmark( aboolShowStatus );
  mdDecryptScore = ( mdDecryptRateGbPerSec / 0.831 ) * 1000;
  return ( mdDecryptScore );
} // double cAesBench::runDecryptBenchmark16384KB( string &asResult )

double cAesBench::getEncryptScore()
{
  return mdEncryptScore;
}

double cAesBench::getEncryptTime()
{
  return mdEncryptTime;
}

double cAesBench::getEncryptRateGbPerSec()
{
  return mdEncryptRateGbPerSec;
}

double cAesBench::getDecryptScore()
{
  return mdDecryptScore;
}

double cAesBench::getDecryptTime()
{
  return mdDecryptTime;
}

double cAesBench::getDecryptRateGbPerSec()
{
  return mdDecryptRateGbPerSec;
}

string cAesBench::getVersion()
{
  return mstrVersion;
}
