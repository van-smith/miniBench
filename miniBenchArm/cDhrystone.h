//#define amd64
#ifndef CDHRYSTONE_H_INCLUDED
#define CDHRYSTONE_H_INCLUDED

#include <sys/timeb.h>
#include "cShortTests.h"

#define Null 0
#define true  1
#define false 0
#define REG
#define structassign(d, s)      memcpy(&(d), &(s), sizeof(d))

typedef enum Enumeration{Ident_1, Ident_2, Ident_3, Ident_4, Ident_5} Enum ;
typedef  long     One_Thirty;
typedef  long     One_Fifty;
typedef char    Capital_Letter;
typedef char    Str_30 [31]; //this was 31
typedef  long     Arr_1_Dim [100];		//originally this was set to 50
typedef  long     Arr_2_Dim [100] [100];

typedef struct record
{
                         struct record *Ptr_Comp;
                         Enumeration    Discr;
                         union {
                                 struct {
                                         Enumeration Enum_Comp;
                                         long         long_Comp;
                                         char        Str_Comp [31];
                                 } var_1;
                                 struct {
                                         Enumeration E_Comp_2;
                                         char        Str_2_Comp [31];
                                 } var_2;
                                 struct {
                                         char        Ch_1_Comp;
                                         char        Ch_2_Comp;
                                 } var_3;
                         } variant;
} Rec_Type, *Rec_Polonger;

// template<size_t ALIGNMENT>
class CDynamicAlignedObj
{
        public:
            #ifdef amd64
                void * operator new(unsigned long size)
            #else
                void * operator new(unsigned int size)
            #endif
                {
                        // ensure it is aligned
                        void *p = malloc(size);
                        if (!p) throw std::bad_alloc();
                        return(p);
                };

                void operator delete(void *deadObject)
                {
                        // must use _aligned_free since we used _aligned_malloc
                        //_aligned_free(deadObject);
                        free(deadObject);
                }
};

//Applikationsklasse

//class CDhryApp : public CDynamicAlignedObj
class CDhryApp : public cTest
{
public:
  CDhryApp(int aIterations): cTest( aIterations ) {}
  double RunTest( long Iterations );
  long main(long Number_Of_Runs);

        /*private:
        void Proc_3 (Rec_Polonger Ptr_Ref_Par, Rec_Polonger Ptr_Glob, long * long_Glob);
        bool Func_3 (Enumeration Enum_Par_Val);
        Enumeration Func_1( Capital_Letter Ch_1_Par_Val,  Capital_Letter Ch_2_Par_Val, char  * Ch_1_Glob);
        bool Func_2 (Enumeration Enum_Par_Val);
        void Proc_6 (Enumeration Enum_Val_Par, Enumeration *Enum_Ref_Par, long * long_Glob);
        void Proc_7 ( One_Fifty long_1_Par_Val,  One_Fifty long_2_Par_Val,  One_Fifty *long_Par_Ref);
        void Proc_8 (Arr_1_Dim Arr_1_Par_Ref, Arr_2_Dim Arr_2_Par_Ref,   long long_1_Par_Val,   long long_2_Par_Val, long * long_Glob);
        Enumeration Func_1 ( Capital_Letter Ch_1_Par_Val,  Capital_Letter Ch_2_Par_Val);
        bool Func_2 ( Str_30 Str_1_Par_Ref,  Str_30 Str_2_Par_Ref, char * Ch_1_Glob, long * long_Glob);
        void Proc_5 (bool * Bool_Glob, char * Ch_1_Glob);
        void Proc_4 (bool * Bool_Glob, char * Ch_1_Glob, char * Ch_2_Glob);
        void Proc_3 (Rec_Polonger Ptr_Ref_Par);
        void Proc_2 (One_Fifty long_Par_Ref, char * Ch_1_Glob, long * long_Glob);
        void Proc_1 (Rec_Polonger Ptr_Val_Par, Rec_Polonger Ptr_Glob, long * long_Glob);
        */
}; // end for clibench dhrystone,

#endif // CDHRYSTONE_H_INCLUDED
