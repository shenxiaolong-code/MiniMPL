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
    template<typename TList>                                                                            struct ReverseTypeList; 

    template<typename TList>                                                                            struct GetTypeListLength;
    template<template <typename ...> class TList,typename ... Types >                                   struct GetTypeListLength<TList<Types ...>>      : public Size2Type<sizeof...(Types)> {};
#if CPP_STD >= 17
    template<typename TList>                                                                            using inline constexpr size_t  GetTypeListLength_v=GetTypeListLength<TList>::value;
#endif // CPP_STD >= 17

    template<typename T, typename TList>                                                                struct TypeIsInTypeList;
    template<typename T, template <typename ...> class TList>                                           struct TypeIsInTypeList<T,TList<> >             : public FalseType                              {};
    template<typename T, template <typename ...> class TList, typename ... Types >                      struct TypeIsInTypeList<T,TList<T, Types...> >  : public TrueType                               {};
    template<typename T, typename R, template <typename ...> class TList, typename ... Types >          struct TypeIsInTypeList<T,TList<R, Types...> >  : public TypeIsInTypeList<T,TList<Types...> >   {};
#if CPP_STD >= 17
    template<typename T, typename TList>                                                                using inline constexpr size_t  TypeIsInTypeList_v=TypeIsInTypeList<T, TList>::value;
#endif // CPP_STD >= 17

    template<typename T, typename TList, bool bInList=TypeIsInTypeList<T,TList>::value>                 struct FindTypeFirstIndexInTypeList;
    template<typename T, typename TList>                                                                struct FindTypeFirstIndexInTypeList<T,TList,              false> : public Int2Type<-1>                                                       {};
    template<typename T, template <typename ...> class TList, typename ... Types >                      struct FindTypeFirstIndexInTypeList<T,TList<T, Types...>, true > : public Int2Type<0>                                                        {};
    template<typename T, typename R, template <typename ...> class TList, typename ... Types >          struct FindTypeFirstIndexInTypeList<T,TList<R, Types...>, true > : public Int2Type<1+FindTypeFirstIndexInTypeList<T,TList<Types...>>::value> {};
#if CPP_STD >= 17
    template<typename T, typename TList>                                                                using inline constexpr size_t  FindTypeFirstIndexInTypeList_v=FindTypeFirstIndexInTypeList<T, TList>::value;
#endif // CPP_STD >= 17

    template<typename T, typename TList, bool bInList=TypeIsInTypeList<T,TList>::value>                 struct FindTypeLastIndexInTypeList;
    template<typename T, typename TList>                                                                struct FindTypeLastIndexInTypeList<T,TList, false> : public Int2Type<-1>                                                        {};
    template<typename T, typename TList>                                                                struct FindTypeLastIndexInTypeList<T,TList, true>  : public Int2Type<GetTypeListLength<TList>::value - FindTypeFirstIndexInTypeList<T,typename ReverseTypeList<TList>::type>::value - 1> {};
#if CPP_STD >= 17
    template<typename T, typename TList>                                                                using inline constexpr size_t  FindTypeLastIndexInTypeList_v=FindTypeLastIndexInTypeList<T, TList>::value;
#endif // CPP_STD >= 17
    ///////////////////////////////////////////////////////////////////// collect type list ////////////////////////////////////////////////////////////////////////////////////////////  
    template<size_t   N, typename TList>                                                                struct GetFirstNTypes;
    template<template <typename ...> class TList, typename ... Types>                                   struct GetFirstNTypes<0, TList<Types...>> : public Type2Type<TypeList<>> {};
    template<size_t   N, template <typename ...> class TList, typename ... Types>                       struct GetFirstNTypes<N, TList<Types...>> : public InnerDetail::GetFirstNTypesImpl<N, TypeList<Types...>, TypeList<> > {};
    template<size_t   N, typename TList>                                                                using  GetFirstNTypes_t = typename GetFirstNTypes<N, TList>::type;

    template<size_t idx, typename TList>                                                                struct GetAllTypesFromIdx;
    template<size_t idx, template <typename ...> class TList, typename ... Types>                       struct GetAllTypesFromIdx<idx, TList<Types...>> : public InnerDetail::GetAllTypesFromIdxImpl<idx,Types...> {};
    template<size_t idx, typename TList>                                                                using  GetAllTypesFromIdx_t = typename GetAllTypesFromIdx<idx, TList>::type;

    template<size_t N, typename TList>                                                                  struct GetLastNTypes : public GetAllTypesFromIdx<GetTypeListLength<TList>::value - N, TList> {};
    template<size_t N, typename TList>                                                                  using  GetLastNTypes_t = typename GetLastNTypes<N, TList>::type;

    ///////////////////////////////////////////////////////////////////// manipulate type list ////////////////////////////////////////////////////////////////////////////////////////////  
    template <typename T1, template <typename ...> class dst>                                           struct ReplaceWrapperTemplate;
    template <template <typename ...> class src, template <typename...> class dst, typename... Args>    struct ReplaceWrapperTemplate<src<Args...>, dst> : public Type2Type<dst<Args...>> {};
    template <typename T1, template <typename ...> class dst>                                           using  ReplaceWrapperTemplate_t = typename ReplaceWrapperTemplate<T1,dst>::type;

    template<typename TList>                                                                            struct ReverseTypeList; 
    template<template <typename ...> class TList, typename ... Types >                                  struct ReverseTypeList<TList<Types...>> : public ReplaceWrapperTemplate<typename InnerDetail::ReverseTypeListArgs<TypeList<>, TypeList<Types ...> >::type,TList> {};
    template<typename TList>                                                                            using  ReverseTypeList_t = typename ReverseTypeList<TList>::type;


    template<size_t idx, typename TList>                                                                struct FindNthTypeInTypeList;
    template<typename T, template <typename ...> class TList, typename ... Types >                      struct FindNthTypeInTypeList<0,TList<T, Types...>>       : public Type2Type<T>                                   {};
    template<size_t idx, template <typename ...> class TList, typename T, typename ... Types >          struct FindNthTypeInTypeList<idx, TList<T, Types ...>>   : public FindNthTypeInTypeList<idx-1, TList<Types ...>> {};
    template<size_t idx, typename TList>                                                                using  FindNthTypeInTypeList_t =  typename  FindNthTypeInTypeList<idx,TList>::type;

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
