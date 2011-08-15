#include "cSha256Bench.h"

cSha256Bench::cSha256Bench()
{
  mSha256TestVectors[0].stringToHash = "";
  mSha256TestVectors[0].sha256Hash = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
  mSha256TestVectors[1].stringToHash = "a";
  mSha256TestVectors[1].sha256Hash = "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb";
  mSha256TestVectors[1].stringToHash = "abc";
  mSha256TestVectors[1].sha256Hash = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
  mSha256TestVectors[2].stringToHash = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  mSha256TestVectors[2].sha256Hash = "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1";
  mSha256TestVectors[3].stringToHash = "Test vector from febooti.com";
  mSha256TestVectors[3].sha256Hash = "077b18fe29036ada4890bdec192186e10678597a67880290521df70df4bac9ab";
  mSha256TestVectors[4].stringToHash = "The quick brown fox jumps over the lazy dog";
  mSha256TestVectors[4].sha256Hash = "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592";
  mSha256TestVectors[5].stringToHash = "The quick brown fox jumps over the lazy cog";
  mSha256TestVectors[5].sha256Hash = "e4c4d8f3bf76b692de791a173e05321150f7a345b46484fe427f6acc7ecc81be";
  mSha256TestVectors[6].stringToHash = "50,000 a's";
  mSha256TestVectors[6].sha256Hash = "77a0f923b96d18567b52376c56638acc5f030009735888bc47f2da5b4b65e3af";
  mSha256TestVectors[7].stringToHash = "One-million a's";
  mSha256TestVectors[7].sha256Hash = "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0";
  mSha256TestVectors[8].stringToHash = "Ten-million a's";
  mSha256TestVectors[8].sha256Hash = "01f4a87c04b40af59aadc0e812293509709c9a8763a60b7f9e19303322f8b03c";

  mSha256TestVectors[INDEX_50_THOUSAND_A].stringToHash = "";
  for( int i = 1; i <= 50000; i++)
  {
    mSha256TestVectors[INDEX_50_THOUSAND_A].stringToHash += 'a';
  } // for

  mSha256TestVectors[INDEX_1_MILLION_A].stringToHash = "";
  for( int i = 1; i <= 20; i++ )
  {
    mSha256TestVectors[INDEX_1_MILLION_A].stringToHash +=
      mSha256TestVectors[INDEX_50_THOUSAND_A].stringToHash;
  } // for

  mSha256TestVectors[INDEX_10_MILLION_A].stringToHash = "";
  for( int i = 1; i <= 10; i++ )
  {
    mSha256TestVectors[INDEX_10_MILLION_A].stringToHash +=
      mSha256TestVectors[INDEX_1_MILLION_A].stringToHash;
  } // for

  mintRepeatCount = 1;

//  cerr << "cSha256Bench constructor called." << endl;
} // cSha256Bench::cSha256Bench()


cSha256Bench::~cSha256Bench()
{
//  cerr << "cSha256Bench destructor called." << endl;
} // cSha256Bench::~cSha256Bench()

void cSha256Bench::copySha256HashArray( unsigned8BitInt aSource[], unsigned8BitInt aDestination[] )
{
  for( int i = 0; i < 32; i ++ )
  {
    aDestination[ i ] = aSource[ i ];
  }
} // void copySha256HashArray( unsigned8BitInt aSource[], unsigned8BitInt aDestination[] )

string cSha256Bench::runPadlockChecks()
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
} // string cSha256Bench::runPadlockChecks()

