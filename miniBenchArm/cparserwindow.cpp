#include "cparserwindow.h"
#include "ui_cparserwindow.h"

// arrays used for random assignment test and bandwidth tests:
long Source[ 4000000 ];
long SourceB[ 4000000 ];
long Target[ 4000000 ];
double doubleSource[ 4000000 ];
double doubleTarget[ 4000000 ];
int fDummyTarget;
double fdoubleDummyTarget;

class cTest
{
  private:
//    RunTest
  protected:
    int fIterations;
    double fMaxTime;
    double fMinTime;
    double fTotalTime;
    string fTestAuthor;
    string fTestVersion;
  public:
    cTest(int aIterations);
    ~cTest();
    //virtual double getScore();
    //void setIterations( int aiNumberOfIterations );
};

class CQueenApp // from CLIBench
{
public:
  double RunTest( long Iterations );
        long DoQueen( long iterations );
private:
        void Attempt( int i );
        bool a[9],b[17],c[15];
        int x[9];
                //long LoopCount;
};

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
  double elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  cerr  << "Sieve: "
        << elapsedTime
        << " ms "
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

  double elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);

  cerr  << "String Concatenation: "
        << elapsedTime
        << " ms "
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

  double elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);

  cerr  << "HeapSortTest: "
        << elapsedTime
        << " ms "
        << endl;

  printf("%.10f\n", SortArray[ArraySize]);

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

  double elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);

  cerr  << "Integer matrix multiplication: "
        << elapsedTime
        << " ms "
        << endl;

  cerr << mm[0][0] << " " << mm[2][3] << " " << mm[3][2] << " " << mm[4][4] << endl;

  freematrix( MATRIX_SIZE, m1 );
  freematrix( MATRIX_SIZE, m2 );
  freematrix( MATRIX_SIZE, mm );

  return elapsedTime;
}

//////////////////////////////////////////////
// fft adapted from: http://math.nist.gov/scimark2/download_c.html

#define PI  3.1415926535897932

/*-----------------------------------------------------------------------*/

static int int_log2(int n);

double FFT_num_flops(int N)
{
  double Nd = (double) N;
  double logN = (double) int_log2(N);
  return (5.0*Nd-2)*logN + 2*(Nd+1);
}

static int int_log2 (int n)
{
  int k = 1;
  int log = 0;
  for(/*k=1*/; k < n; k *= 2)
  {
    log++;
  }
  if (n != (1 << log))
  {
    printf("FFT: Data length is not a power of 2!: %d ",n);
    exit(1);
  }
  return log;
}

void FFT_bitreverse(int N, double *data)
{
  /* This is the Goldrader bit-reversal algorithm */
  int n=N/2;
  int nm1 = n-1;
  int i=0;
  int j=0;
  for (; i < nm1; i++)
  {
    /*int ii = 2*i; */
    int ii = i << 1;
    /*int jj = 2*j; */
    int jj = j << 1;
    /* int k = n / 2 ; */
    int k = n >> 1;
    if (i < j)
    {
      double tmp_real    = data[ii];
      double tmp_imag    = data[ii+1];
      data[ii]   = data[jj];
      data[ii+1] = data[jj+1];
      data[jj]   = tmp_real;
      data[jj+1] = tmp_imag;
    }
    while (k <= j)
    {
      /*j = j - k ; */
      j -= k;
      /*k = k / 2 ;  */
      k >>= 1 ;
    }
    j += k ;
  }
}

static void FFT_transform_internal (int N, double *data, int direction)
{
  int n = N/2;
  int bit = 0;
  int logn;
  int dual = 1;

  if (n == 1) return;         /* Identity operation! */
  logn = int_log2(n);

  if (N == 0) return;
  /* bit reverse the input data for decimation in time algorithm */
  FFT_bitreverse(N, data) ;
/* apply fft recursion */
/* this loop executed int_log2(N) times */
  for (bit = 0; bit < logn; bit++, dual *= 2)
  {
    double w_real = 1.0;
    double w_imag = 0.0;
    int a;
    int b;
    double theta = 2.0 * direction * PI / (2.0 * (double) dual);
    double s = sin(theta);
    double t = sin(theta / 2.0);
    double s2 = 2.0 * t * t;
    for (a=0, b = 0; b < n; b += 2 * dual)
    {
      int i = 2*b ;
      int j = 2*(b + dual);
      double wd_real = data[j] ;
      double wd_imag = data[j+1] ;
      data[j]   = data[i]   - wd_real;
      data[j+1] = data[i+1] - wd_imag;
      data[i]  += wd_real;
      data[i+1]+= wd_imag;
    }
    /* a = 1 .. (dual-1) */
    for (a = 1; a < dual; a++)
    {
      /* trignometric recurrence for w-> exp(i theta) w */
      {
        double tmp_real = w_real - s * w_imag - s2 * w_real;
        double tmp_imag = w_imag + s * w_real - s2 * w_imag;
        w_real = tmp_real;
        w_imag = tmp_imag;
      }
      for (b = 0; b < n; b += 2 * dual)
      {
        int i = 2*(b + a);
        int j = 2*(b + a + dual);
        double z1_real = data[j];
        double z1_imag = data[j+1];
        double wd_real = w_real * z1_real - w_imag * z1_imag;
        double wd_imag = w_real * z1_imag + w_imag * z1_real;
        data[j]   = data[i]   - wd_real;
        data[j+1] = data[i+1] - wd_imag;
        data[i]  += wd_real;
        data[i+1]+= wd_imag;
      }
    }
  }
}

void FFT_transform(int N, double *data)
{
  FFT_transform_internal(N, data, -1);
}


void FFT_inverse(int N, double *data)
{
  int n = N/2;
  double norm = 0.0;
  int i=0;
  FFT_transform_internal(N, data, +1);

  /* Normalize */
  norm=1/((double) n);
  for(i=0; i<N; i++)
  {
    data[i] *= norm;
  }
}

