#ifndef __TEST_SAMEQUALIFIER_HPP__
#define __TEST_SAMEQUALIFIER_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\sameQualifier.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SAMEQUALIFIER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_SAMEQUALIFIER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SAMEQUALIFIER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SAMEQUALIFIER
#endif

#if defined(RUN_EXAMPLE_SAMEQUALIFIER) && !defined(COMPILE_EXAMPLE_SAMEQUALIFIER)
    #define COMPILE_EXAMPLE_SAMEQUALIFIER
#endif

//#undef RUN_EXAMPLE_SAMEQUALIFIER
//#undef COMPILE_EXAMPLE_SAMEQUALIFIER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SAMEQUALIFIER
#include <MiniMPL/sameQualifier.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>
#include <UT_material/tc_def_qualifier.hpp>

namespace UnitTest
{
    template<typename DataType> struct CTraitType;
    template<> struct CTraitType<ConstStruct> : public MiniMPL::Type2Type<char>{};

    template<typename DataType>
    typename MiniMPL::SameAllQualifier<typename CTraitType<typename MiniMPL::GetRawType<DataType>::type>::type,DataType>::type& RunTest(DataType& obj,unsigned int idx)
    {
        outputTxt((TXTA("\n[RunTest]\ttype name [%s]\n\t\tconst qualifiers ==>%s\n"),typeid(DataType).name(),
            MiniMPL::IsConst<DataType>::value ? TXTA("Const") : TXTA("non-Const")));

        if (idx<obj.m_Chars.size())
        {
            return obj.m_Chars.at(idx);
        }
        else
        {
            return obj.m_Chars.back();
        }
    }

    template<typename T,template<class> class IsXXX>
    void  testTwiceAddRemove()
    {
        using namespace MiniMPL;

        typedef typename GetAddQualifier<IsXXX>             AddHelper;
        typedef typename AddHelper::apply<T>::type          Qualifier_T;
        Static_Assert((IsXXX<Qualifier_T>::value));

        typedef typename GetRemoveQualifier<IsXXX>          RemoveHelper;
        typedef typename RemoveHelper::apply<T>::type       NotQualifier_T;
        Static_Assert((!IsXXX<NotQualifier_T>::value));

        typedef typename SelectQualifier<TrueType,T,IsXXX>::type      SelectType_True;
        Static_Assert((IsXXX<SelectType_True>::value));

        typedef typename SelectQualifier<FalseType,T,IsXXX>::type     SelectType_False;
        Static_Assert(!(IsXXX<SelectType_False>::value));
    }


    template<typename T>
    void testAddRemove(T a)
    {
        using namespace MiniMPL;
        //test Add const
        testTwiceAddRemove<T,IsConst>();
        typedef typename GetAddQualifier<IsConst>::apply<T>::type         Const_T;
        Static_Assert((IsConst<Const_T>::value));

        typedef typename GetRemoveQualifier<IsConst>::apply<T>::type      NotConst_T;
        Static_Assert((!IsConst<NotConst_T>::value));

        //test Add pointer
        testTwiceAddRemove<T,IsCPointer>();
        typedef typename GetAddQualifier<IsCPointer>::apply<T>::type       Pointer_T;
        Static_Assert((IsCPointer<Pointer_T>::value));
        //test Remove pointer
        typedef typename GetRemoveQualifier<IsCPointer>::apply<T>::type    NotCPointer_T;
        Static_Assert((!IsCPointer<NotCPointer_T>::value));

        //test Add reference
        testTwiceAddRemove<T,IsRef>();
        typedef typename GetAddQualifier<IsRef>::apply<T>::type           Ref_T;
        Static_Assert((IsRef<Ref_T>::value));
        //test Remove reference
        typedef typename GetRemoveQualifier<IsRef>::apply<T>::type        NotRef_T;
        Static_Assert((!IsRef<NotRef_T>::value));

        //test Add Volatile
        testTwiceAddRemove<T,IsVolatile>();
        typedef typename GetAddQualifier<IsVolatile>::apply<T>::type      Volatile_T;
        Static_Assert((IsVolatile<Volatile_T>::value));
        //test Remove Volatile
        typedef typename GetRemoveQualifier<IsVolatile>::apply<T>::type   NotVolatile_T;
        Static_Assert((!IsVolatile<NotVolatile_T>::value));

        //test SelectQualifier
        typedef typename SelectQualifier<TrueType,T,IsConst>::type            ConstSelectTrue_T;
        Static_Assert((IsConst<ConstSelectTrue_T>::value));

        typedef typename SelectQualifier<FalseType,T,IsConst>::type           ConstSelectFalse_T;
        Static_Assert(!(IsConst<ConstSelectFalse_T>::value));

        typedef typename SelectQualifier<TrueType,T,IsCPointer>::type          PointerSelectTrue_T;
        Static_Assert((IsCPointer<PointerSelectTrue_T>::value));

        typedef typename SelectQualifier<FalseType,T,IsCPointer>::type         PointerSelectFalse_T;
        Static_Assert(!(IsCPointer<PointerSelectFalse_T>::value));

        typedef typename SelectQualifier<TrueType,T,IsRef>::type              RefSelectTrue_T;
        Static_Assert((IsRef<RefSelectTrue_T>::value));

        typedef typename SelectQualifier<FalseType,T,IsRef>::type             RefSelectFalse_T;
        Static_Assert(!(IsRef<RefSelectFalse_T>::value));

        typedef typename SelectQualifier<TrueType,T,IsVolatile>::type         VolatileSelectTrue_T;
        Static_Assert((IsVolatile<VolatileSelectTrue_T>::value));

        typedef typename SelectQualifier<FalseType,T,IsVolatile>::type        VolatileSelectFalse_T;
        Static_Assert(!(IsVolatile<VolatileSelectFalse_T>::value));        
    }

