#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\longJumpMacro.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MACRO_LONGJUMP to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_MACRO_LONGJUMP

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MACRO_LONGJUMP
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MACRO_LONGJUMP
#endif

#if defined(RUN_EXAMPLE_MACRO_LONGJUMP) && !defined(COMPILE_EXAMPLE_MACRO_LONGJUMP)
    #define COMPILE_EXAMPLE_MACRO_LONGJUMP
#endif

//#undef RUN_EXAMPLE_MACRO_LONGJUMP
#undef COMPILE_EXAMPLE_MACRO_LONGJUMP

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MACRO_LONGJUMP
#include <MiniMPL/longJumpMacro.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_longJumpMacro()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);

    }

#ifdef RUN_EXAMPLE_MACRO_LONGJUMP
    InitRunFunc(TestCase_longJumpMacro);
#else //else of RUN_EXAMPLE_MACRO_LONGJUMP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_MACRO_LONGJUMP)=(outputTxtV(TXT("[Unit test run disabled] longJumpMacro.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"longJumpMacro.h\".")
    #endif
#endif  	// RUN_EXAMPLE_MACRO_LONGJUMP
}

#else //else of COMPILE_EXAMPLE_MACRO_LONGJUMP
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_MACRO_LONGJUMP)=(outputTxtV(TXT("[Unit test compile disabled] longJumpMacro.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"longJumpMacro.h\".")
    #endif
#endif // COMPILE_EXAMPLE_MACRO_LONGJUMP

