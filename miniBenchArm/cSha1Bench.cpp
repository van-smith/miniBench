#include "cSha1Bench.h"
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

cSha1Bench::cSha1Bench()
{
  cerr << "cSha1Bench constructor starts..." << endl;
  mSha1TestVectors[0].stringToHash = "a";
  mSha1TestVectors[0].sha1Hash = "86f7e437faa5a7fce15d1ddcb9eaeaea377667b8";
  mSha1TestVectors[1].stringToHash = "abc";
  mSha1TestVectors[1].sha1Hash = "a9993e364706816aba3e25717850c26c9cd0d89d";
  mSha1TestVectors[2].stringToHash = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  mSha1TestVectors[2].sha1Hash = "84983e441c3bd26ebaae4aa1f95129e5e54670f1";
  mSha1TestVectors[3].stringToHash = "";
  mSha1TestVectors[3].sha1Hash = "da39a3ee5e6b4b0d3255bfef95601890afd80709";
  mSha1TestVectors[4].stringToHash = "The quick brown fox jumps over the lazy dog";
  mSha1TestVectors[4].sha1Hash = "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12";
  mSha1TestVectors[5].stringToHash = "The quick brown fox jumps over the lazy cog";
  mSha1TestVectors[5].sha1Hash = "de9f2c7fd25e1b3afad3e85a0bd17d9b100db4b3";
  mSha1TestVectors[6].stringToHash = "50,000 a's";
  mSha1TestVectors[6].sha1Hash = "b722a56991bfa105233c135c84ea7aa4ea8d1c49";
  mSha1TestVectors[7].stringToHash = "One-million a's";
  mSha1TestVectors[7].sha1Hash = "34aa973cd4c4daa4f61eeb2bdbad27316534016f";
  mSha1TestVectors[8].stringToHash = "Ten-million a's";
  mSha1TestVectors[8].sha1Hash = "b43859b53b0f90da01951b6ab59cc964f3a8671a";

  mSha1TestVectors[INDEX_50_THOUSAND_A].stringToHash = "";
  for( int i = 1; i <= 50000; i++)
  {
    mSha1TestVectors[INDEX_50_THOUSAND_A].stringToHash += 'a';
  } // for

  mSha1TestVectors[INDEX_1_MILLION_A].stringToHash = "";
  for( int i = 1; i <= 20; i++ )
  {
    mSha1TestVectors[INDEX_1_MILLION_A].stringToHash += 
      mSha1TestVectors[INDEX_50_THOUSAND_A].stringToHash;
  } // for

  mSha1TestVectors[INDEX_10_MILLION_A].stringToHash = "";
  for( int i = 1; i <= 10; i++ )
  {
    mSha1TestVectors[INDEX_10_MILLION_A].stringToHash += 
      mSha1TestVectors[INDEX_1_MILLION_A].stringToHash;
  } // for

  mintRepeatCount = 1;

  cerr << "cSha1Bench constructor called." << endl;
} // cSha1Bench::cSha1Bench()


cSha1Bench::~cSha1Bench()
{
  cerr << "cSha1Bench destructor called." << endl;
} // cSha1Bench::~cSha1Bench()

string cSha1Bench::runPadlockChecks()
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
} // string cSha1Bench::runPadlockChecks()

