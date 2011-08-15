#include "cMiniBench.h"

int main(int argc, char *argv[])
{
    cMiniBench miniBench;
    if( miniBench.ParseCommandLine( argc, argv ) )
    {
       miniBench.Run();
       return 0;
    }
    else
    {
       return -1;
    }
}
