#pragma once
/*
  COSBI: Comprehensive Open Source Benchmarking Initiative
  Copyright (c) 2010 Van Smith

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  The current web address of the GNU General Public License is:
  http://www.gnu.org/licenses/gpl.html

  You can contact the authors of this software at:
  cosbi@vanshardware.com
  See www.vanshardware.com or www.cosbi.org for more contact details.
*/
/*
 * Simple class conversion by Van Smith on June 16, 2007
 *
 *          Linpack 100x100 Benchmark In C/C++ For PCs
 *
 ********************************************************************
 *
 *                 Original Source from NETLIB
 *
 *  Translated to C by Bonnie Toy 5/88 (modified on 2/25/94  to fix
 *  a problem with daxpy for unequal increments or equal increments
 *  not equal to 1. Jack Dongarra)
 *
 *  To obtain rolled source BLAS, add -DROLL to the command lines.
 *  To obtain unrolled source BLAS, add -DUNROLL to the command lines.
 *
 *  You must specify one of -DSP or -DDP to compile correctly.
 *
 *  You must specify one of -DROLL or -DUNROLL to compile correctly.
 *
 ********************************************************************
 *
 *                   Changes in this version
 *
 *  1. Function prototypes are declared and function headers have
 *     embedded parameter types to produce code for C and C++
 *
 *  2. Arrays aa and a are declared as [200*200] and [200*201] to
 *     allow compilation with prototypes.
 *
 *  3. Function second changed (compiler dependent).
 *
 *  4. Timing method changed due to inaccuracy of PC clock (see below).
 *
 *  5. Additional date function included (compiler dependent).
 *
 *  6. Additional code used as a standard for a series of benchmarks:-
 *       Automatic run time calibration rather than fixed parameters
 *       Initial calibration with display to show linearity
 *       Results displayed at reasonable rate for viewing (5 seconds)
 *       Facilities for typing in details of system used etc.
 *       Compiler details in code in case .exe files used elsewhere
 *       Results appended to a text file (Linpack.txt)
 *
 *  Roy Longbottom  101323.2241@compuserve.com    14 September 1996
 *
 ************************************************************************
 *
 *                             Timing
 *
 *  The PC timer is updated at about 18 times per second or resolution of
 *  0.05 to 0.06 seconds which is similar to the time taken by the main
 *  time consuming function dgefa on a 100 MHz Pentium. Thus there is no
 *  point in running the dgefa/dges1 combination three times as in the
 *  original version. Main timing for the latter, in the loop run NTIMES,
 *  executes matgen/dgefa, summing the time taken by matgen within the
 *  loop for later deduction from the total time. On a modern PC this sum
 *  can be based on a random selection of 0 or 0.05/0.06. This version
 *  executes the single pass once and the main timing loop five times,
 *  calculating the matgen overhead separately.
 *
 *************************************************************************
 *
 *                    Example of Output
 *
 * Rolled Double Precision Linpack Benchmark - PC Version in 'C/C++'
 *
 * Compiler     Watcom C/C++ 10.5 Win 386
 * Optimisation -zp4 -otexan -fp5 -5r -dDP -dROLL
 *
 *
 * norm resid      resid           machep         x[0]-1          x[n-1]-1
 *  0.4   7.41628980e-014  1.00000000e-015 -1.49880108e-014 -1.89848137e-014
 *
 *
 * Times are reported for matrices of order          100
 * 1 pass times for array with leading dimension of  201
 *
 *     dgefa      dgesl      total     Mflops       unit      ratio
 *   0.06000    0.00000    0.06000      11.44     0.1748     1.0714
 *
 *
 * Calculating matgen overhead
 *
 *       10 times   0.11 seconds
 *       20 times   0.22 seconds
 *       40 times   0.44 seconds
 *       80 times   0.87 seconds
 *      160 times   1.76 seconds
 *      320 times   3.52 seconds
 *      640 times   7.03 seconds
 *
 * Overhead for 1 matgen      0.01098 seconds
 *
 *
 * Calculating matgen/dgefa passes for 5 seconds
 *
 *       10 times   0.71 seconds
 *       20 times   1.38 seconds
 *       40 times   2.80 seconds
 *       80 times   5.66 seconds
 *
 *      Passes used         70
 *
 *  This is followed by output of the normal data for dgefa, dges1,
 *  total, Mflops, unit and ratio with five sets of results for each.
 *
 ************************************************************************
 *
 *                Example from output file Linpack.txt
 *
 * LINPACK BENCHMARK FOR PCs 'C/C++'    n @ 100
 *
 * Month run         9/1996
 * PC model          Escom
 * CPU               Pentium
 * Clock MHz         100
 * Cache             256K
 * Options           Neptune chipset
 * OS/DOS            Windows 95
 * Compiler          Watcom C/C++ 10.5 Win 386
 * OptLevel          -zp4 -otexan -fp5 -5r -dDP -dROLL
 * Run by            Roy Longbottom
 * From              UK
 * Mail              101323.2241@compuserve.com
 *
 * Rolling            Rolled
 * Precision          Double
 * norm. resid                     0.4
 * resid               7.41628980e-014
 * machep              1.00000000e-015             (8.88178420e-016 NON OPT)
 * x[0]-1             -1.49880108e-014
 * x[n-1]-1           -1.89848137e-014
 * matgen 1 seconds            0.01051
 * matgen 2 seconds            0.01050
 * Repetitions                      70
 * Leading dimension               201
 *                               dgefa     dgesl     total    Mflops
 * 1 pass seconds              0.06000   0.00000   0.06000
 * Repeat seconds              0.06092   0.00157   0.06249     10.99
 * Repeat seconds              0.06077   0.00157   0.06234     11.01
 * Repeat seconds              0.06092   0.00157   0.06249     10.99
 * Repeat seconds              0.06092   0.00157   0.06249     10.99
 * Repeat seconds              0.06092   0.00157   0.06249     10.99
 * Average                                                     10.99
 * Leading dimension               200
 * Repeat seconds              0.05936   0.00157   0.06093     11.27
 * Repeat seconds              0.05936   0.00157   0.06093     11.27
 * Repeat seconds              0.05864   0.00157   0.06021     11.40
 * Repeat seconds              0.05936   0.00157   0.06093     11.27
 * Repeat seconds              0.05864   0.00157   0.06021     11.40
 * Average                                                     11.32
 *
 ************************************************************************
 *
 *                     Examples of Results
 *
 *  Precompiled codes were produced via a Watcom C/C++ 10.5 compiler.
 *  Versions are available for DOS, Windows 3/95 and NT/Win 95. Both
 *  non-optimised and optimised programs are available. The latter has
 *  options as in the above example. Although these options can place
 *  functions in-line, in this case, daxpy is not in-lined. Optimisation
 *  reduces 18 instructions in the loop in this function to the following:
 *
 *               L85         fld     st(0)
 *                           fmul    qword ptr [edx]
 *                           add     eax,00000008H
 *                           add     edx,00000008H
 *                           fadd    qword ptr -8H[eax]
 *                           inc     ebx
 *                           fstp    qword ptr -8H[eax]
 *                           cmp     ebx,esi
 *                           jl      L85
 *
 *  Results produced are not consistent between runs but produce similar
 *  speeds when executing at a particular dimension (see above). An example
 *  of other results is 11.4/10.5 Mflops. Most typical double precision
 *  rolled results are:
 *
 *                               Opt   No Opt                        Version/
 *               MHz    Cache  Mflops  Mflops  Make/Options            Via
 *
 *   AM80386DX    40     128K    0.53    0.36  Clone                  Win/W95
 *   80486DX2     66     128K    2.5     1.9   Escom SIS chipset      Win/W95
 *   80486DX2     66     128K    2.3     1.9   Escom SIS chipset       NT/W95
 *   80486DX2     66     128K    2.8     2.0   Escom SIS chipset      Dos/Dos
 *   Pentium     100     256K    11      4.2   Escom Neptune chipset  Win/W95
 *   Pentium     100     256K    11      5.5   Escom Neptune chipset   NT/W95
 *   Pentium     100     256K    12      4.4   Escom Neptune chipset  Dos/Dos
 *   Pentium Pro 200     256K    48     19     Dell XPS Pro200n        NT/NT
 *
 *  The results are as produced when compiled as Linpack.cpp. Compiling as
 *  Linpack.c gives similar speeds but the code is a little different.
 *
 ***************************************************************************
*/

