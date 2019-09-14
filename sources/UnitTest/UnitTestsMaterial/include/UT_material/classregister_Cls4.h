#ifndef CLASSREGISTER_CLS4_H__
#define CLASSREGISTER_CLS4_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/
#include <UT_material/tc_def_classregister.h>

namespace  UnitTest
{
    struct CDri_Value2 :public CGenBase
    {
    public:
        CDri_Value2(void);
        virtual ~CDri_Value2(void);

        virtual  const type_info& getTypeInfo() const;

        int m_CDri_2;
    };
}

#endif // CLASSREGISTER_CLS4_H__
