#ifndef CQUEENS_H_INCLUDED
#define CQUEENS_H_INCLUDED

#include "cShortTests.h"
#include "cStopwatch.h"
//#include <omp.h>
#include "omp.h"

class cQueens // from CLIBench
{
public:
   long DoQueen( long iterations );
private:
   void Attempt( int i );
   bool a[9],b[17],c[15];
   int x[9];
};

class cQueensTest : public cTest
{
public:
  cQueensTest(int aIterations);
protected:
   void RunTest();
   int fIterations;
private:
   int fQueensIterations;
};


#endif // CQUEENS_H_INCLUDED
