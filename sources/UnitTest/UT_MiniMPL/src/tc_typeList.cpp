#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\typeList.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_TYPELIST to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_TYPELIST

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_TYPELIST
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_TYPELIST
#endif

#if defined(RUN_EXAMPLE_TYPELIST) && !defined(COMPILE_EXAMPLE_TYPELIST)
    #define COMPILE_EXAMPLE_TYPELIST
#endif

// #undef RUN_EXAMPLE_TYPELIST
// #undef COMPILE_EXAMPLE_TYPELIST

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_TYPELIST
#include <MiniMPL/typeList.hpp>
#include <UnitTestKit/tc_tracer.h>
#include "MiniMPL/typeListMacro.hpp"

namespace UnitTest
{
    struct T0; struct T1;class T2;struct T3;struct T4;      //fw declare
    struct T5;struct T6;class  T7;class  T8;                //fw declare

    //user defined type list
    typedef MAKE_TYPELIST_3(T1,T2,T3)                           RuleList_3;
    typedef MAKE_TYPELIST_2(T4,T5)                              RuleList_2;
    typedef MAKE_TYPELIST_5(RuleList_3,T6,RuleList_2,T7,T8)     RuleList_all;

    inline void TestCase_typeList()
    {
        PrintTestcase();

        using namespace MiniMPL::TL;
        Static_Assert(!(TypeInList<RuleList_3,T0>::value));
        Static_Assert((TypeInList<RuleList_3,T1>::value));
        Static_Assert((TypeInList<RuleList_3,T2>::value));
        Static_Assert((TypeInList<RuleList_3,T3>::value));
        Static_Assert(!(TypeInList<RuleList_2,T0>::value));
        Static_Assert((TypeInList<RuleList_2,T4>::value));
        Static_Assert((TypeInList<RuleList_2,T5>::value));
        Static_Assert(!(TypeInList<RuleList_all,T0>::value));
        Static_Assert((TypeInList<RuleList_all,T6>::value));
        Static_Assert((TypeInList<RuleList_all,T7>::value));
        Static_Assert((TypeInList<RuleList_all,T8>::value));
        Static_Assert((TypeInList<RuleList_all,RuleList_3>::value));
        Static_Assert((TypeInList<RuleList_all,RuleList_2>::value));        
    }

#ifdef RUN_EXAMPLE_TYPELIST
    InitRunFunc(TestCase_typeList);
#else //else of RUN_EXAMPLE_TYPELIST

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_TYPELIST)=(outputTxtV(TXT("[Unit test run disabled] typeList.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"typeList.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_TYPELIST
}

#else //else of COMPILE_EXAMPLE_TYPELIST
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_TYPELIST)=(outputTxtV(TXT("[Unit test compile disabled] typeList.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"typeList.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_TYPELIST

