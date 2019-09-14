#include <testconfig_OsBase.h>
#include <MiniMPL/macroDef.h>
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\threadCreater_win.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_THREADCREATER_WIN to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_THREADCREATER_WIN

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_THREADCREATER_WIN
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_THREADCREATER_WIN
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_THREADCREATER_WIN
#endif

//#undef RUN_EXAMPLE_THREADCREATER_WIN
//#undef COMPILE_EXAMPLE_THREADCREATER_WIN

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_THREADCREATER_WIN
#include <thread/win32/inc/threadCreater_win.h>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_thread.h>

namespace UnitTest
{

    inline void TestCase_threadCreater_win()
    {
        PrintTestcase();
        outputTxt(L"test COSThreadCreater_Win:\n");

        tc_thread thrd;
        thrd.m_number = 1;
        OS_Win32::COSThreadCreater_Win createrWin;
        createrWin.startThread(thrd);
        createrWin.waitThreadExit(5000,true);
        AssertXI(2==thrd.m_number,(L"Fails to test COSThreadCreater_Win::startThread"));
    }

#ifdef RUN_EXAMPLE_THREADCREATER_WIN
    InitRunFunc(TestCase_threadCreater_win);
#else //else of RUN_EXAMPLE_THREADCREATER_WIN

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] threadCreater_win.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"threadCreater_win.h\".")
    #endif
#endif  	// RUN_EXAMPLE_THREADCREATER_WIN
}

#else //else of COMPILE_EXAMPLE_THREADCREATER_WIN
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] threadCreater_win.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"threadCreater_win.h\".")
    #endif
#endif // COMPILE_EXAMPLE_THREADCREATER_WIN

