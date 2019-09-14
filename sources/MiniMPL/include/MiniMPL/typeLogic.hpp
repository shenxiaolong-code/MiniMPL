#ifndef __TYPELOGIC_HPP__
#define __TYPELOGIC_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           :free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/kitType.hpp>

namespace MiniMPL
{
    template<typename T>
    struct Not_T
    {
        enum{ value = (false==T::value) };
    };

    template<typename T1,typename T2,typename T3=TrueType,typename T4=TrueType,typename T5=TrueType >
    struct And_T
    {
        enum{ value = (T1::value && T2::value && T3::value && T4::value && T5::value ) };
    };

    template<typename T1,typename T2,typename T3=FalseType,typename T4=FalseType,typename T5=FalseType >
    struct Or_T
    {
        enum{ value = (T1::value || T2::value || T3::value || T4::value || T5::value) };
    };

    template<typename T1,typename T2>
    struct Xor_T 
    {
        enum{value = (true==T1::value) ^ (true==T2::value) };
    };
}


#endif // __TYPELOGIC_HPP__
