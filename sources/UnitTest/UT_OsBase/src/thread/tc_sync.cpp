#include <testconfig_OsBase.h>
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\sync.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SYNC to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_SYNC

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SYNC
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SYNC
#endif

#if defined(RUN_EXAMPLE_SYNC) && !defined(COMPILE_EXAMPLE_SYNC)
    #define COMPILE_EXAMPLE_SYNC
#endif

//#undef RUN_EXAMPLE_SYNC
//#undef COMPILE_EXAMPLE_SYNC

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SYNC
#include <thread/sync.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_sync()
    {
        PrintTestcase();

        CSyncNotifier   notiwinb;

        CSyncThread     syncThrdb;
        LockHere(syncThrdb);

        CSyncProcess    syncProssb;
        LockHere(syncProssb);

    }

#ifdef RUN_EXAMPLE_SYNC
    InitRunFunc(TestCase_sync);
#else //else of RUN_EXAMPLE_SYNC

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_SYNC)=(outputTxtV(TXT("[Unit test run disabled] sync.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"sync.h\".")
    #endif
#endif  	// RUN_EXAMPLE_SYNC
}

#else //else of COMPILE_EXAMPLE_SYNC
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_SYNC)=(outputTxtV(TXT("[Unit test compile disabled] sync.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"sync.h\".")
    #endif
#endif // COMPILE_EXAMPLE_SYNC

