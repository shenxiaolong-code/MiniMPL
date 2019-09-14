#ifndef TC_DEF_NOCOPY_H__
#define TC_DEF_NOCOPY_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{
    struct NoCopyObj
    {
        NoCopyObj():m_dat(0){};
        bool operator ()();

        bool operator ()(S4& obj,int& b);

    protected:
        int     m_dat;

    private:
        NoCopyObj(NoCopyObj const&);            //disable copy constructor
        NoCopyObj operator=(NoCopyObj const&);  //disable assign
    };
}

#endif // TC_DEF_NOCOPY_H__
