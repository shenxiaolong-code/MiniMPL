#ifndef BINARYFUNCTION_DETAIL_H__
#define BINARYFUNCTION_DETAIL_H__

/***********************************************************************************************************************
Description         : detail implement of <MiniMPL/binaryFunction.hpp>
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/isXXXEx.hpp>

namespace MiniMPL
{   
    template<typename F, bool bMFPtr=IsMemberFunctionPointer<F>::value> struct BinaryFunction;

    namespace InnerDetail
    {
        template<typename F,bool bBinaryFunc=IsFunction<F>::value>    struct GetBinaryFunctionImpl;
        template<typename F>    struct GetBinaryFunctionImpl<F,true> : public Type2Type<BinaryFunction<F> > {};
        template<typename F>    struct GetBinaryFunctionImpl<BinaryFunction<F>,false> : public GetBinaryFunctionImpl<F> {};
    }
}

#endif // BINARYFUNCTION_DETAIL_H__
