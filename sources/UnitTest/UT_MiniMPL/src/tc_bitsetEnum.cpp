#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\bitsetEnum.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_BITSETENUM to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_BITSETENUM

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_BITSETENUM
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_BITSETENUM
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_BITSETENUM
#endif

//#undef RUN_EXAMPLE_BITSETENUM
//#undef COMPILE_EXAMPLE_BITSETENUM

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_BITSETENUM
#include <MiniMPL/bitsetEnum.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <ut_material/tc_def_enumRange.h>

enum EFontStyle { FONT_NORMAL, FONT_BOLD, FONT_ITALIC };            //need 2 bit to hold (max val is 2)
enum EFontName  { FONT_1, FONT_2, FONT_3, FONT_4, FONT_5};          //need 3 bit to hold (max val is 4)
enum ETextAlignment{ TEXT_LEFT=1, TEXT_RIGHT=2, TEXT_CENTER=3 };    //need 2 bit to hold (max val is 3)
enum ETextFlow  { TEXT_FIX, TEXT_FLOW };                            //need 1 bit to hold (max val is 1)
enum EBorderLine{ NOLINES=0, LINE_TOP=1, LINE_BOTTOM=2, LINE_LEFT=4, LINE_RIGHT=8 }; //need 4 bit to hold (max val is 8)
enum EFontSize  {};    //need 8 bit to hold (assume max val is 255)

namespace MiniMPL
{
    template<>  struct MaskWidth<EFontStyle>       : public MiniMPL::Int2Type<2>    {};
    template<>  struct MaskWidth<EFontName>        : public MiniMPL::Int2Type<3>    {};
    // template<>  struct MaskWidth<ETextAlignment>   : public MiniMPL::Int2Type<2>    {};
    declare_defalut_enum_attribute(ETextAlignment, ETextAlignment(0),TEXT_CENTER);    // use default bit width based on the max enum value.
    DefTypeSpecBitWidth(ETextFlow  ,   1   );
    DefTypeSpecBitWidth(char       ,   2   );
    DefTypeSpecBitWidth(EBorderLine,   4   );
    DefTypeSpecBitWidth(EFontSize  ,   8   );
    //  template<>  struct MaskWidth<ETextFlow>        : public MiniMPL::Int2Type<1>    {};
    //  template<>  struct MaskWidth<EBorderLine>      : public MiniMPL::Int2Type<4>    {};
    //  template<>  struct MaskWidth<EFontSize>        : public MiniMPL::Int2Type<8>    {};
    DefTypeSpecBitWidth(int  ,   3   );
}

namespace MiniMPL {
    declare_defalut_enum_attribute(UnitTest::wrong_enum_range, UnitTest::wrong_enum_range(13), UnitTest::wrong_enum_range(24));    // compile ok
    // declare_defalut_enum_attribute(UnitTest::wrong_enum_range, UnitTest::wrong_enum_range(24), UnitTest::wrong_enum_range(13));    // compile fail
}

namespace UnitTest
{
    typedef MAKE_TYPELIST_8(EFontStyle,EFontName,char,ETextAlignment,ETextFlow,EBorderLine,EFontSize,int)   TAttriListOK;
    typedef MAKE_TYPELIST_5(EFontStyle,EFontName,ETextFlow,ETextFlow,EFontSize)                             TAttriList_Deplicate;

    inline void TestCase_bitsetEnum_width()
    {           
        PrintTestcase();
        using namespace MiniMPL;
        Static_Assert((log2N<0>::value==1));
        Static_Assert((log2N<1>::value==1));
        Static_Assert((log2N<2>::value==2));
        Static_Assert((log2N<3>::value==2));
        Static_Assert((log2N<4>::value==3));
        Static_Assert((log2N<5>::value==3));
        Static_Assert((log2N<6>::value==3));
        Static_Assert((log2N<7>::value==3));
        Static_Assert((log2N<8>::value==4));
        Static_Assert((log2N<9>::value==4));
        Static_Assert((log2N<10>::value==4));
        Static_Assert((log2N<11>::value==4));
        Static_Assert((log2N<12>::value==4));
        Static_Assert((log2N<13>::value==4));
        Static_Assert((log2N<14>::value==4));
        Static_Assert((log2N<15>::value==4));
        Static_Assert((log2N<16>::value==5));
        Static_Assert((log2N<17>::value==5));
        Static_Assert((log2N<31>::value==5));
        Static_Assert((log2N<32>::value==6));
        Static_Assert((log2N<63>::value==6));
        Static_Assert((log2N<64>::value==7));
        Static_Assert((log2N<127>::value==7));
        Static_Assert((log2N<128>::value==8));
        Static_Assert((log2N<255>::value==8));
        Static_Assert((log2N<256>::value==9));
        Static_Assert((log2N<1024>::value==11));

        //
        Static_Assert((CEnumBitWidth<CEnumRangeDefault<ETypeInt>::type>::value==4));
    }

