#ifndef TC_DEF_TYPELIST_H__
#define TC_DEF_TYPELIST_H__

/***********************************************************************************************************************
Description         : 
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com

***********************************************************************************************************************/
#include <MiniMPL/typeListMacro.hpp>
#include <UT_material/tc_def_enum.h>
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{
    typedef MAKE_TYPELIST_6(int,char,S4,S2,char*,void*)                         TList6;
    typedef MAKE_TYPELIST_4(int,char,char*,long)                                TypeList4;
    typedef MAKE_TYPELIST_5(int,char*,S4,S3,S1)                                 Typelist5;
    typedef MAKE_TYPELIST_6(int,char*,MAKE_TYPELIST_2(float,S2),S4,S3,S1)       Typelist71;
    typedef MAKE_TYPELIST_6(MAKE_TYPELIST_2(float,S2),int,char*,S4,S3,S1)       Typelist72;
    typedef MAKE_TYPELIST_6(int,char*,S4,S3,S1,MAKE_TYPELIST_2(float,S2))       Typelist73;

    typedef MAKE_TYPELIST_6(int,char*,ETypeInt,EInt,EnumType,MAKE_TYPELIST_2(float,S2))     Typelist74;
    typedef MAKE_TYPELIST_6(int,char*,S4,EnumType,S1,MAKE_TYPELIST_2(float,S2))             Typelist75;

}

#endif // TC_DEF_TYPELIST_H__
