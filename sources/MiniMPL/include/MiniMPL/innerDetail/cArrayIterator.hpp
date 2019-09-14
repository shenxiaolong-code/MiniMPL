#ifndef CARRAYITERATOR_H__
#define CARRAYITERATOR_H__
/************************************************************************************
author  :	Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
purpose :	iterator for C Array container
*************************************************************************************/
#include <MiniMPL/macro_assert.h>
#include <xutility>

namespace MiniMPL
{
    template<typename TC>
    struct _CArray_iterator
    {
         //std compatibility interface
        typedef std::random_access_iterator_tag     iterator_category;  
        typedef typename TC::value_type             value_type;

        typedef typename TC::pointer            pointer;  
        typedef typename TC::reference          reference;

        typedef _CArray_iterator                _Myt;
        typedef int                             difference_type;

        pointer     m_pE;
        TC const*   m_pC;

        _CArray_iterator(): m_pE(NULL),m_pC(NULL){}

        explicit _CArray_iterator(pointer pE,TC const* pC)
            : m_pE(pE),m_pC(pC)
        {
            ChkExceptionP(pC);
        }

        bool operator==(_Myt const& rOther) const
        {
            return m_pE == rOther.m_pE;
        }

        bool operator!=(_Myt const& rOther) const
        {
            return m_pE != rOther.m_pE;
        }

        bool operator<(_Myt const& rOther) const
        {
            return m_pE<rOther.m_pE;
        }

        bool operator<=(_Myt const& rOther) const
        {
            return !(*this > rOther);
        }

        bool operator>(_Myt const& rOther) const
        {
            return rOther < *this;
        }

        bool operator>=(_Myt const& rOther) const
        {
            return !(*this < rOther);
        }

        pointer operator->() const
        {
            ChkExceptionb(checkIterator(m_pE));
            return m_pE;
        }

        reference operator*() const
        {
            ChkExceptionb(checkIterator(m_pE));
            return *m_pE;
        }

        _Myt& operator++()
        {	// preincrement
            ++m_pE;
            return (*this);
        }

        _Myt operator++(int)
        {	// postincrement
            _Myt _Tmp = *this;
            ++*this;
            return (_Tmp);
        }

        _Myt& operator--()
        {	// predecrement
            --m_pE;
            return (*this);
        }

        _Myt operator--(int)
        {	// postdecrement
            _Myt _Tmp = *this;
            m_pE--;
            return (_Tmp);
        }

        _Myt& operator+=(difference_type _Off)
        {	// increment by integer
            m_pE += _Off;
            return (*this);
        }

        _Myt operator+(difference_type _Off) const
        {	// return this + integer
            _Myt _Tmp = *this;
            return (_Tmp += _Off);
        }

        _Myt& operator-=(difference_type _Off)
        {	// decrement by integer
            return (*this += -_Off);
        }

        _Myt operator-(difference_type _Off) const
        {	// return this - integer
            _Myt _Tmp = *this;
            return (_Tmp -= _Off);
        }

        difference_type operator-(const _Myt& _Right) const
        {	// return difference of iterators
            return m_pE-_Right.m_pE;
        }

        reference operator[](difference_type _Off) const
        {	// subscript
            return (*(*this + _Off));
        }

        bool checkIterator(pointer pE) const
        { 
            return pE && m_pC && m_pC->size()>0 && pE>=&m_pC->m_rObj[0] && m_pE<m_pC->_MyGuard.m_pE;
        }
    };
}

#endif // CARRAYITERATOR_H__
