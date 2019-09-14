#ifndef __UNARYFUNCTION_HPP__
#define __UNARYFUNCTION_HPP__
/***********************************************************************************************************************
* Description         : UnaryFunction definition.
*                       purpose : pack multiple parameter function into unary function.
*                       unary function as one of 3 important function (NoParam/unary/binary), it is used in general design.
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Mail                : xlshen2002@hotmail.com,  xlshen@126.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/unaryFunction_detail.hpp>
#include <MiniMPL/unaryFunctionParamTransfer.hpp>

namespace MiniMPL
{
    template<typename P, typename R>
    struct UnaryFunctionBase
    {
        typedef     P           Param_T;
        typedef     R           Return_T;
    };

    template<typename F,int Idx,typename TUnaryFunctionParams> 
    struct UnaryFunctionDirect : public UnaryFunctionBase<FPP(F,Idx),FR(F)> 
    {
        typedef TUnaryFunctionParams                    UnaryFunctionParams_T;

        UnaryFunctionParams_T   m_Ps;
        F                       m_f;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////
        UnaryFunctionDirect(F f,UnaryFunctionParams_T& params)
            : m_f(f)
            , m_Ps(params)
        { }

        Return_T operator()(Param_T obj)
        {   
            return  UnaryFunctionOperator<F>::ufCall(*this,obj);
        }

        AutoConvertUnaryFunctionParam(operator(),Param_T,Return_T);
    };

    template<typename F,int Idx> 
    struct UnaryFunction: public UnaryFunctionDirect<F,Idx,typename UnaryFuncParams<F,Idx>::type> 
    {
        UnaryFunction(F f,UnaryFunctionParams_T& params) :UnaryFunctionDirect(f,params){}; 
    };

    template<typename F> struct GetUnaryFunctionParam: public GetUFParamImpl<F> {};

    template<typename F,int Idx,typename TUnaryFunctionParams>
    struct GetFunctionReturn<UnaryFunctionDirect<F,Idx,TUnaryFunctionParams> >    : public GetFunctionReturn<F>{};
    template<typename F,int Idx> struct GetFunctionReturn<UnaryFunction<F,Idx> >: public GetFunctionReturn<F>{};
}


#endif // __UNARYFUNCTION_HPP__
