#include "testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase/folderitemfounder.h>
* Author              : Shen.Xiaolong (Shen Tony,2009-2017)
* Mail                : xlshen2002@gmail.com,  xlshen@126.com
* verified platform   : VS2008 (create/refactor on 2017-03-06 16:03:35.89)
* copyright:          : free to use / modify / sale in free and commercial software.
*                       Unique limit: MUST keep those copyright comments in all copies and in supporting documentation.
* usage demo          : #define RUN_EXAMPLE_FOLDERITEMFOUNDER to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_FOLDERITEMFOUNDER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_FOLDERITEMFOUNDER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_FOLDERITEMFOUNDER
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_FOLDERITEMFOUNDER
#endif

//#undef RUN_EXAMPLE_FOLDERITEMFOUNDER
//#undef COMPILE_EXAMPLE_FOLDERITEMFOUNDER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_FOLDERITEMFOUNDER
#include <win32/folderitemfounder.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    using namespace OS_Win32;

    inline void TestCase_folderitemfounder()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        //Static_Assert(0);
        ALWAYS_COMPILE_MSG("NO Test context for <win32/folderitemfounder.h>");

    }

#ifdef RUN_EXAMPLE_FOLDERITEMFOUNDER
    InitRunFunc(TestCase_folderitemfounder);
#else //else of RUN_EXAMPLE_FOLDERITEMFOUNDER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxt((TXT("[Unit test run disabled] folderitemfounder.h\n%s(%d)\n"),TXT(__FILE__),__LINE__)),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"folderitemfounder.h\".")
    #endif
#endif  	// RUN_EXAMPLE_FOLDERITEMFOUNDER
}

#else //else of COMPILE_EXAMPLE_FOLDERITEMFOUNDER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxt((TXT("[Unit test compile disabled] folderitemfounder.h\n%s(%d)\n"),TXT(__FILE__),__LINE__)),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"folderitemfounder.h\".")
    #endif
#endif // COMPILE_EXAMPLE_FOLDERITEMFOUNDER

