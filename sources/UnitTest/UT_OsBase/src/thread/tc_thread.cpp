#include <testconfig_OsBase.h>
#include <MiniMPL/macroDef.h>
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\thread.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_THREAD to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_THREAD

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_THREAD
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_THREAD
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_THREAD
#endif

//#undef RUN_EXAMPLE_THREAD
//#undef COMPILE_EXAMPLE_THREAD

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_THREAD
#include <thread/thread.h>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_thread.h>

namespace UnitTest
{  
    inline void TestCase_threadImpl()
    {
        PrintTestcase();
        outputTxt(L"test callee in derived class:");
        tc_thread tc_thrd;
        tc_thrd.m_number = 7;
        tc_thrd.start();
        tc_thrd.stop();
        ASSERT_AND_LOG(8==tc_thrd.m_number);

        outputTxt(L"test callee in data member pointer:");
        CThread  thrd;
        thrd.setCallback(&UnitTest::tc_thread::run,tc_thrd);
        thrd.start();
        thrd.stop();
        ASSERT_AND_LOG(9==tc_thrd.m_number);
        /*
        CNewThread* pNewThread = new CNewThread();
        pNewThread->setCallback(&UnitTest::tc_thread::run,tc_thrd);
        pNewThread->start();
        */
        waitAllThreadExit(2);    //2 local thread object
    }

    inline void TestCase_thread()
    {
        TestCase_threadImpl();

        waitAllThreadExit(0);   //wait CNewThread exit
    }

#ifdef RUN_EXAMPLE_THREAD
    InitRunFunc(TestCase_thread);
#else //else of RUN_EXAMPLE_THREAD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] thread.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"thread.h\".")
    #endif
#endif  	// RUN_EXAMPLE_THREAD
}

#else //else of COMPILE_EXAMPLE_THREAD
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] thread.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"thread.h\".")
    #endif
#endif // COMPILE_EXAMPLE_THREAD

