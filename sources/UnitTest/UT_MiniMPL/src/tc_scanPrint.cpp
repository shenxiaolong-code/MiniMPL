#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\scanPrint.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SCANPRINT to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_SCANPRINT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SCANPRINT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SCANPRINT
#endif

#if defined(RUN_EXAMPLE_SCANPRINT) && !defined(COMPILE_EXAMPLE_SCANPRINT)
    #define COMPILE_EXAMPLE_SCANPRINT
#endif

//#undef RUN_EXAMPLE_SCANPRINT
//#undef COMPILE_EXAMPLE_SCANPRINT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SCANPRINT
#include <MiniMPL/scanPrint.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <MiniMPL/isXXXEx.hpp>

namespace UnitTest
{
    template<typename T>
    void testgetFmt(int idx)
    {
        using namespace MiniMPL;
        ASSERT_AND_LOG((getFmt<char,T>()==strFmtA[idx]));
        ASSERT_AND_LOG((getFmt<wchar_t,T>()==strFmtW[idx]));

        ASSERT_AND_LOG((getFmt<char,T const>()==strFmtA[idx]));
        ASSERT_AND_LOG((getFmt<wchar_t,T const>()==strFmtW[idx]));

        ASSERT_AND_LOG((getFmt<char,T&>()==strFmtA[idx]));
        ASSERT_AND_LOG((getFmt<wchar_t,T&>()==strFmtW[idx]));

        ASSERT_AND_LOG((getFmt<char,T const&>()==strFmtA[idx]));
        ASSERT_AND_LOG((getFmt<wchar_t,T const&>()==strFmtW[idx]));
    }

    template<typename T, int TVal>
    void testFmtIdx()
    {
        using namespace MiniMPL;
        Static_Assert((CFormatIdx<T>::value == TVal));
        Static_Assert((CFormatIdx<T const>::value == TVal));
        Static_Assert((CFormatIdx<T&>::value == TVal));

        testgetFmt<T>(TVal);
    }

    inline void TestCase_scanPrint()
    {
        PrintTestcase();
        
        using namespace MiniMPL;

        //test CFormatIdx
        testFmtIdx<char,0>();
        testFmtIdx<wchar_t,0>();
        testFmtIdx<unsigned char,0>();
        testFmtIdx<int,1>();
        testFmtIdx<short,1>();
        testFmtIdx<bool,1>();
        testFmtIdx<unsigned int,2>();
        testFmtIdx<unsigned short,2>();
        testFmtIdx<float,3>();
        testFmtIdx<double,4>();
        testFmtIdx<char*,5>();
        testFmtIdx<wchar_t*,5>();
        testFmtIdx<__int64,6>();
        testFmtIdx<unsigned __int64,7>();

        //test GetFmtArr
        ASSERT_AND_LOG(GetFmtArr<char>::value==strFmtA);
        ASSERT_AND_LOG(GetFmtArr<wchar_t>::value==strFmtW);

#if ENABLE_UNSAFE_SCANPRINT
        //test StrPrintType
        Static_Assert((IsSameType<StrPrintType<char>::type,int (__cdecl *)(char *,const char *,...)>::value));
        Static_Assert((IsSameType<StrPrintType<wchar_t>::type,int (__cdecl *)(wchar_t *,const wchar_t *,...)>::value));
#endif // ENABLE_UNSAFE_SCANPRINT

        //test StrPrintTypeS
        Static_Assert((IsSameType<StrPrintTypeS<char>::type,int (__cdecl *)(char *,unsigned int,const char *,...)>::value));
        Static_Assert((IsSameType<StrPrintTypeS<wchar_t>::type,int (__cdecl *)(wchar_t *,unsigned int,const wchar_t *,...)>::value));

#if ENABLE_UNSAFE_SCANPRINT
        //test GetPrintfFunc
        ASSERT_AND_LOG(NULL != GetPrintfFunc<char>::value);
        ASSERT_AND_LOG(NULL != GetPrintfFunc<wchar_t>::value);
#endif // ENABLE_UNSAFE_SCANPRINT

        //test StrPrintTypeS
        Static_Assert((IsSameType<StrPrintTypeS<char>::type,int (__cdecl *)(char *,unsigned int,const char *,...)>::value));
        Static_Assert((IsSameType<StrPrintTypeS<wchar_t>::type,int (__cdecl *)(wchar_t *,unsigned int,const wchar_t *,...)>::value));

        //test GetPrintfFuncS
        ASSERT_AND_LOG(NULL != GetPrintfFuncS<char>::value);
        ASSERT_AND_LOG(NULL != GetPrintfFuncS<wchar_t>::value);

#if ENABLE_UNSAFE_SCANPRINT
        //test StrPrintTypeS
        Static_Assert((IsSameType<StrScanfType<char>::type,int (__cdecl *)(const char *,const char *,...)>::value));
        Static_Assert((IsSameType<StrScanfType<wchar_t>::type,int (__cdecl *)(const wchar_t *,const wchar_t *,...)>::value));
#endif // ENABLE_UNSAFE_SCANPRINT

#if ENABLE_UNSAFE_SCANPRINT
        //test GetScanfFunc
        ASSERT_AND_LOG(NULL != GetScanfFunc<char>::value);
        ASSERT_AND_LOG(NULL != GetScanfFunc<wchar_t>::value);

#endif // ENABLE_UNSAFE_SCANPRINT
        //test GetScanfFuncS
        ASSERT_AND_LOG(NULL != GetScanfFuncS<char>::value);
        ASSERT_AND_LOG(NULL != GetScanfFuncS<wchar_t>::value);
    }

#ifdef RUN_EXAMPLE_SCANPRINT
    InitRunFunc(TestCase_scanPrint);
#else //else of RUN_EXAMPLE_SCANPRINT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_SCANPRINT)=(outputTxtV(TXT("[Unit test run disabled] scanPrint.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"scanPrint.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_SCANPRINT
}

#else //else of COMPILE_EXAMPLE_SCANPRINT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_SCANPRINT)=(outputTxtV(TXT("[Unit test compile disabled] scanPrint.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"scanPrint.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_SCANPRINT

