#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\enumTrait.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_ENUMTRAIT to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_ENUMTRAIT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_ENUMTRAIT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_ENUMTRAIT
#endif

#if defined(RUN_EXAMPLE_ENUMTRAIT) && !defined(COMPILE_EXAMPLE_ENUMTRAIT)
    #define COMPILE_EXAMPLE_ENUMTRAIT
#endif

//#undef RUN_EXAMPLE_ENUMTRAIT
//#undef COMPILE_EXAMPLE_ENUMTRAIT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_ENUMTRAIT
#include <MiniMPL/enumTrait.hpp>
#include <MiniMPL/isXXXEx.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <ut_material/tc_def_enumRange.h>

namespace UnitTest
{               
    inline void TestCase_enumTrait()
    {
        PrintTestcase();

        using namespace MiniMPL;
        typedef SeqEnumRange::Min_T                                 SEnumValueMin;
        typedef SeqEnumRange::Max_T                                 SEnumValueMax;
        typedef NonSeqEnumRange::Min_T                              NSEnumValueMin;
        typedef NonSeqEnumRange::Max_T                              NSEnumValueMax;

        // assert F_max >= F_min
        // using ETypeInt_Fail = CEnumRange<ETypeInt, ETypeInt(10), ETypeInt(5)>;
        // using ETypeInt_OK = CEnumRange<ETypeInt, ETypeInt(5), ETypeInt(10)>;
        // CEnumRange<ETypeInt, ETypeInt(10), ETypeInt(5)> ETypeInt_Fail;
        CEnumRange<ETypeInt, ETypeInt(5), ETypeInt(10)> ETypeInt_OK;

        //test MiniMPL.CEnumRange.Min_T/Max_T with CEnumRangeDefault
        Static_Assert((CEnumRangeDefault<ETypeInt>::type::Min_T::value==13));
        Static_Assert(!(CEnumRangeDefault<ETypeInt>::type::Min_T::value==14));
        Static_Assert((CEnumRangeDefault<ETypeInt>::type::Max_T::value==24));
        Static_Assert(!(CEnumRangeDefault<ETypeInt>::type::Max_T::value==7));
        
        //test MiniMPL.CEnumRange.Min_T/Max_T
        Static_Assert((NonSeqEnumRange::Min_T::value==NS_Val_Min));
        Static_Assert((NonSeqEnumRange::Max_T::value==NS_Val_Max));
        Static_Assert((SeqEnumRange::Min_T::value==S_Val_Min));
        Static_Assert((SeqEnumRange::Max_T::value==S_Val_Max));

        //test MiniMPL.CEnumValue.Next
        Static_Assert((CEnumValue<SeqEnumRange,S_Val_1>::Next<true>::type::value==S_Val_2));        
        Static_Assert((CEnumValue<SeqEnumRange,S_Val_1>::Next<false>::type::value==S_Val_Min));
        Static_Assert(!(CEnumValue<SeqEnumRange,S_Val_1>::Next<false>::type::value==S_Val_2));
        Static_Assert((CEnumValue<NonSeqEnumRange,NS_Val_1>::Next<true>::type::value==NS_Val_3));
        Static_Assert((CEnumValue<NonSeqEnumRange,NS_Val_1>::Next<false>::type::value==NS_Val_Min));
        Static_Assert(!(CEnumValue<NonSeqEnumRange,NS_Val_1>::Next<false>::type::value==NS_Val_3));

        //test MiniMPL.CEnumValue.Last
        Static_Assert((CEnumValue<SeqEnumRange,S_Val_3>::Last<true>::type::value==S_Val_2));        
        Static_Assert((CEnumValue<SeqEnumRange,S_Val_3>::Last<false>::type::value==S_Val_5));       //because SKIP_ENUM_ONE(SeqEnumRange,S_Val_4);
        Static_Assert(!(CEnumValue<SeqEnumRange,S_Val_3>::Last<false>::type::value==S_Val_2));
        Static_Assert((CEnumValue<NonSeqEnumRange,NS_Val_3>::Last<true>::type::value==NS_Val_1));
        Static_Assert((CEnumValue<NonSeqEnumRange,NS_Val_3>::Last<false>::type::value==NS_Val_5));
        Static_Assert(!(CEnumValue<NonSeqEnumRange,NS_Val_3>::Last<false>::type::value==NS_Val_1));

        //test MiniMPL.CGetEnumRange
        Static_Assert((IsSameType<typename SEnumValueMin::EnumRange_T,SeqEnumRange>::value));
        Static_Assert((IsSameType<typename SEnumValueMax::EnumRange_T,SeqEnumRange>::value));
        Static_Assert((IsSameType<typename CEnumValue<SeqEnumRange,S_Val_3>::EnumRange_T,SeqEnumRange>::value));
        Static_Assert((IsSameType<typename CEnumValue<SeqEnumRange,S_Val_6>::EnumRange_T,SeqEnumRange>::value));
        Static_Assert((IsSameType<typename CEnumValue<SeqEnumRange,S_Val_2>::EnumRange_T,typename CEnumValue<SeqEnumRange,S_Val_1>::EnumRange_T>::value));
        Static_Assert((IsSameType<typename SEnumValueMax::EnumRange_T,typename SEnumValueMin::EnumRange_T>::value));
        Static_Assert((IsSameType<typename NSEnumValueMin::EnumRange_T,NonSeqEnumRange>::value));
        Static_Assert((IsSameType<typename NSEnumValueMax::EnumRange_T,NonSeqEnumRange>::value));
        Static_Assert((IsSameType<typename CEnumValue<NonSeqEnumRange,NS_Val_3>::EnumRange_T,NonSeqEnumRange>::value));
        Static_Assert((IsSameType<typename CEnumValue<NonSeqEnumRange,NS_Val_5>::EnumRange_T,NonSeqEnumRange>::value));
        Static_Assert((IsSameType<typename CEnumValue<NonSeqEnumRange,NS_Val_Min>::EnumRange_T,typename CEnumValue<NonSeqEnumRange,NS_Val_1>::EnumRange_T>::value));
        Static_Assert((IsSameType<typename NSEnumValueMax::EnumRange_T,typename NSEnumValueMin::EnumRange_T>::value));

        //test MiniMPL.CGetEnumRangeMax/CGetEnumRangeMin
        Static_Assert((CEnumValue<NonSeqEnumRange,NS_Val_3>::Max_T::value==NS_Val_Max));
        Static_Assert((CEnumValue<NonSeqEnumRange,NS_Val_5>::Max_T::value==NS_Val_Max));
        Static_Assert((CEnumValue<SeqEnumRange,S_Val_3>::Max_T::value==S_Val_Max));
        Static_Assert((CEnumValue<SeqEnumRange,S_Val_5>::Max_T::value==S_Val_Max));
        Static_Assert((CEnumValue<NonSeqEnumRange,NS_Val_3>::Min_T::value==NS_Val_Min));
        Static_Assert((CEnumValue<NonSeqEnumRange,NS_Val_5>::Min_T::value==NS_Val_Min));
        Static_Assert((CEnumValue<SeqEnumRange,S_Val_3>::Min_T::value==S_Val_Min));
        Static_Assert((CEnumValue<SeqEnumRange,S_Val_5>::Min_T::value==S_Val_Min));

        //test CGetEnumRangeSize
        Static_Assert((CGetEnumRangeSize<SeqEnumRange>::value==8));
        Static_Assert(!(CGetEnumRangeSize<SeqEnumRange>::value==9)); 
        Static_Assert((CGetEnumRangeSize<typename CEnumValue<SeqEnumRange,S_Val_5>::EnumRange_T>::value==8));
        Static_Assert(!(CGetEnumRangeSize<typename CEnumValue<SeqEnumRange,S_Val_5>::EnumRange_T>::value==9));
        Static_Assert((CGetEnumRangeSize<SeqEnumSkipOneRange>::value==5));
        Static_Assert(!(CGetEnumRangeSize<SeqEnumSkipOneRange>::value==9));
        Static_Assert((CGetEnumRangeSize<typename CEnumValue<SeqEnumSkipOneRange,S_Val_5>::EnumRange_T >::value==5));
        Static_Assert(!(CGetEnumRangeSize<typename CEnumValue<SeqEnumSkipOneRange,S_Val_5>::EnumRange_T >::value==9));
        Static_Assert((CGetEnumRangeSize<NonSeqEnumRange>::value==6));
        Static_Assert(!(CGetEnumRangeSize<NonSeqEnumRange>::value==7));
        Static_Assert((CGetEnumRangeSize<typename CEnumValue<NonSeqEnumRange,NS_Val_5>::EnumRange_T >::value==6));
        Static_Assert(!(CGetEnumRangeSize<typename CEnumValue<NonSeqEnumRange,NS_Val_5>::EnumRange_T >::value==7));

        //test MiniMPL.CGetEnumValue 
        Static_Assert((CEnumValue<NonSeqEnumRange,NS_Val_3>::Next<true>::type::value==NS_Val_5));
        Static_Assert((CEnumValue<SeqEnumRange,S_Val_3>::Next<true>::type::value==S_Val_5));  //because SKIP_ENUM_ONE(SeqEnumRange,S_Val_4);

        //test MiniMPL.CGetEnumType 
        Static_Assert((IsSameType<typename SEnumValueMin::Enum_T,typename SEnumValueMax::Enum_T>::value));
        Static_Assert((IsSameType<typename NSEnumValueMin::Enum_T,typename NSEnumValueMax::Enum_T>::value));
        Static_Assert((IsSameType<typename NonSeqEnumRange::Enum_T,typename NSEnumValueMax::Enum_T>::value));
        Static_Assert((IsSameType<typename NonSeqEnumRange::Enum_T,typename NSEnumValueMin::Enum_T>::value));
        Static_Assert(!(IsSameType<typename NSEnumValueMin::Enum_T,typename SEnumValueMin::Enum_T>::value));

        //test MiniMPL.CEnumInRange 
        Static_Assert(!(CEnumInRange<typename NSEnumValueMin::Last<true>::type>::value));        
        Static_Assert((CEnumInRange<typename NSEnumValueMax::Last<true>::type>::value)); 
        Static_Assert((CEnumInRange<typename NSEnumValueMin::Next<true>::type>::value));        
        Static_Assert(!(CEnumInRange<typename NSEnumValueMax::Next<true>::type>::value));
        Static_Assert((CEnumInRange<typename NSEnumValueMin::Last<false>::type>::value));        
        Static_Assert(!(CEnumInRange<typename NSEnumValueMax::Last<false>::type>::value)); 
        Static_Assert(!(CEnumInRange<typename NSEnumValueMin::Next<false>::type>::value));        
        Static_Assert((CEnumInRange<typename NSEnumValueMax::Next<false>::type>::value)); 
    }

#ifdef RUN_EXAMPLE_ENUMTRAIT
    InitRunFunc(TestCase_enumTrait);
#else //else of RUN_EXAMPLE_ENUMTRAIT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_ENUMTRAIT)=(outputTxtV(TXT("[Unit test run disabled] enumTrait.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"enumTrait.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_ENUMTRAIT
}

#else //else of COMPILE_EXAMPLE_ENUMTRAIT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_ENUMTRAIT)=(outputTxtV(TXT("[Unit test compile disabled] enumTrait.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"enumTrait.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_ENUMTRAIT

