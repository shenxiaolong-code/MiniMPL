#ifndef __ANYOBJECT_HPP__
#define __ANYOBJECT_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/fromToString.hpp>
#include <MiniMPL/paramPackageCall.hpp>
#include <typeinfo>

namespace MiniMPL
{
    ////////////////////////////////////////////////// Base Declaration/////////////////////////////////////////////////////////////
    /*CAnyObject suits to hold different class which have not any relation and any similarity.*/
    class CAnyObject
    {
    public:
        template<typename operatorType> operator operatorType&() const;
        template<typename operatorType> operator operatorType*() const;
        template<typename NewType> NewType cast2Type() const;   //readability interface , same as : T* pNewVal = (T*)(*this);
        virtual ~CAnyObject(){};

        virtual void  dump() const = 0 ;

    protected:
        virtual bool isTypeCastable(const type_info&) const=0;

    protected:
        CAnyObject(){};
        CAnyObject(CAnyObject const& other);
        CAnyObject& operator=(CAnyObject const& other);
    };    

    //////////////////////////////////////////////////////// Impl /////////////////////////////////////////////////////////////////
    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7> 
    struct ParamPackageCall; //fw declare

    template<typename objectType> 
    class CAnyObjectImpl : public CAnyObject
    {
    public:
        explicit CAnyObjectImpl()
            :m_pObject(new objectType())
            ,m_bAutoDelete(true)
        {}

        explicit CAnyObjectImpl(objectType& Obj,bool bAutoDelete)
            :m_pObject(&Obj)
            ,m_bAutoDelete(bAutoDelete)
        {}

        template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7> 
        explicit CAnyObjectImpl(ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7>& rObj)
            : m_bAutoDelete(true)
        {
            typedef typename TToParamPackageCall<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> >::type  TCallPack;
            m_pObject = static_cast<TCallPack&>(rObj).newObject<objectType>();
        }

        virtual ~CAnyObjectImpl()
        {           
            if (m_bAutoDelete && m_pObject)
            {
                Static_Assert(0!=sizeof(objectType));  //check complete type
                delete m_pObject;
                m_pObject   = NULL;
            }
        }

        inline objectType* getObject() const
        {
            return m_pObject;
        }

    protected:
        //CAnyObjectImpl();
        virtual bool isTypeCastable(const type_info& rType) const
        {
            return !(rType!=typeid(objectType));
        }

        virtual void  dump() const
        { 
            TRACE_INFO((TXT("Real Type : %s\n"),toString(typeid(objectType).name()).c_str()));
#if defined(_MSC_VER)
            __if_exists(objectType::dump)
            {
                m_pObject->dump();
            }
#endif
        }

    private:
        objectType*     m_pObject;            
        bool            m_bAutoDelete;          //maintain objectType instance life cycle
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename operatorType>
    CAnyObject::operator operatorType&() const
    {
        operatorType*   pObject = *this; //implement operator operatorType* 
        AssertP(pObject);
        if (NULL == pObject)
        {
            throw 1;
        }

        return *pObject;
    }

    template<typename operatorType>
    CAnyObject::operator operatorType*() const
    {
        /*! Limition : 
        the operator Type must be the same with actual type.
        operator Type can't be base class because CAnyObject isn't needed for some classes which have shared base class.
        In those cases they can use base class pointer directly, instead of  CAnyObject.
        CAnyObject suits to hold different class which have not any relation and any similarity.
        */
        if(!isTypeCastable(typeid(operatorType)))
        {
            return NULL;
        }

        return ((CAnyObjectImpl<operatorType> const*)this)->getObject();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename ObjectType>
    CAnyObject* bindAnyObject(ObjectType& object,bool bAutoDelete)
    {
        return new CAnyObjectImpl<ObjectType>(object,bAutoDelete);
    }

    template<typename NewType>
    NewType CAnyObject::cast2Type() const
    {
        return *this;
    }
}


#endif // __ANYOBJECT_HPP__
