#ifndef CLASSREGISTER_CLS3_H__
#define CLASSREGISTER_CLS3_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/
#include <UT_material/tc_def_classregister.h>

namespace UnitTest
{
    struct CDri_Value1 : public CGenBase
    {
    public:

        CDri_Value1(void);
        virtual ~CDri_Value1(void);

        virtual  const type_info& getTypeInfo() const;

        int m_CDri_1;
    };

}

#endif // CLASSREGISTER_CLS3_H__
