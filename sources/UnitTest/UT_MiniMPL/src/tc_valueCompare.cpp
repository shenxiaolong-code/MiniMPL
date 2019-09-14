#ifndef __TEST_VALUECOMPARE_HPP__
#define __TEST_VALUECOMPARE_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\valueCompare.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_VALUECOMPARE to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_VALUECOMPARE

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_VALUECOMPARE
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_VALUECOMPARE
#endif

#if defined(RUN_EXAMPLE_VALUECOMPARE) && !defined(COMPILE_EXAMPLE_VALUECOMPARE)
    #define COMPILE_EXAMPLE_VALUECOMPARE
#endif

//#undef RUN_EXAMPLE_VALUECOMPARE
//#undef COMPILE_EXAMPLE_VALUECOMPARE

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_VALUECOMPARE
#include <MiniMPL/valueCompare.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <limits>

namespace UnitTest
{
    inline void TestCase_equal()
    {
        PrintTestcaseSub();
        using namespace MiniMPL;

        //test equal
        AssertB((equal(0.0002,0.0002)));
        AssertB((equal(0.0002,0.0002f)));
        AssertB((equal(0.0002f,0.0002f)));
        AssertB((equal(0.0002f,0.0002)));
        AssertB((!equal(0.0002f,0.0003)));
        AssertB((!equal(0.0002f,0.0003f)));
        AssertB((!equal(0.0002,0.0003)));
        AssertB((!equal(0.0002,0.0003f)));
        AssertB((!equal("abc",L"ABC")));
        AssertB((equal("abc",L"abc")));
        AssertB((!equal(stlStringA("abc"),L"ABC")));
        AssertB((equal(stlStringA("abc"),L"abc")));
        AssertB((!equal(stlStringW(L"abc"),"ABC")));
        AssertB((equal(stlStringW(L"abc"),L"abc")));
        AssertB((equal(stlStringW(L"abc"),stlStringW(L"abc"))));
        AssertB((equal(stlStringW(L"abc"),stlStringA("abc"))));

        AssertB((!equal(stlStringW(L"abcd"),stlStringA("ABC"))));
        AssertB((!equal(stlStringA("abcd"),stlStringA("ABC"))));
        AssertB((!equal(stlStringA("abcd"),stlStringW(L"ABC"))));

        AssertB((equal((std::numeric_limits<float>::max)(),(std::numeric_limits<float>::max)())));
        AssertB((equal((std::numeric_limits<float>::min)(),(std::numeric_limits<float>::min)())));
        AssertB((equal((std::numeric_limits<double>::max)(),(std::numeric_limits<double>::max)())));
        AssertB((equal((std::numeric_limits<double>::min)(),(std::numeric_limits<double>::min)())));
        AssertB((!equal((std::numeric_limits<float>::max)(),(std::numeric_limits<double>::max)())));
        //different precision min precision value comparison,granted same result. 
        AssertB((equal((std::numeric_limits<float>::min)(),(std::numeric_limits<double>::min)())));
    }

    inline void TestCase_TComparer()
    {  
        using namespace MiniMPL;
        TComparer<'='>          oEq;
        TComparer<'!','='>      oNEq;
        TComparer<'<'>          oLesser1;
        TComparer<'<','='>      oLesserEq1;
        TComparer<'>'>          oGreater1;
        TComparer<'>','='>      oGreaterEq1;
        TComparer<'('>          oLesser2;
        TComparer<'['>          oLesserEq2;
        TComparer<')'>          oGreater2;
        TComparer<']'>          oGreaterEq2;

        ASSERT_AND_LOG((oGreater1(5,3)));
        ASSERT_AND_LOG((oGreaterEq1(5,3)));
        ASSERT_AND_LOG((!oLesser1(5,3)));
        ASSERT_AND_LOG((!oLesserEq1(5,3)));
        ASSERT_AND_LOG((!oEq(5,3)));
        ASSERT_AND_LOG((oNEq(5,3)));
        ASSERT_AND_LOG(!(oLesser2(5,3)));
        ASSERT_AND_LOG(!(oLesserEq2(5,3)));
        ASSERT_AND_LOG((oGreater2(5,3)));
        ASSERT_AND_LOG((oGreaterEq2(5,3)));

        ASSERT_AND_LOG((oGreater1(5.2,3)));
        ASSERT_AND_LOG((oGreaterEq1(5,3.0)));
        ASSERT_AND_LOG((!oLesser1(5,3.12)));
        ASSERT_AND_LOG((!oLesserEq1(5.12,3)));
        ASSERT_AND_LOG((!oEq(5.12,3.23)));
        ASSERT_AND_LOG((oNEq(5.11,3.23)));
        ASSERT_AND_LOG(!(oLesser2(5.25,3.36)));
        ASSERT_AND_LOG(!(oLesserEq2(5.12,3.00)));
        ASSERT_AND_LOG((oGreater2(5.2,3)));
        ASSERT_AND_LOG((oGreaterEq2(52,3.55)));
    }

    inline void TestCase_valueCompare()
    {
        PrintTestcase();
        TestCase_TComparer();
        TestCase_equal();        
    }

#ifdef RUN_EXAMPLE_VALUECOMPARE
    InitRunFunc(TestCase_valueCompare);
#else //else of RUN_EXAMPLE_VALUECOMPARE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_VALUECOMPARE)=(outputTxtV(TXT("[Unit test run disabled] valueCompare.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"valueCompare.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_VALUECOMPARE
}

#else //else of COMPILE_EXAMPLE_VALUECOMPARE
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_VALUECOMPARE)=(outputTxtV(TXT("[Unit test compile disabled] valueCompare.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"valueCompare.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_VALUECOMPARE

#endif // __TEST_VALUECOMPARE_HPP__
