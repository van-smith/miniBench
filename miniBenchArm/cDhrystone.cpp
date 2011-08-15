#include "cDhrystone.h"

// Begin CLIBENCH DHRYSTONE
  /*
  ****************************************************************************
  *
  *                   "DHRYSTONE" Benchmark Program
  *
  *
  *  Version:    C, Version 2.1
  *
  *  File:       dhry_1.c (part 2 of 3)
  *
  *  Date:       May 25, 1988
  *
  *  Author:     Reinhold P. Weicker
  *
  ****************************************************************************
*/

Enumeration Func_1( Capital_Letter Ch_1_Par_Val,  Capital_Letter Ch_2_Par_Val, char  * Ch_1_Glob)
{
        Capital_Letter        Ch_1_Loc=' ';
        Capital_Letter        Ch_2_Loc=' ';

        Ch_1_Loc = Ch_1_Par_Val;
        Ch_2_Loc = Ch_1_Loc;
        if (Ch_2_Loc != Ch_2_Par_Val)
        {
                /* then, executed */
                return (Ident_1);
        }
        else  /* not executed */
        {
                *Ch_1_Glob = Ch_1_Loc;
                return (Ident_2);
    }
} /* Func_1 */

bool Func_3 (Enumeration Enum_Par_Val)

{
        Enumeration Enum_Loc;

        Enum_Loc = Enum_Par_Val;
        if (Enum_Loc == Ident_3)
                /* then, executed */
                return (true);
        else /* not executed */
                return (false);
} /* Func_3 */


void Proc_6 (Enumeration Enum_Val_Par, Enumeration *Enum_Ref_Par, long * long_Glob)
/*********************************/
/* executed once */
/* Enum_Val_Par == Ident_3, Enum_Ref_Par becomes Ident_2 */

//Enumeration  Enum_Val_Par;
//Enumeration *Enum_Ref_Par;
{
        *Enum_Ref_Par = Enum_Val_Par;
        if (! Func_3 (Enum_Val_Par))
                /* then, not executed */
                *Enum_Ref_Par = Ident_4;
        switch (Enum_Val_Par)
        {
        case Ident_1:
                *Enum_Ref_Par = Ident_1;
                break;
        case Ident_2:
                if (*long_Glob > 100) //opriginally 100
                        /* then */
                        *Enum_Ref_Par = Ident_1;
                else *Enum_Ref_Par = Ident_4;
                break;
        case Ident_3: /* executed */
                *Enum_Ref_Par = Ident_2;
                break;
        case Ident_4: break;
        case Ident_5:
                *Enum_Ref_Par = Ident_3;
                break;
        } /* switch */
} /* Proc_6 */


void Proc_7 ( One_Fifty long_1_Par_Val,  One_Fifty long_2_Par_Val,  One_Fifty *long_Par_Ref)
/**********************************************/
/* executed three _ftime                                      */
/* first call:      long_1_Par_Val == 2, long_2_Par_Val == 3,  */
/*                  long_Par_Ref becomes 7                    */
/* second call:     long_1_Par_Val == 10, long_2_Par_Val == 5, */
/*                  long_Par_Ref becomes 17                   */
/* third call:      long_1_Par_Val == 6, long_2_Par_Val == 10, */
/*                  long_Par_Ref becomes 18                   */
{
        One_Fifty long_Loc;

        long_Loc = long_1_Par_Val + 2;
        *long_Par_Ref = long_2_Par_Val + long_Loc;
} /* Proc_7 */


void Proc_8 (Arr_1_Dim Arr_1_Par_Ref, Arr_2_Dim Arr_2_Par_Ref,   long long_1_Par_Val,   long long_2_Par_Val, long * long_Glob)
/*********************************************************************/
/* executed once      */
/* long_Par_Val_1 == 3 */
/* long_Par_Val_2 == 7 */
{
        REG One_Fifty long_Index=0;
        REG One_Fifty long_Loc=0;

        long_Loc = long_1_Par_Val + 5;
        Arr_1_Par_Ref [long_Loc] = long_2_Par_Val;
        Arr_1_Par_Ref [long_Loc+1] = Arr_1_Par_Ref [long_Loc];
        Arr_1_Par_Ref [long_Loc+30] = long_Loc;
        for (long_Index = long_Loc; long_Index <= long_Loc+1; ++long_Index)
                Arr_2_Par_Ref[long_Loc][long_Index] = long_Loc;
        Arr_2_Par_Ref[long_Loc][long_Loc-1]+=1;
        Arr_2_Par_Ref[long_Loc+20][long_Loc]=Arr_1_Par_Ref[long_Loc];
        *long_Glob = 5;
} /* Proc_8 */

