#ifndef ENUMTRAIT_DETAIL_H__
#define ENUMTRAIT_DETAIL_H__

/***********************************************************************************************************************
Description         : implement of <MiniMPL\enumTrait.hpp>
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
namespace MiniMPL
{
    template<typename F,F F_min,F F_max>    struct CEnumRange;  //fw declare
    template<typename CEnumRange_T,typename CEnumRange_T::Enum_T TVal>
    struct CEnumValue;                                          //fw declare

    template<typename T>                        struct EnumRangeSizeImpl;
    template<typename F,F F_min,F F_max>        struct EnumRangeSizeImpl< CEnumRange<F,F_min,F_max> >
    {
        typedef CEnumRange<F, F_min, F_max>     TEnumRange;

        struct detail
        {
            template<typename TEnumValue>   struct CountHelper: public Int2Type<1+CountHelper<typename TEnumValue::template Next<true>::type >::value >{};
            template<>                      struct CountHelper<typename TEnumRange::Max_T >   : public Int2Type<1> {};
        };

        enum {value=detail::CountHelper<typename TEnumRange::Min_T >::value};
    };

    template<typename EnumValue_T>  struct EnumInRangeImpl : public MiniMPL::BoolType<
        (EnumValue_T::value >= EnumValue_T::Min_T::value) && 
        (EnumValue_T::value <= EnumValue_T::Max_T::value)> {};
}

#endif // ENUMTRAIT_DETAIL_H__
