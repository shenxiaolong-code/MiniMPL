#include "../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\WinApiPack.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_WINAPIPACK to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_WINAPIPACK

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_WINAPIPACK
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_WINAPIPACK
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_WINAPIPACK
#endif

//#undef RUN_EXAMPLE_WINAPIPACK
//#undef COMPILE_EXAMPLE_WINAPIPACK

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_WINAPIPACK
#include <win32/WinApiPack.h>
#include <UnitTestKit/tc_tracer.h>

using namespace OS_Win32;
namespace UnitTest
{

    inline void TestCase_WinApiPack()
    {
        PrintTestcase();
        MiniMPL::dbgOutput(GetLastErrorText(rand()).c_str());

    }

#ifdef RUN_EXAMPLE_WINAPIPACK
    InitRunFunc(TestCase_WinApiPack);
#else //else of RUN_EXAMPLE_WINAPIPACK

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] WinApiPack.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"WinApiPack.h\".")
    #endif
#endif  	// RUN_EXAMPLE_WINAPIPACK
}

#else //else of COMPILE_EXAMPLE_WINAPIPACK
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] WinApiPack.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"WinApiPack.h\".")
    #endif
#endif // COMPILE_EXAMPLE_WINAPIPACK

