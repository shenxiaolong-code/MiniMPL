#include <UT_material\classregister_Cls4.h>
#include <MiniMPL/classRegisterMacro.hpp>

namespace UnitTest
{
    //IMPLEMENT_CLASS(CDri_Value2,CGenBase);
    //IMPLEMENT_CLASS_BIND_DAT(CDri_Value2,CGenBase,2);
    IMPLEMENT_CLASS_BIND_DAT(CDri_Value2,CGenBase,Device(TXT("Device_name_1"),2,2.34));                   //Test with pNew4

    CDri_Value2::CDri_Value2( void )
    {

    }

    CDri_Value2::~CDri_Value2( void )
    {

    }

    const type_info& CDri_Value2::getTypeInfo() const
    {
        return typeid(CDri_Value2);
    }

}