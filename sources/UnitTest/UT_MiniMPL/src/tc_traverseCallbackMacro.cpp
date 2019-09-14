#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\traverseCallbackMacro.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_TRAVERSECALLBACKMACRO to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_TRAVERSECALLBACKMACRO

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_TRAVERSECALLBACKMACRO
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_TRAVERSECALLBACKMACRO
#endif

#if defined(RUN_EXAMPLE_TRAVERSECALLBACKMACRO) && !defined(COMPILE_EXAMPLE_TRAVERSECALLBACKMACRO)
    #define COMPILE_EXAMPLE_TRAVERSECALLBACKMACRO
#endif

//#undef RUN_EXAMPLE_TRAVERSECALLBACKMACRO
#undef COMPILE_EXAMPLE_TRAVERSECALLBACKMACRO

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_TRAVERSECALLBACKMACRO
#include <MiniMPL/traverseCallbackMacro.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_traverseCallbackMacro()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);

    }

#ifdef RUN_EXAMPLE_TRAVERSECALLBACKMACRO
    InitRunFunc(TestCase_traverseCallbackMacro);
#else //else of RUN_EXAMPLE_TRAVERSECALLBACKMACRO

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_TRAVERSECALLBACKMACRO)=(outputTxtV(TXT("[Unit test run disabled] traverseCallbackMacro.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"traverseCallbackMacro.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_TRAVERSECALLBACKMACRO
}

#else //else of COMPILE_EXAMPLE_TRAVERSECALLBACKMACRO
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_TRAVERSECALLBACKMACRO)=(outputTxtV(TXT("[Unit test compile disabled] traverseCallbackMacro.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"traverseCallbackMacro.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_TRAVERSECALLBACKMACRO

