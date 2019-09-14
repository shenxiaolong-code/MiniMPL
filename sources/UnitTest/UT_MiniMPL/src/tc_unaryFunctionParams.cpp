#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\unaryFuncParams.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_UNARYFUNCPARAMS to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_UNARYFUNCPARAMS

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_UNARYFUNCPARAMS
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_UNARYFUNCPARAMS
#endif

#if defined(RUN_EXAMPLE_UNARYFUNCPARAMS) && !defined(COMPILE_EXAMPLE_UNARYFUNCPARAMS)
    #define COMPILE_EXAMPLE_UNARYFUNCPARAMS
#endif

//#undef RUN_EXAMPLE_UNARYFUNCPARAMS
#undef COMPILE_EXAMPLE_UNARYFUNCPARAMS

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_UNARYFUNCPARAMS
#include <MiniMPL/unaryFuncParams.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_unaryFuncParams()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);

    }

#ifdef RUN_EXAMPLE_UNARYFUNCPARAMS
    InitRunFunc(TestCase_unaryFuncParams);
#else //else of RUN_EXAMPLE_UNARYFUNCPARAMS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_UNARYFUNCPARAMS)=(outputTxtV(TXT("[Unit test run disabled] unaryFuncParams.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"unaryFuncParams.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_UNARYFUNCPARAMS
}

#else //else of COMPILE_EXAMPLE_UNARYFUNCPARAMS
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_UNARYFUNCPARAMS)=(outputTxtV(TXT("[Unit test compile disabled] unaryFuncParams.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"unaryFuncParams.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_UNARYFUNCPARAMS

