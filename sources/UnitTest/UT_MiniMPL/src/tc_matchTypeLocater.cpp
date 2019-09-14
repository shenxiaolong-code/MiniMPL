#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macroDef.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\matchTypeLocater.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MATCHTYPELOCATER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MATCHTYPELOCATER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MATCHTYPELOCATER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MATCHTYPELOCATER
#endif

#if defined(RUN_EXAMPLE_MATCHTYPELOCATER) && !defined(COMPILE_EXAMPLE_MATCHTYPELOCATER)
    #define COMPILE_EXAMPLE_MATCHTYPELOCATER
#endif

//#undef RUN_EXAMPLE_MATCHTYPELOCATER
//#undef COMPILE_EXAMPLE_MATCHTYPELOCATER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MATCHTYPELOCATER
#include <MiniMPL/matchTypeLocater.hpp>
#include <UnitTestKit/tc_tracer.h>
#include "UnitTestKit/tc_dump.h"

namespace UnitTest
{
    struct T0; struct T1;class T2;struct T3;struct T4;      //fw declare
    struct T5;struct T6;class  T7;class  T8;                //fw declare

    //user defined type list
    typedef MAKE_TYPELIST_3(T1,T2,T3)                           RuleList_3;
    typedef MAKE_TYPELIST_2(T4,T5)                              RuleList_2;
    typedef MAKE_TYPELIST_5(RuleList_3,T6,RuleList_2,T7,T8)     RuleList_all;

    //user defined process rule
    template<typename T,typename TRuleList=NullType>    struct TProcess {}; //suitable for left type, here is T8
    template<typename T>        struct TProcess<T,RuleList_3> {};           //T in RuleList_3
    template<typename T>        struct TProcess<T,RuleList_2> {};           //T in RuleList_2
    template<>                  struct TProcess<T6,MiniMPL::NullType>   {}; //suitable for T6
    template<>                  struct TProcess<T7,MiniMPL::NullType>   {}; //suitable for T7

    inline void TestCase_matchTypeLocater()
    {
        PrintTestcase();
        using namespace MiniMPL;
                    
        Static_Assert((IsSameType<typename TMatchTypeLocater<TProcess,T3,RuleList_all>::type,TProcess<T3,RuleList_3> >::value));
        Static_Assert((IsSameType<typename TMatchTypeLocater<TProcess,T5,RuleList_all>::type,TProcess<T5,RuleList_2> >::value));
        Static_Assert((IsSameType<typename TMatchTypeLocater<TProcess,T6,RuleList_all>::type,TProcess<T6,NullType> >::value));
        Static_Assert((IsSameType<typename TMatchTypeLocater<TProcess,T7,RuleList_all>::type,TProcess<T7,NullType> >::value));
        Static_Assert((IsSameType<typename TMatchTypeLocater<TProcess,T8,RuleList_all>::type,TProcess<T8,NullType> >::value));
        Static_Assert((IsSameType<typename TMatchTypeLocater<TProcess,T0,RuleList_all>::type,TProcess<T0,NullType> >::value));

    }

#ifdef RUN_EXAMPLE_MATCHTYPELOCATER
    InitRunFunc(TestCase_matchTypeLocater);
#else //else of RUN_EXAMPLE_MATCHTYPELOCATER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_MATCHTYPELOCATER)=(outputTxtV(TXT("[Unit test run disabled] matchTypeLocater.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"matchTypeLocater.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_MATCHTYPELOCATER
}

#else //else of COMPILE_EXAMPLE_MATCHTYPELOCATER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_MATCHTYPELOCATER)=(outputTxtV(TXT("[Unit test compile disabled] matchTypeLocater.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"matchTypeLocater.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_MATCHTYPELOCATER

