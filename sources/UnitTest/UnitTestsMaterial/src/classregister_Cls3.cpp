#include <UT_material\classregister_Cls3.h>
#include <MiniMPL\classRegisterMacro.hpp>

namespace UnitTest
{
    //IMPLEMENT_CLASS(CDri_Value1,CGenBase);                                                //Test with pNew1,  pCls
    IMPLEMENT_CLASS_BIND_DAT(CDri_Value1,CGenBase,1);                                       //Test with pNew2,pNew3

    CDri_Value1::CDri_Value1( void )
    {

    }

    CDri_Value1::~CDri_Value1( void )
    {

    }

    //IMPLEMENT_CLASS_BIND_DAT(CDri_Value1,CGenBase,Device("CDri_Value1",1,1.11));          //Test with pNew4

    const type_info& CDri_Value1::getTypeInfo() const
    {
        return typeid(CDri_Value1);
    }

}