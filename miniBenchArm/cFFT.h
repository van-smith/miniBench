#ifndef CFFT_H_INCLUDED
#define CFFT_H_INCLUDED

#include "cShortTests.h"

class cFFT : public cTest
{
public:
  cFFT(int aIterations);
  ~cFFT();
  double GetMflops();
protected:
   void Pretest();
   void RunTest();
   void Posttest();
private:
   int N;
   int twoN;
   int int_log2(int n);
   double fMflops;
   double *x;
   double FFT_num_flops(int N);
   double* RandomVector(int N );
   void FFT_bitreverse(int N, double *data);
   void FFT_transform_internal (int N, double *data, int direction);
   void FFT_transform(int N, double *data);
   void FFT_inverse(int N, double *data);
};

#endif // CFFT_H_INCLUDED
