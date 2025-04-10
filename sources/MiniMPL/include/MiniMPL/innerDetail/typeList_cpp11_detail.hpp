#ifndef __TYPELIST_CPP11_DETAIL_HPP__
#define __TYPELIST_CPP11_DETAIL_HPP__
/***********************************************************************************************************************
* Description         : implemented for typeList_cpp11.hpp
                        add/remove qualifier : reference,const,CPointer,Volatile
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/kitType.hpp>

namespace MiniMPL
{
    template <typename ... Args>                                                                        struct TypeList;    // fw declare
    namespace InnerDetail
    {
      template<typename HeadTypes , typename TailTypes >                                                struct ReverseTypeListArgs;
      template<typename ... NewTypes>                                                                   struct ReverseTypeListArgs<TypeList<NewTypes ... >, TypeList<>>                : public Type2Type<TypeList<NewTypes ... >> { };
      template<typename T, typename ... NewTypes , typename ... RawTypes >                              struct ReverseTypeListArgs<TypeList<NewTypes ... >, TypeList<T, RawTypes ...>> : public ReverseTypeListArgs<TypeList<T, NewTypes ...>, TypeList<RawTypes ...>> { };
      
      template<size_t   N, typename     TListIn,   typename     TListOut>                               struct GetFirstNTypesImpl;
      template<typename T, typename ... TailTypes, typename ... HeadTypes>                              struct GetFirstNTypesImpl<1, TypeList<T, TailTypes...>, TypeList<HeadTypes...>> : public Type2Type<TypeList<HeadTypes..., T>> {};
      template<size_t   N, typename     T,         typename ... TailTypes, typename ... HeadTypes>      struct GetFirstNTypesImpl<N, TypeList<T, TailTypes...>, TypeList<HeadTypes...>> : public GetFirstNTypesImpl<N-1, TypeList<TailTypes...>, TypeList<HeadTypes..., T>> {};

      template<size_t idx, typename ... Types>                                                          struct GetAllTypesFromIdxImpl;
      template<                                typename ... Types>                                      struct GetAllTypesFromIdxImpl<0,      Types...> : public Type2Type<TypeList<Types...>> {};
      template<size_t idx, typename     T,     typename ... Types>                                      struct GetAllTypesFromIdxImpl<idx, T, Types...> : public GetAllTypesFromIdxImpl<idx-1, Types...> {};
      
      template<size_t idx, typename R, typename HeadTypes , typename TailTypes >                        struct ReplaceNthTypeInTypeListArgs;
      template<            typename R, typename T, typename ... HeadTypes , typename ... TailTypes >    struct ReplaceNthTypeInTypeListArgs<0,   R, TypeList<HeadTypes ... >, TypeList<T, TailTypes ...>> : public Type2Type<TypeList<HeadTypes ..., R, TailTypes ... >> { };
      template<size_t idx, typename R, typename T, typename ... HeadTypes , typename ... TailTypes >    struct ReplaceNthTypeInTypeListArgs<idx, R, TypeList<HeadTypes ... >, TypeList<T, TailTypes ...>> : public ReplaceNthTypeInTypeListArgs<idx-1, R, TypeList<HeadTypes ... , T>, TypeList<TailTypes ...>> { };
      
      template<size_t idx, typename HeadTypes , typename TailTypes >                                    struct DeleteNthTypeInTypeListArgs;
      template<            typename D, typename ... HeadTypes , typename ... TailTypes >                struct DeleteNthTypeInTypeListArgs<0,   TypeList<HeadTypes ... >, TypeList<D, TailTypes ...>> : public Type2Type<TypeList<HeadTypes ..., TailTypes ... >> { };
      template<size_t idx, typename T, typename ... HeadTypes , typename ... TailTypes >                struct DeleteNthTypeInTypeListArgs<idx, TypeList<HeadTypes ... >, TypeList<T, TailTypes ...>> : public DeleteNthTypeInTypeListArgs<idx-1, TypeList<HeadTypes ... , T>, TypeList<TailTypes ...>> { };

      template<size_t idx, typename I, typename HeadTypes , typename TailTypes , bool b=(idx==0)>       struct InsertTypeInTypeListArgs;     // perhaps hit a compiler bug when idx == 0 on MS VS2019 compiler if no bool b
      template<            typename I, typename ... HeadTypes , typename ... TailTypes >                struct InsertTypeInTypeListArgs<0,   I, TypeList<HeadTypes ... >, TypeList<   TailTypes ...>, true > : public Type2Type<TypeList<HeadTypes ..., I, TailTypes ... >> { };
      template<size_t idx, typename I, typename T, typename ... HeadTypes , typename ... TailTypes >    struct InsertTypeInTypeListArgs<idx, I, TypeList<HeadTypes ... >, TypeList<T, TailTypes ...>, false> : public InsertTypeInTypeListArgs<idx-1, I, TypeList<HeadTypes ... , T>, TypeList<TailTypes ...>> { };
      
    }
}


#endif // __TYPELIST_CPP11_DETAIL_HPP__
