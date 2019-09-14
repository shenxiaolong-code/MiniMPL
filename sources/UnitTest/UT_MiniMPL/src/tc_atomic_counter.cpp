#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\atomic_counter.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_ATOMIC_COUNTER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_ATOMIC_COUNTER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_ATOMIC_COUNTER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_ATOMIC_COUNTER
#endif

#if defined(RUN_EXAMPLE_ATOMIC_COUNTER) && !defined(COMPILE_EXAMPLE_ATOMIC_COUNTER)
    #define COMPILE_EXAMPLE_ATOMIC_COUNTER
#endif

//#undef RUN_EXAMPLE_ATOMIC_COUNTER
//#undef COMPILE_EXAMPLE_ATOMIC_COUNTER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_ATOMIC_COUNTER
#include <MiniMPL/atomic_counter.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_atomic_counter()
    {
        PrintTestcase();

        using namespace MiniMPL;
        atomic_counter counter;

        ASSERT_AND_LOG(1==++counter);
        ASSERT_AND_LOG(2==++counter);
        ASSERT_AND_LOG(1==--counter);
        ASSERT_AND_LOG(0==--counter);
        ASSERT_AND_LOG(1==++counter);
        ASSERT_AND_LOG(4==(counter+=3));
        ASSERT_AND_LOG(2==(counter-=2));

        ASSERT_AND_LOG(2==counter.reset());
        ASSERT_AND_LOG(0==counter);
    }

#ifdef RUN_EXAMPLE_ATOMIC_COUNTER
    InitRunFunc(TestCase_atomic_counter);
#else //else of RUN_EXAMPLE_ATOMIC_COUNTER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_ATOMIC_COUNTER)=(outputTxtV(TXT("[Unit test run disabled] atomic_counter.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"atomic_counter.h\".")
    #endif
#endif  	// RUN_EXAMPLE_ATOMIC_COUNTER
}

#else //else of COMPILE_EXAMPLE_ATOMIC_COUNTER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_ATOMIC_COUNTER)=(outputTxtV(TXT("[Unit test compile disabled] atomic_counter.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"atomic_counter.h\".")
    #endif
#endif // COMPILE_EXAMPLE_ATOMIC_COUNTER

