#include <testconfig_OsBase.h>
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\threadManager.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_THREADMANAGER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_THREADMANAGER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_THREADMANAGER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_THREADMANAGER
#endif

#if defined(RUN_EXAMPLE_THREADMANAGER) && !defined(COMPILE_EXAMPLE_THREADMANAGER)
    #define COMPILE_EXAMPLE_THREADMANAGER
#endif

//#undef RUN_EXAMPLE_THREADMANAGER
//#undef COMPILE_EXAMPLE_THREADMANAGER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_THREADMANAGER
#include <thread/threadManager.h>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_thread.h>

namespace UnitTest
{

    inline void TestCase_threadManager()
    {
        PrintTestcase();
        CThreadMananger& rInst = CThreadMananger::getInstance();
        int others=rInst.size();
        CThread thrd0[3];
        ASSERT_AND_LOG((others+3)==rInst.size());
        tc_thread exThrd[2];
        ASSERT_AND_LOG((others+5)==rInst.size());
        TpThread pThrd=TpThread(new CThread());
        ASSERT_AND_LOG((others+6)==rInst.size());
        pThrd.reset();
        ASSERT_AND_LOG((others+5)==rInst.size());
        
    }

#ifdef RUN_EXAMPLE_THREADMANAGER
    InitRunFunc(TestCase_threadManager);
#else //else of RUN_EXAMPLE_THREADMANAGER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_THREADMANAGER)=(outputTxtV(TXT("[Unit test run disabled] threadManager.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"threadManager.h\".")
    #endif
#endif  	// RUN_EXAMPLE_THREADMANAGER
}

#else //else of COMPILE_EXAMPLE_THREADMANAGER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_THREADMANAGER)=(outputTxtV(TXT("[Unit test compile disabled] threadManager.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"threadManager.h\".")
    #endif
#endif // COMPILE_EXAMPLE_THREADMANAGER

