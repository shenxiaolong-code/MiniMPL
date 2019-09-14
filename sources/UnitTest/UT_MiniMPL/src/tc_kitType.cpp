#ifndef __TEST_KITTYPE_HPP__
#define __TEST_KITTYPE_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\kitType.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_KITTYPE to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_KITTYPE

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_KITTYPE
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_KITTYPE
#endif

#if defined(RUN_EXAMPLE_KITTYPE) && !defined(COMPILE_EXAMPLE_KITTYPE)
    #define COMPILE_EXAMPLE_KITTYPE
#endif

//#undef RUN_EXAMPLE_KITTYPE
//#undef COMPILE_EXAMPLE_KITTYPE

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_KITTYPE
#include <MiniMPL/kitType.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <MiniMPL/isXXXEx.hpp>

namespace UnitTest
{
     enum  {Ninety_Nine=99};

    inline void TestCase_kitType()
    {
        PrintTestcase();

        using namespace MiniMPL;
        Static_Assert((TrueType::value==true));
        Static_Assert(!(TrueType::value==false));
        Static_Assert((FalseType::value==false));
        Static_Assert(!(FalseType::value==true));
        Static_Assert((Int2Type<5>::value==5));
        Static_Assert(!(Int2Type<6>::value==5));
        ASSERT_AND_LOG((Value2Type<char,'c'>::value=='c'));
        ASSERT_AND_LOG(!(Value2Type<char,'c'>::value=='d'));
        ASSERT_AND_LOG((Value2Type<unsigned,3>::value==3));
        ASSERT_AND_LOG(!(Value2Type<unsigned,3>::value==5));

        //test Type2Type  , 99 is 'c'
        typedef Int2Type<99>            TType_Int;
        typedef Int2Type<'c'>           TType_Char;
        typedef Int2Type<99u>           TType_Unsigned;
        typedef Int2Type<99l>           TType_long;
        typedef Int2Type<Ninety_Nine>   TType_Enum;
        Static_Assert(TType_Char::value==TType_Unsigned::value);
        Static_Assert(TType_long::value==TType_Enum::value);
        Static_Assert(TType_Char::value==TType_Enum::value);
        Static_Assert(TType_Unsigned::value==TType_long::value);
        Static_Assert(TType_Enum::value==TType_Int::value);

        Static_Assert((TrueType::value==true));
        Static_Assert((FalseType::value==false));
        Static_Assert((Int2Type<5>::value==5));        
//         Static_Assert((Value2Type<char,'c'>::value=='c'));
//         Static_Assert((!Value2Type<char,'c'>::value=='d'));
//         Static_Assert((Value2Type<wchar_t,'c'>::value=='c'));
//         Static_Assert((!Value2Type<wchar_t,'c'>::value=='d'));
//         Static_Assert((Value2Type<unsigned,4>::value==4));
//         Static_Assert((Value2Type<unsigned,4>::value==4));
//         
        //demo If_T
        MiniMPL::If_T<true,int,char*>::type Tif1 = 2;
        MiniMPL::If_T<false,int,char*>::type Tif2 = "false";

        MiniMPL::If_Evl<TrueType,int,char*>::type Tif11 = 2;
        MiniMPL::If_Evl<FalseType,int,char*>::type Tif21 = "false";

        //demo If_T and lazy_If_T
        Static_Assert((MiniMPL::IsSameType<MiniMPL::If_T<true,int,char>::type,int>::value));
        Static_Assert((!MiniMPL::IsSameType<MiniMPL::If_T<false,int,char>::type,int>::value));
        Static_Assert((MiniMPL::IsSameType<MiniMPL::If_T<false,int,char>::type,char>::value));
        Static_Assert((!MiniMPL::IsSameType<MiniMPL::If_T<true,int,char>::type,char>::value));
    }

#ifdef RUN_EXAMPLE_KITTYPE
    InitRunFunc(TestCase_kitType);
#else //else of RUN_EXAMPLE_KITTYPE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_KITTYPE)=(outputTxtV(TXT("[Unit test run disabled] kitType.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"kitType.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_KITTYPE
}

#else //else of COMPILE_EXAMPLE_KITTYPE
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_KITTYPE)=(outputTxtV(TXT("[Unit test compile disabled] kitType.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"kitType.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_KITTYPE

#endif // __TEST_KITTYPE_HPP__
