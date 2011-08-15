#include "cShortTests.h"

cTest::cTest(int aIterations)
{
  fIterations = aIterations;
  fTestAuthor = "Van Smith";
  fMinTimeSeconds = 9e99;
  fMaxTimeSeconds = -1.0;
  cerr << "constructor called for "
       << fIterations
       << " iterations."
       << endl;
};

cTest::~cTest()
{
  cerr << "destructor called" << endl;
};

double cTest::GetScore()
{
   return 1000 * ( fMinTimeSeconds / fReferenceTime );
}

void cTest::Pretest()
{
   cerr << "cTest::Pretest() dummy routine." << endl;
}

void cTest::RunTest()
{
   cerr << "cTest::RunTest() dummy routine." << endl;
}

void cTest::Posttest()
{
   cerr << "cTest::Posttest() dummy routine." << endl;
}

double cTest::Run()
{
   cStopwatch lStopwatch;
   double elapsedTime = -1.0;

   for( int i = 0; i < fIterations; i++ )
   {
      Pretest();

      lStopwatch.StartStopwatch();
      RunTest();
      elapsedTime = lStopwatch.StopStopwatch();
      if( elapsedTime < fMinTimeSeconds ){ fMinTimeSeconds = elapsedTime; }
      if( elapsedTime > fMaxTimeSeconds ){ fMaxTimeSeconds = elapsedTime; }

      Posttest();
   }

   return elapsedTime;
}

int cTest::GetNumberOfThreads()
{
   return fiNumThreads;
}
//*************************************** cTest ends

// arrays used for random assignment test and bandwidth tests:
long Source[ 4000000 ];
//long SourceB[ 4000000 ];
long Target[ 4000000 ];
double doubleSource[ 4000000 ];
double doubleTarget[ 4000000 ];
int fDummyTarget;
double fdoubleDummyTarget;

double Sieve( int Iterations )
{
  //// from: http://www.kano.net/javabench/src/cpp/sieve.cpp

  //vector<char> primes(8192 + 1);
  //vector<char>::iterator pbegin = primes.begin();
  //vector<char>::iterator begin = pbegin + 2;
  //vector<char>::iterator end = primes.end();

  clock_t stopTime;
  clock_t startTime = clock();

  //while (Iterations--)
  //{
  //  fill(begin, end, 1);
  //  for (vector<char>::iterator i = begin; i < end; ++i)
  //  {
  //    if (*i)
  //    {
  //      const size_t p = i - pbegin;
  //      for (vector<char>::iterator k = i + p; k < end; k += p)
  //      {
  //        *k = 0;
  //      }
  //    }
  //  }
  //}

        // from http://bruscy.multicon.pl/pages/przemek/java_not_really_faster_than_cpp.html
// $Id: sieve.g++,v 1.6 2001/07/11 17:45:46 doug Exp $
// http://www.bagley.org/~doug/shootout/
// From Bill Lear
// with help from Stephane Lajoie
        const int PRIMES_SIZE=8192;
        bool primes[PRIMES_SIZE+1];
    int count=0;
    while (Iterations--) {
        count=0;
        memset(primes, true, sizeof(primes) );

        for (int i=2; i <= PRIMES_SIZE; ++i) {
            if (primes[i]) {
                for (int k = i + i; k <= PRIMES_SIZE; k += i) {
                    primes[k] = false;
                }
                ++count;
            }
        }
    }

  cerr << "Count: " << count << endl;

  stopTime = clock();
  double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);
  cerr  << "Sieve: "
        << elapsedTime
        << " s "
        << endl;
  //cerr << "Count: " << count(begin, end, 1) << endl;
  return elapsedTime;
}

double StringConcatenation( int Iterations )
{
  // from: http://www.kano.net/javabench/src/cpp/strcat.cpp
  string str;
  int i;
  size_t capacity = 31;
  str.reserve(capacity); // as per C-string
  size_t newLength = 6;

  clock_t stopTime;
  clock_t startTime = clock();

  for (i = 0; i < Iterations; i++)
  {
    if(newLength > capacity)
          {
      capacity *= 2;
            str.reserve(capacity);
    }
    str += "hello\n";
    newLength += 6;
  }
  stopTime = clock();

  double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);

  cerr  << "String Concatenation: "
        << elapsedTime
        << " s "
        << endl;
  cerr << str.length() << endl;

  return elapsedTime;
}

