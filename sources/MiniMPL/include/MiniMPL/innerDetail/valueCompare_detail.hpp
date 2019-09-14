#ifndef VALUECOMPARE_DETAIL_H__
#define VALUECOMPARE_DETAIL_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	detail implement for valueCompare.hpp
*************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/sameQualifier.hpp>
#include <MiniMPL/innerDetail/isXXXEx_detail.hpp>
#include <MiniMPL/macro_assert.h>

#if 1==USE_FLOAT_MIN_THRESHOLD_CMP
    #include <MiniMPL/productSpecialDef.h>    //#define Float_Cmp_Threshold
#else
    #include <limits>                         //use std::numeric_limits
#endif // 1==USE_FLOAT_MIN_THRESHOLD_CMP

namespace MiniMPL
{
    namespace InnerDetail
    {  
        template<typename TL,typename TR>
        struct IsFloatCompare : public And_T<isBuildinFloat<TL> ,isBuildinFloat<TR> > {};
#if 0==USE_FLOAT_MIN_THRESHOLD_CMP
        template<typename TL,typename TR>
        struct FloatCmpThresholdType : public If_T<(sizeof(TL)>sizeof(TR)),TR,TL> {};
#endif // 0==USE_FLOAT_MIN_THRESHOLD_CMP

        template<bool bStrCmp>
        struct StringEqualImpl
        {
            template<bool bStlStr>  struct GetCString
            {
                template<typename TChar>
                static TChar const* CStr(stlStringPack(TChar) const& rStr){ return rStr.c_str();    }
            };
            template<>              struct GetCString<false>
            {
                template<typename TChar>    static TChar* CStr(TChar* pStr){ return pStr;           }
            };

            template <typename CharL,typename CharR>
            static bool equalImpl(CharL const* p1,CharR const* p2)
            {
                while(*p1!='\0' && *p2!='\0')
                { 
                    if (*p1++ != *p2++)
                    {
                        return false;
                    }
                }
                return *p1=='\0' && *p2=='\0';
            }

            template <typename TL,typename TR>
            static bool equalImpl(TL const& p1,TR const& p2,
                ENABLE_IF((Xor_T<IsStringStl<TL>,IsStringStl<TR> >::value)))
            {
                return equalImpl(GetCString<IsStringStl<TL>::value>::CStr(p1),
                    GetCString<IsStringStl<TR>::value>::CStr(p2));
            }

            template <typename TL,typename TR>
            static bool equalImpl(TL const& p1,TR const& p2,
                ENABLE_IF((And_T<IsStringStl<TL>,IsStringStl<TR> >::value)))
            {
                return (p1.size()==p2.size()) && equalImpl(GetCString<IsStringStl<TL>::value>::CStr(p1),
                    GetCString<IsStringStl<TR>::value>::CStr(p2));
            }
        };

        template<>
        struct StringEqualImpl<false>
        {
            template <typename TL,typename TR>
            static bool equalImpl(TL const& p1,TR const& p2,ENABLE_IF((!IsFloatCompare<TL,TR>::value)))
            {
                return p1==p2;
            }

            template <typename TL,typename TR>
            static bool equalImpl(TL const& p1,TR const& p2,ENABLE_IF((IsFloatCompare<TL,TR>::value)))
            {  
                //float d1_1 = -1.0f/9.0f;                //-1.1111112
                //float d10_1 = -10.0f/9.0f;              //-0.11111111
                //bool bEqualMin=equal(d1_1,d10_1/10);    //OK: bEqualMin is true
                // 
                //float d2_3  = -2.0f/3.0f;               //-0.66666669
                //float d20_3 = -20.0f/3.0f;              //-6.6666665
                //bool bEqualMax=equal(d2_3,d20_3/10);    //OK: bEqualMax is true,if use 0.0000001 => false
#if 1==USE_FLOAT_MIN_THRESHOLD_CMP
                return fabs(p1-p2) <= Float_Cmp_Threshold;    //0.000001
#else
                typedef typename FloatCmpThresholdType<TL,TR>::type  LowPrecisionType;
                return fabs(p1-p2) <= std::numeric_limits<LowPrecisionType>::epsilon();
#endif // 1==USE_FLOAT_MIN_THRESHOLD_CMP
            }
        };

        template <typename TL,typename TR>
        struct StringEqual : public StringEqualImpl< And_T<IsString<RAWTYPE(TL)>,IsString<RAWTYPE(TR)> >::value >{};
    }

    template <typename TL,typename TR>
    inline bool equal(TL const& p1,TR const& p2)
    {
        return InnerDetail::StringEqual<TL,TR>::equalImpl(p1,p2);
    }

    template <typename TL,typename TR>
    inline bool lesser(TL const& p1,TR const& p2)
    {
        return p1 < p2;
    }

    template <typename TL,typename TR>
    inline bool notEqual(TL const& p1,TR const& p2 )
    {
        return !equal(p1,p2);
    }

    template <typename TL,typename TR>
    inline bool lesserEqual(TL const& p1,TR const& p2 )
    {
        return lesser(p1,p2) || equal(p1,p2);
    }

    template <typename TL,typename TR>
    inline bool greater(TL const& p1,TR const& p2 )
    {
        return lesser(p2,p1);
    }

    template <typename TL,typename TR>
    inline bool greaterEqual(TL const& p1,TR const& p2 )
    {
        return greater(p1,p2) || equal(p1,p2);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<char ch,char ch2='\0'>      struct TCompareImpl;
    template<> struct TCompareImpl<'='>    
    {
        template <typename TL,typename TR> 
        bool operator()(TL const& p1,TR const& p2) const { return equal(p1,p2);  }
    };
    template<> struct TCompareImpl<'!','='>    
    {
        template <typename TL,typename TR> 
        bool operator()(TL const& p1,TR const& p2) const { return notEqual(p1,p2);    }
    };
    template<> struct TCompareImpl<'<'>    
    {
        template <typename TL,typename TR> 
        bool operator()(TL const& p1,TR const& p2) const { return lesser(p1,p2);      }
    };
    template<> struct TCompareImpl<'<','='>    
    {
        template <typename TL,typename TR> 
        bool operator()(TL const& p1,TR const& p2) const { return lesserEqual(p1,p2); }
    };
    template<> struct TCompareImpl<'>'>    
    {
        template <typename TL,typename TR> 
        bool operator()(TL const& p1,TR const& p2) const { return greater(p1,p2);     }
    };
    template<> struct TCompareImpl<'>','='>    
    {
        template <typename TL,typename TR> 
        bool operator()(TL const& p1,TR const& p2) const { return greaterEqual(p1,p2); }
    };
}

#endif // VALUECOMPARE_DETAIL_H__
