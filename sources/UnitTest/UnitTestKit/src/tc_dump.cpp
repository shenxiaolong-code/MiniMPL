#include <UnitTestKit\tc_dump.h>

std::wostream&  tcOutW=std::wcout;
std::ostream&   tcOutA=std::cout;
#if 1==USE_UNICODE_STRING
extern std::wostream&   tcOut=tcOutW;
#else
extern std::ostream&    tcOut=tcOutA;
#endif

namespace UnitTest
{
    stlString getTypeName( const char* pStr )
    {  
        stlString ret;
        const char* p = pStr;
        while('\0' != *p)
        {               
            ret += stlString::value_type(*p);
            p++;
        }
        return ret;
    }
}



