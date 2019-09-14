#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macroDef.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\macro_traceLog.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MACRO_TRACELOG to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MACRO_TRACELOG

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MACRO_TRACELOG
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MACRO_TRACELOG
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_MACRO_TRACELOG
#endif

//#undef RUN_EXAMPLE_MACRO_TRACELOG
//#undef COMPILE_EXAMPLE_MACRO_TRACELOG

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MACRO_TRACELOG
#include <MiniMPL/macro_traceLog.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_macro_traceLog()
    {
        PrintTestcase();
        using namespace MiniMPL;

        int Var32 = 123;

        outputTxt(TXT("demo HEREINFO :\n") HEREINFO() TXT("\n"));
        outputTxtStreamA("e.g."     << __FUNCTION__       << " "      << __LINE__   << " "      << 123 << std::endl     );
        outputTxtStreamW(L"e.g."    << TXTW(__FUNCTION__) << L" "     << __LINE__   << L" "     << 123 << L"\r\n"       );
        outputTxtStream(TXT("e.g.") << TXT(__FUNCTION__)  << TXT(" ") << __LINE__   << TXT(" ") << 123 << TXT("\r\n")   );


        //////////////////////////////////////////////////////////////////////////
        ALWAYS_LOG_HERE();
        ALWAYS_LOG_HERE_INFO((TXT("Demo ALWAYS_LOG_HERE_INFO")));
        ALWAYS_LOG_HERE_INFO((TXT("\ndemo ALWAYS_LOG_HERE_INFO : Var32=%d,str=%s"),Var32,TXT("Demo")));

        TRACE_HERE();
        TRACE_HERE_INFO((TXT("demo TRACE_HERE : Var32=%d,str=%s"),Var32,TXT("Demo")));

        ALWAYS_LOG_HERE_INFO((TXT("\ndemo TRACE_INFO : Var32=%d,str=%s"),Var32,TXT("Demo")));
    }

#ifdef RUN_EXAMPLE_MACRO_TRACELOG
    InitRunFunc(TestCase_macro_traceLog);
#else //else of RUN_EXAMPLE_MACRO_TRACELOG

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] macro_traceLog.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"macro_traceLog.h\".")
    #endif
#endif  	// RUN_EXAMPLE_MACRO_TRACELOG
}

#else //else of COMPILE_EXAMPLE_MACRO_TRACELOG
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] macro_traceLog.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"macro_traceLog.h\".")
    #endif
#endif // COMPILE_EXAMPLE_MACRO_TRACELOG

