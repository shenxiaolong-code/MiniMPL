#ifndef __TEST_TYPELOGIC_HPP__
#define __TEST_TYPELOGIC_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\typeLogic.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_TYPELOGIC to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_TYPELOGIC

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_TYPELOGIC
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_TYPELOGIC
#endif

#if defined(RUN_EXAMPLE_TYPELOGIC) && !defined(COMPILE_EXAMPLE_TYPELOGIC)
    #define COMPILE_EXAMPLE_TYPELOGIC
#endif

//#undef RUN_EXAMPLE_TYPELOGIC
//#undef COMPILE_EXAMPLE_TYPELOGIC

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_TYPELOGIC
#include <MiniMPL/typeLogic.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    inline void TestCase_typeLogic()
    {
        PrintTestcase();
        using namespace MiniMPL;

        typedef BoolType<true>               Bool11_T;
        typedef BoolType<true>               Bool12_T;
        typedef BoolType<true>               Bool13_T;
        typedef BoolType<1>                  Bool14_T;
        typedef BoolType<1>                  Bool15_T;

        typedef BoolType<false>              Bool01_T;
        typedef BoolType<false>              Bool02_T;
        typedef BoolType<false>              Bool03_T;
        typedef BoolType<0>                  Bool04_T;
        typedef BoolType<0>                  Bool05_T;

        //test Not_T
        Static_Assert(!Not_T<Bool11_T>::value);
        Static_Assert(!Not_T<Bool14_T>::value);
        Static_Assert(Not_T<Bool01_T>::value);
        Static_Assert(Not_T<Bool04_T>::value);

        //test And_T
        Static_Assert((And_T<Bool11_T,Bool12_T,Bool13_T,Bool14_T,Bool15_T>::value));
        Static_Assert((!And_T<Bool11_T,Bool12_T,Bool13_T,Bool14_T,Bool01_T>::value));
        Static_Assert((And_T<Bool11_T,Bool12_T,Bool13_T,Bool14_T,Bool11_T>::value));
        Static_Assert(!(And_T<Bool01_T,Bool02_T,Bool03_T,Bool04_T,Bool05_T>::value));
        Static_Assert(!(And_T<Bool01_T,Bool02_T,Bool03_T,Bool04_T,Bool11_T>::value));
        Static_Assert(!(And_T<Bool01_T,Bool02_T,Bool03_T,Bool04_T,Bool11_T>::value));

        //test Or_T
        Static_Assert((Or_T<Bool11_T,Bool12_T,Bool13_T,Bool14_T,Bool01_T>::value));
        Static_Assert((Or_T<Bool11_T,Bool12_T,Bool13_T,Bool14_T,Bool11_T>::value));
        Static_Assert((Or_T<Bool01_T,Bool02_T,Bool03_T,Bool04_T,Bool15_T>::value));
        Static_Assert((Or_T<Bool01_T,Bool02_T,Bool03_T,Bool04_T,Bool11_T>::value));
        Static_Assert((Or_T<Bool01_T,Bool02_T,Bool03_T,Bool04_T,Bool11_T>::value));

        //test Xor_T
        Static_Assert((Xor_T<Bool01_T,Bool11_T>::value));
        Static_Assert((Xor_T<Bool01_T,Bool14_T>::value));
        Static_Assert((Xor_T<Bool11_T,Bool01_T>::value));
        Static_Assert((Xor_T<Bool11_T,Bool04_T>::value));
        Static_Assert(!(Xor_T<Bool11_T,Bool14_T>::value));
        Static_Assert(!(Xor_T<Bool01_T,Bool04_T>::value));
    }

#ifdef RUN_EXAMPLE_TYPELOGIC
    InitRunFunc(TestCase_typeLogic);
#else //else of RUN_EXAMPLE_TYPELOGIC

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_TYPELOGIC)=(outputTxtV(TXT("[Unit test run disabled] typeLogic.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"typeLogic.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_TYPELOGIC
}

#else //else of COMPILE_EXAMPLE_TYPELOGIC
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_TYPELOGIC)=(outputTxtV(TXT("[Unit test compile disabled] typeLogic.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"typeLogic.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_TYPELOGIC

#endif // __TEST_TYPELOGIC_HPP__
