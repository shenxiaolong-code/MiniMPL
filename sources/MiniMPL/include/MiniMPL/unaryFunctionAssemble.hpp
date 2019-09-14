#ifndef __UNARYFUNCTIONASSEMBLE_HPP__
#define __UNARYFUNCTIONASSEMBLE_HPP__
/***********************************************************************************************************************
* Description         : assemble unary function by abstract logic
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/unaryFunctionAssemble_detail.hpp>

namespace MiniMPL
{
    template<typename TUF1,typename TUF2> struct GetFunctionReturn2T : public GetFunctionReturn2T_Impl<TUF1,TUF2>{};

    template<typename TUF1,typename TUF2>
    struct UnaryFunctionPipe
    {
        typedef typename GetFunctionReturn2T<TUF1,TUF2>::type TReturn;

        UnaryFunctionPipe(TUF1 const& uf1,TUF2 const& uf2)
            : m_uf1(uf1),m_uf2(uf2) { }

        template<typename TP1>
        TReturn operator()(TP1& p1)
        {
            return m_uf2(m_uf1(p1));
        }

        TUF1    m_uf1;
        TUF2    m_uf2;
    };

    template<typename TUF1,typename TUF2>
    UnaryFunctionPipe<TUF1,TUF2> makeUnaryFunctionPipe(TUF1 const& uf1,TUF2 const& uf2)
    {
        return UnaryFunctionPipe<TUF1,TUF2>(uf1,uf2);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename IF_T, typename DO_T>
    struct IfDO
    {
    public:
        IfDO(IF_T& rIf,DO_T& rDo)
            : m_if(rIf)
            , m_do(rDo)
        { };

        template<typename Param_T> bool operator()(Param_T& obj)
        {
            if (m_if(obj))
            {
                m_do(obj);
                return true;
            }

            return false;
        }

        IF_T&	m_if;
        DO_T&	m_do;
    };

    template<typename IF_T, typename DO_T>
    IfDO<IF_T,DO_T> makeIfDO(IF_T& rIf,DO_T& rDo)
    {
        return IfDO<IF_T,DO_T>(rIf,rDo);
    }
}


#endif // __UNARYFUNCTIONASSEMBLE_HPP__
