#ifndef TC_UNARYFUNCTIONPARAMTRANSFER_H__
#define TC_UNARYFUNCTIONPARAMTRANSFER_H__

/***********************************************************************************************************************
Description         : test material
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
***********************************************************************************************************************/
#include <MiniMPL/unaryFunctionParamTransfer.hpp>

namespace UnitTest
{
    struct structFromInt
    {
        structFromInt(int const& i): m_a(i){};
        int m_a;
    };

    struct UFParamConverter
    {
        int autoConvert(structFromInt obj)
        {
            return obj.m_a;
        }

        int autoConvertP(structFromInt* pObj)
        {
            return pObj->m_a;
        }

        AutoConvertUnaryFunctionParam(autoConvert,structFromInt,int)
        AutoConvertUnaryFunctionParam(autoConvertP,structFromInt*,int)
    };
}

#endif // TC_UNARYFUNCTIONPARAMTRANSFER_H__
