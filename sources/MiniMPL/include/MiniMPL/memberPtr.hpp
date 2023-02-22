#ifndef __MEMBERPTR_HPP__
#define __MEMBERPTR_HPP__
/***********************************************************************************************************************
* Description         : pack one/multiple level struct/class data member pointer into single member pointer.
*                       for functor, it is useful in fetching struct member with unified style 
*                       for single member pointer, it is useful in access multiple-level struct member directly with unified style.
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/memberPtr_detail.hpp>
#include <MiniMPL/any_cast.hpp>

#define makePtrToSelf(S)            (S S::*)MiniMPL::any_cast( 0 )
#define makePtrToMember(S,M,V)      (M S::*)MiniMPL::any_cast( &((S*) (NULL))->##V )
#define makePtrToMemberT(T,V)       (T)MiniMPL::any_cast( &((MiniMPL::GetStruct<T>::type*) (NULL))->##V )     //e.g.makePtrToMember(S4,int,m_ss3.m_ss2.m_ss1.m_s1)

#define MMP(M)                      MiniMPL::makeMemberPtr(M)
#define MMP2(M1,M2)                 MiniMPL::linkMemberPtr(M1,M2)
#define MMP3(M1,M2,M3)              MMP2(MMP2(M1,M2),M3)
#define MMP4(M1,M2,M3,M4)           MMP2(MMP3(M1,M2,M3),M4)
#define MMP5(M1,M2,M3,M4,M5)        MMP2(MMP4(M1,M2,M3,M4),M5)

namespace MiniMPL
{
    template<typename T>        struct GetStruct  : public InnerDetail::GetStructImpl<T>    {};
    template<typename T>        struct GetMember  : public InnerDetail::GetMemberImpl<T>    {};

    template<typename T>            struct IsDataMemberPtr                      : FalseType {};
    template<typename S,typename M> struct IsDataMemberPtr<M S::*>              : TrueType  {};
    template<typename T>            struct IsDataMemberPtr<CDataMemberPtr<T> >  : TrueType  {};
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    namespace CGetType
    {
        template<typename T>    struct TMemberPtr : public InnerDetail::getTMemberPtr<T>    {};
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename S,typename M1,typename M2>
    inline M2 S::*const linkMemberPtr(M1 S::*const ptr1,M2 M1::*const ptr2)
    {      
        return (M2 S::*)any_cast((TMemberOffset)any_cast(ptr1)+(TMemberOffset)any_cast(ptr2));
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct CDataMemberPtr
    {
        template<typename TP> inline TP& operator()(TP& rObj) const
        {
            return rObj;
        }
    };

    template<typename T>    CDataMemberPtr<T> makeMemberPtr()
    {
        return CDataMemberPtr<T>();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename S,typename M>
    struct CDataMemberPtr<M S::*> :protected Type2Type<M S::*>
    {
        CDataMemberPtr(type const ptr) : m_ptr(ptr) {};
        operator type() {return m_ptr;}

        template<typename TP>
        inline typename AdaptQualifier<M,TP>::type operator()(TP& rObj) const
        {
            return rObj.*m_ptr;
        }

        type m_ptr;
    };
    template<typename S,typename M>
    struct CDataMemberPtr<M S::* const> : public CDataMemberPtr<M S::*>{};

    template<typename S,typename M>
    CDataMemberPtr<M S::*> makeMemberPtr(M S::*const pMember)
    {
        return CDataMemberPtr<M S::*>(pMember);
    }

    template<typename T>
    inline CDataMemberPtr<T>& makeMemberPtr(CDataMemberPtr<T>& rPtr)
    {
        return rPtr;
    }
    template<typename T> struct GetUnaryFunctionParam;    //fw declare, decouple
    template<typename T> struct GetUnaryFunctionParam<CDataMemberPtr<T> >   : public GetStruct<CDataMemberPtr<T> >{};

    template<typename T> struct GetFunctionReturn;        //fw declare, decouple
    template<typename T> struct GetFunctionReturn<CDataMemberPtr<T> >       : public GetMember<CDataMemberPtr<T> >{};
}


#endif // __MEMBERPTR_HPP__
