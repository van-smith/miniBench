#include "cWhetstone.h"

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