// heap sort taken from: http://www.kano.net/javabench/src/cpp/heapsort.cpp

void heapsort(int n, double *ra)
{
  int i, j;
  int ir = n;
  int l = (n >> 1) + 1;
  double rra;

  for (;;)
  {
    if (l > 1)
    {
      rra = ra[--l];
    }
    else
    {
            rra = ra[ir];
            ra[ir] = ra[1];
            if (--ir == 1) {
                ra[1] = rra;
                return;
            }
        }
        i = l;
        j = l << 1;
        while (j <= ir) {
            if (j < ir && ra[j] < ra[j+1]) { ++j; }
            if (rra < ra[j]) {
                ra[i] = ra[j];
                j += (i = j);
            } else {
                j = ir + 1;
            }
        }
        ra[i] = rra;
    }
}

double HeapSortTest( int ArraySize )
{
  double *SortArray;
  int liFill;

  /* create an array of N random doubles */
  SortArray = (double *) malloc( ( ArraySize + 1 ) * sizeof( double ) );

  // fill the array with crap:
  for ( liFill = 0; liFill < ArraySize; liFill++ )
  {
    SortArray[ liFill ] = 1.213909507 * rand();
  }


  clock_t stopTime;
  clock_t startTime = clock();

  heapsort( ArraySize, SortArray );

  stopTime = clock();

  double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);

  cerr  << "HeapSortTest: "
        << elapsedTime
        << " s "
        << endl;

  cerr << "Heap sort array size: " << ArraySize << "; last element: " << SortArray[ArraySize] << endl;

  free( SortArray );

  return elapsedTime;

}
//////////////////
// integer matrix multiply from http://www.kano.net/javabench/src/cpp/matrix.cpp
#define MATRIX_SIZE 800

int **mkmatrix(int rows, int cols)
{
  int i, j, count = 1;
  int **m = (int **) malloc(rows * sizeof(int *));
  for (i=0; i<rows; i++)
  {
    m[i] = (int *) malloc(cols * sizeof(int));
    for (j=0; j<cols; j++)
    {
      m[i][j] = count++;
    }
  }
  return(m);
}

void zeromatrix(int rows, int cols, int **m)
{
  int i, j;
  for (i=0; i<rows; i++)
  {
    for (j=0; j<cols; j++)
    {
      m[i][j] = 0;
    }
  }
}

void freematrix(int rows, int **m)
{
  while (--rows > -1)
  {
    free(m[rows]);
  }
  free(m);
}

int **mmult(int rows, int cols, int **m1, int **m2, int **m3)
{
  int i, j, k, val;
  for (i=0; i<rows; i++)
  {
    for (j=0; j<cols; j++)
    {
            val = 0;
            for (k=0; k<cols; k++)
      {
        val += m1[i][k] * m2[k][j];
            }
            m3[i][j] = val;
    }
  }
  return(m3);
}

double IntegerMatrixMultiplication( int Iterations )
{
  int **m1 = mkmatrix(MATRIX_SIZE, MATRIX_SIZE);
  int **m2 = mkmatrix(MATRIX_SIZE, MATRIX_SIZE);
  int **mm = mkmatrix(MATRIX_SIZE, MATRIX_SIZE);
  int i;

  cerr  << "Integer matrix multiplication starts... "
        << endl;

  clock_t stopTime;
  clock_t startTime = clock();

  for ( i = 0; i < Iterations; i++ )
  {
    mm = mmult(MATRIX_SIZE, MATRIX_SIZE, m1, m2, mm);
  }
  stopTime = clock();

  double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);

  cerr  << "Integer matrix multiplication: "
        << elapsedTime
        << " s "
        << endl;

  cerr << mm[0][0] << " " << mm[2][3] << " " << mm[3][2] << " " << mm[4][4] << endl;

  freematrix( MATRIX_SIZE, m1 );
  freematrix( MATRIX_SIZE, m2 );
  freematrix( MATRIX_SIZE, mm );

  return elapsedTime;
}
//==============================================================================================

