#ifndef __BITSETENUM_HPP__
#define __BITSETENUM_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/innerDetail/bitsetEnum_detail.hpp>
#include <MiniMPL/isXXXEx.hpp>

// override default CEnumBitWidth defintion
#define DefTypeSpecBitWidth(T,W) template<>  struct MaskWidth< T >: public MiniMPL::Int2Type< W > {}
// #define DefTypeSpecBitWidth(T,W) template<>  struct MaskWidth< T >: public CEnumBitWidth< CEnumRange<T,T(0),T(detail::TMaxMaskValue< W >::value)>  > {}

namespace MiniMPL
{
    template<typename TEnumList,typename TStorage>
    struct TBitFlagCombine
    {
        //TStorage MUST can hold all flag
        Static_Assert(MiniMPL::TL::Length<TEnumList>::value<=(sizeof(TStorage)<<3));
        template<typename T>
        struct TBitValue : Int2Type<1 << MiniMPL::TL::IndexOf<TEnumList,T>::value>{};

        TStorage&       m_mask;
        TBitFlagCombine(TStorage& mask) : m_mask(mask) {};

        template<typename T>
        TStorage& setFlag(bool bTrue)
        {
            if (bTrue)
            {
                m_mask |= TBitValue<T>::value;
            }
            else
            {
                m_mask &= ~TBitValue<T>::value;
            }
            return m_mask;
        }

        template<typename T>
        bool getFlag()
        {
            return 0 != (m_mask & TBitValue<T>::value);
        }
    };

    template<typename TEnumList,typename TStorage>
    struct TBitValueCombine : public detail::TBitValueCombineBase<TEnumList,TStorage>
    {
        TStorage&   m_mask;
        TBitValueCombine(TStorage& mask) : m_mask(mask) {};

        template<typename T>
        TStorage& setValue(T attr)
        {  
            using namespace detail;

            //TStorage MUST can hold all type data bit field in TEnumList
            Static_Assert((TMaskEndIndex<typename MiniMPL::TL::TypeAt<TEnumList,MiniMPL::TL::Length<TEnumList>::value-1>::type>::value <= (sizeof(TStorage)<<3)));

            //T MUST in TEnumList
            Static_Assert((MiniMPL::TL::IndexOf<TEnumList,T>::value != -1));  

            //Value MUST lesser (equal) max bit width value
            ASSERT_AND_LOG(attr<=TMaxMaskValue<MaskWidth<T>::value>::value);

            //clear zero at T position
            //e.g : 0b 00000000 00000000 00000000 00011100   => 0b 11111111 11111111 11111111 11100011 
            m_mask &= ~(TBitWidthValue<T>::value << TMaskStartIndex<T>::value);
            m_mask |= (attr << TMaskStartIndex<T>::value);
            return m_mask;
        }

        template<typename T>
        T& getValue(T& attr)
        {  
            using namespace detail;
            //TStorage MUST can hold all type data bit field in TEnumList
            Static_Assert((TMaskEndIndex<typename MiniMPL::TL::TypeAt<TEnumList,MiniMPL::TL::Length<TEnumList>::value-1>::type>::value <= (sizeof(TStorage)<<3)));

            //T MUST in TEnumList
            Static_Assert((MiniMPL::TL::IndexOf<TEnumList,T>::value != -1));

            attr = T( (m_mask >> TMaskStartIndex<T>::value) &  TBitWidthValue<T>::value);
            return attr;
        }
    };
}


#endif // __BITSETENUM_HPP__
