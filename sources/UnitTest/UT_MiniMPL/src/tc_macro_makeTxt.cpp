#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macroDef.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\macro_makeTxt.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MACRO_MAKETXT to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MACRO_MAKETXT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MACRO_MAKETXT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MACRO_MAKETXT
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_MACRO_MAKETXT
#endif

//#undef RUN_EXAMPLE_MACRO_MAKETXT
//#undef COMPILE_EXAMPLE_MACRO_MAKETXT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MACRO_MAKETXT
#include <MiniMPL/macro_makeTxt.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_macro_makeTxt()
    {
        PrintTestcase();

        outputTxt(TXT("Demo MAKESTR\n"));
        outputTxt(MAKESTR(48));
        outputTxt(TXT("\n"));
        outputTxt(MAKESTR2(48,<==Demo MAKESTR2));
        outputTxt(TXT("\n"));
        outputTxt(MAKESTR3(48,<==Demo MAKESTR3,\n));

        outputTxt(MAKESTR(Condition(1)));

        outputTxt(TXT("\n"));
        outputTxt(MAKESTR(InitRunFunc(TestCase_Macro)));
        PrintRN();
        outputTxt(MAKESTR(InitRunFunc(TestCase_Macro)));
        PrintRN();
        outputTxt(MAKESTR(InitRunFunc(TestCase_Macro)));

    }

#ifdef RUN_EXAMPLE_MACRO_MAKETXT
    InitRunFunc(TestCase_macro_makeTxt);
#else //else of RUN_EXAMPLE_MACRO_MAKETXT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] macro_makeTxt.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"macro_makeTxt.h\".")
    #endif
#endif  	// RUN_EXAMPLE_MACRO_MAKETXT
}

#else //else of COMPILE_EXAMPLE_MACRO_MAKETXT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] macro_makeTxt.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"macro_makeTxt.h\".")
    #endif
#endif // COMPILE_EXAMPLE_MACRO_MAKETXT

