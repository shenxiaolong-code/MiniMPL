#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\fromToString.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_FROMTOSTRING to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_FROMTOSTRING

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_FROMTOSTRING
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_FROMTOSTRING
#endif

#if defined(RUN_EXAMPLE_FROMTOSTRING) && !defined(COMPILE_EXAMPLE_FROMTOSTRING)
    #define COMPILE_EXAMPLE_FROMTOSTRING
#endif

//#undef RUN_EXAMPLE_FROMTOSTRING
//#undef COMPILE_EXAMPLE_FROMTOSTRING

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_FROMTOSTRING
#include <MiniMPL/fromToString.hpp>
#include <MiniMPL/productSpecialDef.h>
#include <UnitTestKit/tc_tracer.h>
#include <UT_MiniMPL/ut_material.h>
#include <MiniMPL/valueCompare.hpp>

namespace UnitTest
{
    struct ConstrunctFromStr
    {
        ConstrunctFromStr(){};
        ConstrunctFromStr(char const*){};
        ConstrunctFromStr(wchar_t const*){};
    };

    //extend customized type example
    inline stlStringA toStringA(UnitTest::S4 const& val)
    {
        return MiniMPL::toStringA(val.m_s4);
    }

    stlStringW toStringW(UnitTest::S4 const&  val)
    {
        return MiniMPL::toStringW(val.m_s4);
    }

    inline bool fromString(stlStringA const& from,UnitTest::S4& to)
    {
        return MiniMPL::fromString(from,to.m_s4);
    }
    inline bool fromString(stlStringW const& from,UnitTest::S4& to)
    {
        return MiniMPL::fromString(from,to.m_s4);
    }
}

namespace UnitTest
{
    static stlChar tmpBuf[32] = TXT("32");

    template<typename T>
    void testStrFmt(T& val)
    {
        outputTxtV(TXT("type[%s]\n"),getTypeName<T>().c_str());

        stlStringA  strA = MiniMPL::toStringA(val);
        T newValA;
        newValA; //UNUSED(newVal);
        ASSERT_AND_LOG(MiniMPL::fromString(strA,newValA));
        ASSERT_AND_LOG(MiniMPL::equal(val,newValA));

        stlStringW  strW = MiniMPL::toStringW(val);
        T newValW;
        newValW; //UNUSED(newVal);
        ASSERT_AND_LOG(MiniMPL::fromString(strW,newValW));
        ASSERT_AND_LOG(MiniMPL::equal(val,newValW));

        stlString  str = MiniMPL::toString(val);
        T newVal;
        newVal; //UNUSED(newVal);
        ASSERT_AND_LOG(MiniMPL::fromString(str,newVal));
        ASSERT_AND_LOG(MiniMPL::equal(val,newVal));
    }

