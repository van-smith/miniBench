#include "cMiniBench.h"

cMiniBench::cMiniBench()
{
   cerr << "cMiniBench constructor called." << endl;
   LinpackRolled = 0;
   LinpackUnrolled = 0;
   FlopsFpuFloatAdd = 0;
   FlopsFpuFloatMul = 0;
   FlopsSseFloatAdd = 0;
   FlopsFpuFloatMulAdd = 0;
   FlopsFpuFloatDiv = 0;
   FlopsFpuDoubleMul = 0;
   FlopsFpuDoubleDiv = 0;
   FlopsFpuDoubleAdd = 0;
   FlopsSseFloatMul = 0;
   FlopsSseFloatDiv = 0;
   FlopsSseFloatMulAdd = 0;
   FlopsSse2DoubleAdd = 0;
   FlopsSse2DoubleMul = 0;
   FlopsSse2DoubleMulAdd = 0;
   FlopsSse2DoubleMulAdd2 = 0;
   FlopsSse2DoubleMulAdd3 = 0;
   FlopsSse2DoubleMulAdd4 = 0;
   FlopsSse2DoubleMulAdd5 = 0;
   FlopsFpuDoubleMulAdd3 = 0;
   FlopsSse2DoubleAddMax = 0;
   FlopsSse2DoubleMulMax = 0;
   FlopsSse2DoubleDiv = 0;
   Sha1ScoreOverall = 0;
   Sha1ScoreSmallStrings = 0;
   Sha1Score50KString = 0;
   Sha1Score1MString = 0;
   Sha1Score10MString = 0;
   Sha256ScoreOverall = 0;
   Sha256ScoreSmallStrings = 0;
   Sha256Score50KString = 0;
   Sha256Score1MString = 0;
   Sha256Score10MString = 0;
   AesEncrypt8kBScore = 0;
   AesDecrypt8kBScore = 0;
   AesEncrypt16kBScore = 0;
   AesDecrypt16kBScore = 0;
   AesEncrypt32kBScore = 0;
   AesDecrypt32kBScore = 0;
   AesEncrypt64kBScore = 0;
   AesDecrypt64kBScore = 0;
   AesEncrypt128kBScore = 0;
   AesDecrypt128kBScore = 0;
   AesEncrypt256kBScore = 0;
   AesDecrypt256kBScore = 0;
   AesEncrypt512kBScore = 0;
   AesDecrypt512kBScore = 0;
   AesEncrypt1024kBScore = 0;
   AesDecrypt1024kBScore = 0;
   AesEncrypt2048kBScore = 0;
   AesDecrypt2048kBScore = 0;
   AesEncrypt4096kBScore = 0;
   AesDecrypt4096kBScore = 0;
   AesEncrypt8192kBScore = 0;
   AesDecrypt8192kBScore = 0;
   AesEncrypt16384kBScore = 0;
   AesDecrypt16384kBScore = 0;
   WhetstoneTestTime = 1e99;
   DhrystoneTestTime = 1e99;
   QueenTestTime = 1e99;
   PiTestTime = 1e99;
   fftTestTime = 1e99;
   HeapSortTestTime = 1e99;
   IntegerMatrixMultiplicationTime = 1e99;
   sieveTime = 1e99;
   StringConcatenationTime = 1e99;
   FibTestTime = 1e99;
   IntegerArithmeticTime = 1e99;
   Int64ArithmeticTime = 1e99;
   doubleArithmeticTime = 1e99;
   trigTime = 1e99;
   ioTime = 1e99;
   RandomAssignmentTime = 1e99;
   StreamCopyBandwidth = 0;
   StreamScaleBandwidth = 0;
   StreamAddBandwidth = 0;
   StreamTriadBandwidth = 0;
   BandwidthIntegerReadTime = 1e99;
   BandwidthIntegerReadReverseTime = 1e99;
   BandwidthIntegerReadBP64Time = 1e99;
   BandwidthIntegerReadPrefetchNTA = 1e99;
   BandwidthIntegerWriteTime = 1e99;
   BandwidthIntegerWriteUnrollTime = 1e99;
   BandwidthIntegerCopyTime = 1e99;
   BandwidthIntegerAddTime = 1e99;
   BandwidthIntegerScaleTime = 1e99;
   BandwidthIntegerTriadTime = 1e99;
   BandwidthIntegerCopyBP64Time = 1e99;
   BandwidthDoubleReadTime = 1e99;
   BandwidthDoubleReadReverseTime = 1e99;
   BandwidthDoubleWriteTime = 1e99;
   BandwidthDoubleCopyTime = 1e99;
   BandwidthMemCpyTime = 1e99;

}

