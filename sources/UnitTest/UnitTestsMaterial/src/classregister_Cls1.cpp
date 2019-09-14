#include <UT_material/classregister_Cls1.h>
#include <MiniMPL/classRegisterMacro.hpp>

namespace UnitTest
{
    //IMPLEMENT_CLASS(CDri_Type1,CDemoCast);
    //IMPLEMENT_CLASS_BIND_DAT(CDri_Type1,CDemoCast,2);
    IMPLEMENT_CLASS_BIND_TYPE(CDri_Type1,CDemoCast,DemoTraintType);     //Test with pNew7, pNew7 will be not CDri_Type1 because predefined base is different

    CDri_Type1::CDri_Type1( void )
    {

    }

    CDri_Type1::~CDri_Type1( void )
    {

    }

    const type_info& CDri_Type1::getTypeInfo() const
    {
        return typeid(CDri_Type1);
    }
}
