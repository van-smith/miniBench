#include "cFlops.h"
#define debug

cFlops::cFlops()
{
  cerr << "Constructor called." << endl;
} // cFlops::cFlops()

cFlops::~cFlops()
{
  cerr << "Destructor called." << endl;
}

double cFlops::runFpuFloatMulTest()
{
  vs2005align64 float x[ ARRAY_SIZE_SP ] gccAlign64;
  int liFlopCount = 0;
  sFlopsResult lFlopsResult;

  // initialize array
  for( int i = 0; i < ARRAY_SIZE_SP; i++ )
  {
    x[ i ] = 1.001f;
  } // for

#ifdef debug
  cerr << "Starting FPU SP multiplication test..." << endl;
  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
#endif

  clock_t endTime;
  clock_t startTime = clock();
  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
  {
    for( int i = 0; i < ARRAY_SIZE_SP - 1; i += 16 )
    {
      x[ i ]      *= 1.001f;
      x[ i + 1 ]  *= 1.001f;
      x[ i + 2 ]  *= 1.001f;
      x[ i + 3 ]  *= 1.001f;
      x[ i + 4 ]  *= 1.001f;
      x[ i + 5 ]  *= 1.001f;
      x[ i + 6 ]  *= 1.001f;
      x[ i + 7 ]  *= 1.001f;
      x[ i + 8 ]  *= 1.001f;
      x[ i + 9 ]  *= 1.001f;
      x[ i + 10 ] *= 1.001f;
      x[ i + 11 ] *= 1.001f;
      x[ i + 12 ] *= 1.001f;
      x[ i + 13 ] *= 1.001f;
      x[ i + 14 ] *= 1.001f;
      x[ i + 15 ] *= 1.001f;
    } // for
  } // for
  endTime = clock();

  liFlopCount = ARRAY_SIZE_SP * ITERATION_COUNT; 
  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;

#ifdef debug
  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
  cerr << endl << "FPU SP multiplication test took " << lFlopsResult.time << " seconds." << endl;
  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
#endif

  mFpuFloatMulResult = lFlopsResult;
  return mFpuFloatMulResult.mflops;
} // cFlops::runFpuFloatMulTest()

double cFlops::runFpuFloatDivTest()
{
  vs2005align64 float x[ ARRAY_SIZE_SP ] gccAlign64;
  int liFlopCount = 0;
  sFlopsResult lFlopsResult;

  // initialize array
  for( int i = 0; i < ARRAY_SIZE_SP; i++ )
  {
    x[ i ] = 1.001f;
  } // for

#ifdef debug
  cerr << "Starting FPU SP division test..." << endl;
  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
#endif

  clock_t endTime;
  clock_t startTime = clock();
  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
  {
    for( int i = 0; i < ARRAY_SIZE_SP - 1; i += 16 )
    {
      x[ i ]      /= 0.999f;
      x[ i + 1 ]  /= 0.999f;
      x[ i + 2 ]  /= 0.999f;
      x[ i + 3 ]  /= 0.999f;
      x[ i + 4 ]  /= 0.999f;
      x[ i + 5 ]  /= 0.999f;
      x[ i + 6 ]  /= 0.999f;
      x[ i + 7 ]  /= 0.999f;
      x[ i + 8 ]  /= 0.999f;
      x[ i + 9 ]  /= 0.999f;
      x[ i + 10 ] /= 0.999f;
      x[ i + 11 ] /= 0.999f;
      x[ i + 12 ] /= 0.999f;
      x[ i + 13 ] /= 0.999f;
      x[ i + 14 ] /= 0.999f;
      x[ i + 15 ] /= 0.999f;
    } // for
  } // for
  endTime = clock();

  liFlopCount = ARRAY_SIZE_SP * ITERATION_COUNT; 
  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;

#ifdef debug
  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
  cerr << endl << "FPU SP division test took " << lFlopsResult.time << " seconds." << endl;
  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
#endif
  mFpuFloatDivResult = lFlopsResult;
  return mFpuFloatDivResult.mflops;
} // double cFlops::runFpuFloatDivTest()

double cFlops::runFpuFloatAddTest()
{
  vs2005align64 float x[ ARRAY_SIZE_SP ] gccAlign64;
  int liFlopCount = 0;
  sFlopsResult lFlopsResult;

  // initialize array
  for( int i = 0; i < ARRAY_SIZE_SP; i++ )
  {
    x[ i ] = 1.001f;
  } // for

#ifdef debug
  cerr << "Starting FPU SP addition test..." << endl;
  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
#endif

  clock_t endTime;
  clock_t startTime = clock();
  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
  {
    for( int i = 0; i < ARRAY_SIZE_SP - 1; i += 16 )
    {
      x[ i ]      += 1.001f;
      x[ i + 1 ]  += 1.001f;
      x[ i + 2 ]  += 1.001f;
      x[ i + 3 ]  += 1.001f;
      x[ i + 4 ]  += 1.001f;
      x[ i + 5 ]  += 1.001f;
      x[ i + 6 ]  += 1.001f;
      x[ i + 7 ]  += 1.001f;
      x[ i + 8 ]  += 1.001f;
      x[ i + 9 ]  += 1.001f;
      x[ i + 10 ] += 1.001f;
      x[ i + 11 ] += 1.001f;
      x[ i + 12 ] += 1.001f;
      x[ i + 13 ] += 1.001f;
      x[ i + 14 ] += 1.001f;
      x[ i + 15 ] += 1.001f;
    } // for
  } // for
  endTime = clock();

  liFlopCount = ARRAY_SIZE_SP * ITERATION_COUNT; 
  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;

#ifdef debug
  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
  cerr << endl << "FPU SP addition test took " << lFlopsResult.time << " seconds." << endl;
  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
#endif
  mFpuFloatAddResult = lFlopsResult;
  return mFpuFloatAddResult.mflops;
} // double cFlops::runFpuFloatAddTest()