double* RandomVector(int N )
{
  int i;
  double* x = ( double* ) malloc( sizeof( double ) * N );
  for (i=0; i<N; i++)
  {
    x[i] = 1.213909507 * rand() / PI;
  }
  return x;
}

double fftTest( int Iterations )
{
  /* initialize FFT data as complex (N real/img pairs) */
  int N = ( int ) pow( (double)2, 20 );
  int twoN = 2*N;

  double *x;
  int liFill;
  /* create the array */
  x = (double *) malloc( ( twoN + 1 ) * sizeof( double ) );
  // fill the array with crap:
  for ( liFill = 0; liFill < twoN; liFill++ )
  {
    x[ liFill ] = 1.213909507 * rand() / PI;
  }

  int i=0;
  double flops = 0.0;
  clock_t stopTime;
  clock_t startTime = clock();

  for ( i=0; i < Iterations; i++)
  {
    FFT_transform(twoN, x);     /* forward transform */
    FFT_inverse(twoN, x);       /* backward transform */
  }

  stopTime = clock();
  double elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  flops = ( FFT_num_flops(N) * Iterations ) / elapsedTime / 1000;
  free(x);

  cerr  << "FFT: "
        << elapsedTime
        << " ms "
        << endl;

  cerr << "Flops: " << flops << endl;

  return elapsedTime;
}

// for clibench dhrystone:
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>

#define Null 0
#define true  1
#define false 0
#define REG
#define structassign(d, s)      memcpy(&(d), &(s), sizeof(d))

typedef enum Enumeration{Ident_1, Ident_2, Ident_3, Ident_4, Ident_5} Enum ;
typedef  long     One_Thirty;
typedef  long     One_Fifty;
typedef char    Capital_Letter;
typedef char    Str_30 [31]; //this was 31
typedef  long     Arr_1_Dim [100];		//originally this was set to 50
typedef  long     Arr_2_Dim [100] [100];

typedef struct record
{
                         struct record *Ptr_Comp;
                         Enumeration    Discr;
                         union {
                                 struct {
                                         Enumeration Enum_Comp;
                                         long         long_Comp;
                                         char        Str_Comp [31];
                                 } var_1;
                                 struct {
                                         Enumeration E_Comp_2;
                                         char        Str_2_Comp [31];
                                 } var_2;
                                 struct {
                                         char        Ch_1_Comp;
                                         char        Ch_2_Comp;
                                 } var_3;
                         } variant;
} Rec_Type, *Rec_Polonger;

// template<size_t ALIGNMENT>
class CDynamicAlignedObj
{
        public:
                void * operator new(unsigned int size)
                {
                        // ensure it is aligned
                        void *p = malloc(size);
                        if (!p) throw std::bad_alloc();
                        return(p);
                };

                void operator delete(void *deadObject)
                {
                        // must use _aligned_free since we used _aligned_malloc
                        //_aligned_free(deadObject);
                        free(deadObject);
                }
};


//Applikationsklasse

//class CDhryApp : public CDynamicAlignedObj
class CDhryApp : public cTest
{
public:
  CDhryApp(int aIterations): cTest( aIterations ) {}
  double RunTest( long Iterations );
  long main(long Number_Of_Runs);

        /*private:
        void Proc_3 (Rec_Polonger Ptr_Ref_Par, Rec_Polonger Ptr_Glob, long * long_Glob);
        bool Func_3 (Enumeration Enum_Par_Val);
        Enumeration Func_1( Capital_Letter Ch_1_Par_Val,  Capital_Letter Ch_2_Par_Val, char  * Ch_1_Glob);
        bool Func_2 (Enumeration Enum_Par_Val);
        void Proc_6 (Enumeration Enum_Val_Par, Enumeration *Enum_Ref_Par, long * long_Glob);
        void Proc_7 ( One_Fifty long_1_Par_Val,  One_Fifty long_2_Par_Val,  One_Fifty *long_Par_Ref);
        void Proc_8 (Arr_1_Dim Arr_1_Par_Ref, Arr_2_Dim Arr_2_Par_Ref,   long long_1_Par_Val,   long long_2_Par_Val, long * long_Glob);
        Enumeration Func_1 ( Capital_Letter Ch_1_Par_Val,  Capital_Letter Ch_2_Par_Val);
        bool Func_2 ( Str_30 Str_1_Par_Ref,  Str_30 Str_2_Par_Ref, char * Ch_1_Glob, long * long_Glob);
        void Proc_5 (bool * Bool_Glob, char * Ch_1_Glob);
        void Proc_4 (bool * Bool_Glob, char * Ch_1_Glob, char * Ch_2_Glob);
        void Proc_3 (Rec_Polonger Ptr_Ref_Par);
        void Proc_2 (One_Fifty long_Par_Ref, char * Ch_1_Glob, long * long_Glob);
        void Proc_1 (Rec_Polonger Ptr_Val_Par, Rec_Polonger Ptr_Glob, long * long_Glob);
        */
};


// end for clibench dhrystone,

// end dhrystone

// begin clibench whetstone
class CWhetApp
{
public:
  double RunTest( long Iterations );
  long main(long wiederhole);
private:
        void p0();
        void p3(double x, double y, double *z);
        void pa(double e[4]);
        double		x1, x2, x3, x4, x, y, z, t, t1, t2;
        double 		e1[4];
        long		ii, j, k, l, n1, n2, n3, n4, n6, n7, n8, n9, n10, n11;
};
// end clibench whetstone

