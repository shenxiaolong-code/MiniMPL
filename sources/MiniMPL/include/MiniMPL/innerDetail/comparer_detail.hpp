#ifndef COMPARER_DETAIL_H__
#define COMPARER_DETAIL_H__

/***********************************************************************************************************************
Description         : detail implement of <MiniMPL/comparer.hpp>
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/unaryFunction.hpp>
#include <MiniMPL/memberPtr.hpp>
#include <MiniMPL/binaryFunction.hpp>
#include <MiniMPL/functionParams.hpp>

namespace MiniMPL
{
    //get comparer function return type
    namespace InnerDetail
    {
        template<typename TF,bool bFunc=IsFunction<TF>::value>  struct TGetComparerReturn;
        template<typename TF>   struct TGetComparerReturn<TF,true>      : public GetFunctionReturn<TF>  {};
        template<typename TObj> struct TGetComparerReturn<TObj,false>   : public Type2Type<bool>        {};
    }
}

#endif // COMPARER_DETAIL_H__
