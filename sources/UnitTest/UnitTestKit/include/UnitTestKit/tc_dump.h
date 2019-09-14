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