double intArithmetic(int intMax)
{
  clock_t stopTime;
  clock_t startTime = clock();

  int intResult = 1;
  int i = 1;
  while (i < intMax)
  {
          intResult -= i++;
          intResult += i++;
          intResult *= i++;
          intResult /= i++;
  }

  stopTime = clock();
  double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);

  cerr  << setiosflags( ios::fixed )
        << setprecision( 0 );
  cerr  << "Integer arithmetic elapsed time: "
        << elapsedTime
        << " s with int Max of "
        << intMax
        << endl;
  cerr  << "i: "
        << i
        << endl;
  cerr  << "intResult: "
        << intResult
        << endl;

  return elapsedTime;
}

double doubleArithmetic(double doubleMin, double doubleMax)
{
   clock_t stopTime;
   clock_t startTime = clock();

   double doubleResult = doubleMin;
   double i = doubleMin;
   while (i < doubleMax)
   {
          doubleResult -= i++;
          doubleResult += i++;
          doubleResult *= i++;
          doubleResult /= i++;
   }

   stopTime = clock();
   double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);

   cerr  << "Double-precision floating point arithmetic elapsed time: "
        << elapsedTime
        << " s with doubleMin "
        << setiosflags( ios::fixed )
        << setprecision( 6 )
        << doubleMin
        << ", doubleMax "
        << doubleMax
        << endl;
   cerr  << "i: "
        << i
        << endl;
   cerr  << "doubleResult: "
        << doubleResult
        << endl;

   return elapsedTime;
}

double longArithmetic(long long longMin, long long longMax)
{
   clock_t stopTime;
   clock_t startTime = clock();

   long long longResult = longMin;
   long long i = longMin;
   while (i < longMax)
   {
          longResult -= i++;
          longResult += i++;
          longResult *= i++;
          longResult /= i++;
   }

   stopTime = clock();
   double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);
   cerr << "Long arithmetic elapsed time: " << elapsedTime << " s with longMax " << longMax << endl;
   cerr << " i: " << i << endl;
   cerr << " longResult: " << longResult << endl;
   return elapsedTime;
}


double trig(double trigMax)
{
   clock_t stopTime;
   clock_t startTime = clock();

   double sine       = 0;
   double cosine     = 0;
   double tangent    = 0;
   double logarithm  = 0;
   double squareRoot = 0;

   double i = 0.0;
   while (i < trigMax)
   {
          sine = sin(i);
          cosine = cos(i);
          tangent = tan(i);
          logarithm = log10(i);
          squareRoot = sqrt(i);
          i++;
   }
   stopTime = clock();
  double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);

  cerr << setiosflags( ios::fixed )
       << setprecision( 0 );
  cerr  << "Transcendental function floating point arithmetic elapsed time: "
        << elapsedTime
        << " s with max of "
        << trigMax
        << endl;
  cerr << setiosflags( ios::fixed )
       << setprecision( 6 );
  cerr  << "i: "
        << i
        << endl;
  cerr  << "sine: "
        << sine
        << endl;
  cerr  << "cosine: "
        << cosine
        << endl;
  cerr  << "tangent: "
        << tangent
        << endl;
  cerr  << "logarithm: "
        << logarithm
        << endl;
  cerr  << "squareRoot: "
        << squareRoot
        << endl;

        return elapsedTime;
}

double io(int ioMax)
{
   clock_t stopTime;

   clock_t startTime = clock();
   FILE *stream;
   stream = fopen("DeleteMe_minibench.txt", "w");
   int i = 0;
   while (i++ < ioMax)
   {
          fputs("abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefgh\n", stream);
   }
   fclose(stream);

   char readLine[100];
   stream = fopen("DeleteMe_minibench.txt", "r");
   i = 0;
   while (i++ < ioMax)
   {
          fgets(readLine, 100, stream);
   }
   fclose(stream);
   stopTime = clock();

  double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);

  cerr  << setiosflags( ios::fixed )
        << setprecision( 0 );
  cerr  << "I/O elapsed time: "
        << elapsedTime
        << " s with max of "
        << ioMax
        << endl;
  cerr  << "i:"
        << i
        << endl;
  cerr  << "readLine: "
        << readLine
        << endl;

        return elapsedTime;
}