double intArithmetic(int intMax)
{
        double elapsedTime;
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
        elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);

  cerr  << setiosflags( ios::fixed )
        << setprecision( 0 );
  cerr  << "Integer arithmetic elapsed time: "
        << elapsedTime
        << " ms with int Max of "
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
        double elapsedTime;
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
        elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);

  cerr  << "Double-precision floating point arithmetic elapsed time: "
        << elapsedTime
        << " ms with doubleMin "
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
        double elapsedTime;
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
        elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
        printf("Long arithmetic elapsed time: %1.0f ms with longMax %I64d\n", elapsedTime, longMax);
        printf(" i: %I64d\n", i);
        printf(" longResult: %I64d\n", longResult);
        return elapsedTime;
}


double trig(double trigMax)
{
        double elapsedTime;
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
        elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);

  cerr << setiosflags( ios::fixed )
       << setprecision( 0 );
  cerr  << "Transcendental function floating point arithmetic elapsed time: "
        << elapsedTime
        << " ms with max of "
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
        double elapsedTime;
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

        elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);

  cerr  << setiosflags( ios::fixed )
        << setprecision( 0 );
  cerr  << "I/O elapsed time: "
        << elapsedTime
        << " ms with max of "
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
  double elapsedTime;
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

  elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  double memoryBandwidth =
          ( 2 * 4 * ITERATIONS * (double)TWO_MILLION ) / ( elapsedTime * (double) 1000.0 );

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

int Fibonacci(int n)
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

double FibTest(int n)
{
  double elapsedTime;
  clock_t stopTime;
  clock_t startTime;
  int intResult;

  startTime = clock();
  intResult = Fibonacci( n );
  // have to output result or optimizer will jump over stopTime
  cerr  << "intResult: "
        << intResult
        << endl;
  stopTime = clock();

  elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  cerr << setiosflags( ios::fixed )
       << setprecision( 0 );
  cerr  << "Fibonacci elapsed time: "
        << elapsedTime
        << " ms with n of "
        << n
        << endl;

  return elapsedTime;
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
        double elapsedTime;
        clock_t stopTime;
        clock_t startTime;

        startTime = clock();
        ComputePi( n );
        stopTime = clock();

        elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);

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

cParserWindow::cParserWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::cParserWindow)
{
   ui->setupUi(this);
   fqstrInputFileName = "";
}

cParserWindow::~cParserWindow()
{
   delete ui;
}

void cParserWindow::cboxWithLabelsClicked( bool Value )
{
   fParser.SetLabelResults( Value );
   if( fqstrInputFileName != "" )
   {
      ParseFile();
   }
}

void cParserWindow::btnCopyResultsToClipboardClicked()
{
   CopyResultsToClipboard();
}

void cParserWindow::CopyResultsToClipboard()
{
   ui->plainTextEdit_Output->selectAll();
   ui->plainTextEdit_Output->copy();
   ui->statusBar->showMessage( "Results have been copied to the clipboard.", 10000 );
}

void cParserWindow::btnAllClicked()
{
   ui->cbox64bitIntegerMath->setChecked( true );
   ui->cboxAES->setChecked( true );
   ui->cboxDhrystone->setChecked( true );
   ui->cboxDoubleMath->setChecked( true );
   ui->cboxFft->setChecked( true );
   ui->cboxFibonacci->setChecked( true );
   ui->cboxFlops->setChecked( true );
   ui->cboxHeapSort->setChecked( true );
   ui->cboxIntegerMath->setChecked( true );
   ui->cboxIntegerMatrixMul->setChecked( true );
   ui->cboxIO->setChecked( true );
   ui->cboxLinpack->setChecked( true );
   ui->cboxMemoryBandwidth->setChecked( true );
   ui->cboxMemoryLatency->setChecked( true );
   ui->cboxPi->setChecked( true );
   ui->cboxQueens->setChecked( true );
   ui->cboxSHA1->setChecked( true );
   ui->cboxSHA256->setChecked( true );
   ui->cboxSieve->setChecked( true );
   ui->cboxStringConcatenation->setChecked( true );
   ui->cboxTrig->setChecked( true );
   ui->cboxWhetstone->setChecked( true );
}

void cParserWindow::btnNoneClicked()
{
   ui->cbox64bitIntegerMath->setChecked( false );
   ui->cboxAES->setChecked( false );
   ui->cboxDhrystone->setChecked( false );
   ui->cboxDoubleMath->setChecked( false );
   ui->cboxFft->setChecked( false );
   ui->cboxFibonacci->setChecked( false );
   ui->cboxFlops->setChecked( false );
   ui->cboxHeapSort->setChecked( false );
   ui->cboxIntegerMath->setChecked( false );
   ui->cboxIntegerMatrixMul->setChecked( false );
   ui->cboxIO->setChecked( false );
   ui->cboxLinpack->setChecked( false );
   ui->cboxMemoryBandwidth->setChecked( false );
   ui->cboxMemoryLatency->setChecked( false );
   ui->cboxPi->setChecked( false );
   ui->cboxQueens->setChecked( false );
   ui->cboxSHA1->setChecked( false );
   ui->cboxSHA256->setChecked( false );
   ui->cboxSieve->setChecked( false );
   ui->cboxStringConcatenation->setChecked( false );
   ui->cboxTrig->setChecked( false );
   ui->cboxWhetstone->setChecked( false );
}

void cParserWindow::StatusBarUpdate( QString aStatusMessage )
{
   ui->statusBar->showMessage( aStatusMessage, 15000 );
   cerr << aStatusMessage.toStdString() << endl;
   QApplication::processEvents();
}

void cParserWindow::OutputSeconds(double adoubleResult, QString aOutputMessage )
{
   QString lqstrResult;
   lqstrResult.setNum( adoubleResult / 1000, 'g', 4 );
   ui->plainTextEdit_Output->appendPlainText( aOutputMessage + lqstrResult );
   QApplication::processEvents();
}

void cParserWindow::OutputRaw(double adoubleResult, QString aOutputMessage )
{
   QString lqstrResult;
   lqstrResult.setNum( adoubleResult, 'g', 4 );
   ui->plainTextEdit_Output->appendPlainText( aOutputMessage + lqstrResult );
   QApplication::processEvents();
}

