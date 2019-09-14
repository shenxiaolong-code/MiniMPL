#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macroDef.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\vldFix.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_VLDFIX to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_VLDFIX

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_VLDFIX
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_VLDFIX
#endif

#if defined(RUN_EXAMPLE_VLDFIX) && !defined(COMPILE_EXAMPLE_VLDFIX)
    #define COMPILE_EXAMPLE_VLDFIX
#endif

#undef RUN_EXAMPLE_VLDFIX
//#undef COMPILE_EXAMPLE_VLDFIX

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_VLDFIX
#include <MiniMPL/vldFix.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_vldFix()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
    }

#ifdef RUN_EXAMPLE_VLDFIX
    InitRunFunc(TestCase_vldFix);
#else //else of RUN_EXAMPLE_VLDFIX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_VLDFIX)=(outputTxtV(TXT("[Unit test run disabled] vldFix.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"vldFix.h\".")
    #endif
#endif  	// RUN_EXAMPLE_VLDFIX
}

#else //else of COMPILE_EXAMPLE_VLDFIX
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_VLDFIX)=(outputTxtV(TXT("[Unit test compile disabled] vldFix.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"vldFix.h\".")
    #endif
#endif // COMPILE_EXAMPLE_VLDFIX

