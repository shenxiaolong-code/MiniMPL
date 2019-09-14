#ifndef MEMBERPTR_DETAIL_H__
#define MEMBERPTR_DETAIL_H__
/***********************************************************************************************************************
Description         : detail implement of memberPtr.hpp
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           :free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/sameQualifier.hpp>

namespace MiniMPL 
{
    template<typename T>                struct CDataMemberPtr;    //fw declare
    typedef unsigned long               TMemberOffset;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    namespace InnerDetail
    {
        //Member pointer MUST has "M S::*" form.
        template<typename T>                struct GetStructImpl;
        template <typename S, typename M>   struct GetStructImpl<M S::*>        : public Type2Type<S>           {};
        template <typename S, typename M>   struct GetStructImpl<M S::* const>  : public GetStructImpl<M S::*>  {};
        template <typename S, typename M>   struct GetStructImpl<CDataMemberPtr<M S::*> >   : public Type2Type<S>   {};
        template <typename S, typename M>   struct GetStructImpl<CDataMemberPtr<M S::* const> >   : public Type2Type<S> {};
        template <typename T>   struct GetStructImpl<CDataMemberPtr<T> >            : public Type2Type<T>           {};

        template <typename T>               struct GetMemberImpl;
        template <typename S, typename M>   struct GetMemberImpl<M S::*>        : public Type2Type<M>           {}; 
        template <typename S, typename M>   struct GetMemberImpl<M S::* const>  : public GetMemberImpl<M S::*>  {}; 
        template <typename S, typename M>   struct GetMemberImpl<CDataMemberPtr<M S::*> >  : public Type2Type<M>    {}; 
        template <typename S, typename M>   struct GetMemberImpl<CDataMemberPtr<M S::* const> >  : public Type2Type<M>  {}; 
        template <typename T>   struct GetMemberImpl<CDataMemberPtr<T> >            : public Type2Type<T>           {}; 

        template<typename T> struct getTMemberPtr                   : public Type2Type<CDataMemberPtr<T> >          {};
        template<typename T> struct getTMemberPtr<CDataMemberPtr<T> >   : public Type2Type<CDataMemberPtr<T> >          {};
    }
    

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename M, typename TP>
    struct AdaptQualifier :  public AddRef<SC(M,TP)> {};
}

#endif // MEMBERPTR_DETAIL_H__
