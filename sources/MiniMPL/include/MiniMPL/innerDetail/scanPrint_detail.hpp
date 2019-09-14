#ifndef SCANPRINT_DETAIL_H__
#define SCANPRINT_DETAIL_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	implement of get format string index
*************************************************************************************/
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/isXXXEx.hpp>

namespace MiniMPL 
{
    namespace InnerDetail
    {
        template<typename T,bool bEnum=IsEnumType<T>::value>   struct CEnumPrintFmt;   //no non-enum definition
        template<typename T>    struct CEnumPrintFmt<T,true> :  public MiniMPL::Int2Type<1>{};   //enum like int

        template<typename T>    struct CFormatIdxImpl : public CEnumPrintFmt<T>{};
        template<>  struct CFormatIdxImpl<bool>              : public Int2Type<1>{};
        template<>  struct CFormatIdxImpl<char>              : public Int2Type<0>{};        
        template<>  struct CFormatIdxImpl<unsigned char>     : public Int2Type<0>{};
        template<>  struct CFormatIdxImpl<signed char>       : public Int2Type<0>{};
        template<>  struct CFormatIdxImpl<wchar_t>           : public Int2Type<0>{};
        template<>  struct CFormatIdxImpl<short>             : public Int2Type<1>{};
        template<>  struct CFormatIdxImpl<unsigned short>    : public Int2Type<2>{};
        template<>  struct CFormatIdxImpl<int>               : public Int2Type<1>{};
        template<>  struct CFormatIdxImpl<unsigned int>      : public Int2Type<2>{};
        template<>  struct CFormatIdxImpl<long>              : public Int2Type<1>{};
        template<>  struct CFormatIdxImpl<unsigned long>     : public Int2Type<2>{};
        template<>  struct CFormatIdxImpl<float>             : public Int2Type<3>{};
        template<>  struct CFormatIdxImpl<double>            : public Int2Type<4>{};
        template<>  struct CFormatIdxImpl<long double>       : public Int2Type<4>{};
        template<>  struct CFormatIdxImpl<__int64>           : public Int2Type<6>{};
        template<>  struct CFormatIdxImpl<unsigned __int64>  : public Int2Type<7>{};
        //for string, doesn't recommend to use scanf/printf to implement toString/fromString, recommend Str2Str
        template<>  struct CFormatIdxImpl<char*>             : public Int2Type<5>{};
        template<unsigned iLen>  struct CFormatIdxImpl<char[iLen]>   : public Int2Type<5>       {};
        template<unsigned iLen>  struct CFormatIdxImpl<char(&)[iLen]>: public Int2Type<5>       {};
        template<>  struct CFormatIdxImpl<wchar_t*>          : public Int2Type<5>{};
        template<unsigned iLen>  struct CFormatIdxImpl<wchar_t[iLen]>   : public Int2Type<5>    {};
        template<unsigned iLen>  struct CFormatIdxImpl<wchar_t(&)[iLen]>: public Int2Type<5>    {};
    }
}

#endif // SCANPRINT_DETAIL_H__
