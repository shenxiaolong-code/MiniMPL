#ifndef __STDALGORITHMEX_HPP__
#define __STDALGORITHMEX_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/container.hpp>
#include <MiniMPL/comparer.hpp>
#include <algorithm>

namespace MiniMPL
{
    template<typename C,typename Tester_T>
    ETP(C) find(C& arr, const Tester_T& rTester)
    {  
        return iterator2CPointer(arr,std::find_if(arr.begin(),arr.end(),rTester));
    }

    template<typename C,typename Compare_T>
    void sort(C& arr, const Compare_T& rCmp)
    {   
        std::sort(arr.begin(),arr.end(),rCmp);
    }

    template<typename C,typename S,typename M>
    void sort(C& arr,M S::* pMember,bool bIncrease=true)
    {
        bool (*pF)(M const&,M const&) = bIncrease ? lesser<M,M> : greater<M,M>;
        return sort(arr,makeComparer(MMP(pMember),pF));
    }

    template<typename C,typename Process_T>
	const Process_T& forEach(C& arr,const Process_T& rCmp)
    {   
        if (0!=arr.size())
        {
            std::for_each(arr.begin(),arr.end(),rCmp);
        }
        return rCmp;
    }

    //Note:Compare_T should be CLesser
    template<typename C,typename Compare_T>
    ETP(C) maxElement(C& arr, const Compare_T& rCmp)
    {  
        return iterator2CPointer(arr,std::max_element(arr.begin(),arr.end(),rCmp));
    }

    //Note:Compare_T should be CLesser
    template<typename C,typename Compare_T>
    ETP(C) minElement(C& arr, const Compare_T& rCmp)
    {   
        return iterator2CPointer(arr,std::min_element(arr.begin(),arr.end(),rCmp));
    }
}


#endif // __STDALGORITHMEX_HPP__
