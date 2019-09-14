#ifndef __SWAP_HPP__
#define __SWAP_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/macroDef.h>
#include <MiniMPL/typeLogic.hpp>
#include <MiniMPL/isXXXEx.hpp>

namespace MiniMPL
{
    template<typename DataType>
    inline void swap(DataType& left,DataType& right,ENABLE_NOT(IsStlContainer<DataType>::value))
    {  
        if (&left == &right) return;  //same element

        DataType tmp = left;
        left = right;
        right = tmp;
    }

    template<typename DataType>
    inline void swap(DataType& left,DataType& right,ENABLE_IF(IsStlContainer<DataType>::value))
    {  
        if (&left == &right) return;  //same element
        left.swap(right);
    }

    template<typename DataType,unsigned int LEN>
    inline void swap(DataType(&left)[LEN],DataType(&right)[LEN] )
    {  
        if (&left == &right) return;  //same element
        for (unsigned int i=0;i<LEN;i++)
        {
            swap(left[i],right[i]);
        }
    }

    template<typename DataType,typename Comparer_T>
    inline bool swapIf(DataType& left,DataType& right,Comparer_T& cmp)
    {
        if (cmp(left,right))
        {
            swap(left,right);
            return true;
        } 
        return false;
    }

    template<typename DataType,typename Comparer_T>
    inline bool swapNotIf(DataType& left,DataType& right,Comparer_T& cmp)
    {
        if (!cmp(left,right))
        {
            swap(left,right);
            return true;
        }
        return false;
    }
}


#endif // __SWAP_HPP__