    inline void TestCase_sameQualifier()
    {
        PrintTestcase();
        using namespace MiniMPL;

        UnitTest::S3 v3;
        testAddRemove(v3);

        const UnitTest::S4 v4;
        testAddRemove(v4);

        const UnitTest::S4 *p=NULL;
        testAddRemove(p);

        stlSmartptr<int> stlPtr;
        testAddRemove(stlPtr);

        ConstStruct obj;
        obj.m_a = 112;
        for (int i=0;i<10;i++)
        {
            obj.m_Chars.push_back('1'+i);
        }

        ConstStruct const& demo=obj;

        char        ch  = RunTest(obj,2);
        char const& cCh = RunTest(demo,3);

        process(RunTest(obj,5));
        process(RunTest(demo,6));

        //demo SameAllQualifier
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::SameAllQualifier<int, float const*>::type,int const*>::value));
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::SameAllQualifier<int, float const*>::type,int const>::value));
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::SameAllQualifier<int, float* const>::type,int const*>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::SameAllQualifier<int, float* const>::type,int const>::value)); //see IsConst for int const* and int* const
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::SameAllQualifier<int, float const>::type,int const>::value)); //see IsConst for int const* and int* const
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::SameAllQualifier<int, float const>::type,const int>::value)); //see IsConst for int const* and int* const
        
        Static_Assert((!MiniMPL::IsSameType<typename MiniMPL::SameAllQualifier<int,const float>::type,const float>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::SameAllQualifier<const int,volatile float>::type,volatile int>::value));
        Static_Assert((!MiniMPL::IsSameType<typename MiniMPL::SameAllQualifier<const int,volatile char>::type,char>::value));

        //demo RefAdapter
        Static_Assert((!MiniMPL::IsRef<typename MiniMPL::RefAdapter<int>::type>::value));          //if it is build-in type,keep original type : ref type / non-ref type
        Static_Assert((MiniMPL::IsRef<typename MiniMPL::RefAdapter<int&>::type>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int&>::type,int&>::value)); 
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int>::type,int>::value)); 
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int>::type,int&>::value)); 
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int&>::type,int>::value)); 
        Static_Assert(!(MiniMPL::IsRef<typename MiniMPL::RefAdapter<const int>::type>::value));    
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int&>::type,int&>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int>::type,int>::value));
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int>::type,int&>::value));
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int&>::type,bool>::value));
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int&>::type,char>::value));        
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int>::type,bool>::value));
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::RefAdapter<int>::type,char>::value));
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::RefAdapter<S3&>::type,S3>::value));  //if it is not build-in type, it is always ref-type
        Static_Assert(!(MiniMPL::IsSameType<typename MiniMPL::RefAdapter<S3>::type,S3>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::RefAdapter<S3&>::type,S3&>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::RefAdapter<S3>::type,S3&>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::RefAdapter<S3*>::type,S3*>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::RefAdapter<stlVector<S3>::iterator>::type,stlVector<S3>::iterator>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::RefAdapter<stlSmartptr<S3> >::type,stlSmartptr<S3>>::value));
        Static_Assert((MiniMPL::IsRef<typename MiniMPL::RefAdapter<ConstStruct>::type>::value));
        Static_Assert((MiniMPL::IsRef<typename MiniMPL::RefAdapter<int[20]>::type>::value));
        Static_Assert((MiniMPL::IsRef<typename MiniMPL::RefAdapter<ConstStruct[20]>::type>::value));        //need reference because original type is not reference type
        Static_Assert((MiniMPL::IsRef<typename MiniMPL::RefAdapter<int(&)[20]>::type>::value));	            //RefAdapter will give reference type for reference type
        Static_Assert((MiniMPL::IsRef<typename MiniMPL::RefAdapter<ConstStruct(&)[20]>::type>::value));     //RefAdapter will give reference type for reference type

        //test same const
        //demo SameConst
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::SameConst<int,const float>::type,const int>::value));
        Static_Assert((!MiniMPL::IsSameType<typename MiniMPL::SameConst<int,const float>::type,const float>::value));
        Static_Assert((MiniMPL::IsSameType<typename MiniMPL::SameConst<const int,float>::type,int>::value));
        Static_Assert((!MiniMPL::IsSameType<typename MiniMPL::SameConst<const int,char>::type,char>::value));
        Static_Assert((MiniMPL::IsConst<MiniMPL::SameConst<int,const char>::type>::value));
        Static_Assert((MiniMPL::IsConst<MiniMPL::SameConst<const int,const char>::type>::value));
        Static_Assert((!MiniMPL::IsConst<MiniMPL::SameConst<const int,char>::type>::value));
        Static_Assert((!MiniMPL::IsConst<MiniMPL::SameConst<int,char>::type>::value));

        //test Same SameRef
        Static_Assert((MiniMPL::IsRef<MiniMPL::SameRef<int&,const char&>::type>::value));
        Static_Assert((MiniMPL::IsRef<MiniMPL::SameRef<int,const char&>::type>::value));
        Static_Assert((!MiniMPL::IsRef<MiniMPL::SameRef<int&,char>::type>::value));
        Static_Assert((!MiniMPL::IsRef<MiniMPL::SameRef<int,char>::type>::value));

        //test Same SamePointer
        Static_Assert((MiniMPL::IsPointer<MiniMPL::SamePointer<int&,const char*>::type>::value));
        Static_Assert((MiniMPL::IsPointer<MiniMPL::SamePointer<int,const char*>::type>::value));
        Static_Assert((!MiniMPL::IsPointer<MiniMPL::SamePointer<int&,char>::type>::value));
        Static_Assert((!MiniMPL::IsPointer<MiniMPL::SamePointer<int,char>::type>::value));
        Static_Assert((IsPointer<wchar_t*>::value));
        Static_Assert((IsPointer<char*>::value));
        Static_Assert((IsPointer<int*>::value));
        Static_Assert((!IsPointer<int>::value));
        Static_Assert((!IsPointer<char>::value));
        Static_Assert((!IsPointer<wchar_t>::value));
        Static_Assert((!IsPointer<int S4::*>::value)); //member pointer is not pointer

        //test Same SameVolatile
        Static_Assert((MiniMPL::IsVolatile<MiniMPL::SameVolatile<int,volatile char>::type>::value));
        Static_Assert((MiniMPL::IsVolatile<MiniMPL::SameVolatile<int,volatile char>::type>::value));
        Static_Assert((!MiniMPL::IsVolatile<MiniMPL::SameVolatile<int,char>::type>::value));
        Static_Assert((!MiniMPL::IsVolatile<MiniMPL::SameVolatile<int,char>::type>::value));
    }

#ifdef RUN_EXAMPLE_SAMEQUALIFIER
    InitRunFunc(TestCase_sameQualifier);
#else //else of RUN_EXAMPLE_SAMEQUALIFIER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_SAMEQUALIFIER)=(outputTxtV(TXT("[Unit test run disabled] sameQualifier.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"sameQualifier.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_SAMEQUALIFIER
}

#else //else of COMPILE_EXAMPLE_SAMEQUALIFIER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_SAMEQUALIFIER)=(outputTxtV(TXT("[Unit test compile disabled] sameQualifier.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"sameQualifier.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_SAMEQUALIFIER

#endif // __TEST_SAMEQUALIFIER_HPP__
