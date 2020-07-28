#ifndef CONTAINER_DETAIL_H__
#define CONTAINER_DETAIL_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	inner detail for container.hpp
*************************************************************************************/
#include <MiniMPL/sameQualifier.hpp>

namespace MiniMPL
{
    namespace CGetType
    {
        template<typename T>    struct TContainer;
    }
    template<typename Stl_T>    struct TContainer;
    namespace InnerDetail
    {
        template<typename T> struct GetTContainer                           : public Type2Type<T>{};
        template<typename T> struct GetTContainer<TContainer<T> >           : public Type2Type<TContainer<T> >{};
        template<typename T,unsigned TLEN>  struct GetTContainer<T[TLEN] >  : public Type2Type<TContainer<T[TLEN]> >{};
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct  Get_Container_value_typeNoRef       : public If_Evl<IsConst<T>,typename AddConst<typename T::value_type>::type,typename T::value_type>{};
    template<typename T>
    struct  Get_Container_value_type            : public Get_Container_value_typeNoRef<typename RemoveRef<T>::type>{};
    template<typename T,unsigned TLEN>
    struct  Get_Container_value_type<T[TLEN]>   : public RemoveRef<T>{};

    template<typename T>
    struct Get_Container_CPointer : public AddCPointer<typename Get_Container_value_type<T>::type>{};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename C,typename iterator_T>
    typename MiniMPL::Get_Container_CPointer<C>::type iterator2CPointer(C& arr,const iterator_T& it,ENABLE_IF((IsStlIterator<iterator_T>::value)))
    {    
        return it==arr.end() ? NULL : &*it;
    }
    template<typename C,typename iterator_T>
    typename MiniMPL::Get_Container_CPointer<C>::type iterator2CPointer(C& arr,iterator_T it,ENABLE_NOT((IsStlIterator<iterator_T>::value)))
    {   //some customized iterator is hard-code address by static_cast, it can't be referenced. 
        return it==arr.end() ? NULL : &*it;
    }

    //////////////////////////////////////////////////////////////////////////
    namespace InnerDetail
    {
        template<typename T,template<class> class impler >
        struct CArrAddRemoveImpl : Type2Type<TContainer<typename impler<T>::type > > {};
    }
}

#endif // CONTAINER_DETAIL_H__
