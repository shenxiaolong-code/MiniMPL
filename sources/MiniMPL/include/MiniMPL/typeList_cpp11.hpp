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
    
    template <typename T1, template <typename ...> class dst>                                           struct ReplaceWrapperTemplate;
    template <template <typename ...> class src, template <typename...> class dst, typename... Args>    struct ReplaceWrapperTemplate<src<Args...>, dst> : public Type2Type<dst<Args...>> {};
    template <typename T1, template <typename ...> class dst>                                           using  ReplaceWrapperTemplate_t = typename ReplaceWrapperTemplate<T1,dst>::type;

    template<typename TList>                                                                            struct GetTypeListLength;
    template<template <typename ...> class TList,typename ... Types >                                   struct GetTypeListLength<TList<Types ...>>      : public Size2Type<sizeof...(Types)> {};
#if CPP17_ENABLED
    template<typename TList>                                                                            using inline constexpr size_t  GetTypeListLength_v=GetTypeListLength<TList>::value;
#endif

    template<size_t idx, typename TList>                                                                struct GetNthTypeInTypeList;
    template<typename T, template <typename ...> class TList, typename ... Types >                      struct GetNthTypeInTypeList<0,TList<T, Types...>> : public Type2Type<T>  { };
    template<size_t idx, template <typename ...> class TList, typename T, typename ... Types >          struct GetNthTypeInTypeList<idx, TList<T, Types ...>> : public GetNthTypeInTypeList<idx-1, TList<Types ...>> { };
    template<size_t idx, typename TList>                                                                using  GetNthTypeInTypeList_t =  typename  GetNthTypeInTypeList<idx,TList>::type;

    template<size_t idx, typename R, typename TList>                                                    struct ReplaceNthTypeInList;
    template<size_t idx, typename R, template <typename ...> class TList, typename ... Types >          struct ReplaceNthTypeInList<idx, R, TList<Types...>> : public ReplaceWrapperTemplate<typename InnerDetail::ReplaceNthTypeInListArgs<idx, R , TypeList<>, TypeList<Types ...> >::type,TList> {};
    template<size_t idx, typename R, typename TList>                                                    using  ReplaceNthTypeInList_t = typename ReplaceNthTypeInList<idx, R, TList>::type;

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