    inline void TestCase_bitsetEnum_flag()
    {           
        PrintTestcase();
        short flags = 0x81;
        MiniMPL::TBitFlagCombine<TAttriListOK,short>  hlp(flags);
        hlp.setFlag<EFontStyle>(true);
        hlp.setFlag<EFontName>(false);
        hlp.setFlag<char>(true);
        hlp.setFlag<ETextAlignment>(false);
        hlp.setFlag<ETextFlow>(false);
        hlp.setFlag<EBorderLine>(true);
        hlp.setFlag<EFontSize>(true);
        hlp.setFlag<int>(false);

        ASSERT_AND_LOG(true==hlp.getFlag<EFontStyle>());
        ASSERT_AND_LOG(false==hlp.getFlag<EFontName>());
        ASSERT_AND_LOG(true==hlp.getFlag<char>());
        ASSERT_AND_LOG(false==hlp.getFlag<ETextAlignment>());
        ASSERT_AND_LOG(false==hlp.getFlag<ETextFlow>());
        ASSERT_AND_LOG(true==hlp.getFlag<EBorderLine>());
        ASSERT_AND_LOG(true==hlp.getFlag<EFontSize>());
        ASSERT_AND_LOG(false==hlp.getFlag<int>());
    }

    inline void TestCase_bitsetEnum_static()
    {
        PrintTestcase();
        //test short can't hold all bit fields
        typedef MiniMPL::TBitValueCombine<TAttriListOK,short>  AttribCombFail_NoEnoughMem;
        short memByte1=0;        
        //AttribCombFail_NoEnoughMem oFail(memByte1);       //compile error -- Test OK
        //Test type list can't has duplicate type
        typedef MiniMPL::TBitValueCombine<TAttriList_Deplicate,unsigned>  AttribCombFail_DuplicateType;
        unsigned memByte2=0;
        //AttribCombFail_DuplicateType oFail(memByte2);    //compile error --Test OK
    }

    inline void TestCase_bitsetEnum_value()
    {
        PrintTestcase();
        typedef MiniMPL::TBitValueCombine<TAttriListOK,unsigned>  AttribCombOK;
        //EFontStyle, EFontName,ETextAlignment,ETextFlow,EBorderLine,EFontSize
        unsigned myMask = 0;
        AttribCombOK hlp(myMask);
        hlp.setValue(FONT_BOLD);
        hlp.setValue(FONT_3);
        hlp.setValue(TEXT_RIGHT);
        hlp.setValue(char(2));
        AttribCombOK(myMask).setValue(TEXT_FLOW);
        AttribCombOK(myMask).setValue(int(5));
        AttribCombOK(myMask).setValue(LINE_LEFT);
        AttribCombOK(myMask).setValue(EFontSize(5));

        EFontStyle ef=FONT_ITALIC;
        ASSERT_AND_LOG(FONT_BOLD==AttribCombOK(myMask).getValue(ef));

        EFontName en=FONT_4;
        ASSERT_AND_LOG(FONT_3==AttribCombOK(myMask).getValue(en));

        ETextAlignment ea=TEXT_LEFT;
        ASSERT_AND_LOG(TEXT_RIGHT==hlp.getValue(ea));

        ETextFlow et=TEXT_FIX;
        ASSERT_AND_LOG(TEXT_FLOW==hlp.getValue(et));

        EBorderLine eb=LINE_TOP;
        ASSERT_AND_LOG(LINE_LEFT==hlp.getValue(eb));

        EFontSize es=EFontSize(0);
        ASSERT_AND_LOG(5==hlp.getValue(es));

        char ec = 8;
        ASSERT_AND_LOG(2==hlp.getValue(ec));

        int ei = 8;
        ASSERT_AND_LOG(5==hlp.getValue(ei));
    }

    inline void TestCase_bitsetEnum()
    {
        TestCase_bitsetEnum_static();
        TestCase_bitsetEnum_flag();
        TestCase_bitsetEnum_value();
    }

#ifdef RUN_EXAMPLE_BITSETENUM
    InitRunFunc(TestCase_bitsetEnum);
    InitRunFunc(TestCase_bitsetEnum_width);
#else //else of RUN_EXAMPLE_BITSETENUM

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] bitsetEnum.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"bitsetEnum.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_BITSETENUM
}

#else //else of COMPILE_EXAMPLE_BITSETENUM
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] bitsetEnum.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"bitsetEnum.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_BITSETENUM