bool cSha256Bench::runSha256ValidationTests( bool aboolShowStatus )
{
  if( aboolShowStatus ) cerr << endl << "SHA-256 Validation Tests:" << endl << endl;
  for( int i = 0; i <= 8; i++ )
  {
    if( aboolShowStatus ) cerr << "== Test " << i + 1 << " starts ==" << endl;
    if( i < 6 )
    {
      mSha256.hashThisString( mSha256TestVectors[i].stringToHash );
      if( aboolShowStatus ) cerr << "Test string: " << mSha256TestVectors[i].stringToHash << endl;
    } else if( i == 6 )
    {
      if( aboolShowStatus ) cerr << "Test string is 50,000 'a's." << endl;
      mSha256.hashThisString( mSha256TestVectors[INDEX_50_THOUSAND_A].stringToHash );
    } else if( i == 7 )
    {
      if( aboolShowStatus ) cerr << "Test string is 1,000,000 'a's." << endl;
      mSha256.hashThisString( mSha256TestVectors[INDEX_1_MILLION_A].stringToHash );
    } else if( i == 8 )
    {
      if( aboolShowStatus ) cerr << "Test string is 10,000,000 'a's." << endl;
      mSha256.hashThisString( mSha256TestVectors[INDEX_10_MILLION_A].stringToHash );
    } else
    {
      if( aboolShowStatus ) cerr << "cSha256Bench::RunSha256ValidationTests(): i is too big: " << i << endl;
    } // else
    string lstrOutput = mSha256.getSha256ResultAsHex();
    if( aboolShowStatus ) cerr << "Expected hash:" << endl << "0x" << mSha256TestVectors[i].sha256Hash << endl;
    if( aboolShowStatus ) cerr << "Computed hash:" << endl << "0x" << lstrOutput << endl;
    if( lstrOutput != mSha256TestVectors[i].sha256Hash )
    {
      if( aboolShowStatus ) cerr << "== Test " << i + 1 << " failed! ==" << endl;
      if( aboolShowStatus ) cerr << "Computed value: " << lstrOutput << ", expected value: " << mSha256TestVectors[i].sha256Hash << endl;
      throw( "cSha256Bench::RunSha256ValidationTests failed." );
    } // if
    if( aboolShowStatus ) cerr << "== Test " << i + 1 << " passed! ==" << endl;
  } // for
  if( aboolShowStatus ) cerr << endl;
  return true;
} // string cSha256Bench::runSha256ValidationTests()

