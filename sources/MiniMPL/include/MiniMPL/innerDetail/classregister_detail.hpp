#ifndef CLASSREGISTER_DETAIL_H__
#define CLASSREGISTER_DETAIL_H__

/***********************************************************************************************************************
Description         : detail implement of <MiniMPL/classRegister.hpp>
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
namespace MiniMPL
{
    template<typename T>
    inline bool removeClassRegister(T* pThis,T*& pHead, T* T::*pNext)
    {
        T* pLast=0;
        T* pCur=pHead;
        while(pCur!=pThis)
        {
            pLast = pThis;
            pCur = pCur->*pNext;
        }

        if (!pLast)
        {
            pHead = pThis->*pNext;
        }
        else
        {
            pLast->*pNext = pThis->*pNext;
        }
        pThis->*pNext = 0;
        return true;
    }

    namespace InnerDetail
    {  // TraitType and TraitData is only inner support tools, it shouldn't be used as one utility for outer application

        template<typename T> struct TraitType   
        {   //avoid to create unnecessary (big) object
            typedef T type;
            virtual ~TraitType(){};

            virtual T const* getDat()  const
            {
                return 0;
            }
        };

        template<typename T> struct TraitData : public TraitType<T>
        {
            TraitData(T const& obj)
                : m_obj(obj)
            {
            }
            virtual ~TraitData(){};

            virtual T  const* getDat() const
            {
                return &m_obj;
            }

             const T    m_obj;
        };

        template<typename T> 
        TraitData<T> makeTraitData(T const& obj)
        {
            return TraitData<T>(obj);
        }
    }

    //////////////////////////////////////////////Supported class : CObjectCreater //////////////////////////////////////
    template<typename B> class CTypeObjectCreater; 

    class CObjectCreater
    {
        friend struct ClassRegister;

    public:
        template<typename B>
        const CTypeObjectCreater<B>*	getTypedCreater() const
        {
            if (getTypeInfo()==typeid(B))
            {
                return (CTypeObjectCreater<B>*)this;
            }

            return NULL;
        }

        virtual ~CObjectCreater(){};
        virtual  const type_info& getTypeInfo() const  = 0;
    }; 

    template<typename B> 
    class CTypeObjectCreater : public CObjectCreater
    {
    public:
        virtual B* createObject() const = 0;

        virtual  const type_info& getTypeInfo() const 
        { 
            return typeid(B);
        }
    };

    template<typename D,typename B> 
    class CTypeObjectCreaterImpl : public CTypeObjectCreater<B>
    {
    public:
        virtual B* createObject() const
        {
            return new D();
        }
    };
}

#endif // CLASSREGISTER_DETAIL_H__
