#ifndef STRINGTRAIT_DETAIL_H__
#define STRINGTRAIT_DETAIL_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	detail implement for fromToString.hpp
				implement of stringtrait.hpp , consist of 3 parts:
				1. non-string variable          => string (T*,T[],stl string)
				2. string (T*,T[],stl string)   => non-string variable
				3. string <=> string
    refer to:   scanf function from MSDN
*************************************************************************************/
#include <MiniMPL/isXXXEx.hpp>

namespace MiniMPL
{
    namespace InnerDetail
    {
        template<typename RawT> struct RawCharTypeImpl;
        template<> struct RawCharTypeImpl<char*>     : public Type2Type<char>        {};
        template<> struct RawCharTypeImpl<wchar_t*>  : public Type2Type<wchar_t>     {};
        template<typename C> struct RawCharTypeImpl<stlStringPack<C >>          : public Type2Type<C> {};
        template<typename C,unsigned iLEN> struct RawCharTypeImpl<C[iLEN]>      : public Type2Type<C> {};
        template<typename C,unsigned iLEN> struct RawCharTypeImpl<C(&)[iLEN]>   : public Type2Type<C> {};
        template<typename C,unsigned iLEN> struct RawCharTypeImpl<C(*)[iLEN]>   : public Type2Type<C> {};

        template<typename T,bool bIsString=IsString<T>::value>
        struct getCharTypeImpl;

        template<typename T>
        struct getCharTypeImpl<T,true> : public RawCharTypeImpl<RAWTYPE(T)> {};
    }
}

#endif // STRINGTRAIT_DETAIL_H__
