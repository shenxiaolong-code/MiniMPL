#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macroDef.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\macro_assert.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MACRO_ASSERT to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MACRO_ASSERT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MACRO_ASSERT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MACRO_ASSERT
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_MACRO_ASSERT
#endif

//#undef RUN_EXAMPLE_MACRO_ASSERT
//#undef COMPILE_EXAMPLE_MACRO_ASSERT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MACRO_ASSERT
#include <MiniMPL/macro_assert.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
#define ENABLE_MACRO_DEMO_ASSERT_BREAK					0

    inline void TestCase_macro_assert()
    {
        PrintTestcase();

#if ENABLE_MACRO_DEMO_ASSERT_BREAK==0
    #if defined(_MSC_VER) && (WINVER >= 0x0500)
        #pragma push_macro("Assert_Trigger")
        #pragma push_macro("ChkExceptionThrow")

        #undef	Assert_Trigger
        #define Assert_Trigger()        0
        #undef	ChkExceptionThrow
        #define ChkExceptionThrow()     0
    #endif	//end defined(_MSC_VER)
#endif   //end ENABLE_MACRO_DEMO_ASSERT_BREAK==0

        int Var32 = 123;
        AssertXI(false,(TXT("\ndemo AssertXI : Var32=%d,str=%s"),Var32,TXT("Demo")));
        AssertX(!TXT("this is one demo AssertX."));
        AssertX(false);
        AssertX(1==2);
        AssertX(NULL);
        int *pX = NULL;
        AssertP(pX);
        AssertB(Var32);
        Assertb(3==2);

        ChkExceptionInfo(1==2,(TXT("demo ChkExceptionInfo : Var32=%d,str=%s"),Var32,TXT("Demo")));
        ChkExceptionX(1==2);
        ChkExceptionB(Var32);
        ChkExceptionP(pX);
        ChkExceptionb(1==5);
        PrintRN();

        CHECK_TRUE_ELSE_RETURN_VAL(1==1,);
        CHECK_NULL_ELSE_RETURN_VAL(&Var32,);
        CHECK_TRUE_ELSE_RETURN_VAL(Var32+1,);
        CHECK_TRUE_ELSE_RETURN_VAL(&Var32,);

#if ENABLE_MACRO_DEMO_ASSERT_BREAK==0	
    #if defined(_MSC_VER) && (WINVER >= 0x0500)
        #pragma pop_macro("Assert_Trigger")
        #pragma pop_macro("ChkExceptionThrow")
    #endif	//end defined(_MSC_VER)
#endif   //end ENABLE_MACRO_DEMO_ASSERT_BREAK==0
    }

#ifdef RUN_EXAMPLE_MACRO_ASSERT
    InitRunFunc(TestCase_macro_assert);
#else //else of RUN_EXAMPLE_MACRO_ASSERT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] macro_assert.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"macro_assert.h\".")
    #endif
#endif  	// RUN_EXAMPLE_MACRO_ASSERT
}

#else //else of COMPILE_EXAMPLE_MACRO_ASSERT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] macro_assert.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"macro_assert.h\".")
    #endif
#endif // COMPILE_EXAMPLE_MACRO_ASSERT

