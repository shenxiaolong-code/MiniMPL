#ifndef __VALUECOMPARE_HPP__
#define __VALUECOMPARE_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/valueCompare_detail.hpp>
#include <MiniMPL/memberPtr.hpp>
#include <MiniMPL/comparer.hpp>

#ifndef max
    #define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
    #define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef LimitVal
    #define LimitVal(x,l,r)     ( (x)<(l) ?  (l) : ( (x)>(r) ? (r):(x) ) )
#endif

namespace MiniMPL
{
    //Note : TL , TR should include cv-r qualifier ( const& )
    template <typename TL,typename TR>
    inline bool equal(TL const& p1,TR const& p2);

    template <typename TL,typename TR>
    inline bool lesser(TL const& p1,TR const& p2);

    template <typename TL,typename TR>
    inline bool notEqual(TL const& p1,TR const& p2 );

    template <typename TL,typename TR>
    inline bool lesserEqual(TL const& p1,TR const& p2 );

    template <typename TL,typename TR>
    inline bool greater(TL const& p1,TR const& p2 );

    template <typename TL,typename TR>
    inline bool greaterEqual(TL const& p1,TR const& p2 );
       
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //literal style
    struct CEqual           : public TCompareImpl<'='>      {};
    struct CNotEqual        : public TCompareImpl<'!','='>  {};
    struct CLesser          : public TCompareImpl<'<'>      {};
    struct CLesserEqual     : public TCompareImpl<'<','='>  {};
    struct CGreater         : public TCompareImpl<'>'>      {};
    struct CGreaterEqual    : public TCompareImpl<'>','='>  {};  
    
    //template style
    template<char ch,char ch2='\0'> struct TComparer : public TCompareImpl<ch,ch2>{};
    template<>  struct TComparer<'!'>       : public CNotEqual          {}; 
    template<>  struct TComparer<'<','>'>   : public CNotEqual          {}; 
    template<>  struct TComparer<'('>       : public CLesser            {};
    template<>  struct TComparer<'!','('>   : public CGreaterEqual      {};
    template<>  struct TComparer<'['>       : public CLesserEqual       {};
    template<>  struct TComparer<'!','['>   : public CGreater           {};
    template<>  struct TComparer<')'>       : public CGreater           {};
    template<>  struct TComparer<'!',')'>   : public CLesserEqual       {};
    template<>  struct TComparer<']'>       : public CGreaterEqual      {};
    template<>  struct TComparer<'!',']'>   : public CLesser            {};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    ResultComparer<CDataMemberPtr<T>,CLesser>  makeMaxMinComparerStd(CDataMemberPtr<T> const& ptr)
    {   //used in std::max_element and std::min_element
        return makeComparer(ptr,CLesser());
    }
    template<typename S,typename M>
    ResultComparer<CDataMemberPtr<M S::*>,CLesser>  makeMaxMinComparerStd(M S::* ptr)
    {   //used in std::max_element and std::min_element
        return makeComparer(MMP(ptr));
    }
}

#endif // __VALUECOMPARE_HPP__