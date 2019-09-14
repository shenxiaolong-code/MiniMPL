#ifndef TC_DEF_TYPE_H__
#define TC_DEF_TYPE_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/

namespace UnitTest 
{
    class AbstractClass
    { 
        virtual void f()=0;
    };
    class CDemoIndenpent {};
    class CDemoBase 
    {
        char m_b[200];
    };
    class CDemoDrived : public CDemoBase
    {
        char m_d[500];
    };
}

#endif // TC_DEF_TYPE_H__
