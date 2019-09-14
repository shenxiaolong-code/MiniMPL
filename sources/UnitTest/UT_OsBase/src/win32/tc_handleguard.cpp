#include "testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase/handleguard.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_HANDLEGUARD to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_HANDLEGUARD

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_HANDLEGUARD
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_HANDLEGUARD
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_HANDLEGUARD
#endif

//#undef RUN_EXAMPLE_HANDLEGUARD
//#undef COMPILE_EXAMPLE_HANDLEGUARD

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_HANDLEGUARD
#include <Win32/handleguard.h>
#include <UnitTestKit/tc_tracer.h>
#include <UnitTestKit/tc_path.h>
#include <win32/WinApiPack.h>

namespace UnitTest
{
    inline void TestCase_handleguard()
    {
        PrintTestcase();
        using namespace OS_Win32;
        stlStringA path=getOutputPathA();
        path += "\\UT_OsBase.cpp";

        //test CHandle constructor        
        CHandle hcRaw;
        CHandle hcFile(CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0));
        if (!hcFile.isValid())
        {
            MiniMPL::dbgOutput(GetLastErrorText(GetLastError()).c_str());
        }
        
        //test CHandle operator
        HANDLE hRaw = hcRaw;
        hRaw = hcFile;

        //test close
        CHandle hcFile1(hcFile);
        hcFile.close();
        ASSERT_AND_LOG(!hcFile1.isValid());
    }

#ifdef RUN_EXAMPLE_HANDLEGUARD
    InitRunFunc(TestCase_handleguard);
#else //else of RUN_EXAMPLE_HANDLEGUARD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] handleguard.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"handleguard.h\".")
    #endif
#endif  	// RUN_EXAMPLE_HANDLEGUARD
}

#else //else of COMPILE_EXAMPLE_HANDLEGUARD
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] handleguard.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"handleguard.h\".")
    #endif
#endif // COMPILE_EXAMPLE_HANDLEGUARD

