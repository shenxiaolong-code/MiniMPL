#include <testconfig_OsBase.h>
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\asyncCall.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_ASYNCCALL to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_ASYNCCALL

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_ASYNCCALL
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_ASYNCCALL
#endif

#if defined(RUN_EXAMPLE_ASYNCCALL) && !defined(COMPILE_EXAMPLE_ASYNCCALL)
    #define COMPILE_EXAMPLE_ASYNCCALL
#endif

//#undef RUN_EXAMPLE_ASYNCCALL
//#undef COMPILE_EXAMPLE_ASYNCCALL

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_ASYNCCALL
#include <thread/asyncCall.h>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_thread.h>

namespace UnitTest
{

    inline void TestCase_asyncCall()
    {
        PrintTestcase();
        using namespace MiniMPL;
        tc_thread td;
        asyncExecute(TpCallbacker(makeCallbacker(&tc_thread::run,td)));
        td.m_wait.waitNotification(); //life cycle confirm

        asyncExecute(TpCallbacker(makeCallbacker(&tc_thread::run,td)),EAsync_NewThread);

        waitAllThreadExit(1);  //1 local thread object
    }

#ifdef RUN_EXAMPLE_ASYNCCALL
    InitRunFunc(TestCase_asyncCall);
#else //else of RUN_EXAMPLE_ASYNCCALL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_ASYNCCALL)=(outputTxtV(TXT("[Unit test run disabled] asyncCall.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"asyncCall.h\".")
    #endif
#endif  	// RUN_EXAMPLE_ASYNCCALL
}

#else //else of COMPILE_EXAMPLE_ASYNCCALL
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_ASYNCCALL)=(outputTxtV(TXT("[Unit test compile disabled] asyncCall.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"asyncCall.h\".")
    #endif
#endif // COMPILE_EXAMPLE_ASYNCCALL

