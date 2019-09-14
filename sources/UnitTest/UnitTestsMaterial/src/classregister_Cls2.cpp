#include <UT_material\classregister_Cls2.h>
#include <MiniMPL/classRegisterMacro.hpp>

namespace UnitTest
{
    //IMPLEMENT_CLASS(CDri_Type2,CGenBase);
    //IMPLEMENT_CLASS_BIND_DAT(CDri_Type2,CGenBase,2);
    IMPLEMENT_CLASS_BIND_DAT(CDri_Type2,CGenBase,DemoTraintType());      //Test with pNew7 by createObjectByTraitType

    CDri_Type2::CDri_Type2( void )
    {

    }

    CDri_Type2::~CDri_Type2( void )
    {

    }

    const type_info& CDri_Type2::getTypeInfo() const
    {
        return typeid(CDri_Type2);
    }

}