#include "../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\IReceiver.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_IRECEIVER to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_IRECEIVER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_IRECEIVER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_IRECEIVER
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_IRECEIVER
#endif

//#undef RUN_EXAMPLE_IRECEIVER
#undef COMPILE_EXAMPLE_IRECEIVER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_IRECEIVER
#include <communicator/IReceiver.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_IReceiver()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);

    }

#ifdef RUN_EXAMPLE_IRECEIVER
    InitRunFunc(TestCase_IReceiver);
#else //else of RUN_EXAMPLE_IRECEIVER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] IReceiver.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"IReceiver.h\".")
    #endif
#endif  	// RUN_EXAMPLE_IRECEIVER
}

#else //else of COMPILE_EXAMPLE_IRECEIVER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] IReceiver.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"IReceiver.h\".")
    #endif
#endif // COMPILE_EXAMPLE_IRECEIVER

