#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\unaryFunctionAssemble.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_UNARYFUNCTIONASSEMBLE to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_UNARYFUNCTIONASSEMBLE

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_UNARYFUNCTIONASSEMBLE
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_UNARYFUNCTIONASSEMBLE
#endif

#if defined(RUN_EXAMPLE_UNARYFUNCTIONASSEMBLE) && !defined(COMPILE_EXAMPLE_UNARYFUNCTIONASSEMBLE)
    #define COMPILE_EXAMPLE_UNARYFUNCTIONASSEMBLE
#endif

//#undef RUN_EXAMPLE_UNARYFUNCTIONASSEMBLE
//#undef COMPILE_EXAMPLE_UNARYFUNCTIONASSEMBLE

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_UNARYFUNCTIONASSEMBLE
#include <MiniMPL/unaryFunctionAssemble.hpp>
#include <UnitTestKit/tc_tracer.h>
#include "UT_material/tc_def_typeStruct.h"
#include "MiniMPL/memberPtr.hpp"
#include <MiniMPL/unaryFunctionCreater.hpp>
#include "UT_material/tc_def_globalFunc.h"

namespace UnitTest
{
    inline void TestCase_UnaryFunctionPipe()
    {
        PrintTestcaseSub();
        using namespace MiniMPL;

        S4  oS4_1;
        typedef void (*TfprintObjectS3)(S3 const&);
        typedef CDataMemberPtr<S3 S4::*>    TS4_S3;
        typedef CDataMemberPtr<int S3::*>   TS3_int;

        TfprintObjectS3 p = printObject;
        makeUnaryFunctionPipe(TS4_S3(&S4::m_ss3),makeUnaryFunction(p,_$))(oS4_1);

        typedef S3 (*TfgetS3FromS4)(S4&);
        int iS3 = makeUnaryFunctionPipe(makeUnaryFunction(getS3FromS4,_$),TS3_int(&S3::m_s3))(oS4_1);
        ASSERT_AND_LOG(iS3==oS4_1.m_ss3.m_s3);

        typedef S3& (*TfgetS3FromS4Ref)(S4&);
        Static_Assert((IsSameType<typename UnaryFunctionPipe<TfgetS3FromS4,TS3_int>::TReturn,int>::value));
        Static_Assert((IsSameType<typename UnaryFunctionPipe<TfgetS3FromS4Ref,TS3_int>::TReturn,int&>::value));

        Static_Assert((IsSameType<typename UnaryFunctionPipe<TS4_S3,TfgetS3FromS4>::TReturn,S3>::value));
        Static_Assert((IsSameType<typename UnaryFunctionPipe<TS4_S3,TfgetS3FromS4Ref>::TReturn,S3&>::value));
    }

    inline void TestCase_unaryFunctionAssemble()
    {
        PrintTestcase();
        TestCase_UnaryFunctionPipe();        
    }

#ifdef RUN_EXAMPLE_UNARYFUNCTIONASSEMBLE
    InitRunFunc(TestCase_unaryFunctionAssemble);
#else //else of RUN_EXAMPLE_UNARYFUNCTIONASSEMBLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_UNARYFUNCTIONASSEMBLE)=(outputTxtV(TXT("[Unit test run disabled] unaryFunctionAssemble.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"unaryFunctionAssemble.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_UNARYFUNCTIONASSEMBLE
}

#else //else of COMPILE_EXAMPLE_UNARYFUNCTIONASSEMBLE
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_UNARYFUNCTIONASSEMBLE)=(outputTxtV(TXT("[Unit test compile disabled] unaryFunctionAssemble.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"unaryFunctionAssemble.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_UNARYFUNCTIONASSEMBLE

