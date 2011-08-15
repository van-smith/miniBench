#ifndef CWHETSTONE_H_INCLUDED
#define CWHETSTONE_H_INCLUDED

#include "cShortTests.h"

// begin clibench whetstone
class CWhetApp
{
public:
  double RunTest( long Iterations );
  long main(long wiederhole);
private:
        void p0();
        void p3(double x, double y, double *z);
        void pa(double e[4]);
        double		x1, x2, x3, x4, x, y, z, t, t1, t2;
        double 		e1[4];
        long		ii, j, k, l, n1, n2, n3, n4, n6, n7, n8, n9, n10, n11;
};
// end clibench whetstone


#endif // CWHETSTONE_H_INCLUDED