bool Func_2 ( Str_30 Str_1_Par_Ref,  Str_30 Str_2_Par_Ref, char * Ch_1_Glob, long * long_Glob)
/*************************************************/
/* executed once */
/* Str_1_Par_Ref == "DHRYSTONE PROGRAM, 1'ST STRING" */
/* Str_2_Par_Ref == "DHRYSTONE PROGRAM, 2'ND STRING" */

//  Str_30 Str_1_Par_Ref;
//Str_30  Str_2_Par_Ref;
{
        REG One_Thirty        long_Loc=0;
        Capital_Letter    Ch_Loc=' ';

        long_Loc = 2;
        while (long_Loc <= 2) /* loop body executed once */
                if (Func_1 (Str_1_Par_Ref[long_Loc],
                        Str_2_Par_Ref[long_Loc+1], Ch_1_Glob) == Ident_1)
                        /* then, executed */
                {
                        Ch_Loc = 'A';
                        long_Loc += 1;
                } /* if, while */
                if (Ch_Loc >= 'W' && Ch_Loc < 'Z')
                        /* then, not executed */
                        long_Loc = 7;
                if (Ch_Loc == 'R')
                        /* then, not executed */
                        return (true);
                else /* executed */
                {
                        if (strcmp (Str_1_Par_Ref, Str_2_Par_Ref) > 0)
                                /* then, not executed */
                        {
                                long_Loc += 7;
                                *long_Glob = long_Loc;
                                return (true);
                        }
                        else /* executed */
                                return (false);
                } /* if Ch_Loc */
} /* Func_2 */

/* end of variables for time measurement */

void Proc_5 (bool * Bool_Glob, char * Ch_1_Glob) /* without parameters */
/*******/
/* executed once */
{
        *Ch_1_Glob = 'A';
        *Bool_Glob = false;
} /* Proc_5 */

void Proc_4 (bool * Bool_Glob, char * Ch_1_Glob, char * Ch_2_Glob) /* without parameters */
/*******/
/* executed once */
{
        bool Bool_Loc;

        Bool_Loc = *Ch_1_Glob == 'A';
        *Bool_Glob = Bool_Loc | *Bool_Glob;
        *Ch_2_Glob = 'B';
} /* Proc_4*/

void Proc_3 (Rec_Polonger Ptr_Ref_Par, Rec_Polonger Ptr_Glob, long * long_Glob)
/******************/
/* executed once */
/* Ptr_Ref_Par becomes Ptr_Glob */

//Rec_Polonger *Ptr_Ref_Par;

{
        if (Ptr_Glob != Null)
                /* then, executed */
                Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
        Proc_7 (10, (long) long_Glob, &Ptr_Glob->variant.var_1.long_Comp);
} /* Proc_3 */

void Proc_2 (One_Fifty long_Par_Ref, char * Ch_1_Glob, long * long_Glob)
/******************/
/* executed once */
/* *long_Par_Ref == 1, becomes 4 */

