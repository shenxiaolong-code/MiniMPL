#include <UT_material/tc_def_NoCopy.h>
#include <ostream>
#include <MiniMPL/macroDef.h>

namespace UnitTest
{
    using namespace std;

    bool NoCopyObj::operator()()
    {
        m_dat = 5;
        outputTxtV(TXT("I am function object\n%s"),HEREINFO());
        return true;
    }

    bool NoCopyObj::operator()( S4& obj,int& b )
    {
        m_dat = b;
        obj.printNoParam();
        return true;
    }

}