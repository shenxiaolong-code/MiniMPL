#ifndef __TRAVERSECALLBACKMACRO_HPP__
#define __TRAVERSECALLBACKMACRO_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/enumTrait.hpp>
#include <MiniMPL/paramPackageCall.hpp>
#include <MiniMPL/kitType.hpp>

//for C++ syntax, template-function/template-member-function can't be callback function,here use one package to make it possible.
//TDeclare_Template_CallBack_T is used callback form  : template<typename T> R func(...)
#define Declare_Template_CallBack_T(FID,exeFunc,F)                                          \
struct Callback_##FID : public MiniMPL::Type2Type<F>                                        \
{                                                                                           \
    template<typename T>                                                                    \
    struct apply: public MiniMPL::Value2Type<type, & exeFunc < T > >{};                     \
}

//TDeclare_Template_CallBack_V is used callback form : template<T Val> R func(...)
#define Declare_Template_CallBack_V(FID,exeFunc,F)                                          \
struct Callback_##FID : public MiniMPL::Type2Type<F>                                        \
{                                                                                           \
    template<typename T> struct apply;                                                      \
    template<typename E,E E_min,E E_max,E TVal>                                             \
    struct apply<MiniMPL::CEnumValue<MiniMPL::CEnumRange<E,E_min,E_max>,TVal> >             \
    : public MiniMPL::Value2Type<type, & exeFunc < TVal > >{};                              \
}
//TODO performance priority strategy : Declare_Template_CallBack_T and Declare_Template_CallBack_V

#define Declare_Template_CallBack(FID,exeFunc,F)                                                \
struct Callback_##FID : public MiniMPL::Type2Type<F>                                            \
{   /* used as Callback_T in execute/executeFrom */                                             \
    template<typename E,E E_min,E E_max,E TVal>                                                 \
    static type getInterface(MiniMPL::CEnumValue<MiniMPL::CEnumRange<E,E_min,E_max>,TVal>*)     \
    {                                                                                           \
        type pf =  & exeFunc < TVal > ; /*recognize override function */                        \
        return  pf;                                                                             \
    }                                                                                           \
    template<typename T>                                                                        \
    static type getInterface(T*)                                                                \
    {                                                                                           \
        type pf =  & exeFunc < T > ; /*recognize override function */                           \
        return  pf;                                                                             \
    }                                                                                           \
}
#define CallBackT(FID)          Callback_##FID
#define CallBackTParam(FID)     MiniMPL::TToParamPackageCall<typename CallBackT(FID)::type>::type
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define Declare_Template_Tester(FID,exeFunc,F)                                                  \
struct Tester_##FID : public MiniMPL::Type2Type<F>                                              \
{   /* used as Tester in applyTester of getFuncAddr */                                          \
    template<typename T,typename TesterParam_T>                                                 \
    static bool test(TesterParam_T& p)                                                          \
    {                                                                                           \
        return ::MiniMPL::doPackCall(& exeFunc < T >,p);                                        \
    }                                                                                           \
}
#define TesterT(FID)        Tester_##FID
#define TesterTParam(FID)   MiniMPL::TToParamPackageCall<typename TesterT(FID)::type>::type
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define Declare_Template_FuncID(FID,exeFunc)                                                    \
struct FuncID_##FID                                                                             \
{   /* used as FuncIdGenerator in applyFuncIdGenerator of getAllFuncAddr */                     \
    template<typename TR,typename T>                                                            \
    static TR getId()                                                                           \
    {                                                                                           \
        return exeFunc < T >();                                                                 \
    }                                                                                           \
}

#define FuncIDT(FID)  FuncID_##FID

#endif // __TRAVERSECALLBACKMACRO_HPP__
