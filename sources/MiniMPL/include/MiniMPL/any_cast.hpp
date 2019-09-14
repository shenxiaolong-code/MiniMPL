#ifndef __ANY_CAST_HPP__
#define __ANY_CAST_HPP__
/***********************************************************************************************************************
* Description         : static_cast/reinterpret_cast and directly type cast can't process some type conversion.
*                       e.g. function pointer type, data member pointer type.
*                       Note: convertable correctness MUST be confirmed by user.
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/

namespace MiniMPL
{
    template<typename TR, typename TP>
    union CAnyCast
    {
        CAnyCast(TP p): m_P(p){};

        TP m_P;
        TR m_R;
    };

    template<typename TR,typename TP> inline TR any_cast(TP p)
    {
        return CAnyCast<TR,TP>(p).m_R;
    } 
}


#endif // __ANY_CAST_HPP__