//#define windowsos
//#define vs2005
#define DP

#ifdef SP
  #define REAL float
  #define ZERO 0.0
  #define ONE 1.0
  #define PREC "Single "
#else
  #ifdef DP
    #define REAL double
    #define ZERO 0.0e0
    #define ONE 1.0e0
    #define PREC "Double "
  #endif
#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <iomanip>
#ifdef windowsos
  #ifdef vs2005
    #include "..\..\common\cosbiDefine.h"
    #include "..\..\common\cosbiCommon.h"
  #else
    #include "..\common\cosbiDefine.h"
    #include "..\common\cosbiCommon.h"
  #endif
#else
  #include "cosbiDefine.h"
  #include "cosbiCommon.h"
#endif
#include "cShortTests.h"
//#include <omp.h>
#include "omp.h"

using namespace std;

/* TIME TIME TIME TIME TIME TIME TIME TIME TIME TIME TIME TIME TIME */
inline REAL second()
{
  REAL secs;
  clock_t Time;
  Time = clock();
  secs = (REAL)Time / (REAL)CLOCKS_PER_SEC;
  return secs ;
}

enum enumRolling { eRolled, eUnrolled };

class cLinpack
{
  private:
    enumRolling mRolling;
    static const int NTIMES = 10;
    REAL atime[9][15];
    char this_month;
    int this_year;
    string mstrRolling;
  protected:
    void print_time (int row);
    void matgen (REAL a[], int lda, int n, REAL b[], REAL *norma);
    void dgefa (REAL a[], int lda, int n, int ipvt[], int *info);
    void dgesl (REAL a[],int lda,int n,int ipvt[],REAL b[],int job);
    void dmxpy (int n1, REAL y[], int n2, int ldm, REAL x[], REAL m[]);
    void daxpy (int n, REAL da, REAL dx[], int incx, REAL dy[], int incy);
    REAL epslon (REAL x);
    int idamax (int n, REAL dx[], int incx);
    void dscal (int n, REAL da, REAL dx[], int incx);
    REAL ddot (int n, REAL dx[], int incx, REAL dy[], int incy);
  public:
    cLinpack();
    ~cLinpack();
    void runBenchmark();
    int getFlops();
    void setRolling( enumRolling aRolling );
};

class cLinpackTest : public cTest
{
public:
   cLinpackTest(int aIterations);
   int GetFlops();
   void SetRolling( enumRolling aRolling );
   string GetRolling();
protected:
   void RunTest();
   int fIterations;
   int fiFlops;
private:
   enumRolling fRolling;
};
