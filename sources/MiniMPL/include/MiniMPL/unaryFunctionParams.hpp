#ifndef __UNARYFUNCPARAMS_HPP__
#define __UNARYFUNCPARAMS_HPP__
/***********************************************************************************************************************
* Description         : implement unary function parameter package definition
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/functionParams.hpp>
#include <MiniMPL/paramPackShift.hpp>

namespace MiniMPL
{
    template<typename F,unsigned Idx>
    struct TFunctionParamsErase : TErase<typename InnerDetail::FunctionParamsImpl<F>::Params_T>::template apply<Idx>{};

    template<typename F,int Idx> struct UnaryFuncParams : public InnerDetail::TAddTClassToPackImpl<typename TFunctionParamsErase<F,Idx>::type,F> {};
    template<typename F> struct UnaryFuncParams<F,0> : public Type2Type<typename InnerDetail::FunctionParamsImpl<F>::Params_T> {};
}


#endif // __UNARYFUNCPARAMS_HPP__
