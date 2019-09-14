#ifndef __ARRAYTRAIT_HPP__
#define __ARRAYTRAIT_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/kitType.hpp>

#ifndef arraySize
    template<typename T , unsigned int LEN>  
    char (&ArraySizeHelper(T(&)[LEN])) [LEN];  //return array reference
    #define arraySize(x)    sizeof(ArraySizeHelper(x))
#endif

namespace MiniMPL
{
    template<typename T>					struct ArrayTester              : FalseType {};  //array pointer is not array
    template<typename T,unsigned int LEN>	struct ArrayTester<T[LEN]>      : TrueType  {};
    template<typename T,unsigned int LEN>	struct ArrayTester<T(&)[LEN]>   : TrueType  {};

    template<typename T>                    struct ArrayValueType;
    template<typename S,unsigned int LEN>   struct ArrayValueType<S[LEN]>    : public Type2Type<S> {};
    template<typename S,unsigned int LEN>   struct ArrayValueType<S(&)[LEN]> : public Type2Type<S> {};

    template<typename T> struct ArraySize;
    template<typename S,unsigned int LEN>   struct ArraySize<S[LEN]>    : public Int2Type<LEN> {};
    template<typename S,unsigned int LEN>   struct ArraySize<S(&)[LEN]> : public Int2Type<LEN> {};
}


#endif // __ARRAYTRAIT_HPP__