    /******************************************************************************************************
    boo,char, unsigned char,wchar_t,short,unsigned short,
    int,unsigned int,long,unsigned long,float,double,__int64,unsigned __int64,long __int64;
    ******************************************************************************************************/
    inline void TestCase_StrFmt()
    {  
        PrintTestcase();
        outputTxt(TXT("Test fromString/toString\n"));

        bool                bVal=false;
        testStrFmt(bVal);
        char                cVal='\0';
        testStrFmt(cVal);
        cVal    = 55;
        testStrFmt(cVal);
        signed char         scVal='\0';
        testStrFmt(scVal);
        scVal    = 55;
        testStrFmt(scVal);
        wchar_t             wcVal='\0';  
        testStrFmt(wcVal);
        wcVal = 0;
        testStrFmt(wcVal);
        unsigned char       ucVal=10;
        testStrFmt(ucVal);
        ucVal = 0;
        testStrFmt(ucVal);
        short               sVal=10;
        testStrFmt(sVal);
        sVal = 0;
        testStrFmt(sVal);
        unsigned short      usVal=100;
        testStrFmt(usVal);
        usVal=0;
        testStrFmt(usVal);
        int                 iVal=100;
        testStrFmt(iVal);
        iVal=0;
        testStrFmt(iVal);
        unsigned int        uiVal=100;
        testStrFmt(uiVal);
        uiVal=0;
        testStrFmt(uiVal);
        long                lVal=100;
        testStrFmt(lVal);
        lVal=0;
        testStrFmt(lVal);
        long long           llVal=100;
        testStrFmt(llVal);
        llVal=0;
        testStrFmt(llVal);
        unsigned long       ulVal=100;
        testStrFmt(ulVal);
        ulVal=0;
        testStrFmt(ulVal);
        float               fVal=100.0f;
        testStrFmt(fVal);
        fVal=0;
        testStrFmt(fVal);
        double              dVal=100.0;
        testStrFmt(dVal);
        dVal=0;
        testStrFmt(dVal);
        long double         ldVal=100.0;
        testStrFmt(ldVal);
        ldVal=0;
        testStrFmt(ldVal);
        __int64             iiVal=100; 
        testStrFmt(iiVal);
        iiVal=0;
        testStrFmt(iiVal);
        unsigned __int64    uiiVal=100; 
        testStrFmt(uiiVal);
        uiiVal=0;
        testStrFmt(uiiVal);
    }

