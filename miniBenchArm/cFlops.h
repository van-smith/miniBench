#pragma once
//#define windowsos
//#define vs2005
//#define debug

#include <string>
#include <iostream>
#include <time.h>
#include <math.h>

#ifdef windowsos
  #ifdef vs2005
    #include "..\..\common\cosbiDefine.h"
  #else
    #include "..\common\cosbiDefine.h"
  #endif
#else
  #include "cosbiDefine.h"
#endif

using namespace std;

vs2005align16 struct sVectorDouble
{
   double x;
   double y;
} gccAlign16;

vs2005align16 struct sVectorFloat
{
  float s0;
  float s1;
  float s2;
  float s3;
} gccAlign16;

struct sFlopsResult
{
  double time;
  double mflops;
  double score;
};

class cFlops
{
private:
  static const int ARRAY_SIZE_SP = 32000;
  static const int ARRAY_SIZE_DP = 16000;
  static const int ARRAY_SIZE_VF = 8000;
  static const int ARRAY_SIZE_VF2 = 1600;
  static const int ARRAY_SIZE_VD = 8000;
  static const int ARRAY_SIZE_VD2 = 4000;
  static const int ARRAY_SIZE_VD3 = 1600;//2000;
  static const int ONE_MILLION = 1000000;
  static const int ITERATION_COUNT = 50000;
protected:
  sFlopsResult mFpuFloatMulResult;
  sFlopsResult mFpuFloatDivResult;
  sFlopsResult mFpuFloatAddResult;
//  sFlopsResult mSseFloatMulResult;
//  sFlopsResult mSseFloatDivResult;
//  sFlopsResult mSseFloatAddResult;
//  sFlopsResult mSseFloatMulAddResult;
//  sFlopsResult mSseFloatDivAddResult;
  sFlopsResult mFpuDoubleMulResult;
  sFlopsResult mFpuDoubleDivResult;
  sFlopsResult mFpuDoubleAddResult;
//  sFlopsResult mSse2DoubleMulResult;
//  sFlopsResult mSse2DoubleMulMaxResult;
//  sFlopsResult mSse2DoubleMulAddResult;
//  sFlopsResult mSse2DoubleMulAdd2Result;
//  sFlopsResult mSse2DoubleMulAdd3Result;
//  sFlopsResult mSse2DoubleMulAdd4Result;
//  sFlopsResult mSse2DoubleMulAdd5Result;
  sFlopsResult mFpuDoubleMulAdd3Result;
//  sFlopsResult mSse2DoubleDivResult;
//  sFlopsResult mSse2DoubleAddResult;
//  sFlopsResult mSse2DoubleAddMaxResult;
public:
  cFlops();
  ~cFlops();
  double runFpuFloatMulTest();
  double runFpuFloatDivTest();
  double runFpuFloatAddTest();
  double runFpuDoubleMulTest();
  double runFpuDoubleDivTest();
  double runFpuDoubleAddTest();
//  double runSseFloatAddTest();
//  double runSseFloatMulTest();
//  double runSseFloatDivTest();
//  double runSseFloatMulAddTest();
//  double runSse2DoubleAddTest();
//  double runSse2DoubleMulTest();
//  double runSse2DoubleMulAddTest();
//  double runSse2DoubleMulAdd2Test();
//  double runSse2DoubleMulAdd3Test();
//  double runSse2DoubleMulAdd4Test();
//  double runSse2DoubleMulAdd5Test();
  double runFpuDoubleMulAdd3Test();
//  double runSse2DoubleAddMaxTest();
//  double runSse2DoubleMulMaxTest();
//  double runSse2DoubleDivTest();
}; // class cFlops
