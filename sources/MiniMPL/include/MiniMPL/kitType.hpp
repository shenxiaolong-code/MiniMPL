#ifndef __KITTYPE_HPP__
#define __KITTYPE_HPP__
/***********************************************************************************************************************
* Description         : base type used by MiniMPL namespace
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/platformEnv.h>
#include <cstddef>

namespace MiniMPL
{
    struct								        NullType;
    typedef char						        Yes_Type;
    typedef struct { char dummy[2]; }	        No_Type;
    template<typename T>                        using sfinae_helper_t = NullType;                             // need C++11, else use HasXXXType(type)

    template<typename T>                        struct Type2Type                                                                            { typedef T type;                   };
    template <typename T, typename=NullType>    struct getType                                          : public Type2Type<T>               {                                   };
    template <typename T>                       struct getType<T, sfinae_helper_t<typename T::type> >   : public getType<typename T::type>  {                                   };  // C++ template lazy mechanism. sfinae_helper_t will force to parse it immediately. here sfinae_helper_t is same to std::void_t
    template<typename T>                        using  getType_t = typename getType<T>::type;             // get type embed type

    template<typename T, T val>                 struct ValueType                                        : public Type2Type<T>               { static constexpr T value = val;   };  // ValueType should keep val type info : int, float, double, pointer, reference, enum
    // template<auto val>                       struct ValueType{}                                      : public Type2Type<decltype(val)>   {                                   };  //C++20 support non-type template parameters keyword auto, it is more powerful.
    template<typename T>                        constexpr bool getValue_v = T::value;                                                                                               // get type embed value , see std::is_same_v.  inline constexpr requires C++17

    template<typename T>                                                struct Type2Value;
    template<typename T, T val, template<typename V, V> class Impl_T >  struct Type2Value<Impl_T<T, val> > : public ValueType<T,val> {};
    
    template<bool x>                            using BoolType=ValueType<bool,x>;                       // std::bool_constant<x>
    template<int TVal>                          using Int2Type=ValueType<int,TVal>;                     // std::integral_constant<int, TVal>
    template<size_t TVal>                       using Size2Type=ValueType<size_t,TVal>;                 // size_t requires #include <cstddef> 
                                                using TrueType=BoolType<true>;                          // std::true_type 
                                                using FalseType=BoolType<false>;                        // std::false_type
    
    // string bind
    template <const char* ptr>                  struct ConstString : public ValueType<const char*, ptr> {};
    template <int>                              struct GetString;
    // constexpr const char                     example_string[] = "demo binding integer with string";
    // template <>                              struct GetString<111> : public ConstString<example_string> {};
#if CPP17_ENABLED
    template <int v>                            inline constexpr decltype(GetString<v>::value) getString_v = GetString<v>::value;
#endif

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<bool,typename True_T,typename False_T>         struct If_T                         : public Type2Type<True_T>     {} ; //std::conditional<b, True_T, False_T>
    template<typename True_T,typename False_T>              struct If_T<false,True_T,False_T>   : public Type2Type<False_T>    {} ;
    template<typename B,typename True_T,typename False_T>   struct If_Evl : public If_T<B::value,True_T,False_T> {};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //resolve compile requirement "uninstantiated template class can't be base class". e.g.
    //template<typename T> struct CImpl;
    //CImpl can't be base class without instance T, but DelayApply<CImpl> can! (transfer non-type to type)
    template<template<class> class Impl_T>   struct DelayApply
    {    
        template<typename T> struct apply: public Impl_T<T>{};
    };
}


#endif // __KITTYPE_HPP__
