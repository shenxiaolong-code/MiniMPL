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

namespace MiniMPL {
    constexpr const char        example_string[] = "demo binding integer with string";
    template <>                 struct GetString<111> : public ConstString<example_string> {};
}

namespace UnitTest
{
    enum  {Ninety_Nine=99};
    using TypeValue_5=MiniMPL::ValueType<int , 5>;
    enum  EnumType_1 {  EnumType_1_v1, 
                        EnumType_1_v2,
                        EnumType_1_v3, };
    using EnumType_1_val2=MiniMPL::ValueType<EnumType_1 , EnumType_1_v2>;                        
    enum  EnumType_2 {  EnumType_2_v1, 
                        EnumType_2_v2,
                        EnumType_2_v3, };
    using EnumType_2_val3=MiniMPL::ValueType<EnumType_2 , EnumType_2_v3>;                        

    using TypeValueEnum=MiniMPL::ValueType<EnumType_1 , EnumType_1_v2>;
    TypeValue_5 formal_func_param_enum_compile_fail(EnumType_1);
    TypeValue_5 formal_func_param_enum_ok(EnumType_2);
    TypeValue_5 formal_func_param_int_ok(int);

    struct EmbedType_1{
        typedef int               type;        
    };
    struct EmbedType_2{
        typedef EmbedType_1       type;        
    };
    struct EmbedType_3{
        typedef EmbedType_2       type;        
    };

    inline void TestCase_kitType()
    {
        PrintTestcase();

        using namespace MiniMPL;

       // test getType , getType_t and getValue_v
       Static_Assert((TrueType::value == true));
       Static_Assert((getValue_v<TrueType> == true));
       static_assert(getValue_v<TrueType> == true, "The value should be true.");

       std::cout << "[before C++17] GetString<111>::value   = " << MiniMPL::GetString<111>::value  << std::endl;
#if CPP17_ENABLED
       std::cout << "[From C++17  ] getString_v<111>::value = " << getString_v<111>                << std::endl;
#endif

       Static_Assert((MiniMPL::IsSameType<getType_t<MiniMPL::If_T<true,int,char>>,int>::value));
       Static_Assert((MiniMPL::IsSameType<typename getType<EmbedType_3>::type,int>::value));
       Static_Assert((MiniMPL::IsSameType<typename getType<EmbedType_2>::type,int>::value));

       Static_Assert((MiniMPL::IsSameType<getType_t<EmbedType_3>, int>::value));
       Static_Assert((MiniMPL::IsSameType_v<typename getType<EmbedType_3>::type, int>));
       Static_Assert((MiniMPL::IsSameType_v<getType_t<EmbedType_3>, int>));

        // test ValueType
        Static_Assert((TrueType::value==true));
        Static_Assert(!(TrueType::value==false));
        Static_Assert((FalseType::value==false));
        Static_Assert(!(FalseType::value==true));
        Static_Assert((Int2Type<5>::value==5));
        Static_Assert(!(Int2Type<6>::value==5));
        Static_Assert((ValueType<char,'c'>::value=='c'));
        Static_Assert(!(ValueType<char,'c'>::value=='d'));
        Static_Assert((ValueType<unsigned,3>::value==3));
        Static_Assert(!(ValueType<unsigned,3>::value==5));

        // test Type2Value
        Static_Assert((Type2Value<TypeValue_5>::value == 5));
        Static_Assert((Type2Value<TypeValueEnum>::value == EnumType_1_v2));
        // Static_Assert((Type2Value<decltype(formal_func_param_enum_compile_fail(Type2Value<EnumType_2_val3>::value))>::value == 5));
        Static_Assert((Type2Value<decltype(formal_func_param_enum_ok(Type2Value<EnumType_2_val3>::value))>::value == 5));
        Static_Assert((Type2Value<decltype(formal_func_param_int_ok(Type2Value<EnumType_2_val3>::value))>::value == 5));        // implicit convert
        Static_Assert((Type2Value<ValueType<int , 3> >::value == 3));
        Static_Assert((Type2Value<TrueType>::value==true));
        Static_Assert(!(Type2Value<TrueType>::value==false));
        Static_Assert((Type2Value<FalseType>::value==false));
        Static_Assert(!(Type2Value<FalseType>::value==true));
        Static_Assert((Type2Value<TrueType>::value == true));
        Static_Assert(!(Type2Value<TrueType>::value == false));
        Static_Assert((Type2Value<FalseType>::value == false));
        Static_Assert(!(Type2Value<FalseType>::value == true));
        Static_Assert((Type2Value<Int2Type<5>>::value == 5));
        Static_Assert(!(Type2Value<Int2Type<6>>::value == 5));
        // ASSERT_AND_LOG((Type2Value<ValueType<char, 'c'>>::value=='c'));
        // ASSERT_AND_LOG(!(Type2Value<ValueType<char, 'c'>>::value=='d'));
        // ASSERT_AND_LOG((Type2Value<ValueType<unsigned, 3>>::value==3));
        // ASSERT_AND_LOG(!(Type2Value<ValueType<unsigned, 3>>::value==5));

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
        Static_Assert((ValueType<char,'c'>::value=='c'));
        Static_Assert(!(ValueType<char,'c'>::value=='d'));
        Static_Assert((ValueType<wchar_t,'c'>::value=='c'));
        Static_Assert(!(ValueType<wchar_t,'c'>::value=='d'));
        Static_Assert((ValueType<unsigned,4>::value==4));
        Static_Assert((ValueType<unsigned,4>::value==4));
        
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
