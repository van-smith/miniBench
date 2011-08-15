#ifndef CSHORTTESTS_H
#define CSHORTTESTS_H
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <time.h>
#include <float.h>
#include <math.h>
#include <iomanip>   // needed for setiosflags, etc.
#include <string.h>  // memset
#include <stdlib.h>  // malloc, free, rand
#include "cStopwatch.h"
using namespace std;

double Sieve( int Iterations );
double StringConcatenation( int Iterations );
double HeapSortTest( int ArraySize );
double IntegerMatrixMultiplication( int Iterations );
double intArithmetic(int intMax);
double doubleArithmetic(double doubleMin, double doubleMax);
double longArithmetic(long long longMin, long long longMax);
double trig(double trigMax);
double io(int ioMax);
double RandomAssignment( int NumDigits );
double BandwidthIntegerWrite( int aiArraySize );
double BandwidthMemCpy( int aiArraySize );
double BandwidthDoubleCopy( int aiArraySize );
double PiTest(int n);

class cTest
{
  public:
    cTest( int aIterations );
    ~cTest();
    double GetScore();
    double Run();
    int GetNumberOfThreads();
    //void setIterations( int aiNumberOfIterations );
  private:
  protected:
    int fIterations;
    int fiNumThreads;
    double fMaxTimeSeconds;
    double fMinTimeSeconds;
    double fTotalTime;
    string fTestName;
    string fTestAuthor;
    string fTestVersion;
    double fReferenceTime;
    virtual void Pretest();
    virtual void RunTest();
    virtual void Posttest();
};

class cFibTest : public cTest
{
   public:
      cFibTest( int aIterations );
      void SetFibNumber( int value );
      int GetFibNumber();
      int GetResult();
   protected:
      int fFibNumber;
      int fResult;
      void RunTest();
   private:
      int Fibonacci(int n);
};
#endif // CSHORTTESTS_H
