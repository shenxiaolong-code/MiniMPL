#include "testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase/memmapfile.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MEMMAPFILE to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MEMMAPFILE

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MEMMAPFILE
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MEMMAPFILE
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_MEMMAPFILE
#endif

//#undef RUN_EXAMPLE_MEMMAPFILE
//#undef COMPILE_EXAMPLE_MEMMAPFILE

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MEMMAPFILE
#include <Win32/memmapfile.h>
#include <UnitTestKit/tc_tracer.h>
#include <UnitTestKit/tc_path.h>

namespace UnitTest
{

    inline void TestCase_memmapfile()
    {
        PrintTestcase();
        using namespace OS_Win32;
        stlStringA path=getOutputPathA();
        path += "\\UT_OsBase.cpp";

        //test CHandle constructor        
        CHandle hcRaw;
        CHandle hcFile(CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0));

        CMemMapFile memfile;
        LPVOID pVoid = memfile.acceptFile(hcFile,true);
        if (pVoid)
        {
            MiniMPL::dbgOutput((char*)pVoid);
        }

    }

#ifdef RUN_EXAMPLE_MEMMAPFILE
    InitRunFunc(TestCase_memmapfile);
#else //else of RUN_EXAMPLE_MEMMAPFILE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] memmapfile.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"memmapfile.h\".")
    #endif
#endif  	// RUN_EXAMPLE_MEMMAPFILE
}

#else //else of COMPILE_EXAMPLE_MEMMAPFILE
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] memmapfile.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"memmapfile.h\".")
    #endif
#endif // COMPILE_EXAMPLE_MEMMAPFILE