bool cSha1Bench::runSha1ValidationTests( bool aboolShowStatus )
{
  string lstrOutput;
  if( aboolShowStatus ) cerr << endl << "SHA-1 Validation Tests:" << endl << endl;
  for( int i = 0; i <= 8; i++ )
  {
    if( aboolShowStatus ) cerr << "== Test " << i + 1 << " starts ==" << endl;
    if( i < 6 )
    {
      mSha1.hashThisString( mSha1TestVectors[i].stringToHash );
      if( aboolShowStatus ) cerr << "Test string: " << mSha1TestVectors[i].stringToHash << endl;
    } else if( i == 6 )
    {
      if( aboolShowStatus ) cerr << "Test string is 50,000 'a's." << endl;
      mSha1.hashThisString( mSha1TestVectors[INDEX_50_THOUSAND_A].stringToHash );
    } else if( i == 7 )
    {
      if( aboolShowStatus ) cerr << "Test string is 1,000,000 'a's." << endl;
      mSha1.hashThisString( mSha1TestVectors[INDEX_1_MILLION_A].stringToHash );
    } else if( i == 8 )
    {
      if( aboolShowStatus ) cerr << "Test string is 10,000,000 'a's." << endl;
      mSha1.hashThisString( mSha1TestVectors[INDEX_10_MILLION_A].stringToHash );
    } else
    {
      if( aboolShowStatus ) cerr << "cSha1Bench::RunSha1ValidationTests(): i is too big: " << i << endl; 
    } // else
    lstrOutput = mSha1.getSha1ResultAsHex();
    if( aboolShowStatus ) cerr << "Expected hash: 0x" << mSha1TestVectors[i].sha1Hash << endl;
    if( aboolShowStatus ) cerr << "Computed hash: 0x" << lstrOutput << endl;
    if( lstrOutput != mSha1TestVectors[i].sha1Hash )
    {
      if( aboolShowStatus ) cerr << "== Test " << i + 1 << " failed! ==" << endl;
      if( aboolShowStatus ) cerr << "Computed value: " << lstrOutput << ", expected value: " << mSha1TestVectors[i].sha1Hash << endl;
      throw( "cSha1Bench::RunSha1ValidationTests failed." );
    } // if
    if( aboolShowStatus ) cerr << "== Test " << i + 1 << " passed! ==" << endl;
  } // for
  if( aboolShowStatus ) cerr << endl;
  return true;
} // string cSha1Bench::runSha1ValidationTests()

