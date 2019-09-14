#ifndef __TEST_PLACEHOLDER_HPP__
#define __TEST_PLACEHOLDER_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\placeHolder.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_PLACEHOLDER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_PLACEHOLDER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_PLACEHOLDER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_PLACEHOLDER
#endif

#if defined(RUN_EXAMPLE_PLACEHOLDER) && !defined(COMPILE_EXAMPLE_PLACEHOLDER)
    #define COMPILE_EXAMPLE_PLACEHOLDER
#endif

//#undef RUN_EXAMPLE_PLACEHOLDER
//#undef COMPILE_EXAMPLE_PLACEHOLDER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_PLACEHOLDER
#include <MiniMPL/placeHolder.hpp>
#include <MiniMPL/macroDef.h>
#include <UnitTestKit/tc_tracer.h>
#include <MiniMPL/isXXXEx.hpp>
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{
    template<typename T>    struct GetArgValue;
    template<unsigned Idx>  struct GetArgValue<MiniMPL::Args<Idx> > : public MiniMPL::Int2Type<Idx>{};

    template<typename T,typename TP>
    void testArgs()
    {
        using namespace MiniMPL;
#define  ArgsList int,char,bool const,char&,int const&,char * const *

        typedef typename T::template apply<ArgsList>::type  TArg;
        outputTxtV(TXTA("Args[%d] type:\t%s\n"),GetArgValue<T>::value,typeid(TArg).name());

        Static_Assert((IsSameType<TArg,TP>::value));
        Static_Assert(!(IsSameType<TArg,UnitTest::S2>::value));
    }

    inline void TestCase_placeHolder()
    {
        PrintTestcase();
        using namespace MiniMPL;

        //Args<1>
        testArgs<Args<1>,int>();

        //Args<2>
        testArgs<Args<2>,char>();

        //Args<3>
        testArgs<Args<3>,bool const>();

        //Args<4>
        testArgs<Args<4>,char&>();

        //Args<5>
        testArgs<Args<5>,int const&>();

        //Args<6>
        testArgs<Args<6>,char * const *>();

    }

#ifdef RUN_EXAMPLE_PLACEHOLDER
    InitRunFunc(TestCase_placeHolder);
#else //else of RUN_EXAMPLE_PLACEHOLDER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_PLACEHOLDER)=(outputTxtV(TXT("[Unit test run disabled] placeHolder.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"placeHolder.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_PLACEHOLDER
}

#else //else of COMPILE_EXAMPLE_PLACEHOLDER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_PLACEHOLDER)=(outputTxtV(TXT("[Unit test compile disabled] placeHolder.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"placeHolder.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_PLACEHOLDER

#endif // __TEST_PLACEHOLDER_HPP__
