#ifndef __KITTYPE_HPP__
#define __KITTYPE_HPP__
/***********************************************************************************************************************
* Description         : base type used by MiniMPL namespace
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
namespace MiniMPL
{
    struct									        NullType;
    typedef char						            Yes_Type;
    typedef struct { char dummy[2]; }	            No_Type;

    template<typename T>    struct Type2Type        { typedef T type;       };

    template<bool x> struct BoolType                { enum  { value=(x) };  };
    struct  TrueType      : public BoolType<true>   { };
    struct  FalseType     : public BoolType<false>  { };

    //Int2Type::value is compile-period constant expression, it can apply for compile period calculation, e.g Static_Assert
    //and the T can only integer or enum type
    template<int TVal>       struct Int2Type        { enum { value=TVal  };  };

    //Value2Type::value is not compile-period constant expression, it can't apply for compile period calculation, e.g Static_Assert
    //but it works well in runtime period, and it can hold non-integer type, e.g. function pointer, member pointer etc.
    template<typename T,T TVal>  struct  Value2Type   : public Type2Type<T>   { static const T value; };
    template<typename T,T TVal>  T const Value2Type<T,TVal>::value=TVal;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<bool,typename True_T,typename False_T>         struct If_T                         : public Type2Type<True_T>     {} ;
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
