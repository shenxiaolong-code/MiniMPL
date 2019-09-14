#ifndef __CONTAINER_HPP__
#define __CONTAINER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/isXXXEx.hpp>
#include <MiniMPL/addRemove.hpp>
#include <MiniMPL/arrayTrait.hpp>
#include <MiniMPL/innerDetail/container_detail.hpp>
#include <MiniMPL/innerDetail/cArrayContainer.hpp>
#include <MiniMPL/macro_class.h>

/////////////////////////////////////////////////////// data set wrapper ////////////////////////////////////////////////////////////
//below macro is used to reduce string length in function interface
#define ET(X)       typename MiniMPL::Get_Container_value_type<X>::type   //ET : element type of STL container or C Array
#define ETP(X)      typename MiniMPL::Get_Container_CPointer<X>::type     //ET : element type of STL container or C Array

namespace MiniMPL
{
    namespace CGetType
    {
        template<typename T> struct TContainer : public InnerDetail::GetTContainer<typename RemoveRef<T>::type>{};
    }

////////////////////////////////C Array container ///////////////////////////////////////////////////////////////////////////
    template<typename Stl_T> struct TContainer : public Stl_T {};
    template<typename T,unsigned TLEN>
    struct TContainer<T[TLEN]> : public CArrayBase<T[TLEN]>
    {   //provide interface similiar like std::vector
        TContainer(_TArrayRef rObj,size_type iSize): CArrayBase(rObj,iSize) {};
    };

    ///////////////////////////////////make Container helper///////////////////////////////////////////////////////////////////////////////////////////
    template<typename Stl_T>
    Stl_T& makeContainer(Stl_T& stlArr,ENABLE_IF(IsStlContainer<Stl_T>::value))
    {
        return	stlArr;
    }
    template<typename S,unsigned int LEN>
    TContainer<S[LEN]> makeContainer(S (&obj)[LEN],unsigned int iSize)
    {   //MUST indicate real data number , default is full
        return TContainer<S[LEN]>(obj,iSize);
    };

    template<typename TArr>
    inline TContainer<TArr>& makeContainer(TContainer<TArr>& rArr)
    {
        return	rArr;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename S,unsigned int LEN>
    TContainer<S[LEN]> makeContainer_fullArray(S (&obj)[LEN])
    {   //MUST indicate real data number , default is full
        return TContainer<S[LEN]>(obj,LEN);
    };
    template<typename S,unsigned int LEN>
    TContainer<S[LEN]> makeContainer_emptyArray(S (&obj)[LEN])
    {   //MUST indicate real data number , default is full
        return TContainer<S[LEN]>(obj,0);
    };

    template<typename TContainer,typename TE>
    inline bool eraseUnsortedArray(TContainer& cArr,TE& pE)
    {
        for (TContainer::iterator it=cArr.begin();it!=cArr.end();++it)
        {
            if (*it==pE)
            {
                std::swap(*it,cArr.back());
                cArr.erase(--cArr.end());
                return true;
            }
        }
        return false;
    }

    ///////////////////////////override isXXX interface for TContainer<T[TLEN]>///////////////////////////////////////////////
    template<typename T> struct IsConst<TContainer<T> >         : public IsConst<T>{};
    template<typename T> struct IsRef<TContainer<T> >           : public IsRef<T>{};
    template<typename T> struct IsVolatile<TContainer<T> >      : public IsVolatile<T>{};
    template<typename T> struct IsCPointer<TContainer<T> >      : public IsCPointer<T>{};

    template<typename T> struct AddConst<TContainer<T> >        : public InnerDetail::CArrAddRemoveImpl<T,AddConst>       {};
    template<typename T> struct RemoveConst<TContainer<T> >     : public InnerDetail::CArrAddRemoveImpl<T,RemoveConst>    {};

    template<typename T> struct AddRef<TContainer<T> >          : public InnerDetail::CArrAddRemoveImpl<T,AddRef>         {};
    template<typename T> struct RemoveRef<TContainer<T> >       : public InnerDetail::CArrAddRemoveImpl<T,RemoveRef>      {};

    template<typename T> struct AddVolatile<TContainer<T> >     : public InnerDetail::CArrAddRemoveImpl<T,AddVolatile>    {};
    template<typename T> struct RemoveVolatile<TContainer<T> >  : public InnerDetail::CArrAddRemoveImpl<T,RemoveVolatile> {};

    template<typename T> struct AddCPointer<TContainer<T> >     : public InnerDetail::CArrAddRemoveImpl<T,AddCPointer>    {};
    template<typename T> struct RemoveCPointer<TContainer<T> >  : public InnerDetail::CArrAddRemoveImpl<T,RemoveCPointer> {};
}

#endif // __CONTAINER_HPP__
