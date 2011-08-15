#include "cQueens.h"

void cQueens::Attempt(int i)
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


long cQueens::DoQueen(long Iterations)
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


cQueensTest::cQueensTest( int aIterations ) : cTest( aIterations )
{
   cerr << "cQueensTest constructor called." << endl;
   fQueensIterations = 25000; // default value
   fTestName = "Queens";
}

void cQueensTest::RunTest()
{
   #pragma omp parallel
   {
      cQueens lQueens;
      int liDummy = lQueens.DoQueen( fQueensIterations );
      fiNumThreads = omp_get_num_threads();
   }
}
