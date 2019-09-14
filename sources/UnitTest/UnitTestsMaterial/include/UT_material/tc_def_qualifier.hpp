#ifndef TC_QUALIFIER_H__
#define TC_QUALIFIER_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	test material
*************************************************************************************/
#include <MiniMPL\productSpecialDef.h>
#include <MiniMPL\macroDef.h>
#include <MiniMPL\isXXX.hpp>
#include <UnitTestKit\tc_dump.h>

namespace UnitTest
{
    template<typename DataType>
    void process(DataType& obj)
    {
        outputTxtV(TXT("\n[process]\tType name [%s]\n\t\tconst qualifiers ==> %s\n\t\tvalue [%d]\n"),getTypeName<DataType>().c_str(),
            MiniMPL::IsConst<DataType>::value ? TXT("Const") : TXT("non-Const"),obj);
    }
}

#endif // TC_QUALIFIER_H__
