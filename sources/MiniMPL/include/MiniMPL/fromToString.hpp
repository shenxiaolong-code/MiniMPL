#ifndef __STLSTRINGCONVERT_HPP__
#define __STLSTRINGCONVERT_HPP__
/***********************************************************************************************************************
* Description         : with unified interface,convert any buildin type variable to stlString / convert string into any buildin type variable
                        for customized type, pls override toStringA/toStringW and fromString in namespace MiniMPL
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/innerDetail/fromToString_detail.hpp>

#if 1==USE_UNICODE_STRING
    #define     toString            toStringW
#else
    #define     toString            toStringA
#endif // 1==USE_UNICODE_STRING

#define PRINTPARAM(S) MiniMPL::toString(S).c_str()
namespace MiniMPL
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T> inline stlStringA toStringA(T const& val)
    {
        return InnerDetail::CToString<T,stlStringA>::execute(val);
    }

    template<typename T> inline stlStringW toStringW(T const&  val)
    {
        return InnerDetail::CToString<T,stlStringW>::execute(val);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename TString,typename T>
    inline bool fromString(TString const& from,T& to)
    {
        return InnerDetail::CFromString<TString,T>::execute(from,to);
    }
}


#endif // __STLSTRINGCONVERT_HPP__
