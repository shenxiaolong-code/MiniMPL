#ifndef __COMPARER_HPP__
#define __COMPARER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/comparer_detail.hpp>
#include <MiniMPL/binaryFunction.hpp>
#include <MiniMPL/memberPtr.hpp>
#include <MiniMPL/sameQualifier.hpp>

namespace MiniMPL
{
    template<typename TBinaryFunc>
    TBinaryFunc& makeComparer(TBinaryFunc& f)
    {
        return f;
    }

    template<typename TUnaryFunc,typename TBinaryFunc>
    struct ResultComparer
    {
        typedef typename InnerDetail::TGetComparerReturn<TBinaryFunc>::type     Return_T;

        explicit ResultComparer(TPP(TUnaryFunc) uf,TPP(TBinaryFunc) bf)
            : m_uf(uf)
            , m_bf(bf)
        {};

        template<typename TL,typename TR>
        Return_T operator()(TL& p1,TR& p2) const
        {
            return m_bf(m_uf(p1),m_uf(p2));
        }

    protected:        
        TUnaryFunc      m_uf;
        TBinaryFunc     m_bf;
    };

    template<typename TUnaryFunc,typename TBinaryFunc>
    inline ResultComparer<TUnaryFunc,TBinaryFunc>  makeComparer(TUnaryFunc uf,TBinaryFunc bf)
    {
        return ResultComparer<TUnaryFunc,TBinaryFunc>(uf,bf);
    }

    template<typename S,typename M,typename TBinaryFunc>
    inline ResultComparer<CDataMemberPtr<M S::*>,TBinaryFunc>  makeComparerByMember(M S::* ptr,TBinaryFunc bf)
    {
        return ResultComparer<CDataMemberPtr<M S::*>,TBinaryFunc>(CDataMemberPtr<M S::*>(ptr),bf);
    }
}

#endif // __COMPARER_HPP__
