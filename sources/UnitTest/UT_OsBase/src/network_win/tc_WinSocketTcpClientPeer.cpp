#include "../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\WinSocketSlot.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_WINSOCKETSLOT to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_WINSOCKETSLOT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_WINSOCKETSLOT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_WINSOCKETSLOT
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_WINSOCKETSLOT
#endif

//#undef RUN_EXAMPLE_WINSOCKETSLOT
#undef COMPILE_EXAMPLE_WINSOCKETSLOT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_WINSOCKETSLOT
#include <network_win/WinSocketTcpClientPeer.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_WinSocketSlot()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);

    }

#ifdef RUN_EXAMPLE_WINSOCKETSLOT
    InitRunFunc(TestCase_WinSocketSlot);
#else //else of RUN_EXAMPLE_WINSOCKETSLOT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] WinSocketSlot.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"WinSocketSlot.h\".")
    #endif
#endif  	// RUN_EXAMPLE_WINSOCKETSLOT
}

#else //else of COMPILE_EXAMPLE_WINSOCKETSLOT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] WinSocketSlot.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"WinSocketSlot.h\".")
    #endif
#endif // COMPILE_EXAMPLE_WINSOCKETSLOT

