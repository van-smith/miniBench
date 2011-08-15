#ifndef CMINIBENCH_H
#define CMINIBENCH_H

#include "cShortTests.h"
#include "cLinpack.h"
#include "cFlops.h"
#include "cSha1Bench.h"
#include "cSha256Bench.h"
#include "cAesBench.h"
#include "cDhrystone.h"
#include "cWhetstone.h"
#include "cQueens.h"
#include "cFFT.h"
#include "cosbiCommon.h"
using namespace std;

//typedef enum enumTest{
enum enumTest{
   eAllTests,
   eAllCpuTests,
   eAes, eDhrystone, eDoubleArithmetic, eFft,
   eFibonacci,
   eFlops, eHeapSort, eIntArithmetic, eInt64Arithmetic, eIntegerMatrixMul,
   eLinpack, ePi, eQueens,
   eSha1, eSha256, eSieve, eStringConcat,
   eTrig, eWhetstone,
   eAllDiskTests,
   eIO,
   eAllMemoryTests,
   eRandomAssignment,
   eStream, eBandwidthIntegerRead,
   eBandwidthIntegerReadReverse,eBandwidthReadBP64,
   eBandwidthReadPrefetchNTA,
   eBandwidthIntegerWrite,
   eBandwidthIntegerWriteUnroll,
   eBandwidthIntegerWriteUnrollBP64,
   eBandwidthIntegerWriteBP64,
   eBandwidthIntegerCopy,
   eBandwidthIntegerAdd,
   eBandwidthIntegerScale,
   eBandwidthIntegerTriad,
   eBandwidthIntegerCopyBP64,
   eBandwidthDoubleRead,
   eBandwidthDoubleReadReverse,
   eBandwidthDoubleWrite,
   eBandwidthDoubleCopy,
   eBandwidthMemCpy,
   eLastTest
};

const string CommandLineArguments[] =
{
   "AllTests",
   "AllCpuTests",
   "Aes", "Dhrystone", "DoubleArithmetic", "FFT",
   "Fibonacci", "Flops", "HeapSort", "IntArithmetic","Int64Arithmetic",
   "IntegerMatrixMul", "Linpack", "Pi",
   "Queens",
   "Sha1", "Sha256", "Sieve",
   "StringConcat", "Trig", "Whetstone",
   "AllDiskTests",
   "IO",
   "AllMemoryTests",
   "RandomAssignment",
   "Stream", "BandwidthIntegerRead",
   "BandwidthIntegerReadReverse","BandwidthReadBP64",
   "BandwidthReadPrefetchNTA",
   "BandwidthIntegerWrite",
   "BandwidthIntegerWriteUnroll",
   "BandwidthIntegerWriteUnrollBP64",
   "BandwidthIntegerWriteBP64",
   "BandwidthIntegerCopy",
   "BandwidthIntegerAdd",
   "BandwidthIntegerScale",
   "BandwidthIntegerTriad",
   "BandwidthIntegerCopyBP64",
   "BandwidthDoubleRead",
   "BandwidthDoubleReadReverse",
   "BandwidthDoubleWrite",
   "BandwidthDoubleCopy",
   "BandwidthMemCpy",
   "iterations="
};

const string MINIBENCH_VERSION = "1.5";

