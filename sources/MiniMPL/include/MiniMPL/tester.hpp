#ifndef __TESTER_HPP__
#define __TESTER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/tester_detail.hpp>
#include <MiniMPL/valueCompare.hpp>
#include <MiniMPL/memberPtr.hpp>
#include <MiniMPL/valueCompare.hpp>
#include <MiniMPL/unaryFunctionAssemble.hpp>
#include <MiniMPL/macroDef.h>

namespace MiniMPL
{
    template<typename Ref_T,class TCmp>
    struct UnaryTester : protected UnaryComparer<Ref_T,TCmp>
    {
        UnaryTester(TPP(Ref_T) cmpRef,TPP(TCmp) rCmp,bool bExpected=true)
            :UnaryComparer(cmpRef,rCmp),m_cmpExpected(bExpected){};

        template<typename T>
        bool operator()(T& rObj)
        {
            return m_cmpExpected == test(rObj);
        }

        bool        m_cmpExpected;
    };

    template<typename Ref_T,class TCmp>  //if C2436, use macro REFADDR to pack parameter at call point. (REFADDR : reference hard-code address)
    UnaryTester<Ref_T,TCmp> makeUnaryTester(Ref_T cmpRef,TCmp rCmp,bool bExpected=true)
    {
        return UnaryTester<Ref_T,TCmp>(cmpRef,rCmp,bExpected);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<bool Tval>
    struct UnaryTester_Fixed
    {
        template<typename T>
        bool operator()(T& /*rObj*/)
        {
            return Tval;
        }
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename UF_T,typename Ref_T,class TCmp>
    struct UnaryTester_Result : public UnaryTester<Ref_T,TCmp>
    {
        UnaryTester_Result(TPP(UF_T) f,TPP(Ref_T) cmpRef,TPP(TCmp) rCmp, bool bExpected=true)
            : UnaryTester(cmpRef,rCmp,bExpected)
            , m_f(f)
        {}

        template<typename TP> bool operator()(TP& obj)
        {
            return UnaryTester::operator ()(m_f(obj));
        }

        UF_T                m_f;
    };

    template<typename TUF,typename Ref_T,typename TCmp>
    UnaryTester_Result<TUF,Ref_T,TCmp> makeUnaryTester_Result(TUF rUf,Ref_T retChk,TCmp rCmp,bool bExpected=true)
    {
        return UnaryTester_Result<TUF,Ref_T,TCmp>(rUf,retChk,rCmp,bExpected);
    }

    template<typename S,typename M,typename Ref_T,typename TCmp>
    UnaryTester_Result<CDataMemberPtr<M S::*>,Ref_T,TCmp> makeUnaryTester_Result(M S::* ptr,Ref_T retChk,TCmp rCmp,bool bExpected=true)
    {
        return makeUnaryTester_Result(CDataMemberPtr<M S::*>(ptr),retChk,rCmp,bExpected);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<char ch,typename UT1,typename UT2>
    struct UnaryTester_Combined
    {
        UnaryTester_Combined(TPP(UT1) ut1,TPP(UT2) ut2)
            : m_ut1(ut1),m_ut2(ut2) {}

        template<typename T>    bool operator()(T& p)
        {
            return InnerDetail::ApplyOperation<ch>::impl(m_ut1,m_ut2,p);
        }

        UT1                 m_ut1;
        UT2                 m_ut2;
    };

    template<char ch,typename TUF1,typename TUF2>
    UnaryTester_Combined<ch,TUF1,TUF2> makeUnaryTester_Combined(TUF1 rUf1,TUF2 rUf2)
    {
        return UnaryTester_Combined<ch,TUF1,TUF2>(rUf1,rUf2);
    }

    namespace CGetType
    {
        template<char ch1,char ch,char ch2,typename ThresholdL,typename ThresholdR=ThresholdL>
        struct TRangeTester : public Type2Type<UnaryTester_Combined<ch,UnaryTester<ThresholdL,TComparer<ch1> > , UnaryTester<ThresholdR,TComparer<ch2> > > >{};

        template<char ch1,char ch,char ch2,typename TUF,typename ThresholdL,typename ThresholdR=ThresholdL>
        struct TRangeTesterUF : public Type2Type<UnaryTester_Combined<ch,UnaryTester_Result<TUF,ThresholdL,TComparer<ch1> > , UnaryTester_Result<TUF,ThresholdR,TComparer<ch2> > > >{};
    }

    template<char ch1,char ch,char ch2,typename ThresholdL,typename ThresholdR>
    UnaryTester_Combined<ch,UnaryTester<ThresholdL,TComparer<ch1> > , UnaryTester<ThresholdR,TComparer<ch2> > >
        makeUnaryTester_Range(ThresholdL lVal,ThresholdR rVal)
    {
        ASSERT_AND_LOG(lVal<=rVal);
        typedef TComparer<ch1>          LCmp;
        typedef UnaryTester<ThresholdL,LCmp>    LCondition;

        typedef TComparer<ch2>          RCmp;   //because TCmp()(m_ret , m_f(obj)); , right cmp need (m_f(obj),m_ret)
        typedef UnaryTester<ThresholdR,RCmp>    RCondition;

        typedef UnaryTester_Combined<ch,LCondition,RCondition>  TCombinedTester;     

        return TCombinedTester(LCondition(lVal,TComparer<ch1>(),true),RCondition(rVal,TComparer<ch2>(),true));
    }

    template<char ch1,char ch,char ch2,typename TUF,typename ThresholdL,typename ThresholdR>
    UnaryTester_Combined<ch,UnaryTester_Result<TUF,ThresholdL,TComparer<ch1> > , UnaryTester_Result<TUF,ThresholdR,TComparer<ch2> > >
        makeUnaryTester_Range(ThresholdL lVal,ThresholdR rVal,TUF rUf)
    {
        ASSERT_AND_LOG(lVal<=rVal);
        typedef TComparer<ch1>          LCmp;
        typedef UnaryTester_Result<TUF,ThresholdL,LCmp>    LCondition;

        typedef TComparer<ch2>          RCmp;   //because TCmp()(m_ret , m_f(obj)); , right cmp need (m_f(obj),m_ret)
        typedef UnaryTester_Result<TUF,ThresholdR,RCmp>    RCondition;

        typedef UnaryTester_Combined<ch,LCondition,RCondition>  TCombinedTester;     

        return TCombinedTester(LCondition(rUf,lVal,TComparer<ch1>(),true),RCondition(rUf,rVal,TComparer<ch2>(),true));
    }
}


#endif // __TESTER_HPP__
