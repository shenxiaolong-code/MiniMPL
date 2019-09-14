#ifndef CLASSREGISTER_CLS2_H__
#define CLASSREGISTER_CLS2_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/
#include <UT_material/tc_def_classregister.h>

namespace UnitTest
{
    class CDri_Type2 :public CGenBase
    {
    public:
        CDri_Type2(void);
        virtual ~CDri_Type2(void);

        virtual  const type_info& getTypeInfo() const;

        int m_CDri_Type2;
    }; 
}

#endif // CLASSREGISTER_CLS2_H__