void cParserWindow::RunTests()
{
   if( ui->cboxAES->isChecked( ) )
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

   if( ui->cboxDhrystone->isChecked( ) )
   {
      StatusBarUpdate( "Running Dhrystone..." );
      CDhryApp dhry( 20000000 );
      OutputSeconds( dhry.RunTest( 20000000 ), "Dhrystone (s): " );
   }

   if( ui->cboxDoubleMath->isChecked( ) )
   {
      StatusBarUpdate( "Running Double Arithmetic..." );
      OutputSeconds( doubleArithmetic( 10000000000.0, 11000000000.0 ), "Double Arithmetic (s): " );
   }

   if( ui->cboxFibonacci->isChecked( ) )
   {
      StatusBarUpdate( "Running Fibonacci( 42 )..." );
      OutputSeconds( FibTest( 42 ), "Fib(42) (s): " );
   }

   if( ui->cboxFlops->isChecked( ) )
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

   if( ui->cboxFft->isChecked( ) )
   {
      StatusBarUpdate( "Running FFT..." );
      OutputSeconds( fftTest( 1 ), "FFT (s): " );
   }

   if( ui->cboxHeapSort->isChecked( ) )
   {
      StatusBarUpdate( "Running Heap Sort..." );
      OutputSeconds( HeapSortTest( 5000000 ), "Heap Sort (s): " );
   }

   if( ui->cboxIntegerMath->isChecked( ) )
   {
      StatusBarUpdate( "Running Integer Arithmetic..." );
      OutputSeconds( intArithmetic( 1000000000 ), "Integer Arithmetic (s): " );
   }

   if( ui->cbox64bitIntegerMath->isChecked( ) )
   {
      StatusBarUpdate( "Running 64-bit Arithmetic..." );
      OutputSeconds( longArithmetic( 10000000000, 11000000000 ), "64-bit Arithmetic (s): " );
   }
   if( ui->cboxIntegerMatrixMul->isChecked( ) )
   {
      StatusBarUpdate( "Running Integer Matrix Multiplication..." );
      OutputSeconds( IntegerMatrixMultiplication( 1 ), "Integer Matrix Multiplication (s): " );
   }

   if( ui->cboxIO->isChecked( ) )
   {
      StatusBarUpdate( "Running I/O..." );
      OutputSeconds( io( 10000000 ), "I/O (s): " );
   }

   if( ui->cboxLinpack->isChecked( ) )
   {
      cLinpack lLinpack;

      StatusBarUpdate( "Running Linpack rolled..." );
      lLinpack.runBenchmark();
      OutputRaw( lLinpack.getFlops(), "LinPack rolled (FLOPS): " );

      StatusBarUpdate( "Running Linpack unrolled..." );
      lLinpack.setRolling( eUnrolled );
      lLinpack.runBenchmark();
      OutputRaw( lLinpack.getFlops(), "LinPack unrolled (FLOPS): " );
   }

   if( ui->cboxMemoryBandwidth->isChecked( ) )
   {
      StatusBarUpdate( "Memory Bandwidth Integer Write (MB/s): " );
      OutputRaw( BandwidthIntegerWrite( 2000000 ), "Memory Bandwidth Integer Write (MB/s): " );

      StatusBarUpdate( "Memory Bandwidth MemCpy (MB/s): " );
      OutputRaw( BandwidthMemCpy( 2000000 ), "Memory Bandwidth MemCpy (MB/s): " );

      StatusBarUpdate( "Memory Bandwidth Double Copy (MB/s): " );
      OutputRaw( BandwidthDoubleCopy( 2000000 ), "Memory Bandwidth Double Copy (MB/s): " );
   }

   if( ui->cboxMemoryLatency->isChecked( ) )
   {
      StatusBarUpdate( "Memory Latency Random Assignment (MB/s): " );
      OutputRaw( RandomAssignment( 2000000 ), "Memory Latency Random Assignment (MB/s): " );
   }

   if( ui->cboxPi->isChecked( ) )
   {
      StatusBarUpdate( "Running Pi( 10,000 )..." );
      OutputSeconds( PiTest( 10000 ), "Pi to 10,000 digits (s): " );
   }

   if( ui->cboxQueens->isChecked( ) )
   {
      StatusBarUpdate( "Running Queens..." );
      CQueenApp queenApp;
      OutputSeconds( queenApp.RunTest(25000), "Queens (s): " );
   }

   if( ui->cboxSHA1->isChecked( ) )
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

   if( ui->cboxSHA256->isChecked( ) )
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

   if( ui->cboxSieve->isChecked( ) )
   {
      StatusBarUpdate( "Sieve..." );
      OutputSeconds( Sieve( 50000 ), "Sieve (s): " );
   }

   if( ui->cboxStringConcatenation->isChecked( ) )
   {
      StatusBarUpdate( "String Concatenation..." );
      OutputSeconds( StringConcatenation( 40000000 ), "String Concatenation (s): " );
   }

   if( ui->cboxTrig->isChecked( ) )
   {
      StatusBarUpdate( "Running Trig..." );
      OutputSeconds( trig( 10000000 ), "Trig (s): " );
   }

   if( ui->cboxWhetstone->isChecked( ) )
   {
      StatusBarUpdate( "Running Whetstone..." );
      CWhetApp whet;
      OutputSeconds( whet.RunTest( 50000 ), "Whetstone (s): " );
   }

   StatusBarUpdate( "All tests finished!" );
}

