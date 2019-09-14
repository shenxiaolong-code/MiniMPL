#ifndef __SMARTPOINTER_HPP__
#define __SMARTPOINTER_HPP__
/***********************************************************************************************************************
* Description         : smart pointer support. it can be replaced by customized ref counter smart pointer
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/atomic_counter.h>

namespace MiniMPL
{
    template<typename T> void checkTypeIntegrityAndDelete(T* pObj);

	template<typename T>	struct RefCountSmartPtr
	{
        typedef T element_type;     //compatibility interface
        typedef T value_type;

	public:
        RefCountSmartPtr()
            : _p(NULL)
            , _c(NULL)
        {}

		explicit RefCountSmartPtr(T* pObj) 
            : _p(pObj)
		{ 
			_c = _p ? new atomic_counter(1) : NULL; 
		}

        //copy constructor : same type, it is the one of default copy constructor 
        RefCountSmartPtr(RefCountSmartPtr const& rOther) 
            : _p(rOther.get())
            , _c(rOther.getCounterPtr())
        { 
            if (_c)
            {
                ++(*_c);
            }
        }

        //copy constructor : derive type  => Base type
        template<typename D> 
        RefCountSmartPtr(RefCountSmartPtr<D> const& rOther) 
            : _p(rOther.get())
            , _c(rOther.getCounterPtr())
        { 
            //if D is not derived from T, compile error
            if (_c)
            {
                ++(*_c);
            }
        }

		~RefCountSmartPtr()
		{
			checked_delete();
		}

        RefCountSmartPtr& operator=(RefCountSmartPtr<T> const& rOther)
		{
			if (_p==rOther.get())
			{
				return *this;
			}

			checked_delete();
			_p			= rOther.get();
			_c	= rOther.getCounterPtr();
			if (_c)
			{
				++*_c;
			}

			return *this;
		}

        template<typename D>
        RefCountSmartPtr& operator=(RefCountSmartPtr<D> const& rOther)
        {
            //if D is not derived from T, compile error
            if (_p==rOther.get())
            {
                return *this;
            }

            checked_delete();
            _p			= rOther.get();
            _c	= rOther.getCounterPtr();
            if (_p)
            {
                ++*_c;
            }

            return *this;
        }

		inline T*	operator->() const
		{
			return _p;
		}

		inline T&	operator*() const
		{
			//ChkExceptionP(NULL != m_pObj);
			return *_p;
		}

        template<typename D> 
        inline bool operator==(RefCountSmartPtr<D> const& rOther) const 
        {
            return operator==(rOther.get());
        }

        template<typename D> 
        inline bool operator!=(RefCountSmartPtr<D> const& rOther) const 
        {
            return operator!=(rOther.get());
        }

        inline bool operator==(T const* p) const
        {
            return _p==p;
        }

        inline bool operator!=(T const* p) const
        {
            return _p!=p;
        }
        
        typedef T * RefCountSmartPtr::*unspecified_bool_type;
        operator unspecified_bool_type() const
        {
            return _p ? &RefCountSmartPtr::_p : NULL;
        }
        /*
        1. disable "operator bool()" , because it will cause SmartPtr_V2 is comparable.
        example: 
        testSmartPtr<T> p1,p2;
        p1>p2 can pass compile , because it will implement below procedure:
        p1.operator bool() > p2.operator bool()
        In fact, p1>p2 should compile fails.

        2. disable "operator T*() const", becasue example:
        void testSmartPtr(SmartPtr_V2<T> obj);
        testSmartPtr(SmartPtr_V2<T>(new T())); //Note : No ref
        it will implement below procedure:
        new T()                             ==> pT;
        SmartPtr_V2::SmartPtr_V2(pT)        ==> tmpObj1;
        tmpObj1.operator T*()               ==> pT;
        SmartPtr_V2::SmartPtr_V2(pT)        ==> tmpObj2;
        testSmartPtr(tmpObj2);
        above procedure generate two SmartPtr_V2 who point to same object without ref-counter. 
        it causes memory own issue.

        it won't call copy constructor SmartPtr_V2(SmartPtr_V2& rOther) -- it is expected.
        so disable "operator T*() const" to avoid potential mistake 
        and force to call SmartPtr_V2(SmartPtr_V2& rOther) , instead of SmartPtr_V2::SmartPtr_V2(T*) 

        weakness : below implicit conversion will fails , but it can ensure correctness -- we prefer to avoid potential risk.
        SmartPtr_V2<T> rObj(new T());
        T* pT = rObj;
        */

        RefCountSmartPtr& reset(T* pNewObj)
		{
			checked_delete();
			_p	= pNewObj;
			_c = _p ? new atomic_counter(1) : NULL;
			return *this;
		}

        inline T*	get() const
        {
            return _p;
        }

        long use_count() const
        {
            return _c ? _c->m_count : 0;
        }

		inline atomic_counter*	getCounterPtr() const
		{
			return _c;
		}

        inline void checked_delete()
		{ 
			if (_c && --*_c==0)
			{
				checkTypeIntegrityAndDelete(_p);
				delete _c;                
			}
            _c   = NULL;
            _p          = NULL;
		}

	protected:
		T*                  _p;
		atomic_counter*		_c;
	};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T> void checkTypeIntegrityAndDelete(T* pObj)
    {
        typedef char testCompleteType[sizeof(T)?1:-1];      //prevent from T is forward declaration type.
        0 != sizeof(testCompleteType);                      //avoid release optimize
        delete pObj;
    }
}

#endif // __SMARTPOINTER_HPP__
