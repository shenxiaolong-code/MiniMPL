#ifndef __CLASSREGISTER_HPP__
#define __CLASSREGISTER_HPP__
/***********************************************************************************************************************
* Description         : completely decouple object factory and concrete derived class.
*                       ClassRegister/ClassRegisterEx can create any class instance IMPLICITLY.
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/classregister_detail.hpp>
#include <MiniMPL/anyObject.hpp>
#include <MiniMPL/macroDef.h>

namespace MiniMPL
{
    template<typename B>	
    struct ClassRegisterEx;    //fw declare

    struct ClassRegister
    {
    public:         
        virtual ~ClassRegister()
        {
            removeClassRegister(this,ClassRegister::gs_pHeader,&ClassRegister::m_pNextClass);
        };
        stlString const &   getName() const {   return m_strClassName;  }

        template<typename B>    
        CTypeObjectCreater<B>*  getObjectCreater() const
        {
            ClassRegisterEx<B>* pRegister = getTypedRegister<B>();
            if (pRegister)
            {
                return pRegister->getObjectCreater();
            }
            return NULL;
        }

        template<typename B>    
        B*  tryCreateObject() const
        {
            TRACE_INFO((TXT("creating class %s\n"),m_strClassName.c_str()));
            ClassRegisterEx<B>* pRegister = getTypedRegister<B>();
            if (pRegister)
            {
                return pRegister->createObject();
            }

            AssertX(TXT("Try to create wrong object."));
            return NULL;
        }

        template<typename B>    
        ClassRegisterEx<B>*     getTypedRegister() const
        {
            if (getTypeInfo()==typeid(B))
            {
                return (ClassRegisterEx<B>*)(this);
            }
            return NULL;
        }

        virtual void    dump()
        {
            TRACE_INFO((TXT("Class name : %s\n"),m_strClassName.c_str()));
        }

    protected:        
        explicit ClassRegister(stlString const& strClassName) :m_strClassName(strClassName)
        {
            m_pNextClass    = gs_pHeader;
            gs_pHeader		= this;
        }
        virtual const type_info&    getTypeInfo() const = 0;

    public:
        const stlString         m_strClassName;     //name of class	
        ClassRegister*          m_pNextClass;       // next node pointer of list
        static ClassRegister*   gs_pHeader;         // list header 

    private:        
        ClassRegister();        
        ClassRegister( ClassRegister&);
        ClassRegister& operator=( ClassRegister&); 
    };

    inline bool registerClass(ClassRegister* pObj)
    {
        pObj->m_pNextClass          = ClassRegister::gs_pHeader;
        ClassRegister::gs_pHeader   = pObj;
        return true;
    }

    //////////////////////ClassRegisterEx<B>////////////////////////////////
    template<typename B>        //B; base class type ; 
    struct ClassRegisterEx   :   public ClassRegister
    {
    public:
        template<typename S>                        //S : struct trait type
        explicit ClassRegisterEx(stlString ClassName,CTypeObjectCreater<B>* pCreater,S obj)
            : ClassRegister(ClassName)
            , m_pCreater(pCreater)
            , m_pTrait(bindAnyObject(*new S(obj),true))
        {
            AssertX(NULL != m_pCreater);
            m_pNextClassEx    = ClassRegisterEx<B>::m_pHeaderEx;
            ClassRegisterEx<B>::m_pHeaderEx = this; 
        }

        virtual ~ClassRegisterEx()
        {
            removeClassRegister(this,ClassRegisterEx::m_pHeaderEx,&ClassRegisterEx::m_pNextClassEx);

            if (m_pCreater)
            {
                delete m_pCreater;
            }
            delete m_pTrait;
        }

        CTypeObjectCreater<B>*  getObjectCreater() const { return m_pCreater; } 
        B*  createObject() const {   return getObjectCreater()->createObject();  } 

        template<typename T> 
        bool   isTraitType() const
        {
            return (InnerDetail::TraitType<T>*)(*m_pTrait) || (InnerDetail::TraitData<T>*)(*m_pTrait);
        }

        template<typename T> 
        T const*  getTraitValue() const
        {
            InnerDetail::TraitData<T>* pTraitValue = *m_pTrait;
            if (pTraitValue)
            {
                return pTraitValue->getDat();
            }

            return NULL;
        }

        virtual const type_info&    getTypeInfo() const { return typeid(B); }

    protected:
        CTypeObjectCreater<B>*          m_pCreater;
        CAnyObject*						m_pTrait;

    public:
        static ClassRegisterEx*         m_pHeaderEx;
        ClassRegisterEx*                m_pNextClassEx;
    };    

    template<typename B>
    ClassRegisterEx<B>*     ClassRegisterEx<B>::m_pHeaderEx=NULL;
}

#endif // __CLASSREGISTER_HPP__