    inline void TestCase_fromToString()
    {
        PrintTestcase();
        
        TestCase_StrFmt();
        using namespace MiniMPL;

        char str[] = "I am string";
        wchar_t wstr[] = L"I am string";
        stlString stlStr  = MiniMPL::toString(str);   //char ==> stlString
        stlString stlStrw = MiniMPL::toString(wstr);  //wchat_t ==> stlString
        ASSERT_AND_LOG(stlStr==stlStrw);

        stlStringA  stlA("I am string");
        stlStringW  stlw(L"I am string");
        stlString stlStrCpy  = MiniMPL::toString(stlA);   //stlStringA ==> stlString
        stlString stlStrCpyw = MiniMPL::toString(stlw);   //stlStringW ==> stlString
        ASSERT_AND_LOG(stlStrCpy==stlStrCpyw);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        stlStringA stlA1 = MiniMPL::toStringA(stlw);
        stlStringA stlA2 = MiniMPL::toStringA(wstr);
        stlStringA stlA3 = MiniMPL::toStringA(str);
        stlStringA stlA4 = MiniMPL::toStringA(stlA);

        stlStringW stlW1 = MiniMPL::toStringW(stlA);
        stlStringW stlW2 = MiniMPL::toStringW(str);
        stlStringW stlW3 = MiniMPL::toStringW(wstr);
        stlStringW stlW4 = MiniMPL::toStringW(stlw);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        outputTxtV(TXTA("toStringA[bool]:%s\n"),MiniMPL::toStringA(true).c_str());
        outputTxtV(TXTA("toStringA['c']:%s\n"),MiniMPL::toStringA('c').c_str());
        outputTxtV(TXTA("toStringA[unsigned char('c')]:%s\n"),MiniMPL::toStringA(unsigned char('c')).c_str());
        outputTxtV(TXTA("toStringA[2]:%s\n"),MiniMPL::toStringA(2).c_str());
        outputTxtV(TXTA("toStringA[2.5600f]:%s\n"),MiniMPL::toStringA(2.5600f).c_str());
        outputTxtV(TXTA("toStringA[2.5600]:%s\n"),MiniMPL::toStringA(2.5600).c_str());
        outputTxtV(TXTA("toStringA[I am string]:%s\n"),MiniMPL::toStringA("I am string.").c_str());
        outputTxtV(TXTA("toStringA[(wchat_t)I am string]:%s\n"),MiniMPL::toStringA(L"I am string.").c_str());

        outputTxtV(TXTW("toStringW[bool]:%s\n"),MiniMPL::toStringW(true).c_str());
        outputTxtV(TXTW("toStringW['c']:%s\n"),MiniMPL::toStringW('c').c_str());
        outputTxtV(TXTW("toStringW[unsigned char('c')]:%s\n"),MiniMPL::toStringW(unsigned char('c')).c_str());
        outputTxtV(TXTW("toStringW[2]:%s\n"),MiniMPL::toStringW(2).c_str());
        outputTxtV(TXTW("toStringW[2.5600f]:%s\n"),MiniMPL::toStringW(2.5600f).c_str());
        outputTxtV(TXTW("toStringW[2.5600]:%s\n"),MiniMPL::toStringW(2.5600).c_str());
        outputTxtV(TXTW("toStringW[I am string]:%s\n"),MiniMPL::toStringW("I am string.").c_str());
        outputTxtV(TXTW("toStringW[(wchat_t)I am string]:%s\n"),MiniMPL::toStringW(L"I am string.").c_str());

        outputTxtV(TXT("toString[bool]:%s\n"),MiniMPL::toString(true).c_str());
        outputTxtV(TXT("toString['c']:%s\n"),MiniMPL::toString('c').c_str());
        outputTxtV(TXT("toString[unsigned char('c')]:%s\n"),MiniMPL::toString(unsigned char('c')).c_str());
        outputTxtV(TXT("toString[2]:%s\n"),MiniMPL::toString(2).c_str());
        outputTxtV(TXT("toString[2.5600f]:%s\n"),MiniMPL::toString(2.5600f).c_str());
        outputTxtV(TXT("toString[2.5600]:%s\n"),MiniMPL::toString(2.5600).c_str());
        outputTxtV(TXT("toString[I am string]:%s\n"),MiniMPL::toString("I am string.").c_str());
        outputTxtV(TXT("toString[(wchat_t)I am string]:%s\n"),MiniMPL::toString(L"I am string.").c_str());

        enum toStringEnum{toString_Val1=0,toString_Val2=1};
        outputTxtV(TXTA("toString[toStringEnum]:%s\n"),MiniMPL::toStringA(toString_Val2).c_str());
        outputTxtV(TXTW("toString[toStringEnum]:%s\n"),MiniMPL::toStringW(toString_Val2).c_str());
        outputTxtV(TXT("toString[toStringEnum]:%s\n"),MiniMPL::toString(toString_Val2).c_str());
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int         vNull_i=0;
        char        vNullA[8]={0};
        wchar_t     vNullW[8]={0};

        char*       pNullA = NULL;
        stlStringA  stlA2Arr;
        stlStringW  stlW2Arr;
        ASSERT_AND_LOG(!MiniMPL::fromString(pNullA,vNull_i));
        ASSERT_AND_LOG(MiniMPL::fromString(pNullA,vNullA));
        ASSERT_AND_LOG(MiniMPL::fromString(pNullA,vNullW));
        ASSERT_AND_LOG(MiniMPL::fromString(stlA2Arr,vNullA));
        ASSERT_AND_LOG(MiniMPL::fromString(stlW2Arr,vNullW));
        ASSERT_AND_LOG(MiniMPL::fromString(stlW2Arr,vNullA));
        ASSERT_AND_LOG(MiniMPL::fromString(stlA2Arr,vNullW));

        wchar_t*    pNullW = NULL;
        ASSERT_AND_LOG(!MiniMPL::fromString(pNullW,vNull_i));
        ASSERT_AND_LOG(MiniMPL::fromString(pNullW,vNullA));
        ASSERT_AND_LOG(MiniMPL::fromString(pNullW,vNullW));

        stlStringA stlEnum("1");
        toStringEnum vEnum=toString_Val1;
        ASSERT_AND_LOG(MiniMPL::fromString(stlEnum,vEnum));
        ASSERT_AND_LOG(vEnum==1);

        stlStringA stlInt("5");
        int vInt=0;
        ASSERT_AND_LOG(MiniMPL::fromString(stlInt,vInt));
        ASSERT_AND_LOG(vInt==5);

        stlStringA stlfloat("3.34");
        float vfloat=0;
        ASSERT_AND_LOG(MiniMPL::fromString(stlfloat,vfloat));

        stlStringA stlDouble("2.50");
        double vDouble=0;
        ASSERT_AND_LOG(MiniMPL::fromString(stlDouble,vDouble));

        stlStringA stlstr("str");
        char vStr[15]={0};
        ASSERT_AND_LOG(MiniMPL::fromString(stlstr,vStr));
        ASSERT_AND_LOG((0==strcmp(vStr,stlstr.c_str())));

        stlStringA vStlA;
        ASSERT_AND_LOG(MiniMPL::fromString(stlstr,vStlA));
        ASSERT_AND_LOG((0==strcmp(vStlA.c_str(),stlstr.c_str())));

        stlStringA stlChar("c");
        char vChar =0;
        ASSERT_AND_LOG(MiniMPL::fromString(stlChar,vChar));
        ASSERT_AND_LOG(vChar=='c');

        stlStringA stlshort("2");
        short sChar =0;
        ASSERT_AND_LOG(MiniMPL::fromString(stlshort,sChar));
        ASSERT_AND_LOG(sChar==2);

        stlStringW stlEnumW(L"1");
        toStringEnum vEnumW=toString_Val1;
        ASSERT_AND_LOG(MiniMPL::fromString(stlEnumW,vEnumW));
        ASSERT_AND_LOG(vEnumW==1);

        stlStringW stlIntW(L"5");
        int vIntW=0;
        ASSERT_AND_LOG(MiniMPL::fromString(stlIntW,vIntW));
        ASSERT_AND_LOG(vIntW==5);

        stlStringW stlfloatW(L"3.34");
        float vfloatW=0;
        ASSERT_AND_LOG(MiniMPL::fromString(stlfloatW,vfloatW));

        stlStringW stlDoubleW(L"2.50");
        double vDoubleW=0;
        ASSERT_AND_LOG(MiniMPL::fromString(stlDoubleW,vDoubleW));

        stlStringW stlstrW(L"str");
        wchar_t vStrW[15]={0};
        ASSERT_AND_LOG(MiniMPL::fromString(stlstrW,vStrW));
        ASSERT_AND_LOG((0==wcscmp(vStrW,stlstrW.c_str())));

        stlStringW stlCharW(L"c");
        wchar_t vCharW =0;
        ASSERT_AND_LOG(MiniMPL::fromString(stlCharW,vCharW));
        ASSERT_AND_LOG(vCharW==wchar_t('c'));

        stlStringA stlS4A("55");
        S4 s4Obj;
        ASSERT_AND_LOG(fromString(stlS4A,s4Obj));
        ASSERT_AND_LOG(s4Obj.m_s4==55);
        stlStringW stlS4W(L"44");
        ASSERT_AND_LOG(fromString(stlS4W,s4Obj));
        ASSERT_AND_LOG(s4Obj.m_s4==44);

        ConstrunctFromStr objConstr;
        InnerDetail::TFromTo<char*,ConstrunctFromStr>::execute("adf",objConstr);

        stlStringA strA1,strA2;
        stlStringW strW1,strW2;
        InnerDetail::TFromTo<stlStringA,stlStringA>::execute(strA1,strA2);
        InnerDetail::TFromTo<char*,stlStringA>::execute("adf",strA2);         //auto construct
        InnerDetail::TFromTo<wchar_t*,stlStringA>::execute(L"adf",strA2);     //non auto construct

    }

#ifdef RUN_EXAMPLE_FROMTOSTRING
    InitRunFunc(TestCase_fromToString);
#else //else of RUN_EXAMPLE_FROMTOSTRING

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_FROMTOSTRING)=(outputTxtV(TXT("[Unit test run disabled] fromToString.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"fromToString.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_FROMTOSTRING
}

#else //else of COMPILE_EXAMPLE_FROMTOSTRING
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_FROMTOSTRING)=(outputTxtV(TXT("[Unit test compile disabled] fromToString.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"fromToString.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_FROMTOSTRING

