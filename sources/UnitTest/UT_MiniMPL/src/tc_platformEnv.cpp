#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\platformEnv.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_PLATFORMENV to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_PLATFORMENV

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_PLATFORMENV
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_PLATFORMENV
#endif

#if defined(RUN_EXAMPLE_PLATFORMENV) && !defined(COMPILE_EXAMPLE_PLATFORMENV)
    #define COMPILE_EXAMPLE_PLATFORMENV
#endif

//#undef RUN_EXAMPLE_PLATFORMENV
//#undef COMPILE_EXAMPLE_PLATFORMENV

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_PLATFORMENV
#include <MiniMPL/platformEnv.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    inline void TestCase_platformEnv()
    {
        PrintTestcase();
#ifdef MSVC
        ALWAYS_COMPILE_MSG("************** Test platform environment **************");
        #pragma message("it is microsoft Visual C++ development enviorment")
        #pragma message("\r\nvisual studio version list:")
        plat_info_vsList();

        #pragma message("\r\ncurrent visual studio version info:")
        plat_info_vs();

        #pragma message("\r\nC++11 support info:")
        plat_info_cpp();

        #pragma message("\r\nRTTI support info:")
        plat_info_rtti();
#else
        # error "NO supported platform test case"
#endif
    }

#ifdef RUN_EXAMPLE_PLATFORMENV
    InitRunFunc(TestCase_platformEnv);
#else //else of RUN_EXAMPLE_PLATFORMENV

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_PLATFORMENV)=(outputTxtV(TXT("[Unit test run disabled] platformEnv.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"platformEnv.h\".")
    #endif
#endif  	// RUN_EXAMPLE_PLATFORMENV
}

#else //else of COMPILE_EXAMPLE_PLATFORMENV
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_PLATFORMENV)=(outputTxtV(TXT("[Unit test compile disabled] platformEnv.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"platformEnv.h\".")
    #endif
#endif // COMPILE_EXAMPLE_PLATFORMENV

