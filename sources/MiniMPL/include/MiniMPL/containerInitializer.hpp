#ifndef __CONTAINERINITIALIZER_HPP__
#define __CONTAINERINITIALIZER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/container.hpp>

namespace MiniMPL
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename TData>
    struct ContainerInitializer
    {
        typedef typename CGetType::TContainer<TData>::type    _TContainer;
        typedef typename If_Evl<IsArray<TData>,_TContainer,typename AddRef<_TContainer>::type>::type  TContainer;

        typedef typename _TContainer::value_type               value_type;

        TContainer            m_dSet;

        ContainerInitializer(TContainer dSet): m_dSet(dSet){};

        ContainerInitializer& operator=(value_type const& dat)
        {   
            m_dSet.clear();
            operator+=(dat);
            return *this;
        }
        ContainerInitializer& operator+=(value_type const& dat)
        {   
            m_dSet.push_back(dat);
            return *this;
        }
        ContainerInitializer& operator,(value_type const& dat)
        {
            m_dSet.push_back(dat);
            return *this;
        }        
    };

    template<typename T>
    ContainerInitializer<T> makeInitializer(T& obj) 
    { 
        return ContainerInitializer<T>(makeContainer(obj)); 
    }
    template<typename T,unsigned int TSize>
    typename ContainerInitializer<T[TSize]> makeInitializer(T(&rObj)[TSize],unsigned int iSize=0) 
    { 
        return ContainerInitializer<T[TSize]>(makeContainer(rObj,iSize)); 
    }
}


#endif // __CONTAINERINITIALIZER_HPP__
