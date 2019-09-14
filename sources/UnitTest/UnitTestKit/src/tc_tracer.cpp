#include <UnitTestKit/tc_tracer.h>  
#include <MiniMPL/libConfig.h>

namespace UnitTest
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CTestcaseTrace::CTestcaseTrace( const stlChar* pFunc,const stlChar* pPos,const stlChar* pTime ) : m_pFunc(pFunc),m_pPos(pPos)
    {
        outputTxtV(TXT(FmtBegin),m_pFunc);

        outputTxtV(TXT("%s\n"),m_pPos);
        outputTxtV(TXT("%s\n"),pTime);
    }

    CTestcaseTrace::~CTestcaseTrace()
    {
        outputTxtV(TXT("\n%s"),m_pPos);
        outputTxtV(TXT(FmtEnd),m_pFunc);        
    }

}
