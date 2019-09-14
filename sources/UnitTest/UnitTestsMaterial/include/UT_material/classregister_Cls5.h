#ifndef CLASSREGISTER_CLS5_H__
#define CLASSREGISTER_CLS5_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/
#include <UT_material/tc_def_classregister.h>

namespace UnitTest
{
    class CDri_Value3 :public CGenBase
    {
    public:
        CDri_Value3(void);
        virtual ~CDri_Value3(void);

        virtual  const type_info& getTypeInfo() const;

        int m_CDri_3;
    };
}

#endif // CLASSREGISTER_CLS5_H__
