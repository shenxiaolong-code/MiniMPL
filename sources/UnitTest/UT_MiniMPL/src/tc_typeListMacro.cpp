#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\typeListMacro.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_TYPELISTMACRO to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_TYPELISTMACRO

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_TYPELISTMACRO
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_TYPELISTMACRO
#endif

#if defined(RUN_EXAMPLE_TYPELISTMACRO) && !defined(COMPILE_EXAMPLE_TYPELISTMACRO)
    #define COMPILE_EXAMPLE_TYPELISTMACRO
#endif

//#undef RUN_EXAMPLE_TYPELISTMACRO
#undef COMPILE_EXAMPLE_TYPELISTMACRO

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_TYPELISTMACRO
#include <MiniMPL/typeListMacro.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_typeListMacro()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);

    }

#ifdef RUN_EXAMPLE_TYPELISTMACRO
    InitRunFunc(TestCase_typeListMacro);
#else //else of RUN_EXAMPLE_TYPELISTMACRO

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_TYPELISTMACRO)=(outputTxtV(TXT("[Unit test run disabled] typeListMacro.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"typeListMacro.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_TYPELISTMACRO
}

#else //else of COMPILE_EXAMPLE_TYPELISTMACRO
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_TYPELISTMACRO)=(outputTxtV(TXT("[Unit test compile disabled] typeListMacro.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"typeListMacro.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_TYPELISTMACRO