double cFlops::runFpuDoubleMulTest()
{
  vs2005align64 double x[ ARRAY_SIZE_DP ];
  int liFlopCount = 0;
  sFlopsResult lFlopsResult;

  // initialize array
  for( int i = 0; i < ARRAY_SIZE_DP; i++ )
  {
    x[ i ] = 1.001;
  } // for

#ifdef debug
  cerr << "Starting FPU DP multiplication test..." << endl;
  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
#endif

  clock_t endTime;
  clock_t startTime = clock();
  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
  {
    for( int i = 0; i < ARRAY_SIZE_DP - 1; i += 16 )
    {
      x[ i ]      *= 1.001;
      x[ i + 1 ]  *= 1.001;
      x[ i + 2 ]  *= 1.001;
      x[ i + 3 ]  *= 1.001;
      x[ i + 4 ]  *= 1.001;
      x[ i + 5 ]  *= 1.001;
      x[ i + 6 ]  *= 1.001;
      x[ i + 7 ]  *= 1.001;
      x[ i + 8 ]  *= 1.001;
      x[ i + 9 ]  *= 1.001;
      x[ i + 10 ] *= 1.001;
      x[ i + 11 ] *= 1.001;
      x[ i + 12 ] *= 1.001;
      x[ i + 13 ] *= 1.001;
      x[ i + 14 ] *= 1.001;
      x[ i + 15 ] *= 1.001;
    } // for
  } // for
  endTime = clock();

  liFlopCount += ARRAY_SIZE_DP * ITERATION_COUNT; 
  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;

#ifdef debug
  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
  cerr << endl << "FPU DP multiplication test took " << lFlopsResult.time << " seconds." << endl;
  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
#endif 
  mFpuDoubleMulResult = lFlopsResult;
  return mFpuDoubleMulResult.mflops;
} //   double cFlops::runFpuDoubleMulTest()

double cFlops::runFpuDoubleDivTest()
{
  vs2005align64 double x[ ARRAY_SIZE_DP ];
  int liFlopCount = 0;
  sFlopsResult lFlopsResult;

  // initialize array
  for( int i = 0; i < ARRAY_SIZE_DP; i++ )
  {
    x[ i ] = 1.001;
  } // for

#ifdef debug
  cerr << "Starting FPU DP division test..." << endl;
  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
#endif

  clock_t endTime;
  clock_t startTime = clock();
  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
  {
    for( int i = 0; i < ARRAY_SIZE_DP - 1; i += 16 )
    {
      x[ i ]      /= 1.001;
      x[ i + 1 ]  /= 1.001;
      x[ i + 2 ]  /= 1.001;
      x[ i + 3 ]  /= 1.001;
      x[ i + 4 ]  /= 1.001;
      x[ i + 5 ]  /= 1.001;
      x[ i + 6 ]  /= 1.001;
      x[ i + 7 ]  /= 1.001;
      x[ i + 8 ]  /= 1.001;
      x[ i + 9 ]  /= 1.001;
      x[ i + 10 ] /= 1.001;
      x[ i + 11 ] /= 1.001;
      x[ i + 12 ] /= 1.001;
      x[ i + 13 ] /= 1.001;
      x[ i + 14 ] /= 1.001;
      x[ i + 15 ] /= 1.001;
    } // for
  } // for
  endTime = clock();

  liFlopCount = ARRAY_SIZE_DP * ITERATION_COUNT; 
  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
  lFlopsResult.mflops = (double)liFlopCount / lFlopsResult.time / (double)ONE_MILLION;

#ifdef debug
  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
  cerr << endl << "FPU DP division test took " << lFlopsResult.time << " seconds." << endl;
  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
#endif
  mFpuDoubleDivResult =lFlopsResult;
  return mFpuDoubleDivResult.mflops;
} // double cFlops::runFpuDoubleDivTest()

double cFlops::runFpuDoubleAddTest()
{
  vs2005align64 double x[ ARRAY_SIZE_DP ];
  int liFlopCount = 0;
  sFlopsResult lFlopsResult;

  // initialize array
  for( int i = 0; i < ARRAY_SIZE_DP; i++ )
  {
    x[ i ] = 1.001;
  } // for

#ifdef debug
  cerr << "Starting FPU DP add test..." << endl;
  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
#endif

  clock_t endTime;
  clock_t startTime = clock();
  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
  {
    for( int i = 0; i < ARRAY_SIZE_DP - 1; i += 16 )
    {
      x[ i ]      += 1.001;
      x[ i + 1 ]  += 1.001;
      x[ i + 2 ]  += 1.001;
      x[ i + 3 ]  += 1.001;
      x[ i + 4 ]  += 1.001;
      x[ i + 5 ]  += 1.001;
      x[ i + 6 ]  += 1.001;
      x[ i + 7 ]  += 1.001;
      x[ i + 8 ]  += 1.001;
      x[ i + 9 ]  += 1.001;
      x[ i + 10 ] += 1.001;
      x[ i + 11 ] += 1.001;
      x[ i + 12 ] += 1.001;
      x[ i + 13 ] += 1.001;
      x[ i + 14 ] += 1.001;
      x[ i + 15 ] += 1.001;
    } // for
  } // for
  endTime = clock();

  liFlopCount += ARRAY_SIZE_DP * ITERATION_COUNT; 
  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;

#ifdef debug
  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
  for( int i = 0; i < 10; i++ )
  {
    cerr << x[ i ] << endl;
  } // for
  cerr << endl << "FPU DP add test took " << lFlopsResult.time << " seconds." << endl;
  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
#endif
  mFpuDoubleAddResult = lFlopsResult;
  return mFpuDoubleAddResult.mflops;
} // double cFlops::runFpuDoubleAddTest()

