#include "testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase/calllocker.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_CALLLOCKER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_CALLLOCKER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_CALLLOCKER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_CALLLOCKER
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_CALLLOCKER
#endif

//#undef RUN_EXAMPLE_CALLLOCKER
//#undef COMPILE_EXAMPLE_CALLLOCKER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_CALLLOCKER
#include <thread/calllocker.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    struct DemoLockCall : public TLockCallBase<DemoLockCall>
    {
        void exclusionOp()
        {
            MiniMPL::dbgOutput(("UnitTest.DemoLockCall.exclusionOp\n"));
        }

        void testReadyExclusion()
        {
            innerLock();
            MiniMPL::dbgOutput(("UnitTest.DemoLockCall.testReadyExclusion\n"));
        }
    };

    struct DemoLockCallCompileFail
    {
        void exclusionOp()
        {
            MiniMPL::dbgOutput(("UnitTest.DemoLockCallCompileFail.exclusionOp\n"));
        }
    };

    inline void TestCase_calllocker()
    {
        PrintTestcase();
        DemoLockCall obj;
        obj.useLocker()->exclusionOp();
        obj.testReadyExclusion();
        
        makeCallLocker(obj,obj.m_lock)->exclusionOp();

        CSyncThread lock;
        makeCallLocker(obj,lock)->exclusionOp();

        //OK , compile fail : construct base instance directly
        //TLockCallBase<DemoLockCall>().makeCallLocker();

        //OK , compile fail : DemoLockCallCompileFail isn't derived from TLockCallBase<DemoLockCallCompileFail>
        //TLockCallBase<DemoExcludeCallCompileFail>().makeCallLocker();
    }

#ifdef RUN_EXAMPLE_CALLLOCKER
    InitRunFunc(TestCase_calllocker);
#else //else of RUN_EXAMPLE_CALLLOCKER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] calllocker.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"calllocker.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_CALLLOCKER
}

#else //else of COMPILE_EXAMPLE_CALLLOCKER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] calllocker.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"calllocker.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_CALLLOCKER