void cParserWindow::btnRunTestClicked()
{
   QString lqsI;
   QString lqsIterations;
   int liIterations = ui->spinBox_Iterations->value();
   QApplication::setOverrideCursor(Qt::WaitCursor);
   lqsIterations.setNum(liIterations);
   for( int i = 1; i <= liIterations; i++)
   {
      lqsI.setNum(i);
      ui->plainTextEdit_Output->appendPlainText( "*****************************************************" );
      ui->plainTextEdit_Output->appendPlainText( "Executing iteration " + lqsI + " of " + lqsIterations);
      QApplication::processEvents();
      RunTests();
      ui->plainTextEdit_Output->appendPlainText( "*****************************************************" );
      QApplication::processEvents();
   }
   CopyResultsToClipboard();
   ui->pushButton_CopyResultsToClipboard->setEnabled( true );
   QApplication::restoreOverrideCursor();
}

void cParserWindow::btnOpenFileHandler()
{
   QString lqstrSaveFileName;
   lqstrSaveFileName = QFileDialog::getSaveFileName(this,
                      tr("Save benchmark results file"), "",
                      tr("text file (*.txt)"));
   QFile file( lqstrSaveFileName );
   if (!file.open(QFile::WriteOnly | QFile::Text))
   {
      QMessageBox::warning(this, tr("Application"),
                           tr("Cannot write file %1:\n%2.")
                           .arg(lqstrSaveFileName)
                           .arg(file.errorString()));
   }
   QTextStream out(&file);
   QApplication::setOverrideCursor(Qt::WaitCursor);
   out << ui->plainTextEdit_Output->toPlainText();
   QApplication::restoreOverrideCursor();
   file.close();
   StatusBarUpdate("File saved!");
}

void cParserWindow::ParseFile()
{
   QApplication::setOverrideCursor(Qt::WaitCursor);
   ui->plainTextEdit_Output->setPlainText(
         fParser.ParseInputFile( fqstrInputFileName ) );
   //ui->plainTextEdit_Input->setPlainText( fParser.GetInputString() );
   CopyResultsToClipboard();
   ui->pushButton_CopyResultsToClipboard->setEnabled( true );
   QApplication::restoreOverrideCursor();
}

cTest::cTest(int aIterations)
{
  fIterations = aIterations;
  cerr << "constructor called for "
       << fIterations
       << " iterations."
       << endl;
};

cTest::~cTest()
{
  cerr << "destructor called" << endl;
};



Enumeration Func_1( Capital_Letter Ch_1_Par_Val,  Capital_Letter Ch_2_Par_Val, char  * Ch_1_Glob)
{
        Capital_Letter        Ch_1_Loc=' ';
        Capital_Letter        Ch_2_Loc=' ';

        Ch_1_Loc = Ch_1_Par_Val;
        Ch_2_Loc = Ch_1_Loc;
        if (Ch_2_Loc != Ch_2_Par_Val)
        {
                /* then, executed */
                return (Ident_1);
        }
        else  /* not executed */
        {
                *Ch_1_Glob = Ch_1_Loc;
                return (Ident_2);
    }
} /* Func_1 */

bool Func_3 (Enumeration Enum_Par_Val)

{
        Enumeration Enum_Loc;

        Enum_Loc = Enum_Par_Val;
        if (Enum_Loc == Ident_3)
                /* then, executed */
                return (true);
        else /* not executed */
                return (false);
} /* Func_3 */


void Proc_6 (Enumeration Enum_Val_Par, Enumeration *Enum_Ref_Par, long * long_Glob)
/*********************************/
/* executed once */
/* Enum_Val_Par == Ident_3, Enum_Ref_Par becomes Ident_2 */

//Enumeration  Enum_Val_Par;
//Enumeration *Enum_Ref_Par;
{
        *Enum_Ref_Par = Enum_Val_Par;
        if (! Func_3 (Enum_Val_Par))
                /* then, not executed */
                *Enum_Ref_Par = Ident_4;
        switch (Enum_Val_Par)
        {
        case Ident_1:
                *Enum_Ref_Par = Ident_1;
                break;
        case Ident_2:
                if (*long_Glob > 100) //opriginally 100
                        /* then */
                        *Enum_Ref_Par = Ident_1;
                else *Enum_Ref_Par = Ident_4;
                break;
        case Ident_3: /* executed */
                *Enum_Ref_Par = Ident_2;
                break;
        case Ident_4: break;
        case Ident_5:
                *Enum_Ref_Par = Ident_3;
                break;
        } /* switch */
} /* Proc_6 */


void Proc_7 ( One_Fifty long_1_Par_Val,  One_Fifty long_2_Par_Val,  One_Fifty *long_Par_Ref)
/**********************************************/
/* executed three _ftime                                      */
/* first call:      long_1_Par_Val == 2, long_2_Par_Val == 3,  */
/*                  long_Par_Ref becomes 7                    */
/* second call:     long_1_Par_Val == 10, long_2_Par_Val == 5, */
/*                  long_Par_Ref becomes 17                   */
/* third call:      long_1_Par_Val == 6, long_2_Par_Val == 10, */
/*                  long_Par_Ref becomes 18                   */
{
        One_Fifty long_Loc;

        long_Loc = long_1_Par_Val + 2;
        *long_Par_Ref = long_2_Par_Val + long_Loc;
} /* Proc_7 */


void Proc_8 (Arr_1_Dim Arr_1_Par_Ref, Arr_2_Dim Arr_2_Par_Ref,   long long_1_Par_Val,   long long_2_Par_Val, long * long_Glob)
/*********************************************************************/
/* executed once      */
/* long_Par_Val_1 == 3 */
/* long_Par_Val_2 == 7 */
{
        REG One_Fifty long_Index=0;
        REG One_Fifty long_Loc=0;

        long_Loc = long_1_Par_Val + 5;
        Arr_1_Par_Ref [long_Loc] = long_2_Par_Val;
        Arr_1_Par_Ref [long_Loc+1] = Arr_1_Par_Ref [long_Loc];
        Arr_1_Par_Ref [long_Loc+30] = long_Loc;
        for (long_Index = long_Loc; long_Index <= long_Loc+1; ++long_Index)
                Arr_2_Par_Ref[long_Loc][long_Index] = long_Loc;
        Arr_2_Par_Ref[long_Loc][long_Loc-1]+=1;
        Arr_2_Par_Ref[long_Loc+20][long_Loc]=Arr_1_Par_Ref[long_Loc];
        *long_Glob = 5;
} /* Proc_8 */