double cSha1Bench::runBenchmarkHashSmallStrings( int aiIterations )
{
  string lstrOutput;
  clock_t endTime;
  clock_t startTime = clock();
  for( int i = 0; i < 6; i++ )
  {
    for( int j = 1; j<= aiIterations; j++ )
    {
      mSha1.hashThisString( mSha1TestVectors[i].stringToHash );
    } // for
    lstrOutput = mSha1.getSha1ResultAsHex();
    if( lstrOutput != mSha1TestVectors[i].sha1Hash )
    {
      cerr << "Computed hash failed to equal expected hash for test " << i << endl;
      return( 1 );
    } // if
  } // for
  endTime = clock();
  return (endTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
} // double cSha1Bench::runBenchmarkHashSmallStrings( int aiIterations )

double cSha1Bench::runBenchmarkHashString( string &aStringToHash, 
                                           int aiIterations, 
                                           string astrExpectedHexHash )
{
  clock_t endTime;
  clock_t startTime = clock();
  string lstrHexHashResult;
  for( int j = 1; j<= aiIterations; j++ )
  {
    mSha1.hashThisString( aStringToHash );
  } // for
  lstrHexHashResult = mSha1.getSha1ResultAsHex();
  if( lstrHexHashResult != astrExpectedHexHash )
  {
    cerr << "cSha1Bench::runBenchmarkHashString: Computed hash failed to equal expected hash." << endl;
    cerr << "Expected hash: " << astrExpectedHexHash << endl;
    cerr << "Computed hash: " << lstrHexHashResult << endl;
    return( 1 );
  } // if
  endTime = clock();
  return (endTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
} //double cSha1Bench::runBenchmarkHashString( string &aStringToHash, int aiIterations )

double cSha1Bench::runBenchmark( bool aboolShowStatus )
{
  string lstrOutput;
  clock_t endTime;
  clock_t startTime;

  if( mintRepeatCount > 1 ) cerr << "Repeating tests " << mintRepeatCount << " times." << endl;
  startTime = clock();
  for( int i = 1; i <= mintRepeatCount; i++ )
  {
    // hash the six small test vectors:
    mdSmallStringTime =  runBenchmarkHashSmallStrings( 1000000 );
    if( aboolShowStatus )
    {
      cerr << "Time to hash 6 small strings 1,000,000 times: " << mdSmallStringTime << " ms" << endl;
      cerr << "Score: \t" << getScoreForSmallStrings() << endl;
    }
    // time to hash 50,000 "a"s:

    md50kStringTime = runBenchmarkHashString( mSha1TestVectors[INDEX_50_THOUSAND_A].stringToHash, 
      10000, mSha1TestVectors[INDEX_50_THOUSAND_A].sha1Hash );
    if( aboolShowStatus )
    {
      cerr << "Time to hash 50,000 'a's 10,000 times: " << md50kStringTime << " ms" << endl;
      cerr << "Score: \t" << getScoreFor50kString() << endl;
    }

    // time to hash 1,000,000 "a"s 500 times:
    md1MStringTime = runBenchmarkHashString( mSha1TestVectors[INDEX_1_MILLION_A].stringToHash, 
      500, mSha1TestVectors[INDEX_1_MILLION_A].sha1Hash );
    if( aboolShowStatus )
    {
      cerr << "Time to hash 1,000,000 'a's 500 times: " << md1MStringTime << " ms" << endl;
      cerr << "Score: \t" << getScoreFor1MString() << endl;
    }

    // time to hash 10,000,000 "a"s:
    md10MStringTime = runBenchmarkHashString( mSha1TestVectors[INDEX_10_MILLION_A].stringToHash, 
      50, mSha1TestVectors[INDEX_10_MILLION_A].sha1Hash );
    if( aboolShowStatus )
    {
      cerr << "Time to hash 10,000,000 'a's 50 times: " << md10MStringTime << " ms" << endl;
      cerr << "Score: \t" << getScoreFor10MString() << endl;
    }

  } // for
  // total time:
  endTime = clock();
  mdOverallTime = (endTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  if( aboolShowStatus )
  {
    cerr << "Total time: " << mdOverallTime << " ms" << endl;
    cerr << "Overall score: \t" << getScoreOverall() << endl;
  }
  return mdOverallTime;
} // string cSha1Bench::runBenchmark()

double cSha1Bench::runFileHashBenchmark()
{
  string lStringToHash = readTextFileIntoString( mstrNameOfFileToHash );
  clock_t endTime;
  clock_t startTime = clock();
  for( int i = 1; i <= mintRepeatCount; i++ )
  {
    mSha1.hashThisString( lStringToHash );
  } // for
  endTime = clock();
  double elapsedTime = (endTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  sha1ResultAsHex = mSha1.getSha1ResultAsHex();
  return elapsedTime;
} // double RunFileHashBenchmark( string astrFileName )

void cSha1Bench::forceSoftwareCodePath()
{
   mSha1.mboolCentaurPadlockHashEngineAvailable = false;
} // void cSha1Bench::forceSoftwareCodePath()

void cSha1Bench::forcePadlockCodePath()
{
   mSha1.mboolCentaurPadlockHashEngineAvailable = true;
} // void cSha1Bench::forcePadlockCodePath()

// cSha1Bench::processCommandLine(int argc, char **argv) returns true for normal
// benchmark, false for file benchmark
bool cSha1Bench::processCommandLine(int argc, char **argv)
{
   int i;
   char *c;
   bool lbResult = true;
   for (i = 1; i < argc; i++)
   {
      c = argv[i];
      if (!strcmp(c,"-soft"))
      {
         forceSoftwareCodePath();
      }
      else if (!strcmp(c,"-phe"))
      {
         forcePadlockCodePath();
      }
      else if (!strcmp(c,"-file"))
      {
         mstrNameOfFileToHash = argv[++i];
         lbResult = false;
      }
      else if (!strcmp(c,"-rep"))
      {
         mintRepeatCount = atoi(argv[++i]);
      }
      else //if (!strcmp(c,"-?"))
      {
         cerr << "-soft   : Force software code path." << endl
              << "-phe    : Force VIA Padlock Hash Engine SHA-1 hardware code path." << endl
              << "          WARNING: -phe will crash on systems without Padlock support." << endl
              << "-rep n  : Set repeat count to n." << endl
              << "-file s : Time how long it takes to hash the text file s" << endl
              << "-?      : Display this help message." << endl;
         exit(0);
      }
   }
   return lbResult;
}

double cSha1Bench::getScoreForSmallStrings()
{
  return 1000 * ( 4500 / mdSmallStringTime );
}

double cSha1Bench::getScoreFor50kString()
{
  return 1000 * ( 4400 / md50kStringTime );
}

double cSha1Bench::getScoreFor1MString()
{
  return 1000 * ( 4400 / md1MStringTime );
}

double cSha1Bench::getScoreFor10MString()
{
  return 1000 * ( 4400 / md10MStringTime );
}

double cSha1Bench::getScoreOverall()
{
  return 1000 * ( 18070 / mdOverallTime );
}
