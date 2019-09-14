#ifndef UNARYFUNCTIONASSEMBLE_DETAIL_H__
#define UNARYFUNCTIONASSEMBLE_DETAIL_H__

/***********************************************************************************************************************
Description         : implement of <MiniMPL\unaryFunctionAssemble.hpp>
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/unaryFunction.hpp>
#include <MiniMPL/memberPtr.hpp>
#include <MiniMPL/sameQualifier.hpp>

namespace MiniMPL
{
    template<typename TUF1,typename TUF2> 
    struct GetFunctionReturn2T_Impl : public GetFunctionReturn<TUF2>{};
    template<typename TUF1,typename S, typename M>
    struct GetFunctionReturn2T_Impl<TUF1,M S::*>                : public SameAllQualifier<M,typename GetFunctionReturn<TUF1>::type>{};
    template<typename TUF1,typename S, typename M>
    struct GetFunctionReturn2T_Impl<TUF1,M S::* const>          : public GetFunctionReturn2T_Impl<TUF1,M S::*>{};
    template<typename TUF1,typename TMemPtr>
    struct GetFunctionReturn2T_Impl<TUF1,CDataMemberPtr<TMemPtr> >  : public GetFunctionReturn2T_Impl<TUF1,TMemPtr>{};
}

#endif // UNARYFUNCTIONASSEMBLE_DETAIL_H__
