#ifndef TC_TRACER_H__
#define TC_TRACER_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	output test case message
*************************************************************************************/
#include <MiniMPL\productSpecialDef.h>
#include <MiniMPL\macro_makeTxt.h>
#include <MiniMPL\macro_traceLog.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace UnitTest
{
#define FmtBegin    "\n+++++++++++++++++++++++++++++++++++++++++ Testcase [%s] begin +++++++++++++++++++++++++++++++++++++++++\n"
#define FmtEnd      "\n----------------------------------------- Testcase [%s] End -------------------------------------------\n"

#define FmtTitle1   "\n                     **************************** %s ****************************                     \n"
#define FmtTitle2   "\n                          >>>>>>>>>>>>>>>>>>>>>>> %s <<<<<<<<<<<<<<<<<<<<<<<                          \n"
#define Testcase    HEREINFO_POSA() TXTA(" Compile:") TXTA(__DATE__) " " TXTA(__TIME__) TXTA(" modify:") TXTA(__TIMESTAMP__)

#define PrintTitle1(X)          outputTxtV(TXT(FmtTitle1),X);outputTxt(HEREINFO_POS() TXT("\n") )
#define PrintTitle2(X)          outputTxtV(TXT(FmtTitle2),X);outputTxt(HEREINFO_POS() TXT("\n") )
#define PrintTestcase()         CheckMacroExpand(Testcase); UnitTest::CTestcaseTrace local(TXT(__FUNCTION__),HEREINFO_POS(),HEREINFO_TIME())
#define PrintTestcaseSub()      PrintTitle1(TXT(__FUNCTION__))
#define PrintTestcaseSub2()     PrintTitle2(TXT(__FUNCTION__))

#define PrintRN()               outputTxt(TXT("\n"))

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct CTestcaseTrace
    {
        CTestcaseTrace(const stlChar* pFunc,const stlChar* pPos,const stlChar* pTime);
        ~CTestcaseTrace();

    protected:
        const stlChar* m_pFunc;
        const stlChar* m_pPos;
    };
}
#endif // TC_TRACER_H__
