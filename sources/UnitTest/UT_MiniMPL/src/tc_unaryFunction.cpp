#include "../testconfig_MiniMPL.h"
#include <UT_material/tc_def_globalFunc.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\unaryFunction.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_UNARYFUNCTION to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_UNARYFUNCTION

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_UNARYFUNCTION
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_UNARYFUNCTION
#endif

#if defined(RUN_EXAMPLE_UNARYFUNCTION) && !defined(COMPILE_EXAMPLE_UNARYFUNCTION)
    #define COMPILE_EXAMPLE_UNARYFUNCTION
#endif

//#undef RUN_EXAMPLE_UNARYFUNCTION
//#undef COMPILE_EXAMPLE_UNARYFUNCTION

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_UNARYFUNCTION
#include <MiniMPL/unaryFunction.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{
    inline void TestCase_unaryFunction()
    {
        PrintTestcase();

        using namespace MiniMPL;
        S4 obj;
        int p2=1;
        stlSmartptr<S5> pS5(new S5());

        typedef bool (*TUF1P)(S4& obj) ;
        typedef UnaryFunction<TUF1P,1>::UnaryFunctionParams_T UF1P_T;
        Static_Assert((IsSameType<UF1P_T,ParamPackage<> >::value));
        UF1P_T ps01;
        UnaryFunction<TUF1P,1>  uf1p(CallBackRoutineF1,ps01);
        uf1p(obj);
        uf1p(&obj);
        uf1p(pS5);    //test derive => base
        uf1p(&pS5);   //test derive => base

        typedef bool (*TUF2P)( S4&,int&);
        typedef UnaryFunction<TUF2P,1>::UnaryFunctionParams_T UF2P_T;
        Static_Assert((IsSameType<UF2P_T,ParamPackage<int&> >::value));
        UF2P_T ps02(p2);        
        UnaryFunction<TUF2P,1>  uf2p(CallBackRoutineF2,ps02);
        uf2p(obj);
        uf2p(&obj);
        uf2p(pS5);    //test derive => base
        uf2p(&pS5);   //test derive => base

        typedef void (S4::*TUMF1P)(int);
        typedef UnaryFunction<TUMF1P,0>::UnaryFunctionParams_T UMF1P0_T;
        Static_Assert((IsSameType<UMF1P0_T,ParamPackage<int> >::value));
        UMF1P0_T mps10(p2);        
        UnaryFunction<TUMF1P,0>  umf2p0(&S4::print1Param,mps10);
        umf2p0(obj);
        umf2p0(&obj);
        umf2p0(pS5);    //test derive => base
        umf2p0(&pS5);   //test derive => base
        typedef UnaryFunction<TUMF1P,1>::UnaryFunctionParams_T UMF1P1_T;
        Static_Assert((IsSameType<UMF1P1_T,ParamPackage<S4&> >::value));
        UMF1P1_T mps11(obj);        
        UnaryFunction<TUMF1P,1>  umf2p1(&S4::print1Param,mps11);
        umf2p1(p2);
        umf2p1(&p2);
        int arrInt[3] = {31,32,33};
        umf2p1(arrInt);

        typedef void (S4::*TUMF2P)(int ,char* );
        typedef UnaryFunction<TUMF2P,0>::UnaryFunctionParams_T UMF2P0_T;
        Static_Assert((IsSameType<UMF2P0_T,ParamPackage<int,char*> >::value));
        UMF2P0_T mps20(p2,"hello0");        
        UnaryFunction<TUMF2P,0>  umf3p0(&S4::print2Params,mps20);
        umf3p0(obj);
        umf3p0(&obj);
        umf3p0(pS5);   //test derive => base
        umf3p0(&pS5);  //test derive => base
        typedef UnaryFunction<TUMF2P,1>::UnaryFunctionParams_T UMF2P1_T;
        Static_Assert((IsSameType<UMF2P1_T,ParamPackage<S4&,char*> >::value));
        UMF2P1_T mps21(obj,"hello1");        
        UnaryFunction<TUMF2P,1>  umf3p1(&S4::print2Params,mps21);
        umf3p1(p2);
        umf3p1(&p2);
        typedef UnaryFunction<TUMF2P,2>::UnaryFunctionParams_T UMF2P2_T;
        Static_Assert((IsSameType<UMF2P2_T,ParamPackage<S4&,int> >::value));
        UMF2P2_T mps31(obj,5);        
        UnaryFunction<TUMF2P,2>  umf3p2(&S4::print2Params,mps31);
        umf3p2("hello3");

        Static_Assert((IsSameType<typename GetUnaryFunctionParam<void (S4::*)()>::type,S4&>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<void (S4::*)()>::type,S4>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<void (S4::*)()>::type,S4*>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<void (S4::*)()>::type,S4 const>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<void (S4::*)()>::type,S4 const&>::value));

        Static_Assert((IsSameType<typename GetUnaryFunctionParam<void (*)(S4)>::type,S4&>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<void (*)(S4)>::type,S4>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<void (*)(S4)>::type,S4*>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<void (*)(S4)>::type,S4 const>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<void (*)(S4)>::type,S4 const&>::value));

        typedef void (S4::*TS4_F0)();
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F0,0> >::type,S4&>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F0,0> >::type,S4&>::value));

        typedef int (S4::*TS4_F5)(int,S4,S3,char&,bool);
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F5,0> >::type,S4&>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F5,1> >::type,int>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F5,2> >::type,S4&>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F5,3> >::type,S3&>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F5,4> >::type,char&>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F5,5> >::type,bool>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F5,1> >::type,int&>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TS4_F5,3> >::type,char>::value));

        typedef int (*TG_F)(int,S4,S3,char&,bool);
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,1> >::type,int>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,1> >::type,int*>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,1> >::type,int&>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,2> >::type,S4&>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,2> >::type,S4>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,2> >::type,S4 const>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,3> >::type,S3&>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,3> >::type,S3*>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,3> >::type,S3 const&>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,4> >::type,char&>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,4> >::type,char*>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,4> >::type,char>::value));
        Static_Assert((IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,5> >::type,bool>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,5> >::type,bool*>::value));
        Static_Assert(!(IsSameType<typename GetUnaryFunctionParam<UnaryFunction<TG_F,5> >::type,bool&>::value));
    }

#ifdef RUN_EXAMPLE_UNARYFUNCTION
    InitRunFunc(TestCase_unaryFunction);
#else //else of RUN_EXAMPLE_UNARYFUNCTION

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_UNARYFUNCTION)=(outputTxtV(TXT("[Unit test run disabled] unaryFunction.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"unaryFunction.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_UNARYFUNCTION
}

#else //else of COMPILE_EXAMPLE_UNARYFUNCTION
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_UNARYFUNCTION)=(outputTxtV(TXT("[Unit test compile disabled] unaryFunction.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"unaryFunction.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_UNARYFUNCTION

