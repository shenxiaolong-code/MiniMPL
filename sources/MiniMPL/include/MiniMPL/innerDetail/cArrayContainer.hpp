#ifndef CARRAYCONTAINER_H__
#define CARRAYCONTAINER_H__
/************************************************************************************
author  :	Shen Tony,2009-2017
verified: 	VS2008	
purpose :	
*************************************************************************************/
#include <MiniMPL/addRemove.hpp>
#include <MiniMPL/isXXX.hpp>
#include <MiniMPL/arrayTrait.hpp>
#include <MiniMPL/valueCompare.hpp>
#include <MiniMPL/innerDetail/cArrayIterator.hpp>
#include <MiniMPL/macro_class.h>

namespace MiniMPL
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct STLContainerInterface
    {   //same with std::vector        
        typedef   RAWTYPE(T)                                        _Val;
        typedef typename If_Evl<IsConst<T>,_Val const,_Val>::type   value_type;
        typedef typename AddConst<value_type>::type                 const_value_type;

        typedef   typename AddRef<value_type>::type                 reference;
        typedef   typename AddRef<const_value_type>::type           const_reference;

        typedef size_t                size_type;
        typedef unsigned __int32      difference_type;      
    };

    template<typename T>
    struct ConstArray : public STLContainerInterface<typename ArrayValueType<T>::type>
    {
        enum {TLEN=ArraySize<T>::value};
        typedef   T                                 _TArray;
        typedef   typename AddRef<_TArray>::type    _TArrayRef;

        typedef   value_type*                       pointer;
        typedef   const_value_type*                 const_pointer;

        typedef _CArray_iterator<ConstArray>        const_iterator;
#if     CONST_CONTAINER_HAS_ITERATOR 
        typedef _CArray_iterator<ConstArray>        iterator;
#endif

        friend struct const_iterator;

        //size_type       m_size;
        const_iterator      _MyGuard;
        _TArrayRef          m_rObj;

        ConstArray(_TArrayRef rObj,size_type iSize)
            :m_rObj(rObj)
        {
            ASSERT_AND_LOG(iSize <= TLEN);
            _MyGuard = const_iterator(&rObj[0]+LimitVal(iSize,0,TLEN),this);
        };

        ConstArray(ConstArray const& rOther)
            : m_rObj(rOther.m_rObj)            
        {                          
            _MyGuard = const_iterator(rOther._MyGuard.m_pE,this);
        }

        size_type size() const
        {
            return _MyGuard.m_pE-m_rObj;
        }

        const_iterator begin() const
        { 
            return size()>0 ? const_iterator(&m_rObj[0],this) : end();
        }

        const_iterator end() const
        {
            return _MyGuard;
        }

        reference front() const throw(...)
        {
            ChkExceptionInfo(size()>0,(TXT("front() on empty container")));
            return *begin();
        }

        reference back() const throw(...)
        {
            ChkExceptionInfo(size()>0,(TXT("back() on empty container")));
            return *(_MyGuard-1);
        }

        reference operator[](size_type _Off) const
        {	
            ChkExceptionInfo(_Off<size(),(TXT("index is out of array range")));
            return m_rObj[_Off];
        }

        Disable_Class_Assign(ConstArray);
    };

    template<typename T>
    struct ModifiableArray : public ConstArray<T>
    {
        typedef typename ConstArray::_TArrayRef     _TArrayRef;
        typedef typename ConstArray::size_type      size_type;   

#if     0==CONST_CONTAINER_HAS_ITERATOR 
        typedef _CArray_iterator<ConstArray>        iterator;
#endif

        ModifiableArray(_TArrayRef rObj,size_type iSize)
            :ConstArray(rObj,iSize)
        {};

        iterator begin()
        {
            return size() > 0 ? const_iterator(&m_rObj[0], this) : end();
        }

        iterator end()
        {
            return _MyGuard;
        }

        size_type capacity() const
        {   //const container has not capacity concept, only has size()
            return TLEN;
        }

        //No return value , need throw if exception
        void push_back(const_reference rVal) throw(...)
        {   //I am not thread-safe because of performance, need user to add lock externally
            ChkExceptionInfo(size()<capacity(),(TXT("push_back() on full container")));
            new ((void*)(&m_rObj[size()])) _Val(rVal);
            _MyGuard++;
        }

        void clear()
        {
            if (0==size())
            {
                return;
            }
            iterator it=--end();
            while(it>=begin())
            {
                it.m_pE->~value_type();
                it--;
            }
            _MyGuard=iterator(m_rObj,this);
        }

        iterator erase(pointer _where)
        {
            return erase(iterator(_where,this));
        }

        iterator erase(iterator _Where)
        {
            CHECK_EQUAL_ELSE_ASSERT_RETURN_VAL(_Where>=begin()&&_Where<end(),false,_Where,(TXT("pointer is out of array range.")));

            iterator retVal = _Where;
            iterator guard  = end()-1;
            for (;_Where != guard;++_Where)
            {
                _Where->~value_type();
                new ((void*)_Where.m_pE) value_type(*(_Where+1));
            }
            guard.m_pE->~value_type();

            --_MyGuard;
            return retVal;
        }

        //check return value to avoid throw exception
        iterator insert(const_pointer _Where, const_reference rVal)
        {   //I am not thread-safe because of performance, need user to add lock externally
            CHECK_EQUAL_ELSE_ASSERT_RETURN_VAL(size()<TLEN,false,end(),(TXT("insert() on full container")));
            CHECK_EQUAL_ELSE_ASSERT_RETURN_VAL((_Where>&m_rObj[0] && _Where<=&m_rObj[size()]),false,end(),(TXT("insert() on invalid position")));

            for (const_pointer it=_MyGuard.m_pE;it>_Where;--it)
            {
                new((void*)it) _Val(*(it-1)); //move to later, we can't assume element support memory move
                (it-1)->~value_type();                
            }
            new ((void*)_Where) _Val(rVal);  //fill element in actual position

            _MyGuard++;
            return iterator(const_cast<pointer>(_Where),this)-1;
        }

        template<typename TC>
        iterator insert(_CArray_iterator<TC> const& _Where, const_reference rVal)
        {
            CHECK_EQUAL_ELSE_ASSERT_RETURN_VAL(size()<TLEN,false,end(),(TXT("insert() on full container")));
            CHECK_TRUE_ELSE_RETURN_VAL((_Where.m_pE > m_rObj && _Where.m_pE<=_MyGuard.m_pE ),end());
            //_Where, const_reference rVal
            return insert(_Where.m_pE,rVal);
        }

        iterator insert(size_type posi, const_reference rVal)
        {   //I am not thread-safe because of performance, need user to add lock externally
            CHECK_EQUAL_ELSE_ASSERT_RETURN_VAL(size()<TLEN,false,end(),(TXT("insert() on full container")));
            CHECK_EQUAL_ELSE_ASSERT_RETURN_VAL(posi<=size(),false,end(),(TXT("insert() on invalid position")));
            return insert(&m_rObj[posi],rVal);
        }
    };

    //if T is const, it will has not member function push_back / insert
    //using push_back will cause compile error : 'push_back' : is not a member of 'MiniMPL::TStdContainer<Stl_T>'
    template<typename T>
    struct CArrayBase : public If_Evl<IsConst<T>,ConstArray<T>,ModifiableArray<T> >::type
    {  
        typedef typename If_Evl<IsConst<T>,ConstArray<T>,ModifiableArray<T> >::type     _ContainerBase;
        typedef typename _ContainerBase::_TArrayRef     _TArrayRef;
        typedef typename _ContainerBase::size_type      size_type;

        CArrayBase(_TArrayRef rObj,size_type iSize)
            :_ContainerBase(rObj,iSize) {};
    };
}

#endif // CARRAYCONTAINER_H__
