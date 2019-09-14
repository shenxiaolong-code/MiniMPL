#include <UT_material\tc_def_classregister.h>
#include <MiniMPL\classRegisterMacro.hpp>

#define Link_ClassRegister_Symbol_UnitTest(X)  Link_ClassRegister_Symbol_N1(UnitTest,X)

Link_ClassRegister_Symbol_UnitTest(CDri_Type1);
Link_ClassRegister_Symbol_UnitTest(CDri_Type2);
Link_ClassRegister_Symbol_UnitTest(CDri_Value1);
Link_ClassRegister_Symbol_UnitTest(CDri_Value2);
Link_ClassRegister_Symbol_UnitTest(CDri_Value3);

namespace UnitTest
{
    _tagDevice::_tagDevice( stlString name,int id ,double price )
    {

        m_name  = name;
        m_id    = id;
        m_price = price;
    }

    stlString _tagDevice::dumpStr() const
    {
#if 1==USE_UNICODE_STRING
        wchar_t buf[128] = {0};
        swprintf_s(buf,TXT("Name : %s\tid:%d\tprice:%f"),m_name.c_str(),m_id,m_price);
#else
        char buf[128] = {0};
        sprintf_s(buf,TXT("Name : %s\tid:%d\tprice:%f"),m_name.c_str(),m_id,m_price);
#endif

        return MiniMPL::toString(buf);
    }

    bool _tagDevice::operator==( _tagDevice const& other ) const
    {
        return m_id == other.m_id;
    }

    bool IsThisDevice( const Device& Dev, const int& p )
    {
        if (Dev.m_id == p)
            return true;

        return false;
    }

}