double cSha256Bench::runBenchmarkHashSmallStrings( int aiIterations )
{
  string lstrOutput;
  clock_t endTime;
  clock_t startTime = clock();
  for( int i = 0; i < 6; i++ )
  {
    for( int j = 1; j<= aiIterations; j++ )
    {
      mSha256.hashThisString( mSha256TestVectors[i].stringToHash );
    } // for
    lstrOutput = mSha256.getSha256ResultAsHex();
    if( lstrOutput != mSha256TestVectors[i].sha256Hash )
    {
      cerr << "Computed hash failed to equal expected hash for test " << i << endl;
      return( 1 );
    } // if
  } // for
  endTime = clock();
  return (endTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
} // double cSha256Bench::runBenchmarkHashSmallStrings( int aiIterations )

double cSha256Bench::runBenchmarkHashString( string &aStringToHash,
                                           int aiIterations, 
                                           string astrExpectedHexHash )
{
  clock_t endTime;
  clock_t startTime = clock();
  string lstrHexHashResult;
  for( int j = 1; j<= aiIterations; j++ )
  {
    mSha256.hashThisString( aStringToHash );
  } // for
  lstrHexHashResult = mSha256.getSha256ResultAsHex();
  if( lstrHexHashResult != astrExpectedHexHash )
  {
    cerr << "cSha256Bench::runBenchmarkHashString: Computed hash failed to equal expected hash." << endl;
    cerr << "Expected hash: " << astrExpectedHexHash << endl;
    cerr << "Computed hash: " << lstrHexHashResult << endl;
    return( 1 );
  } // if
  endTime = clock();
  return (endTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
} //double cSha256Bench::runBenchmarkHashString( string &aStringToHash, int aiIterations )

double cSha256Bench::runBenchmark( bool aboolShowStatus )
{
  string lstrOutput;
  clock_t endTime;
  clock_t startTime;

  if( ( mintRepeatCount > 1 ) && aboolShowStatus )
    cerr << "Repeating tests " << mintRepeatCount << " times." << endl;
  startTime = clock();
  for( int i = 1; i <= mintRepeatCount; i++ )
  {
    // hash the six small test vectors:
    mdSmallStringTime =  runBenchmarkHashSmallStrings( 1000000 );
    if( aboolShowStatus )
    {
      cerr << "Time to hash 6 small strings 1,000,000 times: " << mdSmallStringTime << " ms" << endl;
      cerr << "Score: \t" << getScoreForSmallStrings() << endl;
    } // if

    // time to hash 50,000 "a"s:
    md50kStringTime = runBenchmarkHashString( mSha256TestVectors[INDEX_50_THOUSAND_A].stringToHash,
      10000, mSha256TestVectors[INDEX_50_THOUSAND_A].sha256Hash );
    if( aboolShowStatus )
    {
      cerr << "Time to hash 50,000 'a's 10,000 times: " << md50kStringTime << " ms" << endl;
      cerr << "Score: \t" << getScoreFor50kString() << endl;
    } // if

    // time to hash 1,000,000 "a"s 500 times:
    md1MStringTime = runBenchmarkHashString( mSha256TestVectors[INDEX_1_MILLION_A].stringToHash,
      500, mSha256TestVectors[INDEX_1_MILLION_A].sha256Hash );
    if( aboolShowStatus )
    {
      cerr << "Time to hash 1,000,000 'a's 500 times: " << md1MStringTime << " ms" << endl;
      cerr << "Score: \t" << getScoreFor1MString() << endl;
    } // if

    // time to hash 10,000,000 "a"s:
    md10MStringTime = runBenchmarkHashString( mSha256TestVectors[INDEX_10_MILLION_A].stringToHash,
      50, mSha256TestVectors[INDEX_10_MILLION_A].sha256Hash );
    if( aboolShowStatus )
    {
      cerr << "Time to hash 10,000,000 'a's 50 times: " << md10MStringTime << " ms" << endl;
      cerr << "Score: \t" << getScoreFor10MString() << endl;
    } // if

  } // for
  // total time:
  endTime = clock();
  mdOverallTime = (endTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  if( aboolShowStatus )
  {
    cerr << "Total time: " << mdOverallTime << " ms" << endl;
    cerr << "Overall score: \t" << getScoreOverall() << endl;
  } // if
  return mdOverallTime;
} // string cSha256Bench::runBenchmark()

double cSha256Bench::runFileHashBenchmark()
{
  string lStringToHash = readTextFileIntoString( mstrNameOfFileToHash );
  clock_t endTime;
  clock_t startTime = clock();
  for( int i = 1; i <= mintRepeatCount; i++ )
  {
    mSha256.hashThisString( lStringToHash );
  } // for
  endTime = clock();
  double elapsedTime = (endTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  sha256ResultAsHex = mSha256.getSha256ResultAsHex();
  return elapsedTime;
} // double RunFileHashBenchmark( string astrFileName )

void cSha256Bench::forceSoftwareCodePath()
{
   mSha256.mboolCentaurPadlockHashEngineAvailable = false;
} // void cSha256Bench::forceSoftwareCodePath()

void cSha256Bench::forcePadlockCodePath()
{
   mSha256.mboolCentaurPadlockHashEngineAvailable = true;
} // void cSha256Bench::forcePadlockCodePath()

// cSha256Bench::processCommandLine(int argc, char **argv) returns true for normal
// benchmark, false for file benchmark
bool cSha256Bench::processCommandLine(int argc, char **argv)
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
} // bool cSha256Bench::processCommandLine(int argc, char **argv)


double cSha256Bench::getScoreForSmallStrings()
{
  return 1000 * ( 8040 / mdSmallStringTime );
}

double cSha256Bench::getScoreFor50kString()
{
  return 1000 * ( 8290 / md50kStringTime );
}

double cSha256Bench::getScoreFor1MString()
{
  return 1000 * ( 8310 / md1MStringTime );
}

double cSha256Bench::getScoreFor10MString()
{
  return 1000 * ( 8325 / md10MStringTime );
}

double cSha256Bench::getScoreOverall()
{
  return 1000 * ( 32975 / mdOverallTime );
}
