#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\paramPackShift.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_PARAMPACKSHIFT to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_PARAMPACKSHIFT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_PARAMPACKSHIFT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_PARAMPACKSHIFT
#endif

#if defined(RUN_EXAMPLE_PARAMPACKSHIFT) && !defined(COMPILE_EXAMPLE_PARAMPACKSHIFT)
    #define COMPILE_EXAMPLE_PARAMPACKSHIFT
#endif

//#undef RUN_EXAMPLE_PARAMPACKSHIFT
//#undef COMPILE_EXAMPLE_PARAMPACKSHIFT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_PARAMPACKSHIFT
#include <MiniMPL/paramPackShift.hpp>
#include <UnitTestKit/tc_tracer.h>
#include "UT_material/tc_def_typeStruct.h"

namespace UnitTest
{

    inline void TestCase_paramPackShift()
    {
        PrintTestcase();

        using namespace MiniMPL;
        char oc = 5;
        S4   os4;
        typedef ParamPackage<int,S4,char&,char>     TPack;
        TPack oOld(5,os4,oc,'7');
        Static_Assert((IsSameType<S4,typename ParamPackageAt<TPack,2>::type>::value));   //avoid copy

        typedef TTransferPack<TPack>::type          TTransferType;
        TTransferType oNew(5,os4,oc,'7');
        Static_Assert((IsSameType<int,typename ParamPackageAt<TTransferType,1>::type>::value));
        Static_Assert((IsSameType<S4&,typename ParamPackageAt<TTransferType,2>::type>::value));   //avoid copy
        Static_Assert((IsSameType<char&,typename ParamPackageAt<TTransferType,3>::type>::value)); //keep ref because of raw is ref
        Static_Assert((IsSameType<char,typename ParamPackageAt<TTransferType,4>::type>::value));

        typedef TInsert<TPack>          TInsertPack;
        typedef TInsertPack::template apply<S4 const&,1>::type  TIS4cr1;
        Static_Assert((IsSameType<S4 const&,typename ParamPackageAt<TIS4cr1,1>::type>::value));

    }

#ifdef RUN_EXAMPLE_PARAMPACKSHIFT
    InitRunFunc(TestCase_paramPackShift);
#else //else of RUN_EXAMPLE_PARAMPACKSHIFT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_PARAMPACKSHIFT)=(outputTxtV(TXT("[Unit test run disabled] paramPackShift.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"paramPackShift.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_PARAMPACKSHIFT
}

#else //else of COMPILE_EXAMPLE_PARAMPACKSHIFT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_PARAMPACKSHIFT)=(outputTxtV(TXT("[Unit test compile disabled] paramPackShift.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"paramPackShift.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_PARAMPACKSHIFT

