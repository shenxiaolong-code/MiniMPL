#ifndef __MATCHTYPELOCATER_HPP__
#define __MATCHTYPELOCATER_HPP__
/***********************************************************************************************************************
* Description         : if one big type list include several type and several small type list ,and need one procedure to process it.
*                       for different type/type list, there different process rule.
*                       below interface can help to locate process rule.
*                       see source tail comments to detail usage example.
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/typeListMacro.hpp>
#include <MiniMPL/typeLogic.hpp>
#include <MiniMPL/isXXXEx.hpp>

namespace MiniMPL
{
    template<template<class,class> class THandler,typename TP,typename TList>
    struct TMatchTypeLocater : MiniMPL::Type2Type<THandler<TP,TList> > {};
    template<template<class,class> class THandler,typename TP>
    struct TMatchTypeLocater<THandler,TP,TP> : MiniMPL::Type2Type<THandler<TP,MiniMPL::NullType> > {};

    template<template<class,class>class THandler,typename TP,typename THead,typename TTail>
    struct TMatchTypeLocater<THandler,TP,MiniMPL::Typelist<THead,TTail> > 
        : MiniMPL::If_Evl<MiniMPL::IsSameType<TP,THead>
        , THandler<TP,MiniMPL::NullType>
        , typename MiniMPL::If_Evl<MiniMPL::TL::TypeInList<THead,TP>
            , THandler<TP,THead>
            , typename TMatchTypeLocater<THandler,TP,TTail>::type
        >::type > {};
}

/*
struct T0; struct T1;class T2;struct T3;struct T4;      //fw declare
struct T5;struct T6;class  T7;class  T8;                //fw declare

//user defined type list
typedef MAKE_TYPELIST_3(T1,T2,T3)                           RuleList_3;
typedef MAKE_TYPELIST_2(T4,T5)                              RuleList_2;
typedef MAKE_TYPELIST_5(RuleList_3,T6,RuleList_2,T7,T8)     RuleList_all;

//user defined process rule
template<typename T,typename TRuleList=NullType>    struct TProcess {}; //suitable for left type, here is T8
template<typename T>        struct TProcess<T,RuleList_3> {};           //T in RuleList_3
template<typename T>        struct TProcess<T,RuleList_2> {};           //T in RuleList_2
template<>                  struct TProcess<T6,MiniMPL::NullType>   {}; //suitable for T6
template<>                  struct TProcess<T7,MiniMPL::NullType>   {}; //suitable for T7

//usage example: (Note : add typename after typedef if below is used in template class/function )
typedef TMatchTypeLocater<TProcess,T3,RuleList_all>::type  THandler1;  //THandler1 is TProcess<T3,RuleList_3>
typedef TMatchTypeLocater<TProcess,T5,RuleList_all>::type  THandler2;  //THandler2 is TProcess<T5,RuleList_2>
typedef TMatchTypeLocater<TProcess,T6,RuleList_all>::type  THandler3;  //THandler3 is TProcess<T6,NullType>
typedef TMatchTypeLocater<TProcess,T7,RuleList_all>::type  THandler4;  //THandler4 is TProcess<T7,NullType>
typedef TMatchTypeLocater<TProcess,T8,RuleList_all>::type  THandler5;  //THandler5 is TProcess<T8,NullType>
typedef TMatchTypeLocater<TProcess,T0,RuleList_all>::type  THandler6;  //THandler6 is TProcess<T0,NullType>

*/

#endif // __MATCHTYPELOCATER_HPP__
