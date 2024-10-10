#ifndef __MINIMPL_TYPELIST_CPP11_HPP__
#define __MINIMPL_TYPELIST_CPP11_HPP__
/***********************************************************************************************************************
* Description         : Templated type lists, requires at least C++11
*                       note : the typeList.hpp only needs C++03
* Author              : Shen.Xiaolong (at 2024-09-23) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/innerDetail/typeList_cpp11_detail.hpp>

namespace MiniMPL
{    
    template <typename ... Args>                                                                        struct TypeList;        // definition is not necessary ， declaration is enough
    
    ///////////////////////////////////////////////////////////////////// test type list ////////////////////////////////////////////////////////////////////////////////////////////
    template<typename TList>                                                                            struct GetTypeListLength;
    template<template <typename ...> class TList,typename ... Types >                                   struct GetTypeListLength<TList<Types ...>>      : public Size2Type<sizeof...(Types)> {};
#if CPP17_ENABLED
    template<typename TList>                                                                            using inline constexpr size_t  GetTypeListLength_v=GetTypeListLength<TList>::value;
#endif

    template<typename T, typename TList>                                                                struct TypeIsInTypeList;
    template<typename T, template <typename ...> class TList>                                           struct TypeIsInTypeList<T,TList<> >             : public FalseType                              {};
    template<typename T, template <typename ...> class TList, typename ... Types >                      struct TypeIsInTypeList<T,TList<T, Types...> >  : public TrueType                               {};
    template<typename T, typename R, template <typename ...> class TList, typename ... Types >          struct TypeIsInTypeList<T,TList<R, Types...> >  : public TypeIsInTypeList<T,TList<Types...> >   {};

    template<typename T, typename TList, bool bInList=TypeIsInTypeList<T,TList>::value>                 struct GetTypeFirstIndexInTypeList;
    template<typename T, typename TList>                                                                struct GetTypeFirstIndexInTypeList<T,TList,              false> : public Int2Type<-1>                                                       {};
    template<typename T, template <typename ...> class TList, typename ... Types >                      struct GetTypeFirstIndexInTypeList<T,TList<T, Types...>, true > : public Int2Type<0>                                                        {};
    template<typename T, typename R, template <typename ...> class TList, typename ... Types >          struct GetTypeFirstIndexInTypeList<T,TList<R, Types...>, true > : public Int2Type<1+GetTypeFirstIndexInTypeList<T,TList<Types...>>::value>  {};

    ///////////////////////////////////////////////////////////////////// manipulate type list ////////////////////////////////////////////////////////////////////////////////////////////  
    template <typename T1, template <typename ...> class dst>                                           struct ReplaceWrapperTemplate;
    template <template <typename ...> class src, template <typename...> class dst, typename... Args>    struct ReplaceWrapperTemplate<src<Args...>, dst> : public Type2Type<dst<Args...>> {};
    template <typename T1, template <typename ...> class dst>                                           using  ReplaceWrapperTemplate_t = typename ReplaceWrapperTemplate<T1,dst>::type;

    template<size_t idx, typename TList>                                                                struct GetNthTypeInTypeList;
    template<typename T, template <typename ...> class TList, typename ... Types >                      struct GetNthTypeInTypeList<0,TList<T, Types...>>       : public Type2Type<T>                                   {};
    template<size_t idx, template <typename ...> class TList, typename T, typename ... Types >          struct GetNthTypeInTypeList<idx, TList<T, Types ...>>   : public GetNthTypeInTypeList<idx-1, TList<Types ...>>  {};
    template<size_t idx, typename TList>                                                                using  GetNthTypeInTypeList_t =  typename  GetNthTypeInTypeList<idx,TList>::type;

    template<size_t idx, typename R, typename TList>                                                    struct ReplaceNthTypeInTypeList;
    template<size_t idx, typename R, template <typename ...> class TList, typename ... Types >          struct ReplaceNthTypeInTypeList<idx, R, TList<Types...>> : public ReplaceWrapperTemplate<typename InnerDetail::ReplaceNthTypeInTypeListArgs<idx, R , TypeList<>, TypeList<Types ...> >::type,TList> {};
    template<size_t idx, typename R, typename TList>                                                    using  ReplaceNthTypeInTypeList_t = typename ReplaceNthTypeInTypeList<idx, R, TList>::type;

    template<size_t idx, typename TList>                                                                struct DeleteNthTypeInTypeList;
    template<size_t idx, template <typename ...> class TList, typename ... Types >                      struct DeleteNthTypeInTypeList<idx, TList<Types...>> : public ReplaceWrapperTemplate<typename InnerDetail::DeleteNthTypeInTypeListArgs<idx, TypeList<>, TypeList<Types ...> >::type,TList> {};
    template<size_t idx, typename TList>                                                                using  DeleteNthTypeInTypeList_t = typename DeleteNthTypeInTypeList<idx, TList>::type;

    template<size_t idx, typename I, typename TList>                                                    struct InsertTypeInTypeList;
    template<size_t idx, typename I, template <typename ...> class TList, typename ... Types >          struct InsertTypeInTypeList<idx, I, TList<Types...>> : public ReplaceWrapperTemplate<typename InnerDetail::InsertTypeInTypeListArgs<idx, I , TypeList<>, TypeList<Types ...> >::type,TList> {};
    template<size_t idx, typename I, typename TList>                                                    using  InsertTypeInTypeList_t = typename InsertTypeInTypeList<idx, I, TList>::type;

    template<typename I, typename TList>                                                                struct AppendTypeInTypeList : public InsertTypeInTypeList<GetTypeListLength<TList>::value, I, TList >{};
    template<typename I, typename TList>                                                                using  AppendTypeInTypeList_t = typename AppendTypeInTypeList<I, TList>::type;

 
}


#endif // __MINIMPL_TYPELIST_CPP11_HPP__