cMiniBench::~cMiniBench()
{
   cerr << "cMiniBench destructor called." << endl;
}

void cMiniBench::StatusBarUpdate( string aStatusMessage )
{
   cerr << aStatusMessage << endl;
}

void cMiniBench::OutputSeconds(double adoubleResult, string aOutputMessage )
{
//   string lstrResult;
//   lstrResult. setNum( adoubleResult / 1000, 'g', 4 );
   cout << aOutputMessage << " (s): " <<  setw( 6 ) << setiosflags(ios::fixed) << setprecision(3)  << adoubleResult << endl;
}

void cMiniBench::OutputRaw(double adoubleResult, string aOutputMessage )
{
//   string lstrResult;
//   lqstrResult.setNum( adoubleResult, 'g', 4 );
//   cout << aOutputMessage << lqstrResult << endl;
   cout << aOutputMessage << "\t" << setw( 6 ) << setiosflags(ios::fixed) << setprecision(3) << adoubleResult << endl;
}

void cMiniBench::RunTests()
{
   if( TestsToRun[ eAes ] )
   {
      StatusBarUpdate( "Running AES ECB Encypt/Decrypt Tests..." );
      cAesBench AesBench;

      StatusBarUpdate( "Running AES 8kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark8KB( true ), "AES ECB Encrypt 8kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark8KB( true ), "AES ECB Decrypt 8kB score: " );

      StatusBarUpdate( "Running AES 16kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark16KB( true ), "AES ECB Encrypt 16kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark16KB( true ), "AES ECB Decrypt 16kB score: " );

      StatusBarUpdate( "Running AES 32kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark32KB( true ), "AES ECB Encrypt 32kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark32KB( true ), "AES ECB Decrypt 32kB score: " );

      StatusBarUpdate( "Running AES 64kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark64KB( true ), "AES ECB Encrypt 64kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark64KB( true ), "AES ECB Decrypt 64kB score: " );

      StatusBarUpdate( "Running AES 128kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark128KB( true ), "AES ECB Encrypt 128kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark128KB( true ), "AES ECB Decrypt 128kB score: " );

      StatusBarUpdate( "Running AES 256kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark256KB( true ), "AES ECB Encrypt 256kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark256KB( true ), "AES ECB Decrypt 256kB score: " );

      StatusBarUpdate( "Running AES 512kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark512KB( true ), "AES ECB Encrypt 512kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark512KB( true ), "AES ECB Decrypt 512kB score: " );

      StatusBarUpdate( "Running AES 1024kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark1024KB( true ), "AES ECB Encrypt 1024kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark1024KB( true ), "AES ECB Decrypt 1024kB score: " );

      StatusBarUpdate( "Running AES 2048kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark2048KB( true ), "AES ECB Encrypt 2048kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark2048KB( true ), "AES ECB Decrypt 2048kB score: " );

      StatusBarUpdate( "Running AES 4096kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark4096KB( true ), "AES ECB Encrypt 4096kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark4096KB( true ), "AES ECB Decrypt 4096kB score: " );

      StatusBarUpdate( "Running AES 8192kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark8192KB( true ), "AES ECB Encrypt 8192kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark8192KB( true ), "AES ECB Decrypt 8192kB score: " );

      StatusBarUpdate( "Running AES 16384kB ECB Encypt/Decrypt Tests..." );
      OutputRaw( AesBench.runEncryptBenchmark16384KB( true ), "AES ECB Encrypt 16384kB score: " );
      OutputRaw( AesBench.runDecryptBenchmark16384KB( true ), "AES ECB Decrypt 16384kB score: " );
    }

   if( TestsToRun[ eDhrystone ] )
   {
      StatusBarUpdate( "Running Dhrystone..." );
      CDhryApp dhry( 20000000 );
      OutputSeconds( dhry.RunTest( 20000000 ), "Dhrystone" );
   }

   if( TestsToRun[ eDoubleArithmetic ] )
   {
      StatusBarUpdate( "Running Double Arithmetic..." );
      OutputSeconds( doubleArithmetic( 10000000000.0, 11000000000.0 ), "Double Arithmetic (s): " );
   }

   if( TestsToRun[ eFibonacci ] )
   {
      StatusBarUpdate( "Running Fibonacci( 42 )..." );
      cFibTest FibTest( 1 );
      OutputSeconds( FibTest.Run(), "Fib(42)" );
   }


   if( TestsToRun[ eFft ] )
   {
      StatusBarUpdate( "Running FFT..." );
      cFFT FFT( 1 );
      OutputSeconds( FFT.Run(), "FFT" );
   }

   if( TestsToRun[ eFlops ] )
   {
      cFlops lFlops;

      // addition:
      StatusBarUpdate( "MFLOPS SP Add..." );
      OutputRaw( lFlops.runFpuFloatAddTest(), "MFLOPS (SP add): " );
      StatusBarUpdate( "MFLOPS DP Add..." );
      OutputRaw( lFlops.runFpuDoubleAddTest(), "MFLOPS (DP add): " );
      // multiplication
      StatusBarUpdate( "MFLOPS SP Mul..." );
      OutputRaw( lFlops.runFpuFloatMulTest(), "MFLOPS (SP mul): " );
      StatusBarUpdate( "MFLOPS DP Mul..." );
      OutputRaw( lFlops.runFpuDoubleMulTest(), "MFLOPS (DP mul): " );
      // division:
      StatusBarUpdate( "MFLOPS SP Div..." );
      OutputRaw( lFlops.runFpuFloatDivTest(), "MFLOPS (SP div): " );
      StatusBarUpdate( "MFLOPS DP Div..." );
      OutputRaw( lFlops.runFpuDoubleDivTest(), "MFLOPS (DP div): " );
      // mul-add:
      StatusBarUpdate( "MFLOPS DP Mul-Add..." );
      OutputRaw( lFlops.runFpuDoubleMulAdd3Test(), "MFLOPS (DP mul-add): " );
   }

   if( TestsToRun[ eHeapSort ] )
   {
      StatusBarUpdate( "Running Heap Sort..." );
      OutputSeconds( HeapSortTest( 5000000 ), "Heap Sort (s): " );
   }

   if( TestsToRun[ eIntArithmetic ] )
   {
      StatusBarUpdate( "Running Integer Arithmetic..." );
      OutputSeconds( intArithmetic( 1000000000 ), "Integer Arithmetic (s): " );
   }

   if( TestsToRun[ eInt64Arithmetic ] )
   {
      StatusBarUpdate( "Running 64-bit Arithmetic..." );
      OutputSeconds( longArithmetic( 10000000000LL, 11000000000LL ), "64-bit Arithmetic (s): " );
   }

   if( TestsToRun[ eIntegerMatrixMul ] )
   {
      StatusBarUpdate( "Running Integer Matrix Multiplication..." );
      OutputSeconds( IntegerMatrixMultiplication( 1 ), "Integer Matrix Multiplication (s): " );
   }

   if( TestsToRun[ eIO ] )
   {
      StatusBarUpdate( "Running I/O..." );
      OutputSeconds( io( 10000000 ), "I/O (s): " );
      remove( "DeleteMe_minibench.txt" );
   }

   if( TestsToRun[ eLinpack ] )
   {
      cLinpackTest lLinpack( 1 );

      StatusBarUpdate( "Running Linpack rolled..." );
      lLinpack.Run();
      OutputRaw( lLinpack.GetFlops(), "LinPack rolled (FLOPS): " );

      StatusBarUpdate( "Running Linpack unrolled..." );
      lLinpack.SetRolling( eUnrolled );
      lLinpack.Run();
      OutputRaw( lLinpack.GetFlops(), "LinPack unrolled (FLOPS): " );
   }

   if( TestsToRun[ eAllMemoryTests] )
   {
      StatusBarUpdate( "Memory Bandwidth Integer Write (MB/s): " );
      OutputRaw( BandwidthIntegerWrite( 2000000 ), "Memory Bandwidth Integer Write (MB/s): " );

      StatusBarUpdate( "Memory Bandwidth MemCpy (MB/s): " );
      OutputRaw( BandwidthMemCpy( 2000000 ), "Memory Bandwidth MemCpy (MB/s): " );

      StatusBarUpdate( "Memory Bandwidth Double Copy (MB/s): " );
      OutputRaw( BandwidthDoubleCopy( 2000000 ), "Memory Bandwidth Double Copy (MB/s): " );
   }

   if( TestsToRun[ eRandomAssignment ] )
   {
      StatusBarUpdate( "Memory Latency Random Assignment (MB/s): " );
      OutputRaw( RandomAssignment( 2000000 ), "Memory Latency Random Assignment (MB/s): " );
   }

   if( TestsToRun[ ePi ] )
   {
      StatusBarUpdate( "Running Pi( 10,000 )..." );
      int i = 0;

      {
        i += PiTest( 10000 );
      }
      OutputSeconds( i, "Pi to 10,000 digits (s): " );
   }

   if( TestsToRun[ eQueens ] )
   {
      StatusBarUpdate( "Running Queens..." );
      double ldRunTime = 0;
      cQueensTest Queens( 1 );
      ldRunTime = Queens.Run();
/*      #pragma omp parallel
      {
        num_threads = omp_get_num_threads();
        CQueens Queens;
        #pragma omp atomic
        ldRunTime += Queens.RunTest(25000);
      }
*/
      cout << "Queens (seconds per thread): " << ldRunTime << endl;
      cout << "Number of threads = " << Queens.GetNumberOfThreads() << endl;
   }

   if( TestsToRun[ eSha1 ] )
   {
      StatusBarUpdate( "Running SHA1 Tests..." );
      cSha1Bench lSha1Bench;
      if( lSha1Bench.runSha1ValidationTests( true ) )
      {
        OutputSeconds( lSha1Bench.runBenchmark( true ), "SHA1 (s): " );
   //     OutputRaw( lSha1Bench.getScoreOverall() );
   //     OutputRaw( lSha1Bench.getScoreForSmallStrings(), "SHA1 small strings: " );
   //       Sha1Score50KString = lSha1Bench.getScoreFor50kString();
   //       Sha1Score1MString = lSha1Bench.getScoreFor1MString();
   //       Sha1Score10MString = lSha1Bench.getScoreFor10MString();
   //     } // if
      } else
      {
        cerr << "Sha1 validation tests failed!" << endl;
        StatusBarUpdate( "Sha1 validation tests failed!" );
      } // if...else
   }

   if( TestsToRun[ eSha256 ] )
   {
      cSha256Bench lSha256Bench;
      if( lSha256Bench.runSha256ValidationTests( true ) )
      {
         StatusBarUpdate( "Executing SHA-256 timed tests..." );
         OutputSeconds( lSha256Bench.runBenchmark( true ), "SHA256 (s): " );
   //      cerr << "The benchmark took " << TestTime << " milliseconds for all hash tests." << endl;
   //      if( Sha256ScoreOverall < lSha256Bench.getScoreOverall() )
   //      {
   //        Sha256ScoreOverall = lSha256Bench.getScoreOverall();
   //        Sha256ScoreSmallStrings = lSha256Bench.getScoreForSmallStrings();
   //        Sha256Score50KString = lSha256Bench.getScoreFor50kString();
   //        Sha256Score1MString = lSha256Bench.getScoreFor1MString();
   //        Sha256Score10MString = lSha256Bench.getScoreFor10MString();
   //      } // if
       } else
       {
         StatusBarUpdate( "Sha256 validation tests failed!" );
       } // if...else
    }

   if( TestsToRun[ eSieve ] )
   {
      StatusBarUpdate( "Sieve..." );
      OutputSeconds( Sieve( 50000 ), "Sieve (s): " );
   }

   if( TestsToRun[ eStringConcat ] )
   {
      StatusBarUpdate( "String Concatenation..." );
      OutputSeconds( StringConcatenation( 40000000 ), "String Concatenation (s): " );
   }

   if( TestsToRun[ eTrig ] )
   {
      StatusBarUpdate( "Running Trig..." );
      OutputSeconds( trig( 10000000 ), "Trig (s): " );
   }

   if( TestsToRun[ eWhetstone ] )
   {
      StatusBarUpdate( "Running Whetstone..." );
      CWhetApp whet;
      OutputSeconds( whet.RunTest( 50000 ), "Whetstone (s): " );
   }

   StatusBarUpdate( "All tests finished!" );
}