//One_Fifty   *long_Par_Ref;
{
        One_Fifty  long_Loc;
        Enumeration   Enum_Loc;

        long_Loc = long_Par_Ref + 10;
        do /* executed once */
        if (*Ch_1_Glob == 'A')
                /* then, executed */
        {
                long_Loc  = 1;
                long_Par_Ref = long_Loc - *long_Glob;
                Enum_Loc = Ident_1;
        } /* if */
        while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */

void Proc_1 (REG Rec_Polonger Ptr_Val_Par, Rec_Polonger Ptr_Glob, long * long_Glob)
/******************/

// Ptr_Val_Par;
/* executed once */
{
        REG Rec_Polonger Next_Record = Ptr_Val_Par ->Ptr_Comp;
        /* == Ptr_Glob_Next */
        /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
        /* corresponds to "rename" in Ada, "with" in Pascal           */

        structassign (*Ptr_Val_Par ->Ptr_Comp, *Ptr_Glob);
        Ptr_Val_Par ->variant.var_1.long_Comp = 5;
        Next_Record ->variant.var_1.long_Comp
                = Ptr_Val_Par ->variant.var_1.long_Comp;
        Next_Record->Ptr_Comp = Ptr_Val_Par ->Ptr_Comp;
        Proc_3 (Next_Record ->Ptr_Comp, Ptr_Glob, long_Glob);
        /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp
        == Ptr_Glob->Ptr_Comp */
        if (Next_Record ->Discr == Ident_1)
                /* then, executed */
        {
                Next_Record ->variant.var_1.long_Comp = 6;
                Proc_6 (Ptr_Val_Par ->variant.var_1.Enum_Comp,
                        &Next_Record->variant.var_1.Enum_Comp, long_Glob);
                Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
                Proc_7 (Next_Record->variant.var_1.long_Comp, 10,
                        &Next_Record->variant.var_1.long_Comp);
        }
        else /* not executed */
                structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */

long CDhryApp::main(long Number_Of_Runs)
{
        // Replaced all dynamic allocation for allocation
        // on the stack.  It is much faster and is less prone to
        // threads locking
        One_Fifty		_long_1_Loc, *long_1_Loc = &_long_1_Loc;
        One_Fifty       _long_2_Loc, *long_2_Loc = &_long_2_Loc;
        One_Fifty       _long_3_Loc, *long_3_Loc = &_long_3_Loc;
        char            _Ch_Index, *Ch_Index = &_Ch_Index;
        Enumeration     _Enum_Loc, *Enum_Loc = &_Enum_Loc;
        Str_30          Str_1_Loc;
        Str_30          Str_2_Loc;
        long			Run_Index;
        Rec_Type		_Ptr_Glob;
        Rec_Polonger    Ptr_Glob = &_Ptr_Glob;
        Rec_Type		_Next_Ptr_Glob;
        Rec_Polonger	Next_Ptr_Glob = &_Next_Ptr_Glob;
        long			_long_Glob, *long_Glob = &_long_Glob;
        bool            _Bool_Glob, *Bool_Glob = &_Bool_Glob;
        char            _Ch_1_Glob, *Ch_1_Glob = &_Ch_1_Glob;
        char			_Ch_2_Glob, *Ch_2_Glob = &_Ch_2_Glob;
        long			_Arr_1_Glob[100], *Arr_1_Glob = _Arr_1_Glob;
        long			_Arr_2_Glob[100][100], (*Arr_2_Glob)[100] = _Arr_2_Glob;

        *Str_1_Loc=' ';
        *Str_2_Loc=' ';
        Run_Index=0;

        int i=0;
        while (i<100)
        {
                Arr_1_Glob[i]=0;
                int j=0;
                while (j<100)
                {
                        Arr_2_Glob[i][j]=0; //originally this was 50
                        ++j;
                }
                ++i;
        }

        Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
        Ptr_Glob->Discr                       = Ident_1;
        Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
        Ptr_Glob->variant.var_1.long_Comp     = 40;
        *strcpy (Ptr_Glob ->variant.var_1.Str_Comp,
                "DHRYSTONE PROGRAM, SOME STRING");
        strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

        Arr_2_Glob [8][7] = 10;



        Run_Index=1;
        while (Run_Index<Number_Of_Runs)
        {
                ++Run_Index;
                Proc_5(Bool_Glob, Ch_1_Glob);
                Proc_4(Bool_Glob,Ch_1_Glob,Ch_2_Glob);
                *long_1_Loc = 2;
                *long_2_Loc = 3;
                strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
                *Enum_Loc = Ident_2;
                *Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc, Ch_1_Glob, long_Glob);

                while (*long_1_Loc < *long_2_Loc)
                {

                        *long_3_Loc = 5 * *long_1_Loc - *long_2_Loc;

                        Proc_7 (*long_1_Loc, *long_2_Loc, long_3_Loc);

                        *long_1_Loc += 1;
                }


                Proc_8 (Arr_1_Glob, Arr_2_Glob, *long_1_Loc, *long_3_Loc, long_Glob);

                Proc_1 (Ptr_Glob, Ptr_Glob, (long*) &long_Glob);
                for (*Ch_Index = 'A'; *Ch_Index <= *Ch_2_Glob; ++*Ch_Index)

                {
                        if (*Enum_Loc == Func_1 (*Ch_Index, 'C', Ch_1_Glob))

                        {
                                Proc_6 (Ident_1, Enum_Loc, long_Glob);
                                strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
                                *long_2_Loc = Run_Index;
                                *long_Glob = Run_Index;
                        }
                }


                *long_2_Loc = *long_2_Loc * *long_1_Loc;
                *long_1_Loc = *long_2_Loc / *long_3_Loc;
                *long_2_Loc = 7 * (*long_2_Loc - *long_3_Loc) - *long_1_Loc;

                Proc_2 (*long_1_Loc, Ch_1_Glob, long_Glob);


        }


        return (Number_Of_Runs);
}


double CDhryApp::RunTest( long Iterations )
{
  clock_t stopTime;
  clock_t startTime = clock();
  main( Iterations );
  stopTime = clock();
  double elapsedTime = (stopTime - startTime) / CLOCKS_PER_SEC;
  cerr << "Elapsed time (s) " << elapsedTime  << endl;
  double DhrystonePerSec = Iterations / elapsedTime;
  cout << "Dhrystone MIPS: " << DhrystonePerSec / 1757 << endl;
  return elapsedTime;
}

// END CLIBENCH DHRYSTONE