bool Func_2 ( Str_30 Str_1_Par_Ref,  Str_30 Str_2_Par_Ref, char * Ch_1_Glob, long * long_Glob)
/*************************************************/
/* executed once */
/* Str_1_Par_Ref == "DHRYSTONE PROGRAM, 1'ST STRING" */
/* Str_2_Par_Ref == "DHRYSTONE PROGRAM, 2'ND STRING" */

//  Str_30 Str_1_Par_Ref;
//Str_30  Str_2_Par_Ref;
{
        REG One_Thirty        long_Loc=0;
        Capital_Letter    Ch_Loc=' ';

        long_Loc = 2;
        while (long_Loc <= 2) /* loop body executed once */
                if (Func_1 (Str_1_Par_Ref[long_Loc],
                        Str_2_Par_Ref[long_Loc+1], Ch_1_Glob) == Ident_1)
                        /* then, executed */
                {
                        Ch_Loc = 'A';
                        long_Loc += 1;
                } /* if, while */
                if (Ch_Loc >= 'W' && Ch_Loc < 'Z')
                        /* then, not executed */
                        long_Loc = 7;
                if (Ch_Loc == 'R')
                        /* then, not executed */
                        return (true);
                else /* executed */
                {
                        if (strcmp (Str_1_Par_Ref, Str_2_Par_Ref) > 0)
                                /* then, not executed */
                        {
                                long_Loc += 7;
                                *long_Glob = long_Loc;
                                return (true);
                        }
                        else /* executed */
                                return (false);
                } /* if Ch_Loc */
} /* Func_2 */



// Begin CLIBENCH DHRYSTONE
  /*
  ****************************************************************************
  *
  *                   "DHRYSTONE" Benchmark Program
  *
  *
  *  Version:    C, Version 2.1
  *
  *  File:       dhry_1.c (part 2 of 3)
  *
  *  Date:       May 25, 1988
  *
  *  Author:     Reinhold P. Weicker
  *
  ****************************************************************************
*/




/* end of variables for time measurement */

void Proc_5 (bool * Bool_Glob, char * Ch_1_Glob) /* without parameters */
/*******/
/* executed once */
{
        *Ch_1_Glob = 'A';
        *Bool_Glob = false;
} /* Proc_5 */

void Proc_4 (bool * Bool_Glob, char * Ch_1_Glob, char * Ch_2_Glob) /* without parameters */
/*******/
/* executed once */
{
        bool Bool_Loc;

        Bool_Loc = *Ch_1_Glob == 'A';
        *Bool_Glob = Bool_Loc | *Bool_Glob;
        *Ch_2_Glob = 'B';
} /* Proc_4*/


void Proc_3 (Rec_Polonger Ptr_Ref_Par, Rec_Polonger Ptr_Glob, long * long_Glob)
/******************/
/* executed once */
/* Ptr_Ref_Par becomes Ptr_Glob */

//Rec_Polonger *Ptr_Ref_Par;

{
        if (Ptr_Glob != Null)
                /* then, executed */
                Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
        Proc_7 (10, (long) long_Glob, &Ptr_Glob->variant.var_1.long_Comp);
} /* Proc_3 */


void Proc_2 (One_Fifty long_Par_Ref, char * Ch_1_Glob, long * long_Glob)
/******************/
/* executed once */
/* *long_Par_Ref == 1, becomes 4 */

