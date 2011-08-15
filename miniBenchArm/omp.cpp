#include "omp.h"

int omp_get_num_threads (void) __GOMP_NOTHROW
{
	// ARM CPUs typically have only one core
	return(1);
}

