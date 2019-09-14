#ifndef CLASSREGISTER_CLS_H__
#define CLASSREGISTER_CLS_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/
#include <MiniMPL\productSpecialDef.h>
#include <MiniMPL\classregister.hpp>

namespace UnitTest
{
    typedef struct _tagDevice
    {
        stlString       m_name;
        int             m_id;
        double          m_price;

        _tagDevice(stlString name,int id ,double price);

        bool operator==(_tagDevice const& other) const;

        stlString dumpStr() const;

    }Device,*LPDevice;

    bool IsThisDevice(const Device& Dev, const int& p);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct DemoTraintType {};   //define type DemoTraintType for creating object
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CDemoCast 
    {
    public:
        virtual ~CDemoCast(){};
        virtual  const type_info& getTypeInfo() const  = 0;
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CGenBase  : public CDemoCast
    {
    public:
        CGenBase(){;};
        virtual ~CGenBase(){;};
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}




#endif // CLASSREGISTER_CLS_H__
