#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\macroDef.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MACRODEF to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MACRODEF

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MACRODEF
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MACRODEF
#endif

#if defined(RUN_EXAMPLE_MACRODEF) && !defined(COMPILE_EXAMPLE_MACRODEF)
    #define COMPILE_EXAMPLE_MACRODEF
#endif

//#undef RUN_EXAMPLE_MACRODEF
//#undef COMPILE_EXAMPLE_MACRODEF

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MACRODEF
#include <MiniMPL/macroDef.h>
#include <UnitTestKit/tc_tracer.h>
#include <windows.h>

namespace UnitTest
{
    inline void TestCase_macroDef()
    {
        PrintTestcase();

        int Var32 = 123;
        outputTxt(TXT("this is one demo for outputTxt.\n"));
        outputTxtV(TXT("demo MAKEVAR2 : Var32=%d\n"),MAKEVAR2(Var,32));
        outputTxtV(TXT("demo MAKEVAR3 : Var32=%d\n"),MAKEVAR3(Var,3,2));

        TRACE_INFO((TXT("\ndemo TRACE_INFO : Var32=%d,str=%s\n"),Var32,TXT("Demo")));
    }

#ifdef RUN_EXAMPLE_MACRODEF
    InitRunFunc(TestCase_macroDef);
#else //else of RUN_EXAMPLE_MACRODEF

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_MACRODEF)=(outputTxtV(TXT("[Unit test run disabled] macroDef.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"macroDef.h\".")
    #endif
#endif  	// RUN_EXAMPLE_MACRODEF
}

#else //else of COMPILE_EXAMPLE_MACRODEF
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_MACRODEF)=(outputTxtV(TXT("[Unit test compile disabled] macroDef.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"macroDef.h\".")
    #endif
#endif // COMPILE_EXAMPLE_MACRODEF

