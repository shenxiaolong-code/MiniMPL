#ifndef __ENUMTRAIT_HPP__
#define __ENUMTRAIT_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/innerDetail/enumTrait_detail.hpp>
#include <MiniMPL/macro_assert.h>

//global forward declaration
template<typename EnumValue_T>  struct CEnumGetBigger;
template<typename EnumValue_T>  struct CEnumGetSmaller;

namespace MiniMPL
{
    //forward declaration
    template<typename CEnumRange_T,typename CEnumRange_T::Enum_T Val>    struct CEnumValue;

    //CEnumRange : provide Enum/int range properties
    template<typename F,F F_min,F F_max>    struct CEnumRange
    {
        typedef  F                                      Enum_T;
        typedef  CEnumRange<F,F_min,F_max>              EnumRange_T;

        typedef  CEnumValue<EnumRange_T,F_min>          Min_T;
        typedef  CEnumValue<EnumRange_T,F_max>          Max_T;
    };

    //CEnumValue : enum type wrapper, include enum range and enum value info.
    template<typename CEnumRange_T,typename CEnumRange_T::Enum_T TVal>
    struct CEnumValue  : public CEnumRange_T
    {
        enum {value = TVal};
        typedef CEnumValue<CEnumRange_T,TVal>           EnumValue_T;

        template<bool bIncrease> struct Last : Type2Type<typename If_T<bIncrease,CEnumGetSmaller<EnumValue_T>,CEnumGetBigger<EnumValue_T> >::type::type > {};
        template<bool bIncrease> struct Next : Type2Type<typename If_T<bIncrease,CEnumGetBigger<EnumValue_T>,CEnumGetSmaller<EnumValue_T> >::type::type > {};
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Enum property algorithm
    template<typename T>            struct CGetEnumRangeSize : public EnumRangeSizeImpl<T>{};
    template<typename EnumValue_T>  struct CEnumInRange      : public EnumInRangeImpl<EnumValue_T>{};
}

//CEnumGetBigger and CEnumGetSmaller : get bigger and smaller enum value , specialize it to skip some enum value or non-sequential enum value
template<typename EnumValue_T>  struct CEnumGetBigger;
template<typename CEnumRange_T,typename CEnumRange_T::Enum_T TVal>
struct CEnumGetBigger<MiniMPL::CEnumValue<CEnumRange_T,TVal> > : MiniMPL::Type2Type<MiniMPL::CEnumValue<CEnumRange_T,typename CEnumRange_T::Enum_T(TVal+1)> > {};

template<typename EnumValue_T>  struct CEnumGetSmaller;
template<typename CEnumRange_T,typename CEnumRange_T::Enum_T TVal>
struct CEnumGetSmaller<MiniMPL::CEnumValue<CEnumRange_T,TVal> > : MiniMPL::Type2Type<MiniMPL::CEnumValue<CEnumRange_T,typename CEnumRange_T::Enum_T(TVal-1)> > {};

//SKIP_ENUM_MIDDLE/SKIP_ENUM_ONE is used for enum type whose value is not sequential. e.g : 0 ,1 2, 6, 7, 10 [3,4,5,8,9 is lack]
//for sequential enum type, SKIP_ENUM_MIDDLE/SKIP_ENUM_ONE is optional, it can be used to skip some special enum values.
//LIMITION NOTE: SKIP_ENUM_ONE can't be used in Head or tail. In this case, the EnumRange should be adjusted (excluded head or tail).
#define SKIP_ENUM_MIDDLE(E,V1,V2)                                                                                                           \
    Static_Assert((V1<V2));                                                                                                                 \
    Static_Assert((MiniMPL::CEnumInRange<MiniMPL::CEnumValue<E,V1> >::value && MiniMPL::CEnumInRange<MiniMPL::CEnumValue<E,V2> >::value))   \
    template<> struct CEnumGetBigger<MiniMPL::CEnumValue<E,V1> >    : MiniMPL::Type2Type<MiniMPL::CEnumValue<E,V2> >    {};                 \
    template<> struct CEnumGetSmaller<MiniMPL::CEnumValue<E,V2> >   : MiniMPL::Type2Type<MiniMPL::CEnumValue<E,V1> >    {}

#define SKIP_ENUM_ONE(E,V)                                                                                                                  \
    Static_Assert(V>E::Min_T::value && V<E::Max_T::value); /*V can't be head or tail*/                                                      \
    SKIP_ENUM_MIDDLE(E,                                                                                                                     \
    E::Enum_T(CEnumGetSmaller<MiniMPL::CEnumValue<E,V> >::type::value),                                                                     \
    E::Enum_T(CEnumGetBigger<MiniMPL::CEnumValue<E,V> >::type::value) )



#endif // __ENUMTRAIT_HPP__
