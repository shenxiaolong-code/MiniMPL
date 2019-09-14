#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\classRegister.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_CLASSREGISTER to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_CLASSREGISTER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_CLASSREGISTER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_CLASSREGISTER
#endif

#if defined(RUN_EXAMPLE_CLASSREGISTER) && !defined(COMPILE_EXAMPLE_CLASSREGISTER)
    #define COMPILE_EXAMPLE_CLASSREGISTER
#endif

//#undef RUN_EXAMPLE_CLASSREGISTER
#undef COMPILE_EXAMPLE_CLASSREGISTER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_CLASSREGISTER
#include <MiniMPL/classRegister.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    inline void TestCase_classRegister()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);

    }

#ifdef RUN_EXAMPLE_CLASSREGISTER
    InitRunFunc(TestCase_classRegister);
#else //else of RUN_EXAMPLE_CLASSREGISTER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_CLASSREGISTER)=(outputTxtV(TXT("[Unit test run disabled] classRegister.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"classRegister.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_CLASSREGISTER
}

#else //else of COMPILE_EXAMPLE_CLASSREGISTER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_CLASSREGISTER)=(outputTxtV(TXT("[Unit test compile disabled] classRegister.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"classRegister.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_CLASSREGISTER

