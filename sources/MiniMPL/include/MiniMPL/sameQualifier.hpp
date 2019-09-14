#ifndef __SAMEQUALIFIER_HPP__
#define __SAMEQUALIFIER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/isXXX.hpp>
#include <MiniMPL/isXXXEx.hpp>
#include <MiniMPL/addRemove.hpp>
#include <MiniMPL/typeLogic.hpp>

#define SA(X,Y)     typename MiniMPL::SameAllQualifier<X,Y>::type       //Set X by Y  (Same All Qualifier)
#define SC(X,Y)     typename MiniMPL::SameConst<X,Y>::type              //Set X by Y  (Same Const)
#define SCV(X,Y)    typename MiniMPL::SameVolatile<SC(X,Y),Y>::type     //Set X by Y  (Same Const and volatile)
#define TPP(T)      typename MiniMPL::RefAdapter<T>::type               //Type Parameter package

namespace MiniMPL
{   
    template<template<class> class isXXX>             struct GetAddQualifier;
    template<> struct GetAddQualifier<IsRef>        : public DelayApply<AddRef>{};
    template<> struct GetAddQualifier<IsCPointer>   : public DelayApply<AddCPointer>{};
    template<> struct GetAddQualifier<IsConst>      : public DelayApply<AddConst>{};
    template<> struct GetAddQualifier<IsVolatile>   : public DelayApply<AddVolatile>{};

    template<template<class> class isXXX>             struct GetRemoveQualifier;
    template<> struct GetRemoveQualifier<IsRef>     : public DelayApply<RemoveRef>{};
    template<> struct GetRemoveQualifier<IsCPointer>: public DelayApply<RemoveCPointer>{};
    template<> struct GetRemoveQualifier<IsConst>   : public DelayApply<RemoveConst>{};
    template<> struct GetRemoveQualifier<IsVolatile>: public DelayApply<RemoveVolatile>{};
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //isXXX is IsRef/IsCPointer/IsVolatile/IsConst
    template<class Bool_T,typename Target_T,template<class> class isXXX>
    struct SelectQualifier : public If_Evl<Bool_T,GetAddQualifier<isXXX>,GetRemoveQualifier<isXXX> >::type::template apply<Target_T>{};  

    //isXXX is IsRef/IsCPointer/IsVolatile/IsConst
    template<template<class> class isXXX,typename Target_T,typename Ref_T>
    struct SameQualifier : public SelectQualifier<isXXX<Ref_T>,Target_T,isXXX>{};

    //Meta function transform, instead of typedef
    template<typename TargetType,typename RefType>
    struct SameConst : public SameQualifier<IsConst,TargetType,RefType>{ };

    template<typename TargetType,typename RefType>
    struct SameRef : public SameQualifier<IsRef,TargetType,RefType>{ };

    template<typename TargetType,typename RefType>
    struct SamePointer : public SameQualifier<IsCPointer,TargetType,RefType>{ };

    template<typename TargetType,typename RefType>
    struct SameVolatile : public SameQualifier<IsVolatile,TargetType,RefType>{ };

    template<typename TargetType,typename RefType>
    struct SameAllQualifier
    { //pointer is not qualifier , Qualifier has only 3 kind : volatile , const , reference   
    private:
        typedef typename GetRawType<TargetType>::type               Raw_T;              //raw type
        typedef typename SameVolatile<Raw_T,RefType>::type          SameVolatile_T;     //check volatile
        typedef typename SameConst<SameVolatile_T,RefType>::type    SameConst_T;        //check const
        //typedef typename SamePointer<SameConst_T,RefType>::type     SamePointer_T;    //check pointer
        typedef typename SameRef<SameConst_T,RefType>::type         SameRef_T;          //check ref

    public:
        typedef SameRef_T type;
    };

    //if T is class/struct/array,add reference modifier, else keep original type(No change).
    //pointer includes class pointer, smart pointer, iterator
    template<typename T>
    struct RefAdapter : public If_Evl<Or_T<IsRef<T>,IsPointer<T>,IsAtomType<T> >,Type2Type<T>, AddRef<T> >::type {};
}


#endif // __SAMEQUALIFIER_HPP__
