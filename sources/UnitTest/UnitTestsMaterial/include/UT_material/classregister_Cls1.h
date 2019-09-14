#ifndef CLASSREGISTER_CLS1_H__
#define CLASSREGISTER_CLS1_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/
#include <UT_material/tc_def_classregister.h>

namespace UnitTest
{
    class  CDri_Type1 :public CDemoCast
    {
    public:
        CDri_Type1(void);;
        virtual ~CDri_Type1(void);;

        virtual  const type_info& getTypeInfo() const;
    };
}   

#endif // CLASSREGISTER_CLS1_H__
