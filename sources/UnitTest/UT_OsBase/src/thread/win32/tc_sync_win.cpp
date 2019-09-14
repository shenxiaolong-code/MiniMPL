#include <testconfig_OsBase.h>
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\sync_win.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SYNC_WIN to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_SYNC_WIN

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SYNC_WIN
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SYNC_WIN
#endif

#if defined(RUN_EXAMPLE_SYNC_WIN) && !defined(COMPILE_EXAMPLE_SYNC_WIN)
    #define COMPILE_EXAMPLE_SYNC_WIN
#endif

//#undef RUN_EXAMPLE_SYNC_WIN
//#undef COMPILE_EXAMPLE_SYNC_WIN

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SYNC_WIN
#include <thread/win32/inc/sync_win.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_sync_win()
    {
        PrintTestcase();

        using namespace OS_Win32;

        CSyncNotifier_Win   notiwin;
        CSyncThread_Win     syncThrd;
        CSyncProcess_Win    syncPross(NULL);

    }

#ifdef RUN_EXAMPLE_SYNC_WIN
    InitRunFunc(TestCase_sync_win);
#else //else of RUN_EXAMPLE_SYNC_WIN

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_SYNC_WIN)=(outputTxtV(TXT("[Unit test run disabled] sync_win.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"sync_win.h\".")
    #endif
#endif  	// RUN_EXAMPLE_SYNC_WIN
}

#else //else of COMPILE_EXAMPLE_SYNC_WIN
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_SYNC_WIN)=(outputTxtV(TXT("[Unit test compile disabled] sync_win.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"sync_win.h\".")
    #endif
#endif // COMPILE_EXAMPLE_SYNC_WIN

