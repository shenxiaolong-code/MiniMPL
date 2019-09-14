#ifndef __FUNCTIONPARAMS_HPP__
#define __FUNCTIONPARAMS_HPP__
/***********************************************************************************************************************
Description			: functor is complex, sometime it is needed to detect functor properties .
                      Limit : it is only suitable to the kind of function which has fixed parameter number. 
                      it is say : for style : R (*)(...) , it is not usable. 
                      Support functions style:
                      R (*)(P1);
                      R (*)(P1,P2);
                      R (*)(P1,P2,P3);
                      R (*)(P1,P2,P3,P4);
                      R (*)(P1,P2,P3,P4,P5);
                      R (O::*)(P1);
                      R (O::*)(P1,P2);
                      R (O::*)(P1,P2,P3);
                      R (O::*)(P1,P2,P3,P4);
                      R (O::*)(P1,P2,P3,P4,P5);
                      note : macro FPP is usable to improve deliver parameter performance, it obey below rules:
                      if function parameter (Px) is reference type,  the  FPP(F,x) is reference type also. (because it might be in/out parameter)
                      if function parameter (Px) isn't reference type,  the  FPP(F,x) is :
                      1. non-reference type when Px is Atom type.(e.g. build-in type or enum type)
                      1. reference type when Px isn't Atom type. (e.g. struct/class type)

* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/functionParams_detail.hpp>
#include <MiniMPL/sameQualifier.hpp>

#define FO(F)       typename MiniMPL::GetFunctionClass<F>::type
#define FOR(F)      typename MiniMPL::AddRef<FO(F)>::type
#define FR(F)       typename MiniMPL::GetFunctionReturn<F>::type
#define FP(F,I)     typename MiniMPL::GetFunctionParam<F,I>::type
#define FPP(F,I)    TPP(FP(F,I))        // Function Parameter package

namespace MiniMPL
{
    template<typename F> struct FunctionParams      : public InnerDetail::FunctionParamsImpl<F>{};
    template<typename F> struct GetFunctionReturn   : public Type2Type<typename FunctionParams<F>::Return_T>{};
    template<typename F> struct GetFunctionClass    : public Type2Type<typename FunctionParams<F>::Object_T>{};
    
    template<class F,int idx>  struct GetFunctionParam  : public ParamPackageAt<typename FunctionParams<F>::Params_T,idx> {};
    template<class F>  struct GetFunctionParam<F,0>     : public Type2Type<typename FunctionParams<F>::Object_T> {};

    template<typename F>
    struct GetFunctionParamNum : public MiniMPL::ParamPackageSize<typename FunctionParams<F>::Params_T> {};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename F>
    struct IsConstMemberFunctionPointer : IsConst<typename GetFunctionClass<F>::type>{};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename F> struct GetFunction                         : Type2Type<F> {};
    template<typename F> struct GetFunction<FunctionParams<F> >     : Type2Type<F> {};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename TF> struct TAddTClassToPack : public InnerDetail::TAddTClassToPackImpl<typename FunctionParams<TF>::Params_T,TF>{}; //compatible whit MF and non-MF
    template<typename TF> struct TAddTFToPack     : public TInsert<typename TAddTClassToPack<TF>::type>::template apply<TF,1> {};
    template<typename TF> struct TGetFuncAllTypes : TAddTFToPack<TF>{};
}

#endif // __FUNCTIONPARAMS_HPP__