//One_Fifty   *long_Par_Ref;
{
        One_Fifty  long_Loc;
        Enumeration   Enum_Loc;

        long_Loc = long_Par_Ref + 10;
        do /* executed once */
        if (*Ch_1_Glob == 'A')
                /* then, executed */
        {
                long_Loc  = 1;
                long_Par_Ref = long_Loc - *long_Glob;
                Enum_Loc = Ident_1;
        } /* if */
        while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */


void Proc_1 (REG Rec_Polonger Ptr_Val_Par, Rec_Polonger Ptr_Glob, long * long_Glob)
/******************/

// Ptr_Val_Par;
/* executed once */
{
        REG Rec_Polonger Next_Record = Ptr_Val_Par ->Ptr_Comp;
        /* == Ptr_Glob_Next */
        /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
        /* corresponds to "rename" in Ada, "with" in Pascal           */

        structassign (*Ptr_Val_Par ->Ptr_Comp, *Ptr_Glob);
        Ptr_Val_Par ->variant.var_1.long_Comp = 5;
        Next_Record ->variant.var_1.long_Comp
                = Ptr_Val_Par ->variant.var_1.long_Comp;
        Next_Record->Ptr_Comp = Ptr_Val_Par ->Ptr_Comp;
        Proc_3 (Next_Record ->Ptr_Comp, Ptr_Glob, long_Glob);
        /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp
        == Ptr_Glob->Ptr_Comp */
        if (Next_Record ->Discr == Ident_1)
                /* then, executed */
        {
                Next_Record ->variant.var_1.long_Comp = 6;
                Proc_6 (Ptr_Val_Par ->variant.var_1.Enum_Comp,
                        &Next_Record->variant.var_1.Enum_Comp, long_Glob);
                Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
                Proc_7 (Next_Record->variant.var_1.long_Comp, 10,
                        &Next_Record->variant.var_1.long_Comp);
        }
        else /* not executed */
                structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */



long CDhryApp::main(long Number_Of_Runs)
{
        // Replaced all dynamic allocation for allocation
        // on the stack.  It is much faster and is less prone to
        // threads locking
        One_Fifty		_long_1_Loc, *long_1_Loc = &_long_1_Loc;
        One_Fifty       _long_2_Loc, *long_2_Loc = &_long_2_Loc;
        One_Fifty       _long_3_Loc, *long_3_Loc = &_long_3_Loc;
        char            _Ch_Index, *Ch_Index = &_Ch_Index;
        Enumeration     _Enum_Loc, *Enum_Loc = &_Enum_Loc;
        Str_30          Str_1_Loc;
        Str_30          Str_2_Loc;
        long			Run_Index;
        Rec_Type		_Ptr_Glob;
        Rec_Polonger    Ptr_Glob = &_Ptr_Glob;
        Rec_Type		_Next_Ptr_Glob;
        Rec_Polonger	Next_Ptr_Glob = &_Next_Ptr_Glob;
        long			_long_Glob, *long_Glob = &_long_Glob;
        bool            _Bool_Glob, *Bool_Glob = &_Bool_Glob;
        char            _Ch_1_Glob, *Ch_1_Glob = &_Ch_1_Glob;
        char			_Ch_2_Glob, *Ch_2_Glob = &_Ch_2_Glob;
        long			_Arr_1_Glob[100], *Arr_1_Glob = _Arr_1_Glob;
        long			_Arr_2_Glob[100][100], (*Arr_2_Glob)[100] = _Arr_2_Glob;

        *Str_1_Loc=' ';
        *Str_2_Loc=' ';
        Run_Index=0;

        int i=0;
        while (i<100)
        {
                Arr_1_Glob[i]=0;
                int j=0;
                while (j<100)
                {
                        Arr_2_Glob[i][j]=0; //originally this was 50
                        ++j;
                }
                ++i;
        }

        Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
        Ptr_Glob->Discr                       = Ident_1;
        Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
        Ptr_Glob->variant.var_1.long_Comp     = 40;
        *strcpy (Ptr_Glob ->variant.var_1.Str_Comp,
                "DHRYSTONE PROGRAM, SOME STRING");
        strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

        Arr_2_Glob [8][7] = 10;



        Run_Index=1;
        while (Run_Index<Number_Of_Runs)
        {
                ++Run_Index;
                Proc_5(Bool_Glob, Ch_1_Glob);
                Proc_4(Bool_Glob,Ch_1_Glob,Ch_2_Glob);
                *long_1_Loc = 2;
                *long_2_Loc = 3;
                strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
                *Enum_Loc = Ident_2;
                *Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc, Ch_1_Glob, long_Glob);

                while (*long_1_Loc < *long_2_Loc)
                {

                        *long_3_Loc = 5 * *long_1_Loc - *long_2_Loc;

                        Proc_7 (*long_1_Loc, *long_2_Loc, long_3_Loc);

                        *long_1_Loc += 1;
                }


                Proc_8 (Arr_1_Glob, Arr_2_Glob, *long_1_Loc, *long_3_Loc, long_Glob);

                Proc_1 (Ptr_Glob, Ptr_Glob, (long*) &long_Glob);
                for (*Ch_Index = 'A'; *Ch_Index <= *Ch_2_Glob; ++*Ch_Index)

                {
                        if (*Enum_Loc == Func_1 (*Ch_Index, 'C', Ch_1_Glob))

                        {
                                Proc_6 (Ident_1, Enum_Loc, long_Glob);
                                strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
                                *long_2_Loc = Run_Index;
                                *long_Glob = Run_Index;
                        }
                }


                *long_2_Loc = *long_2_Loc * *long_1_Loc;
                *long_1_Loc = *long_2_Loc / *long_3_Loc;
                *long_2_Loc = 7 * (*long_2_Loc - *long_3_Loc) - *long_1_Loc;

                Proc_2 (*long_1_Loc, Ch_1_Glob, long_Glob);


        }


        return (Number_Of_Runs);
}


double CDhryApp::RunTest( long Iterations )
{
  clock_t stopTime;
  clock_t startTime = clock();
  main( Iterations );
  stopTime = clock();
  double elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  cerr << "Elapsed time (ms) " << elapsedTime  << endl;
  double DhrystonePerSec = Iterations / ( elapsedTime / 1000);
  cout << "Dhrystone MIPS: " << DhrystonePerSec / 1757 << endl;
  return elapsedTime;
}

// END CLIBENCH DHRYSTONE

// Begin CLIBENCH WHETSTONE
void CWhetApp::pa(double e[4])
{
        register int j;

        j = 0;
lab:
        e[0] = (  e[0] + e[1] + e[2] - e[3] ) * t;
        e[1] = (  e[0] + e[1] - e[2] + e[3] ) * t;
        e[2] = (  e[0] - e[1] + e[2] + e[3] ) * t;
        e[3] = ( -e[0] + e[1] + e[2] + e[3] ) / t2;
        j += 1;
        if (j < 6)
                goto lab;
}

void CWhetApp::p3(double x, double y, double *z)
{
        x  = t * (x + y);
        y  = t * (x + y);
        *z = (x + y) /t2;
}

void CWhetApp::p0()
{
        e1[j] = e1[k];
        e1[k] = e1[l];
        e1[l] = e1[j];
}

/*////////pout(int n, int j, int k, double x1, double x2, double x3, double x4)
{
printf("%6.4u%6.4u%6.4u  %5.4u  %5.4u  %5.4u  %5.4u\n",
n, j, k, x1, x2, x3, x4);
}*/

long CWhetApp::main(long ITERATIONS)
{
//	struct _timeb start,ende;
//	_ftime(&start);
//	long dauer;

        /* initialize constants */

        t   =   0.499975;
        t1  =   0.50025;
        t2  =   2.0;

        /* set values of module weights */

        n1  =   0 * ITERATIONS;
        n2  =  12 * ITERATIONS;
        n3  =  14 * ITERATIONS;
        n4  = 345 * ITERATIONS;
        n6  = 210 * ITERATIONS;
        n7  =  32 * ITERATIONS;
        n8  = 899 * ITERATIONS;
        n9  = 616 * ITERATIONS;
        n10 =   0 * ITERATIONS;
        n11 =  93 * ITERATIONS;

        /* MODULE 1:  simple identifiers */

        x1 =  1.0;
        x2 = -1.0;
        x3 = -1.0;
        x4 = -1.0;

        ii=1;
        while (ii<(n1+1))
        {
                x1 = ( x1 + x2 + x3 - x4 ) * t;
                x2 = ( x1 + x2 - x3 - x4 ) * t;
                x3 = ( x1 - x2 + x3 + x4 ) * t;
                x4 = (-x1 + x2 + x3 + x4 ) * t;
                ++ii;
        }
        //////////pout(n1, n1, n1, x1, x2, x3, x4);


        /* MODULE 2:  array elements */

        e1[0] =  1.0;
        e1[1] = -1.0;
        e1[2] = -1.0;
        e1[3] = -1.0;

        ii=1;
        while (ii<(n2+1))
        {
                e1[0] = ( e1[0] + e1[1] + e1[2] - e1[3] ) * t;
                e1[1] = ( e1[0] + e1[1] - e1[2] + e1[3] ) * t;
                e1[2] = ( e1[0] - e1[1] + e1[2] + e1[3] ) * t;
                e1[3] = (-e1[0] + e1[1] + e1[2] + e1[3] ) * t;
                ++ii;
        }

        ////////pout(n2, n3, n2, e1[0], e1[1], e1[2], e1[3]);

        /* MODULE 3:  array as parameter */

        ii=1;
        while (ii<(n3+1))
        {
                pa(e1);
                ++ii;
        }
        ////////pout(n3, n2, n2, e1[0], e1[1], e1[2], e1[3]);


        /* MODULE 4:  conditional jumps */

        j = 1;
        ii=1;
        while (ii<(n4+1))
        {
                if (j == 1)
                        j = 2;
                else
                        j = 3;

                if (j > 2)
                        j = 0;
                else
                        j = 1;

                if (j < 1 )
                        j = 1;
                else
                        j = 0;
                ++ii;
        }

        ////////pout(n4, j, j, x1, x2, x3, x4);

        /* MODULE 5:  omitted */

        /* MODULE 6:  integer arithmetic */

        j = 1;
        k = 2;
        l = 3;
        ii=1;
        while (ii<(n6+1))
        {
                j = j * (k - j) * (l -k);
                k = l * k - (l - j) * k;
                l = (l - k) * (k + j);

                e1[l - 2] = j + k + l;		/* C arrays are zero based */
                e1[k - 2] = j * k * l;
                ++ii;
        }
        ////////pout(n6, j, k, e1[0], e1[1], e1[2], e1[3]);

        /* MODULE 7:  trig. functions */
        x = y = 0.5;
        ii=1;
        while (ii<(n7+1))
        {
                x = t * atan(t2*sin(x)*cos(x)/(cos(x+y)+cos(x-y)-1.0));
                y = t * atan(t2*sin(y)*cos(y)/(cos(x+y)+cos(x-y)-1.0));
                ++ii;
        }
        ////////pout(n7, j, k, x, x, y, y);


        /* MODULE 8:  procedure calls */
        x = y = z = 1.0;
        ii=1;
        while (ii<(n8+1))
        {
                p3(x, y, &z);
                ++ii;
        }
        ////////pout(n8, j, k, x, y, z, z);


        /* MODULE9:  array references */
        j = 1;
        k = 2;
        l = 3;

        e1[0] = 1.0;
        e1[1] = 2.0;
        e1[2] = 3.0;
        ii=1;
        while (ii<(n9+1))
        {
                p0();
                ++ii;
        }
        ////////pout(n9, j, k, e1[0], e1[1], e1[2], e1[3]);

        /* MODULE10:  integer arithmetic */
        j = 2;
        k = 3;
        ii=1;
        while (ii<(n10+1))
        {
                j = j + k;
                k = j + k;
                j = k - j;
                k = k - j - j;
                ++ii;
        }
        ////////pout(n10, j, k, x1, x2, x3, x4);

        /* MODULE11:  standard functions */
        x = 0.75;
        ii=1;
        while (ii<(n11+1))
        {
                x = sqrt( exp( log(x) / t1));
                ++ii;
        }
        ////////pout(n11, j, k, x, x, x, x);
//	_ftime(&ende); dauer=(ende.time-start.time)*1000+(ende.millitm-start.millitm);
        return (ITERATIONS);///(double(dauer)/100));
}

double CWhetApp::RunTest( long Iterations )
{
  clock_t stopTime;
  clock_t startTime = clock();
  main( Iterations );
  stopTime = clock();
  double elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  cerr << "Elapsed time (ms) " << elapsedTime  << endl;
  return elapsedTime;
}
// END CLIBENCH WHETSTONE


void CQueenApp::Attempt(int i)
{
        int j=1;
        while (j<9)
        {
                if ((a[j])&&(b[i+j])&&(c[i-j+7]))
                {
                        x[i]=j;
                        a[j]=false; b[i+j]=false; c[i-j+7]=false;
                        if (i<8) {Attempt(i+1);}
                        a[j]=true;b[i+j]=true;c[i-j+7]=true;
                }
        ++j;
        }
}


long CQueenApp::DoQueen(long Iterations)
{
        long loopCounter = 0;
        int i = 0;
        while( loopCounter < Iterations )
        {
                i=0;
                while (i<9) {a[i]=true;++i;}
                i=0;
                while (i<17) {b[i]=true;++i;}
                i=0;
                while (i<15) {c[i]=true;++i;}
                Attempt(1);
        ++loopCounter;
        }
        return (1);
}

double CQueenApp::RunTest( long Iterations )
{
  clock_t stopTime;
  clock_t startTime = clock();
  DoQueen( Iterations );
  stopTime = clock();
  double elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
  cerr << "Elapsed time (ms) " << elapsedTime  << endl;
  return elapsedTime;
}
