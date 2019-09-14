#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL/stringtrait.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_STRINGTRAIT to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_STRINGTRAIT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_STRINGTRAIT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_STRINGTRAIT
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_STRINGTRAIT
#endif

//#undef RUN_EXAMPLE_STRINGTRAIT
//#undef COMPILE_EXAMPLE_STRINGTRAIT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_STRINGTRAIT
#include <MiniMPL/stringtrait.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <MiniMPL/macro_assert.h>

namespace UnitTest
{
    using namespace MiniMPL;

    inline void TestCase_stringtrait()
    {
        PrintTestcase();

        Static_Assert((IsSameType<char,getCharType<char*>::type>::value));
        Static_Assert(!(IsSameType<char,getCharType<wchar_t*>::type>::value));

        Static_Assert((IsSameType<char,getCharType<stlStringA>::type>::value));
        Static_Assert(!(IsSameType<char,getCharType<stlStringW>::type>::value));

        Static_Assert((IsSameType<char,getCharType<char[4]>::type>::value));
        Static_Assert((IsSameType<char,getCharType<char(&)[4]>::type>::value));

        Static_Assert(!(IsSameType<wchar_t,getCharType<char*>::type>::value));
        Static_Assert((IsSameType<wchar_t,getCharType<wchar_t*>::type>::value));

        Static_Assert(!(IsSameType<wchar_t,getCharType<stlStringA>::type>::value));
        Static_Assert((IsSameType<wchar_t,getCharType<stlStringW>::type>::value));

        Static_Assert(!(IsSameType<wchar_t,getCharType<char[4]>::type>::value));
        Static_Assert(!(IsSameType<wchar_t,getCharType<char(&)[4]>::type>::value));

    }

#ifdef RUN_EXAMPLE_STRINGTRAIT
    InitRunFunc(TestCase_stringtrait);
#else //else of RUN_EXAMPLE_STRINGTRAIT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] stringtrait.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"stringtrait.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_STRINGTRAIT
}

#else //else of COMPILE_EXAMPLE_STRINGTRAIT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] stringtrait.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"stringtrait.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_STRINGTRAIT

