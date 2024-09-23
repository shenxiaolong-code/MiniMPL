#ifndef maskBitCombine_detail_h__
#define maskBitCombine_detail_h__
/************************************************************************************
	author:		Shen Tony,2009-2017
	purpose:	detail implement for maskBitCombine.hpp
*************************************************************************************/
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/typeListMacro.hpp>
#include <MiniMPL/enumTrait.hpp>

namespace MiniMPL
{
    template<int M> struct log2N     : public Int2Type< 1+log2N< (M>>1) >::value > {};
    template<     > struct log2N<0>  : public Int2Type<1> {};
    template<     > struct log2N<1>  : public Int2Type<1> {};

    template<typename T>                    struct CEnumBitWidth;
    template<typename F,F F_min,F F_max>    struct CEnumBitWidth<CEnumRange<F,F_min,F_max> > : public log2N< (F_max - F_min) > {};

    template<typename T> struct MaskWidth   ; //forward declare
    template<typename T> struct MaskWidth   : public CEnumBitWidth< typename CEnumRangeDefault<T>::type > {};        // main template defintion

    namespace detail
    {
        //calculate max value for given mask bit length
        //e.g. for 2  : 0b11  ; for 5 : 0b11111
        template<int TBits>  struct TMaxMaskValue    : public MiniMPL::Int2Type<1<<(TBits-1) | TMaxMaskValue<TBits-1>::value >{};
        template<>           struct TMaxMaskValue<1> : public MiniMPL::Int2Type<1>{};

        template<typename TEnumList,typename T>
        struct TMaskStartIndexImpl
        {
            template<int idx> struct apply : public MiniMPL::Int2Type<apply<idx-1>::value+MaskWidth<typename MiniMPL::TL::TypeAt<TEnumList,idx-1>::type>::value>{}; 
            template<> struct apply<0>     : public MiniMPL::Int2Type<0> {};

            enum {value=apply<MiniMPL::TL::IndexOf<TEnumList,T>::value>::value};
        };

        template<typename TEnumList,typename TStorage>
        struct TBitValueCombineBase
        {
            template<typename T> struct TMaskStartIndex  : public detail::TMaskStartIndexImpl<TEnumList,T>{};
            template<typename T> struct TMaskEndIndex    : public MiniMPL::Int2Type<TMaskStartIndex<T>::value+MaskWidth<T>::value>{};
            template<typename T> struct TBitWidthValue   : public TMaxMaskValue<MaskWidth<T>::value>{};

            //TStorage MUST can hold all type data bit field in TEnumList
            Static_Assert((TMaskEndIndex<typename MiniMPL::TL::TypeAt<TEnumList,MiniMPL::TL::Length<TEnumList>::value-1>::type>::value <= (sizeof(TStorage)<<3)));
            //TEnumList MUST has not duplicate type
            Static_Assert((IsSameType<TEnumList,typename MiniMPL::TL::NoDuplicates<TEnumList>::type>::value));
        };
    }
}



#endif // maskBitCombine_detail_h__
