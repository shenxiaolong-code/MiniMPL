#ifndef __STRINGTRAIT_HPP__
#define __STRINGTRAIT_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/innerDetail/stringtrait_detail.hpp>

namespace MiniMPL
{
    template<typename T>
    struct getCharType : public MiniMPL::InnerDetail::getCharTypeImpl<T> {};

    template<typename char_T> struct getDiffCharType;
    template<> struct getDiffCharType<char>     : public Type2Type<wchar_t> {};
    template<> struct getDiffCharType<wchar_t>  : public Type2Type<char> {};

    template<typename char_T> struct TStlStringStream;
    template<>  struct TStlStringStream<char>      : public Type2Type<std::stringstream>   {};
    template<>  struct TStlStringStream<wchar_t>   : public Type2Type<std::wstringstream>  {};
}


#endif // __STRINGTRAIT_HPP__