class cMiniBench
{
public:
   cMiniBench();
   ~cMiniBench();
   bool ParseCommandLine( int argc, char **argv );
   void Run();
   bool TestsToRun[ eLastTest ];

protected:

private:
    void RunTests();
    void StatusBarUpdate( string aStatusMessage );
    void OutputSeconds( double adoubleResult, string aOutputMessage );
    void OutputRaw( double adoubleResult, string aOutputMessage );
    int iterations;
    static const int intMax =      1000000000; // 1B
    static const double doubleMin =  10000000000.0; // 10B
    static const double doubleMax =   11000000000.0; // 11B
    static const long long int longMin = 10000000000LL; // 10B
    static const long long int longMax = 11000000000LL; // 11B
    static const double trigMax =   10000000; // 10M
    static const int ioMax =        1000000; // 1M
    double LinpackRolled;
    double LinpackUnrolled;
    double FlopsFpuFloatAdd;
    double FlopsFpuFloatMul;
    double FlopsSseFloatAdd;
    double FlopsFpuFloatMulAdd;
    double FlopsFpuFloatDiv;
    double FlopsFpuDoubleMul;
    double FlopsFpuDoubleDiv;
    double FlopsFpuDoubleAdd;
    double FlopsSseFloatMul;
    double FlopsSseFloatDiv;
    double FlopsSseFloatMulAdd;
    double FlopsSse2DoubleAdd;
    double FlopsSse2DoubleMul;
    double FlopsSse2DoubleMulAdd;
    double FlopsSse2DoubleMulAdd2;
    double FlopsSse2DoubleMulAdd3;
    double FlopsSse2DoubleMulAdd4;
    double FlopsSse2DoubleMulAdd5;
    double FlopsFpuDoubleMulAdd3;
    double FlopsSse2DoubleAddMax;
    double FlopsSse2DoubleMulMax;
    double FlopsSse2DoubleDiv;
    double Sha1ScoreOverall;
    double Sha1ScoreSmallStrings;
    double Sha1Score50KString;
    double Sha1Score1MString;
    double Sha1Score10MString;
    double Sha256ScoreOverall;
    double Sha256ScoreSmallStrings;
    double Sha256Score50KString;
    double Sha256Score1MString;
    double Sha256Score10MString;
    double AesEncrypt8kBScore;
    double AesDecrypt8kBScore;
    double AesEncrypt16kBScore;
    double AesDecrypt16kBScore;
    double AesEncrypt32kBScore;
    double AesDecrypt32kBScore;
    double AesEncrypt64kBScore;
    double AesDecrypt64kBScore;
    double AesEncrypt128kBScore;
    double AesDecrypt128kBScore;
    double AesEncrypt256kBScore;
    double AesDecrypt256kBScore;
    double AesEncrypt512kBScore;
    double AesDecrypt512kBScore;
    double AesEncrypt1024kBScore;
    double AesDecrypt1024kBScore;
    double AesEncrypt2048kBScore;
    double AesDecrypt2048kBScore;
    double AesEncrypt4096kBScore;
    double AesDecrypt4096kBScore;
    double AesEncrypt8192kBScore;
    double AesDecrypt8192kBScore;
    double AesEncrypt16384kBScore;
    double AesDecrypt16384kBScore;
    double WhetstoneTestTime;
    double DhrystoneTestTime;
    double QueenTestTime;
    double PiTestTime;
    double fftTestTime;
    double HeapSortTestTime;
    double IntegerMatrixMultiplicationTime;
    double sieveTime;
    double StringConcatenationTime;
    double FibTestTime;
    double IntegerArithmeticTime;
    double Int64ArithmeticTime;
    double doubleArithmeticTime;
    double trigTime;
    double ioTime;
    double RandomAssignmentTime;
    double StreamCopyBandwidth;
    double StreamScaleBandwidth;
    double StreamAddBandwidth;
    double StreamTriadBandwidth;
    double BandwidthIntegerReadTime;
    double BandwidthIntegerReadReverseTime;
    double BandwidthIntegerReadBP64Time;
    double BandwidthIntegerReadPrefetchNTA;
    double BandwidthIntegerWriteTime;
    double BandwidthIntegerWriteUnrollTime;
    double BandwidthIntegerCopyTime;
    double BandwidthIntegerAddTime;
    double BandwidthIntegerScaleTime;
    double BandwidthIntegerTriadTime;
    double BandwidthIntegerCopyBP64Time;
    double BandwidthDoubleReadTime;
    double BandwidthDoubleReadReverseTime;
    double BandwidthDoubleWriteTime;
    double BandwidthDoubleCopyTime;
    double BandwidthMemCpyTime;
};

#endif // CMINIBENCH_H
