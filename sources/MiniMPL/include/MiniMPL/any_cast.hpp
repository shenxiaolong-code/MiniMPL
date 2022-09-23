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
    namespace InnerDetail
    {
        template <typename TR, typename TP>
        union CAnyCastImpl
        {
            CAnyCastImpl(TP p) : m_P(p){};

            TP m_P;
            TR m_R;
        };

        template <typename TP>
        struct CAnyCast_bridge
        {
            CAnyCast_bridge(TP p) : m_P(p){};

            template <typename TR> 
            operator TR()
            {
                return CAnyCastImpl<TR, TP>(m_P).m_R;
            }

            TP m_P;
        };
    }

    //[ warning ] float/double and int/int-similar cast will cause the wrong result because of their different storage mechanism.
    struct CAnyCast
	{
        template<typename TP> 
        InnerDetail::CAnyCast_bridge<TP> operator ()(TP p)
        {
            return InnerDetail::CAnyCast_bridge<TP>(p);
        }
	};

    template<typename TR,typename TP> inline TR any_cast(TP p)
    {
        return InnerDetail::CAnyCastImpl<TR,TP>(p).m_R;
    } 
}

static MiniMPL::CAnyCast      _anycast;


#endif // __ANY_CAST_HPP__
