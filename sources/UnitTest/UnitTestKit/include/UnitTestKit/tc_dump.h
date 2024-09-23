#ifndef TC_DUMP_H__
#define TC_DUMP_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/
#include <MiniMPL\productSpecialDef.h>
#include <iostream>
#include <MiniMPL\macroDef.h>

extern std::wostream&   tcOutW;
extern std::ostream&    tcOutA;

#if 1==USE_UNICODE_STRING
extern std::wostream&   tcOut;
#else
extern std::ostream&    tcOut;
#endif

namespace UnitTest
{
    // template<auto v>                     struct debug_number ;               // auto need C++ 17 . g++ -std=c++17 ...
    template<__int64 v>                     struct debug_number ;
    #define show_number( v )                { using vHelper = typename debug_number< v >::type ; }
    #define static_assert_number( b , v )   if constexpr (!( b )) {  using vHelper = typename debug_number< v >::type ; }

    template<typename T>                    struct debug_type;
    #define show_type(   v )                { using tHelper = typename debug_type< v >::type ;   }
    #define static_assert_type(   b , v )   if constexpr (!( b )) {  using tHelper = typename debug_type< v >::type   ; } 

    stlString getTypeName(const char* pStr);
    template<typename T> inline stlString getTypeName()
    {
        return getTypeName(typeid(T).name());
    }

    template<typename T> inline stlString getTypeName(T&)
    {
        return getTypeName(typeid(T).name());
    }

    template<typename T> inline void showType(T& f)
    {
        outputTxtV(TXT("\nshowType:%s\traw Name :%s\n"),getTypeName<T>().c_str(),getTypeName(typeid(T).raw_name()).c_str());
    }

    template<typename T> inline void showType()
    {
        outputTxtV(TXT("\nshowType:%s\traw Name :%s\n"),getTypeName<T>().c_str(),getTypeName(typeid(T).raw_name()).c_str());
    }
}

#endif // TC_DUMP_H__
