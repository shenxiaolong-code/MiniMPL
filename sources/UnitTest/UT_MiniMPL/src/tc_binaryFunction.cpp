#include "../testconfig_MiniMPL.h"
#include "MiniMPL/macroDef.h"
#include "UT_material/tc_def_typeStruct.h"
#include <list>
#include "MiniMPL/container.hpp"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\binaryFunction.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_BINARYFUNCTION to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_BINARYFUNCTION

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_BINARYFUNCTION
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_BINARYFUNCTION
#endif

#if defined(RUN_EXAMPLE_BINARYFUNCTION) && !defined(COMPILE_EXAMPLE_BINARYFUNCTION)
    #define COMPILE_EXAMPLE_BINARYFUNCTION
#endif

//#undef RUN_EXAMPLE_BINARYFUNCTION
//#undef COMPILE_EXAMPLE_BINARYFUNCTION

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_BINARYFUNCTION
#include <MiniMPL/binaryFunction.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    inline void TestCase_binaryFunction()
    {
        PrintTestcase();

        using namespace MiniMPL;

        typedef int (*TF_12)(int, char);
        typedef BinaryFunction<TF_12>  BF12_T;
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF12_T,1>::type,int>::value));
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF12_T,2>::type,char>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF12_T,1>::type,int&>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF12_T,2>::type,char*>::value));

        typedef int (*TF_1r2r)(int&, char&);
        typedef BinaryFunction<TF_1r2r>  BF1r2r_T;
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF1r2r_T,1>::type,int&>::value));
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF1r2r_T,2>::type,char&>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF1r2r_T,1>::type,int>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF1r2r_T,2>::type,char>::value));

        typedef int (*TF_1r2)(S2&, S4);
        typedef BinaryFunction<TF_1r2>  BF1r2_T;
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF1r2_T,1>::type,S2&>::value));
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF1r2_T,2>::type,S4&>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF1r2_T,1>::type,S2>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF1r2_T,2>::type,S4>::value));

        typedef int (*TF_1p2r)(S3*, S2&);
        typedef BinaryFunction<TF_1p2r>  BF1p2r_T;
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF1p2r_T,1>::type,S3*>::value));
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF1p2r_T,2>::type,S2&>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF1p2r_T,1>::type,S2>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF1p2r_T,2>::type,S4>::value));


        typedef int (*TF_1pr2cr)(int*&, S2 const&);
        typedef BinaryFunction<TF_1pr2cr>  BF1pr2cr_T;
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF1pr2cr_T,1>::type,int*&>::value));
        Static_Assert((IsSameType<GetBinaryFunctionParam<BF1pr2cr_T,2>::type,S2 const&>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF1pr2cr_T,1>::type,S2>::value));
        Static_Assert(!(IsSameType<GetBinaryFunctionParam<BF1pr2cr_T,2>::type,S4>::value));
    }

#ifdef RUN_EXAMPLE_BINARYFUNCTION
    InitRunFunc(TestCase_binaryFunction);
#else //else of RUN_EXAMPLE_BINARYFUNCTION

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_BINARYFUNCTION)=(outputTxtV(TXT("[Unit test run disabled] binaryFunction.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"binaryFunction.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_BINARYFUNCTION
}

#else //else of COMPILE_EXAMPLE_BINARYFUNCTION
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_BINARYFUNCTION)=(outputTxtV(TXT("[Unit test compile disabled] binaryFunction.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"binaryFunction.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_BINARYFUNCTION