//double cFlops::runSseFloatAddTest()
//{
//  vs2005align64 sVectorFloat x[ ARRAY_SIZE_VF ] gccAlign64;
//  vs2005align64 sVectorFloat lvfAddValue gccAlign64;
//  sFlopsResult lFlopsResult;
//  int liOffset;
//  int liFlopCount = 0;
//
//  lvfAddValue.s0 = 1.001f;
//  lvfAddValue.s1 = 1.001f;
//  lvfAddValue.s2 = 1.001f;
//  lvfAddValue.s3 = 1.001f;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VF; i ++ )
//  {
//    x[ i ] = lvfAddValue;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE SP addition test..." << endl;
//  cerr << endl << "Here are the first twelve elements of the array before test:" << endl;
//  for( int i = 0; i < 3; i ++ )
//  {
//    cerr << x[ i ].s0 << endl;
//    cerr << x[ i ].s1 << endl;
//    cerr << x[ i ].s2 << endl;
//    cerr << x[ i ].s3 << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VF - 1; i += 4 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, lvfAddValue
//
//        lea     eax, x
//        add     eax, liOffset
//        movaps  xmm1, [eax]
//        addps   xmm1, xmm0
//        movaps  [eax], xmm1
//
//        add     eax, 16
//        movaps  xmm1, [eax]
//        addps   xmm1, xmm0
//        movaps  [eax], xmm1
//
//        add     eax, 16
//        movaps  xmm1, [eax]
//        addps   xmm1, xmm0
//        movaps  [eax], xmm1
//
//        add     eax, 16
//        movaps  xmm1, [eax]
//        addps   xmm1, xmm0
//        movaps  [eax], xmm1
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VF * ITERATION_COUNT * 4;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first twelve elements of the array after test:" << endl;
//  for( int i = 0; i < 3; i ++ )
//  {
//    cerr << x[ i ].s0 << endl;
//    cerr << x[ i ].s1 << endl;
//    cerr << x[ i ].s2 << endl;
//    cerr << x[ i ].s3 << endl;
//  } // for
//  cerr << endl << "SSE SP addition test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//
//  mSseFloatAddResult = lFlopsResult;
//  return mSseFloatAddResult;
//} // double cFlops::runSseFloatAddTest()
//
//double cFlops::runSseFloatDivTest()
//{
//  vs2005align64 sVectorFloat x[ ARRAY_SIZE_VF ] gccAlign64;
//  vs2005align64 sVectorFloat lvfAddValue gccAlign64;
//  sFlopsResult lFlopsResult;
//  int liOffset;
//  int liFlopCount = 0;
//
//  lvfAddValue.s0 = 0.99999f;
//  lvfAddValue.s1 = 0.99999f;
//  lvfAddValue.s2 = 0.99999f;
//  lvfAddValue.s3 = 0.99999f;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VF; i ++ )
//  {
//    x[ i ] = lvfAddValue;
//  } // for
//
//#ifdef debug
//  cerr << endl << "SSE SP division test..." << endl;
//  cerr << endl << "Here are the first twelve elements of the array before test:" << endl;
//  for( int i = 0; i < 3; i ++ )
//  {
//    cerr << x[ i ].s0 << endl;
//    cerr << x[ i ].s1 << endl;
//    cerr << x[ i ].s2 << endl;
//    cerr << x[ i ].s3 << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VF - 1; i += 4 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, lvfAddValue
//
//        lea     eax, x
//        add     eax, liOffset
//        movaps  xmm1, [eax]
//        divps   xmm1, xmm0
//        movaps  [eax], xmm1
//
//        add     eax, 16
//        movaps  xmm1, [eax]
//        divps   xmm1, xmm0
//        movaps  [eax], xmm1
//
//        add     eax, 16
//        movaps  xmm1, [eax]
//        divps   xmm1, xmm0
//        movaps  [eax], xmm1
//
//        add     eax, 16
//        movaps  xmm1, [eax]
//        divps   xmm1, xmm0
//        movaps  [eax], xmm1
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VF * ITERATION_COUNT * 4;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first twelve elements of the array after test:" << endl;
//  for( int i = 0; i < 3; i ++ )
//  {
//    cerr << x[ i ].s0 << endl;
//    cerr << x[ i ].s1 << endl;
//    cerr << x[ i ].s2 << endl;
//    cerr << x[ i ].s3 << endl;
//  } // for
//  cerr << endl << "SSE SP division test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//
//  mSseFloatDivResult = lFlopsResult;
//  return mSseFloatDivResult;
//} // double cFlops::runSseFloatDivTest()
//
//double cFlops::runSseFloatMulTest()
//{
//  vs2005align64 sVectorFloat x[ ARRAY_SIZE_VF ] gccAlign64;
//  vs2005align64 sVectorFloat lvfAddValue gccAlign64;
//  sFlopsResult lFlopsResult;
//  int liOffset;
//  int liFlopCount = 0;
//
//  lvfAddValue.s0 = 1.00001f;
//  lvfAddValue.s1 = 1.00001f;
//  lvfAddValue.s2 = 1.00001f;
//  lvfAddValue.s3 = 1.00001f;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VF; i ++ )
//  {
//    x[ i ] = lvfAddValue;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE SP multiplication test..." << endl;
//  cerr << endl << "Here are the first twelve elements of the array before test:" << endl;
//  for( int i = 0; i < 3; i ++ )
//  {
//    cerr << x[ i ].s0 << endl;
//    cerr << x[ i ].s1 << endl;
//    cerr << x[ i ].s2 << endl;
//    cerr << x[ i ].s3 << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VF - 1; i += 4 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, lvfAddValue
//
//        lea     eax, x
//        add     eax, liOffset
//        movaps  xmm1, [eax]
//        mulps   xmm1, xmm0
//        movaps  [eax], xmm1
//
//        add     eax, 16
//        movaps  xmm1, [eax]
//        mulps   xmm1, xmm0
//        movaps  [eax], xmm1
//
//        add     eax, 16
//        movaps  xmm1, [eax]
//        mulps   xmm1, xmm0
//        movaps  [eax], xmm1
//
//        add     eax, 16
//        movaps  xmm1, [eax]
//        mulps   xmm1, xmm0
//        movaps  [eax], xmm1
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VF * ITERATION_COUNT * 4;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first twelve elements of the array after test:" << endl;
//  for( int i = 0; i < 3; i ++ )
//  {
//    cerr << x[ i ].s0 << endl;
//    cerr << x[ i ].s1 << endl;
//    cerr << x[ i ].s2 << endl;
//    cerr << x[ i ].s3 << endl;
//  } // for
//  cerr << endl << "SSE SP multiplication test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//
//  mSseFloatMulResult = lFlopsResult;
//  return mSseFloatMulResult;
//} // double::runSseFloatMulTest()
//
//sFlopsResult cFlops::runSseFloatMulAddTest()
//{
//  // x = a * x + b
//  // y = a * y + b
//  int liArraySize = ARRAY_SIZE_VF2;
//  vs2005align64 sVectorFloat x[ ARRAY_SIZE_VF2 ] gccAlign64;
//  vs2005align64 sVectorFloat y[ ARRAY_SIZE_VF2 ] gccAlign64;
//  vs2005align64 sVectorFloat a gccAlign64;
//  vs2005align64 sVectorFloat b gccAlign64;
//  sFlopsResult lFlopsResult;
//  int liOffset;
//  int liFlopCount = 0;
//
//  a.s0 = 1.001f;
//  a.s1 = 1.001f;
//  a.s2 = 1.001f;
//  a.s3 = 1.001f;
//  b.s0 = 0.999f;
//  b.s1 = 0.999f;
//  b.s2 = 0.999f;
//  b.s3 = 0.999f;
//  // initialize array
//  for( int i = 0; i < liArraySize; i ++ )
//  {
//    x[ i ] = a;
//    y[ i ] = b;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE SP mul-add test..." << endl;
//  cerr << endl << "Here are the first twelve elements of the array before test:" << endl;
//  for( int i = 0; i < 3; i ++ )
//  {
//    cerr << x[ i ].s0 << endl;
//    cerr << x[ i ].s1 << endl;
//    cerr << x[ i ].s2 << endl;
//    cerr << x[ i ].s3 << endl;
//    cerr << y[ i ].s0 << endl;
//    cerr << y[ i ].s1 << endl;
//    cerr << y[ i ].s2 << endl;
//    cerr << y[ i ].s3 << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < liArraySize - 1; i += 4 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, a
//        movaps  xmm1, b
//
//        lea     eax, x
//        add     eax, liOffset
//        movaps  xmm2, [eax]
//        mulps   xmm2, xmm0
//        lea     ebx, y
//        add     ebx, liOffset
//        movaps  xmm3, [ebx]
//        addps   xmm3, xmm0
//        mulps   xmm2, xmm1
//        mulps   xmm3, xmm1
//        movaps  [eax], xmm2
//        movaps  [ebx], xmm3
//
//        add     eax, 16
//        movaps  xmm2, [eax]
//        mulps   xmm2, xmm0
//        add     ebx, 16
//        movaps  xmm3, [ebx]
//        addps   xmm3, xmm0
//        mulps   xmm2, xmm1
//        mulps   xmm3, xmm1
//        movaps  [eax], xmm2
//        movaps  [ebx], xmm3
//
//        add     eax, 16
//        movaps  xmm2, [eax]
//        mulps   xmm2, xmm0
//        add     ebx, 16
//        movaps  xmm3, [ebx]
//        addps   xmm3, xmm0
//        mulps   xmm2, xmm1
//        mulps   xmm3, xmm1
//        movaps  [eax], xmm2
//        movaps  [ebx], xmm3
//
//        add     eax, 16
//        movaps  xmm2, [eax]
//        mulps   xmm2, xmm0
//        add     ebx, 16
//        movaps  xmm3, [ebx]
//        addps   xmm3, xmm0
//        mulps   xmm2, xmm1
//        mulps   xmm3, xmm1
//        movaps  [eax], xmm2
//        movaps  [ebx], xmm3
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = liArraySize * ITERATION_COUNT * 16;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first twelve elements of the array after test:" << endl;
//  for( int i = 0; i < 3; i ++ )
//  {
//    cerr << x[ i ].s0 << endl;
//    cerr << x[ i ].s1 << endl;
//    cerr << x[ i ].s2 << endl;
//    cerr << x[ i ].s3 << endl;
//    cerr << y[ i ].s0 << endl;
//    cerr << y[ i ].s1 << endl;
//    cerr << y[ i ].s2 << endl;
//    cerr << y[ i ].s3 << endl;
//  } // for
//  cerr << endl << "SSE SP mul-add test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//
//  mSseFloatMulAddResult = lFlopsResult;
//  return mSseFloatMulAddResult;
//} // sFlopsResult cFlops::runSseFloatMulAddTest()
//
//sFlopsResult cFlops::runSse2DoubleAddTest()
//{
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD ] gccAlign64;
//  vs2005align64 sVectorDouble lvAddValue gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  lvAddValue.x = 1.001;
//  lvAddValue.y = 1.001;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VD; i++ )
//  {
//    x[ i ] = lvAddValue;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP addition test..." << endl;
//  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VD - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, lvAddValue
//
//        lea     eax, x
//        add     eax, liOffset
//        movapd  xmm1, [eax]
//        addpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        addpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        addpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        addpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        addpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        addpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        addpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        addpd   xmm1, xmm0
//        movapd  [eax], xmm1
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VD * ITERATION_COUNT * 2;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Double precision SSE2 addition test took " << mSse2DoubleAddResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << mSse2DoubleAddResult.mflops << endl;
//#endif
//  mSse2DoubleAddResult = lFlopsResult;
//  return mSse2DoubleAddResult;
//} // sFlopsResult cFlops::runSse2DoubleAddTest()
//
//sFlopsResult cFlops::runSse2DoubleMulTest()
//{
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD ] gccAlign64;
//  vs2005align64 sVectorDouble lvAddValue gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  lvAddValue.x = 1.001;
//  lvAddValue.y = 1.001;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VD; i++ )
//  {
//    x[ i ] = lvAddValue;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP multiplication test..." << endl;
//  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VD - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, lvAddValue
//
//        lea     eax, x
//        add     eax, liOffset
//        movapd  xmm1, [eax]
//        mulpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        mulpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        mulpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        mulpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        mulpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        mulpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        mulpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        mulpd   xmm1, xmm0
//        movapd  [eax], xmm1
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VD * ITERATION_COUNT * 2;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Double precision SSE2 multiplication test took " << mSse2DoubleAddResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << mSse2DoubleAddResult.mflops << endl;
//#endif
//  mSse2DoubleMulResult = lFlopsResult;
//  return mSse2DoubleMulResult;
//} // sFlopsResult cFlops::runSse2DoubleMulTest()
//
//sFlopsResult cFlops::runSse2DoubleDivTest()
//{
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD ] gccAlign64;
//  vs2005align64 sVectorDouble lvAddValue gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  lvAddValue.x = 0.99999;
//  lvAddValue.y = 0.99999;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VD; i++ )
//  {
//    x[ i ] = lvAddValue;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP division test..." << endl;
//  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VD - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, lvAddValue
//
//        lea     eax, x
//        add     eax, liOffset
//        movapd  xmm1, [eax]
//        divpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        divpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        divpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        divpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        divpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        divpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        divpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        add     eax, 16
//        movapd  xmm1, [eax]
//        divpd   xmm1, xmm0
//        movapd  [eax], xmm1
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VD * ITERATION_COUNT * 2;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Double precision SSE2 division test took " << mSse2DoubleAddResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << mSse2DoubleAddResult.mflops << endl;
//#endif
//  mSse2DoubleDivResult = lFlopsResult;
//  return mSse2DoubleDivResult;
//} // sFlopsResult cFlops::runSse2DoubleDivTest()
//
//sFlopsResult cFlops::runSse2DoubleAddMaxTest()
//{
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble y[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble z[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble a gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  a.x = 1.001;
//  a.y = 1.001;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VD3; i++ )
//  {
//    x[ i ] = a;
//    y[ i ] = a;
//    z[ i ] = a;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP addition max test..." << endl;
//  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VD3 - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, a
//
//        lea     eax, x
//        lea     ebx, y
//        lea     ecx, z
//
//        add     eax, liOffset // &x[ i ]
//        movapd  xmm1, [eax]
//
//        add     ebx, liOffset // &y[ i ]
//        movapd  xmm2, [ebx]
//
//        add     ecx, liOffset // &z[ i ]
//        movapd  xmm3, [ecx]
//
//        addpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        addpd   xmm2, xmm0
//        movapd  [ebx], xmm2
//
//        addpd   xmm3, xmm0
//        movapd  [ecx], xmm3
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        addpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        addpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        addpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        addpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        addpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        addpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        addpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        addpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        addpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        addpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        addpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        addpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        addpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        addpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        addpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        addpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        addpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        addpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        addpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        addpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        addpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VD3 * ITERATION_COUNT * 6;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << "x:" << endl;
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//    cerr << "y:" << endl;
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//    cerr << "z:" << endl;
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//  cerr << endl << "SSE2 DP addition test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//  mSse2DoubleAddMaxResult = lFlopsResult;
//  return mSse2DoubleAddMaxResult;
//} // sFlopsResult cFlops::runSse2DoubleAddMaxTest()
//
//sFlopsResult cFlops::runSse2DoubleMulAddTest()
//{
//  // x = a * x + b
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD ] gccAlign64;
//  vs2005align64 sVectorDouble lvAddValue gccAlign64;
//  vs2005align64 sVectorDouble lvMulValue gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  lvMulValue.x = 0.999;
//  lvMulValue.y = 0.999;
//  lvAddValue.x = 1.001;
//  lvAddValue.y = 1.001;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VD; i++ )
//  {
//    x[ i ] = lvAddValue;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP mul-add test..." << endl;
//  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VD - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, lvAddValue
//        movaps  xmm1, lvMulValue
//
//        lea     eax, x
//        add     eax, liOffset
//        movapd  xmm2, [eax]
//        mulpd   xmm2, xmm1  // 2 FLOPs
//        addpd   xmm2, xmm0  // 2 FLOPs
//        movapd  [eax], xmm2
//
//        add     eax, 16
//        movapd  xmm2, [eax]
//        mulpd   xmm2, xmm1  // 2 FLOPs
//        addpd   xmm2, xmm0  // 2 FLOPs
//        movapd  [eax], xmm2
//
//        add     eax, 16
//        movapd  xmm2, [eax]
//        mulpd   xmm2, xmm1  // 2 FLOPs
//        addpd   xmm2, xmm0  // 2 FLOPs
//        movapd  [eax], xmm2
//
//        add     eax, 16
//        movapd  xmm2, [eax]
//        mulpd   xmm2, xmm1  // 2 FLOPs
//        addpd   xmm2, xmm0  // 2 FLOPs
//        movapd  [eax], xmm2
//
//        add     eax, 16
//        movapd  xmm2, [eax]
//        mulpd   xmm2, xmm1  // 2 FLOPs
//        addpd   xmm2, xmm0  // 2 FLOPs
//        movapd  [eax], xmm2
//
//        add     eax, 16
//        movapd  xmm2, [eax]
//        mulpd   xmm2, xmm1  // 2 FLOPs
//        addpd   xmm2, xmm0  // 2 FLOPs
//        movapd  [eax], xmm2
//
//        add     eax, 16
//        movapd  xmm2, [eax]
//        mulpd   xmm2, xmm1  // 2 FLOPs
//        addpd   xmm2, xmm0  // 2 FLOPs
//        movapd  [eax], xmm2
//
//        add     eax, 16
//        movapd  xmm2, [eax]
//        mulpd   xmm2, xmm1  // 2 FLOPs
//        addpd   xmm2, xmm0  // 2 FLOPs
//        movapd  [eax], xmm2
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VD * ITERATION_COUNT * 4;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Double precision SSE2 mul-add test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//  mSse2DoubleMulAddResult = lFlopsResult;
//  return mSse2DoubleMulAddResult;
//} // sFlopsResult cFlops::runSse2DoubleMulAddTest()
//
//sFlopsResult cFlops::runSse2DoubleMulAdd2Test()
//{
//  // x = a * x + b
//  // y = a * y + b
//  // z = z + x + y
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble y[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble z[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble a gccAlign64;
//  vs2005align64 sVectorDouble b gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  a.x = 0.999;
//  a.y = 0.999;
//  b.x = 1.001;
//  b.y = 1.001;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VD3; i++ )
//  {
//    x[ i ] = a;
//    y[ i ] = b;
//    z[ i ] = a;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP mul-add2 test..." << endl;
//
//  cerr << endl << "Here are the first ten elements of the array x before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array y before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array z before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  __asm
//  {
//      movaps  xmm0, a
//      movaps  xmm1, b
//  };
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VD3 - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        // compute addresses to the three arrays
//        lea     eax, x
//        add     eax, liOffset
//        lea     ebx, y
//        add     ebx, liOffset
//        lea     ecx, z
//        add     ecx, liOffset
//        // load array elements
//        movapd  xmm2, [eax] // x[ i ]
//        movapd  xmm3, [ebx] // y[ i ]
//        movapd  xmm4, [ecx] // z[ i ]
//        // calculate
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm2  // z[ i ] = z[ i ] + x[ i ]; 2 FLOPs
//        addpd   xmm4, xmm3  // z[ i ] = z[ i ] + y[ i ]; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        add     ebx, 16
//        add     ecx, 16
//        // load array elements
//        movapd  xmm2, [eax] // x[ i ]
//        movapd  xmm3, [ebx] // y[ i ]
//        movapd  xmm4, [ecx] // z[ i ]
//        // calculate
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm2  // z[ i ] = z[ i ] + x[ i ]; 2 FLOPs
//        addpd   xmm4, xmm3  // z[ i ] = z[ i ] + y[ i ]; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        add     ebx, 16
//        add     ecx, 16
//        // load array elements
//        movapd  xmm2, [eax] // x[ i ]
//        movapd  xmm3, [ebx] // y[ i ]
//        movapd  xmm4, [ecx] // z[ i ]
//        // calculate
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm2  // z[ i ] = z[ i ] + x[ i ]; 2 FLOPs
//        addpd   xmm4, xmm3  // z[ i ] = z[ i ] + y[ i ]; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        add     ebx, 16
//        add     ecx, 16
//        // load array elements
//        movapd  xmm2, [eax] // x[ i ]
//        movapd  xmm3, [ebx] // y[ i ]
//        movapd  xmm4, [ecx] // z[ i ]
//        // calculate
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm2  // z[ i ] = z[ i ] + x[ i ]; 2 FLOPs
//        addpd   xmm4, xmm3  // z[ i ] = z[ i ] + y[ i ]; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        add     ebx, 16
//        add     ecx, 16
//        // load array elements
//        movapd  xmm2, [eax] // x[ i ]
//        movapd  xmm3, [ebx] // y[ i ]
//        movapd  xmm4, [ecx] // z[ i ]
//        // calculate
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOP
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOP
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOP
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOP
//        addpd   xmm4, xmm2  // z[ i ] = z[ i ] + x[ i ]; 2 FLOP
//        addpd   xmm4, xmm3  // z[ i ] = z[ i ] + y[ i ]; 2 FLOP
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        add     ebx, 16
//        add     ecx, 16
//        // load array elements
//        movapd  xmm2, [eax] // x[ i ]
//        movapd  xmm3, [ebx] // y[ i ]
//        movapd  xmm4, [ecx] // z[ i ]
//        // calculate
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOP
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOP
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOP
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOP
//        addpd   xmm4, xmm2  // z[ i ] = z[ i ] + x[ i ]; 2 FLOP
//        addpd   xmm4, xmm3  // z[ i ] = z[ i ] + y[ i ]; 2 FLOP
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        add     ebx, 16
//        add     ecx, 16
//        // load array elements
//        movapd  xmm2, [eax] // x[ i ]
//        movapd  xmm3, [ebx] // y[ i ]
//        movapd  xmm4, [ecx] // z[ i ]
//        // calculate
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOP
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOP
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOP
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOP
//        addpd   xmm4, xmm2  // z[ i ] = z[ i ] + x[ i ]; 2 FLOP
//        addpd   xmm4, xmm3  // z[ i ] = z[ i ] + y[ i ]; 2 FLOP
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        add     ebx, 16
//        add     ecx, 16
//        // load array elements
//        movapd  xmm2, [eax] // x[ i ]
//        movapd  xmm3, [ebx] // y[ i ]
//        movapd  xmm4, [ecx] // z[ i ]
//        // calculate
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm2  // z[ i ] = z[ i ] + x[ i ]; 2 FLOPs
//        addpd   xmm4, xmm3  // z[ i ] = z[ i ] + y[ i ]; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VD3 * ITERATION_COUNT * 12;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array x after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array y after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array z after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//
//  cerr << endl << "Double precision SSE2 mul-add2 test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//  mSse2DoubleMulAdd2Result = lFlopsResult;
//  return mSse2DoubleMulAdd2Result;
//} // sFlopsResult cFlops::runSse2DoubleMulAdd2Test()
//
//sFlopsResult cFlops::runSse2DoubleMulAdd3Test()
//{
//  // x = a * x + b
//  // y = a * y + b
//  // z = a * z + b
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble y[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble z[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble a gccAlign64;
//  vs2005align64 sVectorDouble b gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  a.x = 0.999;
//  a.y = 0.999;
//  b.x = 1.001;
//  b.y = 1.001;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VD3; i++ )
//  {
//    x[ i ] = a;
//    y[ i ] = b;
//    z[ i ] = a;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP mul-add3 test..." << endl;
//
//  cerr << endl << "Here are the first ten elements of the array x before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array y before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array z before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  __asm
//  {
//    //pusha
//    movaps  xmm0, a
//    movaps  xmm1, b
//  };
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VD3 - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//
//        // compute addresses to the three arrays
//        // load array elements
//        lea     eax, x
//        add     eax, liOffset
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        lea     ebx, y
//        add     ebx, liOffset
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        lea     ecx, z
//        add     ecx, liOffset
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        // compute next set of addresses
//        // load array elements
//        // calculate
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//
//      } // __asm
//    } // for
//  } // for
//  //__asm
//  //{
//  //  popa
//  //};
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VD3 * ITERATION_COUNT * 12;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array x after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array y after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array z after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//
//  cerr << endl << "Double precision SSE2 mul-add2 test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//  mSse2DoubleMulAdd3Result = lFlopsResult;
//  return mSse2DoubleMulAdd3Result;
//} // sFlopsResult cFlops::runSse2DoubleMulAdd3Test()
//
//sFlopsResult cFlops::runSse2DoubleMulMaxTest()
//{
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble y[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble z[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble a gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  a.x = 1.001;
//  a.y = 1.001;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VD3; i++ )
//  {
//    x[ i ] = a;
//    y[ i ] = a;
//    z[ i ] = a;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP addition test..." << endl;
//  cerr << endl << "Here are the first ten elements of the array before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VD3 - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        movaps  xmm0, a
//
//        lea     eax, x
//        lea     ebx, y
//        lea     ecx, z
//
//        add     eax, liOffset // &x[ i ]
//        movapd  xmm1, [eax]
//
//        add     ebx, liOffset // &y[ i ]
//        movapd  xmm2, [ebx]
//
//        add     ecx, liOffset // &z[ i ]
//        movapd  xmm3, [ecx]
//
//        mulpd   xmm1, xmm0
//        movapd  [eax], xmm1
//
//        mulpd   xmm2, xmm0
//        movapd  [ebx], xmm2
//
//        mulpd   xmm3, xmm0
//        movapd  [ecx], xmm3
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        mulpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        mulpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        mulpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        mulpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        mulpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        mulpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        mulpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        mulpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        mulpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        mulpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        mulpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        mulpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        mulpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        mulpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        mulpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        mulpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        mulpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        mulpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm1, [eax] // x[ i ]
//        mulpd   xmm1, xmm0 // x[ i ] = x[ i ] + a
//
//        add     ebx, 16
//        movapd  xmm2, [ebx] // y[ i ]
//        mulpd   xmm2, xmm0 // y[ i ] = y[ i ] + a
//
//        add     ecx, 16
//        movapd  xmm3, [ecx] // z[ i ]
//        mulpd   xmm3, xmm0 // z[ i ] = z[ i ] + a
//        // store
//        movapd  [eax], xmm1 // store x[ i ]
//        movapd  [ebx], xmm2 // store y[ i ]
//        movapd  [ecx], xmm3 // store z[ i ]
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VD3 * ITERATION_COUNT * 6;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << "x:" << endl;
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//    cerr << "y:" << endl;
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//    cerr << "z:" << endl;
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//  cerr << endl << "SSE2 DP mul-add max test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//  mSse2DoubleMulMaxResult = lFlopsResult;
//  return mSse2DoubleMulMaxResult;
//} // sFlopsResult cFlops::runSse2DoubleMulMaxTest()

double cFlops::runFpuDoubleMulAdd3Test()
{
  // x = a * x + b
  // y = a * y + b
  // z = a * z + b
  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD3 ] gccAlign64;
  vs2005align64 sVectorDouble y[ ARRAY_SIZE_VD3 ] gccAlign64;
  vs2005align64 sVectorDouble z[ ARRAY_SIZE_VD3 ] gccAlign64;
  vs2005align64 sVectorDouble a gccAlign64;
  vs2005align64 sVectorDouble b gccAlign64;
  int liFlopCount = 0;
  sFlopsResult lFlopsResult;

  a.x = 0.999;
  a.y = 0.999;
  b.x = 1.001;
  b.y = 1.001;
  // initialize array
  for( int i = 0; i < ARRAY_SIZE_VD3; i++ )
  {
    x[ i ] = a;
    y[ i ] = b;
    z[ i ] = a;
  } // for

#ifdef debug
  cerr << endl << "Starting FPU DP mul-add3 test..." << endl;

  cerr << endl << "Here are the first ten elements of the array x before test:" << endl;
  for( int i = 0; i < 5; i++ )
  {
    cerr << x[ i ].x << endl;
    cerr << x[ i ].y << endl;
  } // for
  cerr << endl << "Here are the first ten elements of the array y before test:" << endl;
  for( int i = 0; i < 5; i++ )
  {
    cerr << y[ i ].x << endl;
    cerr << y[ i ].y << endl;
  } // for
  cerr << endl << "Here are the first ten elements of the array z before test:" << endl;
  for( int i = 0; i < 5; i++ )
  {
    cerr << z[ i ].x << endl;
    cerr << z[ i ].y << endl;
  } // for
#endif

  clock_t endTime;
  clock_t startTime = clock();

  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
  {
    for( int i = 0; i < ARRAY_SIZE_VD3 - 1; i += 8 )
    {
      // x = a * x + b
      // y = a * y + b
      // z = a * z + b
      x[ i ].x = a.x * x[ i ].x + b.x;
      x[ i ].y = a.y * x[ i ].y + b.y;
      y[ i ].x = a.x * y[ i ].x + b.x;
      y[ i ].y = a.y * y[ i ].y + b.y;
      z[ i ].x = a.x * z[ i ].x + b.x;
      z[ i ].y = a.y * z[ i ].y + b.y;

      x[ i + 1 ].x = a.x * x[ i + 1 ].x + b.x;
      x[ i + 1 ].y = a.y * x[ i + 1 ].y + b.y;
      y[ i + 1 ].x = a.x * y[ i + 1 ].x + b.x;
      y[ i + 1 ].y = a.y * y[ i + 1 ].y + b.y;
      z[ i + 1 ].x = a.x * z[ i + 1 ].x + b.x;
      z[ i + 1 ].y = a.y * z[ i + 1 ].y + b.y;

      x[ i + 2 ].x = a.x * x[ i + 2 ].x + b.x;
      x[ i + 2 ].y = a.y * x[ i + 2 ].y + b.y;
      y[ i + 2 ].x = a.x * y[ i + 2 ].x + b.x;
      y[ i + 2 ].y = a.y * y[ i + 2 ].y + b.y;
      z[ i + 2 ].x = a.x * z[ i + 2 ].x + b.x;
      z[ i + 2 ].y = a.y * z[ i + 2 ].y + b.y;

      x[ i + 3 ].x = a.x * x[ i + 3 ].x + b.x;
      x[ i + 3 ].y = a.y * x[ i + 3 ].y + b.y;
      y[ i + 3 ].x = a.x * y[ i + 3 ].x + b.x;
      y[ i + 3 ].y = a.y * y[ i + 3 ].y + b.y;
      z[ i + 3 ].x = a.x * z[ i + 3 ].x + b.x;
      z[ i + 3 ].y = a.y * z[ i + 3 ].y + b.y;

      x[ i + 4 ].x = a.x * x[ i + 4 ].x + b.x;
      x[ i + 4 ].y = a.y * x[ i + 4 ].y + b.y;
      y[ i + 4 ].x = a.x * y[ i + 4 ].x + b.x;
      y[ i + 4 ].y = a.y * y[ i + 4 ].y + b.y;
      z[ i + 4 ].x = a.x * z[ i + 4 ].x + b.x;
      z[ i + 4 ].y = a.y * z[ i + 4 ].y + b.y;

      x[ i + 5 ].x = a.x * x[ i + 5 ].x + b.x;
      x[ i + 5 ].y = a.y * x[ i + 5 ].y + b.y;
      y[ i + 5 ].x = a.x * y[ i + 5 ].x + b.x;
      y[ i + 5 ].y = a.y * y[ i + 5 ].y + b.y;
      z[ i + 5 ].x = a.x * z[ i + 5 ].x + b.x;
      z[ i + 5 ].y = a.y * z[ i + 5 ].y + b.y;

      x[ i + 6 ].x = a.x * x[ i + 6 ].x + b.x;
      x[ i + 6 ].y = a.y * x[ i + 6 ].y + b.y;
      y[ i + 6 ].x = a.x * y[ i + 6 ].x + b.x;
      y[ i + 6 ].y = a.y * y[ i + 6 ].y + b.y;
      z[ i + 6 ].x = a.x * z[ i + 6 ].x + b.x;
      z[ i + 6 ].y = a.y * z[ i + 6 ].y + b.y;

      x[ i + 7 ].x = a.x * x[ i + 7 ].x + b.x;
      x[ i + 7 ].y = a.y * x[ i + 7 ].y + b.y;
      y[ i + 7 ].x = a.x * y[ i + 7 ].x + b.x;
      y[ i + 7 ].y = a.y * y[ i + 7 ].y + b.y;
      z[ i + 7 ].x = a.x * z[ i + 7 ].x + b.x;
      z[ i + 7 ].y = a.y * z[ i + 7 ].y + b.y;

    } // for
  } // for
  endTime = clock();

  liFlopCount = ARRAY_SIZE_VD3 * ITERATION_COUNT * 12; 
  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;

#ifdef debug
  cerr << endl << "Here are the first ten elements of the array x after test:" << endl;
  for( int i = 0; i < 5; i++ )
  {
    cerr << x[ i ].x << endl;
    cerr << x[ i ].y << endl;
  } // for
  cerr << endl << "Here are the first ten elements of the array y after test:" << endl;
  for( int i = 0; i < 5; i++ )
  {
    cerr << y[ i ].x << endl;
    cerr << y[ i ].y << endl;
  } // for
  cerr << endl << "Here are the first ten elements of the array z after test:" << endl;
  for( int i = 0; i < 5; i++ )
  {
    cerr << z[ i ].x << endl;
    cerr << z[ i ].y << endl;
  } // for

  cerr << endl << "Double precision FPU mul-add3 test took " << lFlopsResult.time << " seconds." << endl;
  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
#endif
  mFpuDoubleMulAdd3Result = lFlopsResult;
  return mFpuDoubleMulAdd3Result.mflops;
} // double cFlops::runFpuDoubleMulAdd3Test()

//sFlopsResult cFlops::runSse2DoubleMulAdd4Test()
//{
//  // x = a * x + b
//  // y = a * y + b
//  // z = a * z + b
//  vs2005align64 sVectorDouble w[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble y[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble z[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble a gccAlign64;
//  vs2005align64 sVectorDouble b gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  a.x = 0.999;
//  a.y = 0.999;
//  b.x = 1.001;
//  b.y = 1.001;
//  // initialize array
//  for( int i = 0; i < ARRAY_SIZE_VD3; i++ )
//  {
//    w[ i ] = b;
//    x[ i ] = a;
//    y[ i ] = b;
//    z[ i ] = a;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP mul-add4 test..." << endl;
//
//  cerr << endl << "Here are the first ten elements of the array w before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << w[ i ].x << endl;
//    cerr << w[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array x before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array y before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array z before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  __asm
//  {
//    //pusha
//    movaps  xmm0, a
//    movaps  xmm1, b
//  };
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < ARRAY_SIZE_VD3 - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//
//        // compute addresses to the three arrays
//        // load array elements
//        lea     eax, x
//        add     eax, liOffset
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        lea     ebx, y
//        add     ebx, liOffset
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        lea     ecx, z
//        add     ecx, liOffset
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        lea     edx, w
//        add     edx, liOffset
//        movapd  xmm5, [edx] // z[ i ]
//        mulpd   xmm5, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        addpd   xmm5, xmm1  // z[ i ] = w[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//        movapd  [edx], xmm5 // store w[ i ]
//
//        // compute next set of addresses
//        // load array elements
//        // calculate
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        add     edx, 16
//        movapd  xmm5, [edx] // w[ i ]
//        mulpd   xmm5, xmm0  // w[ i ] = a * w[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        addpd   xmm5, xmm1  // w[ i ] = w[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//        movapd  [ecx], xmm5 // store w[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        add     edx, 16
//        movapd  xmm5, [edx] // w[ i ]
//        mulpd   xmm5, xmm0  // w[ i ] = a * w[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        addpd   xmm5, xmm1  // w[ i ] = w[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//        movapd  [ecx], xmm5 // store w[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        add     edx, 16
//        movapd  xmm5, [edx] // w[ i ]
//        mulpd   xmm5, xmm0  // w[ i ] = a * w[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        addpd   xmm5, xmm1  // w[ i ] = w[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//        movapd  [ecx], xmm5 // store w[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        add     edx, 16
//        movapd  xmm5, [edx] // w[ i ]
//        mulpd   xmm5, xmm0  // w[ i ] = a * w[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        addpd   xmm5, xmm1  // w[ i ] = w[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//        movapd  [ecx], xmm5 // store w[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        add     edx, 16
//        movapd  xmm5, [edx] // w[ i ]
//        mulpd   xmm5, xmm0  // w[ i ] = a * w[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        addpd   xmm5, xmm1  // w[ i ] = w[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//        movapd  [ecx], xmm5 // store w[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        add     edx, 16
//        movapd  xmm5, [edx] // w[ i ]
//        mulpd   xmm5, xmm0  // w[ i ] = a * w[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        addpd   xmm5, xmm1  // w[ i ] = w[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//        movapd  [ecx], xmm5 // store w[ i ]
//
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        add     ecx, 16
//        movapd  xmm4, [ecx] // z[ i ]
//        mulpd   xmm4, xmm0  // z[ i ] = a * z[ i ]; 2 FLOPs
//        add     edx, 16
//        movapd  xmm5, [edx] // w[ i ]
//        mulpd   xmm5, xmm0  // w[ i ] = a * w[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        addpd   xmm4, xmm1  // z[ i ] = z[ i ] + b; 2 FLOPs
//        addpd   xmm5, xmm1  // w[ i ] = w[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//        movapd  [ecx], xmm4 // store z[ i ]
//        movapd  [ecx], xmm5 // store w[ i ]
//
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = ARRAY_SIZE_VD3 * ITERATION_COUNT * 16;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array w after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << w[ i ].x << endl;
//    cerr << w[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array x after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array y after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array z after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << z[ i ].x << endl;
//    cerr << z[ i ].y << endl;
//  } // for
//
//  cerr << endl << "Double precision SSE2 mul-add4 test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//  mSse2DoubleMulAdd4Result = lFlopsResult;
//  return mSse2DoubleMulAdd4Result;
//} // sFlopsResult cFlops::runSse2DoubleMulAdd4Test()
//
//sFlopsResult cFlops::runSse2DoubleMulAdd5Test()
//{
//  // x = a * x + b
//  // y = a * y + b
//  int liArraySize = ARRAY_SIZE_VD3;
//  vs2005align64 sVectorDouble x[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble y[ ARRAY_SIZE_VD3 ] gccAlign64;
//  vs2005align64 sVectorDouble a gccAlign64;
//  vs2005align64 sVectorDouble b gccAlign64;
//  int liOffset;
//  int liFlopCount = 0;
//  sFlopsResult lFlopsResult;
//
//  a.x = 0.999;
//  a.y = 0.999;
//  b.x = 1.001;
//  b.y = 1.001;
//  // initialize array
//  for( int i = 0; i < liArraySize; i++ )
//  {
//    x[ i ] = a;
//    y[ i ] = b;
//  } // for
//
//#ifdef debug
//  cerr << endl << "Starting SSE2 DP mul-add5 test..." << endl;
//
//  cerr << endl << "Here are the first ten elements of the array x before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array y before test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//  } // for
//#endif
//
//  clock_t endTime;
//  clock_t startTime = clock();
//  __asm
//  {
//      movaps  xmm0, a
//      movaps  xmm1, b
//  };
//  for( int liIterations = 1; liIterations <= ITERATION_COUNT; liIterations++ )
//  {
//    for( int i = 0; i < liArraySize - 1; i += 8 )
//    {
//      liOffset = i * 16;
//      __asm
//      {
//        // compute addresses to the three arrays
//        // load array elements
//        lea     eax, x
//        add     eax, liOffset
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        lea     ebx, y
//        add     ebx, liOffset
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        // calculate
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//
//        // compute next set of addresses
//        // load array elements
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        // calculate
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        // calculate
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        // calculate
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        // calculate
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        // calculate
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//
//        // next block
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//
//        // compute next set of addresses
//        add     eax, 16
//        movapd  xmm2, [eax] // x[ i ]
//        mulpd   xmm2, xmm0  // x[ i ] = a * x[ i ]; 2 FLOPs
//        add     ebx, 16
//        movapd  xmm3, [ebx] // y[ i ]
//        mulpd   xmm3, xmm0  // y[ i ] = a * y[ i ]; 2 FLOPs
//        // calculate
//        addpd   xmm2, xmm1  // x[ i ] = x[ i ] + b; 2 FLOPs
//        addpd   xmm3, xmm1  // y[ i ] = y[ i ] + b; 2 FLOPs
//        // store
//        movapd  [eax], xmm2 // store x[ i ]
//        movapd  [ebx], xmm3 // store y[ i ]
//      } // __asm
//    } // for
//  } // for
//  endTime = clock();
//
//  liFlopCount = liArraySize * ITERATION_COUNT * 8;
//  lFlopsResult.time = (double) (endTime - startTime) / CLOCKS_PER_SEC; // elapsed time in seconds
//  lFlopsResult.mflops = (double) liFlopCount / lFlopsResult.time / (double)ONE_MILLION;
//
//#ifdef debug
//  cerr << endl << "Here are the first ten elements of the array x after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << x[ i ].x << endl;
//    cerr << x[ i ].y << endl;
//  } // for
//  cerr << endl << "Here are the first ten elements of the array y after test:" << endl;
//  for( int i = 0; i < 5; i++ )
//  {
//    cerr << y[ i ].x << endl;
//    cerr << y[ i ].y << endl;
//  } // for
//
//  cerr << endl << "Double precision SSE2 mul-add5 test took " << lFlopsResult.time << " seconds." << endl;
//  cerr << "Measured MFLOPS \t" << lFlopsResult.mflops << endl;
//#endif
//  mSse2DoubleMulAdd5Result = lFlopsResult;
//  return mSse2DoubleMulAdd5Result;
//} // sFlopsResult cFlops::runSse2DoubleMulAdd5Test()
