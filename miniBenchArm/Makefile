# Build for ARM
ACPP=../CodeSourcery/Sourcery_G++_Lite/bin/arm-none-linux-gnueabi-g++
ACPP=../CodeSourcery/Sourcery_G++_Lite/bin/arm-none-linux-gnueabi-gcc
ALDFLAGS=-L../CodeSourcery/Sourcery_G++_Lite/arm-none-linux-gnueabi/libc/armv4t/usr/lib -lstdc++ -lc -lm

# Build for x86
CPP=g++
CPP=gcc
LDFLAGS=-lstdc++ -lc -lm

all:
	$(CPP) -Wall -fexceptions -fexpensive-optimizations -O3 -c cAes.cpp cAesBench.cpp cDhrystone.cpp cFFT.cpp cFlops.cpp cLinpack.cpp cMiniBench.cpp cQueens.cpp cSha1.cpp cSha1Bench.cpp cSha256.cpp cSha256Bench.cpp cShortTests.cpp cWhetstone.cpp cosbiCommon.cpp cosbiCpuid.cpp main.cpp gladman/aescrypt.c gladman/aeskey.c gladman/aestab.c omp.cpp cStopwatch.cpp
	$(CPP) -o miniBench cAes.o cAesBench.o cDhrystone.o cFFT.o cFlops.o cLinpack.o cMiniBench.o cQueens.o cSha1.o cSha1Bench.o cSha256.o cSha256Bench.o cShortTests.o cWhetstone.o cosbiCommon.o cosbiCpuid.o aescrypt.o aeskey.o aestab.o main.o omp.o cStopwatch.o $(LDFLAGS) -s -static
	$(ACPP) -Wall -fexceptions -fexpensive-optimizations -O3 -c cAes.cpp cAesBench.cpp cDhrystone.cpp cFFT.cpp cFlops.cpp cLinpack.cpp cMiniBench.cpp cQueens.cpp cSha1.cpp cSha1Bench.cpp cSha256.cpp cSha256Bench.cpp cShortTests.cpp cWhetstone.cpp cosbiCommon.cpp cosbiCpuid.cpp main.cpp gladman/aescrypt.c gladman/aeskey.c gladman/aestab.c omp.cpp cStopwatch.cpp
	$(ACPP) -o armMiniBench cAes.o cAesBench.o cDhrystone.o cFFT.o cFlops.o cLinpack.o cMiniBench.o cQueens.o cSha1.o cSha1Bench.o cSha256.o cSha256Bench.o cShortTests.o cWhetstone.o cosbiCommon.o cosbiCpuid.o aescrypt.o aeskey.o aestab.o main.o omp.o cStopwatch.o $(ALDFLAGS) -s -static

clean:
	rm -rf *.o armMiniBench