void cMiniBench::Run()
{
   for( int i = 1; i <= iterations; i++)
   {
      cout << "*****************************************************" << endl;
      cout << "Executing iteration " << i << " of " << iterations << "." << endl;
      RunTests();
      cout << "*****************************************************" << endl;
   }
}

bool cMiniBench::ParseCommandLine( int argc, char **argv )
{
   iterations = 1;
   bool lboolNoTestsSelected = true;
   // intialize all tests to false:
   for( int i = eAllTests; i < eLastTest; i++)
   {
      TestsToRun[ i ] = false;
   }
   // if there are no commandline arguments, default to all tests and 1 iteration:
   if (argc == 1)
   {
      TestsToRun[ eAllTests ] = true;
      for( int i = eAllTests + 1; i < eLastTest; i++) TestsToRun[ i ] = true;
      return 1;
   }
   else
   {
      // now check all of the commandline switches:
      for( int i = 1; i < argc; i++ )
      {
         string CurrentArgument = argv[ i ];
         bool FoundArgument = false;
         // look for "iterations="
         if( CurrentArgument.find( CommandLineArguments[ eLastTest ], 0 ) == 0 )
         {
            size_t IterStart = CommandLineArguments[ eLastTest ].length(); // size of the switch name string
            size_t IterEnd = CurrentArgument.length(); // size of input switch string
            string lstrIterations = CurrentArgument.substr( IterStart, IterEnd - IterStart );
            iterations = atoi( lstrIterations.c_str() );
            FoundArgument = true;
         } else // search for a matching test
         {
            for( int j = eAllTests; j < eLastTest; j++ )
            {
               if( CurrentArgument == CommandLineArguments[ j ] )
               {
                  TestsToRun[ j ] = true;
                  FoundArgument = true;
                  lboolNoTestsSelected = false;
                  break;
               }
            } // for j
         }
         if( !FoundArgument )
         {
            cout << "Valid command line arguments:" << endl;
            cout << "=============================" << endl;
            for( int ii = eAllTests; ii <= eLastTest; ii++ )
            {
               cout << CommandLineArguments[ ii ] << endl;
            }
            cout << "=============================" << endl;
            cout << endl;
            cout << "example:" << endl;
            cout << argv[0] << " Dhrystone Whetstone iterations=10" << endl;
            cout << "This would execute the Dhrystone and Whetstone tests ten times.";
            cout << endl << endl;
            iterations = -1;
            return false;
         } // if
      } // for i
   }  // if...else
   if( TestsToRun[ eAllTests ] || lboolNoTestsSelected )
   {
      for( int i = eAllTests + 1; i < eLastTest; i++) TestsToRun[ i ] = true;
   }
   else
   {
      if( TestsToRun[ eAllCpuTests ] )
      {
         for( int i = eAllCpuTests + 1; i < eAllDiskTests; i++) TestsToRun[ i ] = true;
      }
      if( TestsToRun[ eAllDiskTests ] )
      {
         for( int i = eAllDiskTests + 1; i < eAllMemoryTests; i++) TestsToRun[ i ] = true;
      }
      if( TestsToRun[ eAllMemoryTests ] )
      {
         for( int i = eAllMemoryTests + 1; i < eLastTest; i++) TestsToRun[ i ] = true;
      }
   }
   if( iterations > 0 ){ return true; }
   else{ return false; };
}

