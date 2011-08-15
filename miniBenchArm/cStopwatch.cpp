#include "cStopwatch.h"

cStopwatch::cStopwatch()
{
   //cerr << "cStopwatch constructor called." << endl;
   fbIsRunning = false;
} // cStopwatch::cStopwatch()

cStopwatch::~cStopwatch()
{
   //cerr << "cStopwatch destructor called." << endl;
} // cStopwatch::~cStopwatch()

void cStopwatch::StartStopwatch()
{
   int i = gettimeofday( &fpSeconds, &fpTimeZone );
   fdStartSeconds = (double)fpSeconds.tv_sec + 1.0e-6 * (double)fpSeconds.tv_usec;
   fbIsRunning = true;
} // void cStopwatch::StartStopwatch()

double cStopwatch::GetSplitTime()
{
   int i = gettimeofday( &fpSeconds, &fpTimeZone );
   fdSplitSeconds = (double)fpSeconds.tv_sec + 1.0e-6 * (double)fpSeconds.tv_usec;
   if( fbIsRunning )
   {
      return fdSplitSeconds - fdStartSeconds;
   } else
   {
      return -1;
   }
}

double cStopwatch::StopStopwatch()
{
   int i = gettimeofday( &fpSeconds, &fpTimeZone );
   fdStopSeconds = (double)fpSeconds.tv_sec + 1.0e-6 * (double)fpSeconds.tv_usec;
   if( fbIsRunning )
   {
      fbIsRunning = false;
      return fdStopSeconds - fdStartSeconds;
   } else
   {
      return -1;
   }
}
