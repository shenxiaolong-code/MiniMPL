#ifndef __BINARYFUNCTION_HPP__
#define __BINARYFUNCTION_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/innerDetail/binaryFunction_detail.hpp>
#include <MiniMPL/functionParams.hpp>

namespace MiniMPL
{
    template<typename P1,typename P2, typename R>
    struct BinaryFunctionBase
    {
        typedef     P1              TP1;
        typedef     P2              TP2;
        typedef     R               Return_T;
    };

    template<typename F>
    struct BinaryFunction<F,false>  : public BinaryFunctionBase<FPP(F,1),FPP(F,2),FR(F)>
    { 
        explicit BinaryFunction(F f)
            : m_f(f)
        {
            Static_Assert(2==ParamPackageSize<typename FunctionParams<F>::Params_T>::value);
        }

        Return_T operator()(TP1 p1,TP2 p2)
        {   
            return  m_f(p1,p2);
        }

        F   m_f;
    };

    template<typename F>
    struct BinaryFunction<F,true>  : public BinaryFunctionBase<FPP(F,1),FPP(F,2),FR(F)>
    { 
        typedef TPP(FO(F))  Object_T;

        explicit BinaryFunction(Object_T obj,F f)
            : m_obj(obj)
            , m_f(f)
        {
            Static_Assert(2==ParamPackageSize<typename FunctionParams<F>::Params_T>::value);
        }

        Return_T operator()(TP1 p1,TP2 p2)
        {   
            return  (m_obj.*m_f)(p1,p2);
        }

        Object_T    m_obj;
        F           m_f;
    };
                        
    template<typename F,unsigned Idx> struct GetBinaryFunctionParam;
    template<typename F> struct GetBinaryFunctionParam<F,1> : public Type2Type<typename InnerDetail::GetBinaryFunctionImpl<F>::type::TP1> {};
    template<typename F> struct GetBinaryFunctionParam<F,2> : public Type2Type<typename InnerDetail::GetBinaryFunctionImpl<F>::type::TP2> {};

    /////////////////////////////////////////////// binary function creator /////////////////////////////////////////////
    template<typename F> inline BinaryFunction<F> makeBinaryFunction( F f )
    {
        return BinaryFunction<F>(f);
    }
    template<typename F,typename TObj> inline BinaryFunction<F> makeBinaryFunction(TObj& obj, F f )
    {
        return BinaryFunction<F>(obj,f);
    }
}


#endif // __BINARYFUNCTION_HPP__
