#ifndef __COLLECTOR_HPP__
#define __COLLECTOR_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/container.hpp>
#include <MiniMPL/memberPtr.hpp>
#include <MiniMPL/sameQualifier.hpp>
#include <MiniMPL/unaryFunctionParamTransfer.hpp>
#include <MiniMPL/functionParams.hpp>
#include <MiniMPL/memberPtr.hpp>
#include <MiniMPL/unaryFunctionAssemble.hpp>
#include <algorithm>

namespace MiniMPL
{
    template<typename C,typename TUnaryFunc>
    struct Collector
    {
        typedef typename	C                           Container_T;
        typedef typename	Container_T::value_type     value_type;
        typedef typename    Container_T::iterator       iterator;
        typedef typename    Container_T::reference      reference;


        typedef typename    GetUnaryFunctionParam<TUnaryFunc>::type     TUFParam;
        typedef SC(TUFParam,value_type)                                 Param_T;

        Collector(C& rResult,TUnaryFunc uf)
            : m_result(rResult)
            , m_uf(uf)
        {}

        size_t size() const
        {
            return m_result.size();
        }

        template<typename T>
        void operator()(T& obj)
        {
            saveResult(m_uf(obj));
        }
        AutoConvertUnaryFunctionParam(operator(),Param_T,void);

    protected:
        void saveResult(value_type& obj)
        {
            m_result.push_back(obj);
        }
        AutoConvertUnaryFunctionParam(saveResult,value_type,void);

        TUnaryFunc          m_uf;
        Container_T&        m_result;
    };

    template<typename C,typename S,typename M>
    Collector<C,CDataMemberPtr<M S::*> > makeCollector(C& rArr,M S::* const pMemPtr)
    {
        return Collector<C,CDataMemberPtr<M S::*> >(rArr,makeMemberPtr(pMemPtr));
    }
    template<typename C,typename TUF>
    Collector<C,TUF> makeCollector(C& rArr,TUF& rUf)
    {
        return Collector<C,TUF>(rArr,rUf);
    }

    /////////////////////////////////////////collect function///////////////////////////////////////////////////////////////////
    template<typename C,typename Tester_T,typename Collector_T>
    unsigned int collect(C& rDataSet,Tester_T& rTester, Collector_T& rCollector)
    {
        typename CGetType::TContainer<C>::type& rSet = makeContainer(rDataSet);
        _STD for_each(rSet.begin(),rSet.end(),makeIfDO(rTester,rCollector));
        return rCollector.size();
    }
}


#endif // __COLLECTOR_HPP__