double RandomAssignment( int NumDigits )
{
   int liIterate;
   int liFill;
   int liRandomSource;
   int liRandomTarget;
   const int TWO_MILLION = 2097152;
   const int ITERATIONS = 10;
   const int BYTES_PER_ARRAY = 4 * TWO_MILLION;

   for ( liFill = 0; liFill < NumDigits; liFill++ )
   {
    Source[ liFill ] = rand();
   }

   clock_t stopTime;
   clock_t startTime = clock();
   for ( liIterate = 0; liIterate <= ITERATIONS; liIterate++ )
   {
    for ( liFill = 0; liFill <= NumDigits; liFill++ )
    {
      liRandomSource = (int)(NumDigits * ((double) rand() / (double) RAND_MAX));
      liRandomTarget = (int)(NumDigits * ((double) rand() / (double) RAND_MAX));
      Target[ liRandomTarget ] = Source[ liRandomSource ];
    }
   }
   stopTime = clock();

  double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);
  double memoryBandwidth =
          ( ( 2 * 4 * ITERATIONS * (double)TWO_MILLION ) / elapsedTime ) / 1.0e6;

  cerr  << setiosflags( ios::fixed )
        << setprecision( 0 );
  cerr  << "Random Assignment elapsed time: "
        << elapsedTime
        << " ms "
        << endl;
  cerr  << "Block size " << BYTES_PER_ARRAY << " bytes source, " << BYTES_PER_ARRAY << " bytes target."
        << endl;
  cerr  << "Memory bandwidth for random assignment: "
                << memoryBandwidth
                << " MB/s"
                << endl;

  return memoryBandwidth;
}

double BandwidthIntegerWrite( int aiArraySize )
{
  int liIterate;
  int liFill;
  const int NUMBER_OF_ITERATIONS = 1000;
//  const int NUMBER_OF_ARRAY_ELEMENTS = 2000000;
  double elapsedTime;
  double memoryBandwidth;

  clock_t stopTime;
  clock_t startTime = clock();
  for ( liIterate = 1; liIterate < NUMBER_OF_ITERATIONS; liIterate++ )
  {
    for ( liFill = 0; liFill < aiArraySize; liFill++ )
    {
      Target[ liFill ] = liIterate;
    }
  }
  stopTime = clock();

  elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  memoryBandwidth = ( 4 * (double)aiArraySize * (double)NUMBER_OF_ITERATIONS ) / elapsedTime / (double) 1000.0;

  cerr  << setiosflags( ios::fixed )
        << setprecision( 0 );
  cerr  << "Memory Bandwidth, Integer Write: "
        << elapsedTime
        << " ms "
        << endl;
  cerr  << "Memory Bandwidth Integer Write: "
        << memoryBandwidth
        << " MB/s"
        << endl;

  return memoryBandwidth;
}

double BandwidthMemCpy( int aiArraySize )
{
  int liIterate = 0;
  int liFill;
  const int NUMBER_OF_ITERATIONS = 1000;
//  const int NUMBER_OF_ARRAY_ELEMENTS = 2000000;
  double elapsedTime;
  double memoryBandwidth;
  for ( liFill = 0; liFill < aiArraySize; liFill++ )
  {
    Source[ liFill ] = rand();
  }

  clock_t stopTime;
  clock_t startTime = clock();
  for ( liIterate = 0; liIterate < NUMBER_OF_ITERATIONS; liIterate++ )
  {
    memcpy( Target, Source, aiArraySize*4 );
    Source[ liIterate ] = rand(); // for optimizer
  }
  stopTime = clock();

  elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  memoryBandwidth = ( 2 * 4 * aiArraySize * (double)NUMBER_OF_ITERATIONS ) / elapsedTime / (double) 1000.0;

  cerr  << setiosflags( ios::fixed )
        << setprecision( 0 );
  cerr  << "Memory Bandwidth, memcpy time: "
        << elapsedTime
        << " ms "
        << endl;
  cerr  << "Memory Bandwidth, memcpy bandwidth: "
        << memoryBandwidth
        << " MB/s"
        << endl;

  return memoryBandwidth;
}

