#include <UT_material\classregister_Cls5.h>
#include <MiniMPL/classRegisterMacro.hpp>

namespace UnitTest
{
    //IMPLEMENT_CLASS(CDri_Value3,CGenBase);
    //IMPLEMENT_CLASS_BIND_DAT(CDri_Value3,CGenBase,2);
    IMPLEMENT_CLASS_BIND_DAT(CDri_Value3,CGenBase,Device(TXT("Device_name_2"),3,3.45));                   //Test with pNew5

    CDri_Value3::CDri_Value3( void )
    {

    }

    CDri_Value3::~CDri_Value3( void )
    {

    }

    const type_info& CDri_Value3::getTypeInfo() const
    {
        return typeid(CDri_Value3);
    }

}
