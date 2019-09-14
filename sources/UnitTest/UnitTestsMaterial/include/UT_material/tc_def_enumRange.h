#ifndef TC_DEF_ENUMRANGE_H__
#define TC_DEF_ENUMRANGE_H__

/***********************************************************************************************************************
Description         : 
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
***********************************************************************************************************************/
#include <UT_material/tc_def_enum.h>
#include <MiniMPL/enumTrait.hpp>

namespace UnitTest
{
    typedef MiniMPL::CEnumRange<ETypeInt,ETypeInt(0),ETypeInt(9)>   EInt_0_9;
    typedef MiniMPL::CEnumRange<ETypeInt,ETypeInt(3),ETypeInt(5)>   EInt_3_5;

    typedef MiniMPL::CEnumRange<SeqEunm,S_Val_Min,S_Val_Max>        SeqEnumRange;
    SKIP_ENUM_ONE(SeqEnumRange,S_Val_4);                            //skip 4

    //test SKIP_ENUM_ONE
    typedef MiniMPL::CEnumRange<SeqEunm,S_Val_1,S_Val_6>            SeqEnumSkipOneRange;
    // SKIP_ENUM_ONE(SeqEnumSkipOneRange,S_Val_1);                  //fail because S_Val_1 is head of SeqEnumSkipOneRange
    // SKIP_ENUM_ONE(SeqEnumSkipOneRange,S_Val_6);                  //fail because S_Val_6 is tail of SeqEnumSkipOneRange
    SKIP_ENUM_ONE(SeqEnumSkipOneRange,S_Val_3);                     //OK,   S_Val_3 is not head or tail

    typedef MiniMPL::CEnumRange<NonSeqEunm,NS_Val_Min,NS_Val_Max>   NonSeqEnumRange;
    //skip NS_Val_3 when traverse enum type "DemoEunm" : jump from NS_Val_2 to NS_Val_4
    SKIP_ENUM_MIDDLE(NonSeqEnumRange,NS_Val_1,NS_Val_3);                      //skip 2
    SKIP_ENUM_MIDDLE(NonSeqEnumRange,NS_Val_3,NS_Val_5);                      //skip 4
    SKIP_ENUM_MIDDLE(NonSeqEnumRange,NS_Val_5,NS_Val_8);                      //skip 6 ,7

    //SKIP_ENUM_NEXT(EnumRange,NS_Val_3,NS_Val_1);                    //Fail because  NS_Val_3 > NS_Val_1
    //SKIP_ENUM_NEXT(EnumRange,NS_Val_3,DemoEunm(NS_Val_Max+1));      //Fail because  DemoEunm(NS_Val_Max+1) is not in range
}

#endif // TC_DEF_ENUMRANGE_H__