double BandwidthDoubleCopy( int aiArraySize )
{
  int liIterate;
  int liFill;
  const int NUMBER_OF_ITERATIONS = 1000;
//  const int NUMBER_OF_ARRAY_ELEMENTS = 2000000;
  double elapsedTime;
  double memoryBandwidth;

  // fill the array with crap:
  for ( liFill = 0; liFill < aiArraySize; liFill++ )
  {
    doubleSource[ liFill ] = 1.1 * rand();
  }

  clock_t stopTime;
  clock_t startTime = clock();
  for ( liIterate = 1; liIterate < NUMBER_OF_ITERATIONS; liIterate++ )
  {
    for ( liFill = 0; liFill < aiArraySize; liFill++ )
    {
      doubleTarget[ liFill ] = doubleSource[ liFill ];
    }
  }
  stopTime = clock();

  elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  memoryBandwidth = ( 2 * 8 * NUMBER_OF_ITERATIONS * aiArraySize ) / elapsedTime / (double) 1000.0;

  cerr  << setiosflags( ios::fixed )
        << setprecision( 0 );
  cerr  << "Memory Bandwidth, Double Copy: "
        << elapsedTime
        << " ms "
        << endl;
  cerr  << "Memory Bandwidth, Double Copy: "
        << memoryBandwidth
        << " MB/s"
        << endl;

  return memoryBandwidth;
}

cFibTest::cFibTest( int aIterations ) : cTest( aIterations )
{
   cerr << "cFibTest contstructor called." << endl;
   fFibNumber = 42; // default value
   fResult = -1;
   fTestName = "Fibonacci";
}

int cFibTest::Fibonacci(int n)
{
  if (n > 2)
  {
    return Fibonacci( n - 1 ) + Fibonacci( n - 2 );
  }
  else
  {
    return 1;
  }
}

void cFibTest::RunTest()
{
  fResult = Fibonacci( fFibNumber );
}

void cFibTest::SetFibNumber( int value )
{
  fFibNumber = value;
}

int cFibTest::GetFibNumber()
{
   return fFibNumber;
}

int cFibTest::GetResult()
{
   return fResult;
}

string gPiResult;

void ComputePi( int NumDigits )
{
//  string strResult;
  int I;
  int J;
  int K;
  int P;
  int Q;
  int X;
  int Nines;
  int Predigit;
  int arraySize;
  arraySize = ( 10 * NumDigits ) / 3;
  int A[ arraySize ];
  //int * A = new int [ arraySize ];
  int PiLength;
  // initialize string to "-----..."
  for ( I = 0; I <= NumDigits; I++ )
  {
    gPiResult += "-";
  }

  PiLength = 1;
  Nines = 0;
  Predigit = 0;
  // intitialize array:
  for ( I = 0; I <= arraySize; I++ )
    A[I] = 2; // ok

  for ( J = 0; J <= (NumDigits-1); J++ )
  {
    Q = 0;
    P = 2 * arraySize - 1;
    for ( I = (arraySize - 1); I >= 0; I-- )
    {
      X = ( 10*A[I] ) + ( Q*(I+1) );
      A[I] = X % P;
      Q = X / P;
      P = P - 2;
    }
    A[0] = Q % 10;
    Q = Q / 10;
    if ( Q == 9 )
    {
      Nines++;
    }
    else
    {
      if ( Q == 10 )
      {
        gPiResult[PiLength - 1] = char(Predigit + 1 + int('0'));
        for ( K = 1; K <= Nines; K++ )
          gPiResult[ PiLength - 1 + K ] = '0';
        PiLength = PiLength + Nines + 1;
        Predigit = 0;
        Nines = 0;
      }
      else
      {
        gPiResult[PiLength - 1] = char(Predigit + int('0'));
        Predigit = Q;
        for ( K = 1; K <= Nines; K++ )
          gPiResult[ PiLength - 1 + K ] = '9';
        PiLength = PiLength + Nines + 1;
        Nines = 0;
      }
    }
  }
  gPiResult[PiLength - 1] = char( Predigit + int('0') );

  cerr << " pi finished." << endl;
  cerr << "gPiResult = " << gPiResult << endl;
  gPiResult = "";
  cerr << "gPiResult = " << gPiResult << endl;
  //delete [] A;  // gcc barfs -- array auto freed?
  //return strResult; // gcc does not like returning this string
}

double PiTest(int n)
{
   clock_t stopTime;
   clock_t startTime;

   startTime = clock();
   ComputePi( n );
   stopTime = clock();

   double elapsedTime = ((double)stopTime - (double)startTime) / ((double)CLOCKS_PER_SEC);
//  cerr  << setiosflags( ios::fixed )
//        << setprecision( 0 );
//  cerr  << "Calculate Pi elapsed time: "
//        << elapsedTime
//        << " ms with n of "
//        << n
//        << endl;
//  // set number formatting back:
//  cerr << setiosflags( ios::fixed )
//       << setprecision( 2 );
  return elapsedTime;
}


