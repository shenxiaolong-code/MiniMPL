#ifndef TD_DEF_CALLBACKTEMPLATE_H__
#define TD_DEF_CALLBACKTEMPLATE_H__

/***********************************************************************************************************************
Description         : 
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com

***********************************************************************************************************************/
#include <UT_material/tc_def_enum.h>
#include <MiniMPL/traverseCallbackMacro.hpp>

#define UTTrace(X) outputTxtV(TXT("[") TXT(X) TXT("] %s\n"),TXT(__FUNCTION__));
#define UTTrace_Tester()        UTTrace("Tester")
#define UTTrace_Callback()      UTTrace("template call back function")
#define UTTrace_IdGen()         UTTrace("get function ID")

namespace UnitTest
{
    template<typename T>
    bool isMe(const char* p)
    {         
        UTTrace_Tester();
        return MiniMPL::toStringA(typeid(T).name())==p;
    }
    Declare_Template_Tester(TestME,isMe,bool (*)(const char*));

    template<typename T>
    bool isMe2p(int a, char b)
    {         
        UTTrace_Tester();
        return a+b>100;
    }
    Declare_Template_Tester(isMe2p,isMe2p,bool (*)(int, char));

    template<typename T>
    stlStringA getMyId()
    {
        UTTrace_IdGen();
        return typeid(T).name();
    }
    Declare_Template_FuncID(getMyId,getMyId);

    template<typename T>
    bool userFuc(int& sum)
    {  
        UTTrace_Callback();
        using namespace MiniMPL;
        sum++;
        outputTxtV(TXTA("[%d]I am %s.\n"),sum,typeid(T).name());
        return true;
    }
    Declare_Template_CallBack(userFuc,userFuc,bool (*)(int&));

    template<typename T>
    bool isSumGreater5(int a,char c)
    {
        UTTrace_Tester();
        return c > (rand()%a);
    }
    Declare_Template_Tester(isSumGreater5,isSumGreater5,bool (*)(int ,char ));

    template<SeqEunm TVal>
    bool globalEnumFunc(int a,char* pStr)
    {
        printf("globalEnumFunc [%d],param=%d,%s",TVal+1,a,pStr?pStr:"NULL");
        return true;
    }
    Declare_Template_CallBack(globalEnumFunc,globalEnumFunc,bool (*)(int ,char*));

    struct CNonSeqEunmInterface_1
    {
        CNonSeqEunmInterface_1(int p) : m_bResult(false),m_param(p){};

        template<NonSeqEunm TVal>
        void execute()
        {
            using namespace MiniMPL;

            dbgOutputV(TXT("\n\n[NonSeqEunm]Enum value is %d."),TVal);
            dbgOutputV(TXT("\n[CEnumInterface_1::execute] %d\n"),TVal);
            m_bResult = (TVal+m_param) > NS_Val_Max;
        }

        bool m_bResult;
        int m_param;
    };
    Declare_Template_CallBack(CNonSeqEunmInterface_1,::UnitTest::CNonSeqEunmInterface_1::execute,void (CNonSeqEunmInterface_1::*)());

    struct CNonSeqEunmInterface_2
    {
        CNonSeqEunmInterface_2(VCHAR* pStr) : m_bResult(false),m_pStr(pStr){};

        template<NonSeqEunm TVal>
        void execute()
        {
            using namespace MiniMPL;

            dbgOutputV(TXT("\n\n[NonSeqEunm]Enum value is %d."),TVal);
            dbgOutputV(TXT("\n[CEnumInterface_2::execute] %s %d\n"),m_pStr,TVal);
            m_bResult = (TVal+2) > NS_Val_Max;
        }

        bool m_bResult;
        VCHAR* m_pStr;
    };
    Declare_Template_CallBack(CNonSeqEunmInterface_2,::UnitTest::CNonSeqEunmInterface_2::execute,void (CNonSeqEunmInterface_2::*)());

    struct CSeqEunmInterface_1
    {
        CSeqEunmInterface_1(int p) : m_bResult(false),m_param(p){};

        template<SeqEunm TVal>
        void execute()
        {
            using namespace MiniMPL;
            dbgOutputV(TXT("\n\n[SeqEunm]Enum value is %d."),TVal);
            dbgOutputV(TXT("\n[CSeqEunmInterface_1::execute] %d\n"),TVal);
            m_bResult = (TVal+m_param) > NS_Val_Max;
        }

        bool m_bResult;
        int m_param;
    };
    Declare_Template_CallBack(CSeqEunmInterface_1,::UnitTest::CSeqEunmInterface_1::execute,void (CSeqEunmInterface_1::*)());

    struct CSeqEunmInterface_2
    {
        CSeqEunmInterface_2(VCHAR* pStr) : m_bResult(false),m_pStr(pStr){};

        template<SeqEunm TVal>
        void execute()
        {
            using namespace MiniMPL;

            dbgOutputV(TXT("\n\n[SeqEunm]Enum value is %d."),TVal);
            dbgOutputV(TXT("\n[CSeqEunmInterface_2::execute] %s %d\n"),m_pStr,TVal);
            m_bResult = (TVal+2) > NS_Val_Max;
        }

        bool m_bResult;
        VCHAR* m_pStr;
    };
    Declare_Template_CallBack(CSeqEunmInterface_2,::UnitTest::CSeqEunmInterface_2::execute,void (CSeqEunmInterface_2::*)());

    class CTestEnumSuite
    {
    public:
        template<NonSeqEunm TVal>
        bool printEnum()
        {
            using namespace MiniMPL;

            outputTxtV(TXT("CTestEnumSuite::printEnum [%d]\n"),TVal);
            return true;
        }

        template<SeqEunm TVal>
        bool printNext()
        {
            using namespace MiniMPL;

            outputTxtV(TXT("CTestEnumSuite::printNext [%d]\n"),TVal+1);
            return true;
        }

        template<SeqEunm TVal>
        void inOutParam(char p1,int& outParam)
        {
            using namespace MiniMPL;

            outputTxtV(TXT("CTestEnumSuite::inOutParam [%d]\n"),TVal+1);
            outParam = p1+2;
        }

        template<SeqEunm TVal>
        int getReturnValue(char p1,int outParam)
        {
            using namespace MiniMPL;

            outputTxtV(TXT("CTestEnumSuite::inOutParam [%d]\n"),TVal+1);
            return outParam+p1+TVal+4;
        }

        template<SeqEunm TVal>
        bool print2Param(int a,char* pStr)
        {
            printf("CTestEnumSuite::print2Param [%d],param=%d,%s\n",TVal+1,a,pStr?pStr:"NULL");
            return true;
        }

    };
    Declare_Template_CallBack(printEnum,::UnitTest::CTestEnumSuite::printEnum ,bool (CTestEnumSuite::*)());
    Declare_Template_CallBack(printNext,::UnitTest::CTestEnumSuite::printNext ,bool (CTestEnumSuite::*)());
    Declare_Template_CallBack(print2Param,::UnitTest::CTestEnumSuite::print2Param ,bool (CTestEnumSuite::*)(int ,char*));
    Declare_Template_CallBack(inOutParam,::UnitTest::CTestEnumSuite::inOutParam ,void (CTestEnumSuite::*)(char ,int& ));
    Declare_Template_CallBack(getReturnValue,::UnitTest::CTestEnumSuite::getReturnValue ,int (CTestEnumSuite::*)(char,int));
}

#endif // TD_DEF_CALLBACKTEMPLATE_H__
