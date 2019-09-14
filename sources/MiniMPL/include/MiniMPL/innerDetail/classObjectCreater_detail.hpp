#ifndef CLASSOBJECTCREATER_DETAIL_H__
#define CLASSOBJECTCREATER_DETAIL_H__

/***********************************************************************************************************************
Description         : detail implement of <MiniMPL/classObjectCreater.hpp>
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/classRegister.hpp>
#include <MiniMPL/valueCompare.hpp>

namespace MiniMPL
{
    template<typename B>
    inline B* createObjectImpl( ClassRegisterEx<B>* pCls )
    {
        return pCls ? pCls->createObject() : NULL;
    }

    template<typename B>
    inline ClassRegisterEx<B>* getClassRegisterByName(const stlString& strClassName)
    {  
        ClassRegisterEx<B>*    pList   = ClassRegisterEx<B>::m_pHeaderEx;
        while(NULL!=pList)
        {
            if (strClassName == pList->m_strClassName)
                return pList;

            pList   = pList->m_pNextClassEx;
        }

        return NULL;
    }

    template<typename B,typename S>    
    inline ClassRegisterEx<B>* getClassRegisterByTraitType(unsigned int iNo)
    {
        Static_Assert((!IsSameRawType<NullType,S>::value));

        unsigned int idx = 0;
        ClassRegisterEx<B>*  pList   = ClassRegisterEx<B>::m_pHeaderEx;
        while(NULL!=pList)
        {     
            if (pList->isTraitType<S>() && iNo==idx++)
                return pList;

            pList   = pList->m_pNextClassEx;
        }
        return NULL; 
    }

    template<typename B,typename S,typename K> 
    inline ClassRegisterEx<B>* getClassRegister(K const& CmpKey,bool (*IsIt)(S,K const&))
    {//用户自定义的比较函数来比较
        //Static_Assert(!(IsSameRawType<NullType,S>::value || IsSameRawType<NullType,K>::value));
        typedef RAWTYPE(S)     RawS_T;

        ClassRegisterEx<B>*  pList   = ClassRegisterEx<B>::m_pHeaderEx;
        while(NULL!=pList)
        {     
            RawS_T const* pTraitVal = pList->getTraitValue<RawS_T>();    
            if (pTraitVal && IsIt(*pTraitVal,CmpKey))
                return pList;

            pList   = pList->m_pNextClassEx;
        }
        return NULL; 
    }

    template<typename B,typename S,typename M>
    inline ClassRegisterEx<B>* getClassRegister(M const& CmpKey,M S::* pMember,bool (*IsIt)(M const&,M const&) )
    {//用特征结构体中指定的成员值来比较
        //typedef typename GetStruct<MPTR>::type S;

        ClassRegisterEx<B>*  pList   = ClassRegisterEx<B>::m_pHeaderEx;
        while(NULL!=pList)
        {     
            S const* pTraitVal = pList->getTraitValue<S>();
            if (pTraitVal && IsIt((*pTraitVal).*pMember,CmpKey))
                return pList;

            pList   = pList->m_pNextClassEx;
        }
        return NULL; 
    }

    template<typename B,typename K> 
    inline ClassRegisterEx<B>* getClassRegister(const K& CmpKey)
    { //和特征值(结构体)直接相比较，如果特征值为非原子类型，则其必须是可比较的：即有比较操作符
        return getClassRegister<B>(CmpKey,&equal<K,K>);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T,T* T::* TPVal>  struct  ClassListNextImpl   : public Type2Type<T* T::*>   { static type value; };
    template<typename T,T* T::* TPVal>  typename ClassListNextImpl<T,TPVal>::type ClassListNextImpl<T,TPVal>::value=TPVal;

    template<typename T>
    struct  ClassListNext : public ClassListNextImpl<ClassRegisterEx<T>,&ClassRegisterEx<T>::m_pNextClassEx>{};
    template<>
    struct  ClassListNext<void>: public ClassListNextImpl<ClassRegister,&ClassRegister::m_pNextClass>{};

    template<typename T,T** TPVal>  struct  ClassListHeadImpl   : public Type2Type<T*>   { static type* value; };
    template<typename T,T** TPVal>  typename ClassListHeadImpl<T,TPVal>::type* ClassListHeadImpl<T,TPVal>::value=TPVal;

    template<typename T>
    struct  ClassListHead : public ClassListHeadImpl<ClassRegisterEx<T>,&(ClassRegisterEx<T>::m_pHeaderEx)>{};
    template<>
    struct  ClassListHead<void>: public ClassListHeadImpl<ClassRegister,&(ClassRegister::gs_pHeader)>{};
}

#endif // CLASSOBJECTCREATER_DETAIL_H__
