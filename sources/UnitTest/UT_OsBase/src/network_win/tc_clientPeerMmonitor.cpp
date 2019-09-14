#include "../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\clientPeerMmonitor.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_CLIENTPEERMMONITOR to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_CLIENTPEERMMONITOR

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_CLIENTPEERMMONITOR
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_CLIENTPEERMMONITOR
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_CLIENTPEERMMONITOR
#endif

//#undef RUN_EXAMPLE_CLIENTPEERMMONITOR
#undef COMPILE_EXAMPLE_CLIENTPEERMMONITOR

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_CLIENTPEERMMONITOR
#include <network_win/clientPeerMmonitor.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_clientPeerMmonitor()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);
        ALWAYS_COMPILE_MSG("NO Test context for <network_win/clientPeerMmonitor.h>");

    }

#ifdef RUN_EXAMPLE_CLIENTPEERMMONITOR
    InitRunFunc(TestCase_clientPeerMmonitor);
#else //else of RUN_EXAMPLE_CLIENTPEERMMONITOR

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] clientPeerMmonitor.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"clientPeerMmonitor.h\".")
    #endif
#endif  	// RUN_EXAMPLE_CLIENTPEERMMONITOR
}

#else //else of COMPILE_EXAMPLE_CLIENTPEERMMONITOR
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] clientPeerMmonitor.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"clientPeerMmonitor.h\".")
    #endif
#endif // COMPILE_EXAMPLE_CLIENTPEERMMONITOR

