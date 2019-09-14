#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\any_cast.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_ANY_CAST to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_ANY_CAST

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_ANY_CAST
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_ANY_CAST
#endif

#if defined(RUN_EXAMPLE_ANY_CAST) && !defined(COMPILE_EXAMPLE_ANY_CAST)
    #define COMPILE_EXAMPLE_ANY_CAST
#endif

//#undef RUN_EXAMPLE_ANY_CAST
#undef COMPILE_EXAMPLE_ANY_CAST

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_ANY_CAST
#include <MiniMPL/any_cast.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_any_cast()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);

    }

#ifdef RUN_EXAMPLE_ANY_CAST
    InitRunFunc(TestCase_any_cast);
#else //else of RUN_EXAMPLE_ANY_CAST

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_ANY_CAST)=(outputTxtV(TXT("[Unit test run disabled] any_cast.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"any_cast.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_ANY_CAST
}

#else //else of COMPILE_EXAMPLE_ANY_CAST
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_ANY_CAST)=(outputTxtV(TXT("[Unit test compile disabled] any_cast.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"any_cast.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_ANY_CAST

