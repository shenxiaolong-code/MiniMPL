#ifndef TC_DEF_ENUM_H__
#define TC_DEF_ENUM_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	define enum for test
*************************************************************************************/

namespace UnitTest
{
    enum    ETypeInt{};
    enum    EInt{};
    enum    EnumType{VAL_1};

    //sequential enum value, it can execute SKIP_ENUM_NEXT except you want to skip some enum value(s)
    enum SeqEunm {S_Val_Min,S_Val_1,S_Val_2,S_Val_3,S_Val_4,S_Val_5,S_Val_6,S_Val_7,S_Val_Max};

    //non-sequential enum type : value 2,4 is lack
    enum NonSeqEunm
    {   
        NS_Val_Min = 0 ,
        NS_Val_1   = 1,
        NS_Val_3   = 3,
        NS_Val_5   = 5,
        NS_Val_8   = 8,
        NS_Val_Max
    };
}

#endif // TC_DEF_ENUM_H__