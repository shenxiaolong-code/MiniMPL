#ifndef __DYNAMICBUFFER_HPP__
#define __DYNAMICBUFFER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/swap.hpp>

#define AlignDown(N,R)      (N&~(R-1))
#define AlignUp(N,R)        ((N+R-1)&~(R-1) )

template<typename T,bool bExactSize=false>
class TDynamicBuffer
{
    friend void swap(TDynamicBuffer& r1,TDynamicBuffer& r2);
public:
    typedef T                   TElement;
    typedef TElement*           iterator;
    typedef TElement const*     const_iterator;

    TDynamicBuffer()
        :m_bAttached(false)
        ,m_pBuf(NULL)
        ,m_capacity(0)
        ,m_size(0)
    {};

    TDynamicBuffer(TDynamicBuffer const& rOther)
    {
        m_bAttached = rOther.m_bAttached;
        m_capacity  = rOther.m_capacity;
        m_size      = rOther.m_size;
        if (m_bAttached)
        {
            m_pBuf = rOther.m_pBuf;
        }
        else
        {
            m_pBuf = new TElement[m_capacity];
            memcpy(m_pBuf,rOther.m_pBuf,m_size);
        }
    }

    TDynamicBuffer& operator=(TDynamicBuffer const& rOther)
    {
        if (&rOther != this && m_pBuf != rOther.m_pBuf)
        {
            memcpy(getBuffer(rOther.m_size),rOther.m_pBuf,rOther.m_size);
            m_size = rOther.m_size;
        }
        return *this;
    }

    virtual ~TDynamicBuffer()
    {
        freeMemory();
    }

    bool attachBuf(iterator pBuf,unsigned iSize)
    {                     
        freeMemory();
        m_bAttached = true;
        m_pBuf = pBuf;
        m_size = iSize;
        m_capacity = 0;
        return true;
    }

    const_iterator getBuffer() const
    {
        return m_pBuf;
    }

    unsigned getCapacity() const
    {
        return m_capacity;
    }

    iterator getBuffer(unsigned iNewSize)
    {
        if (m_capacity>=iNewSize)
        {
            return m_pBuf;
        }

        freeMemory();
        m_capacity = bExactSize ? iNewSize : AlignUp(iNewSize,8);
        m_pBuf = new TElement[m_capacity];
        memset(m_pBuf,0,m_capacity);
        m_size = 0;
        m_bAttached = false;
        return m_pBuf;
    }

    unsigned getSize() const
    {
        return m_size;
    }

    bool setSize(unsigned iNewSize)
    {
        CHECK_TRUE_ELSE_RETURN_VAL(!m_bAttached && iNewSize<=m_capacity,false);
        m_size = iNewSize;
        return true;
    }

    iterator        begin()         { return m_pBuf;}
    const_iterator  begin() const   { return m_pBuf;}
    iterator        end()           { return m_pBuf ? m_pBuf+m_size : NULL;}
    const_iterator  end() const     { return m_pBuf ? m_pBuf+m_size : NULL;}

protected:
    void freeMemory()
    {
        if (!m_bAttached && m_pBuf)
        {                         
            delete [] m_pBuf;
            m_pBuf = NULL;
            m_capacity = 0;
            m_size = 0;
        }
    }

    bool        m_bAttached;
    unsigned    m_capacity;
    unsigned    m_size;
    TElement*   m_pBuf;
};

template<typename T>
void swap(TDynamicBuffer<T>& r1,TDynamicBuffer<T>& r2)
{
    MiniMPL::swap(r1.m_bAttached,r2.m_bAttached);
    MiniMPL::swap(r1.m_capacity,r2.m_capacity);
    MiniMPL::swap(r1.m_size,r2.m_size);
    MiniMPL::swap(r1.m_pBuf,r2.m_pBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct CRingBuf  : public TDynamicBuffer<T,true>
{  
    CRingBuf(unsigned iSize)
    {
        getBuffer(iSize);
    }

    T& operator[](unsigned idx)
    {
        ASSERT_AND_LOG(getSize()==getCapacity() || (idx>0 && idx <getSize()) );
        return m_pBuf[(m_capacity+(idx%m_capacity))%m_capacity];  //idx might be lesser than 0
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // __DYNAMICBUFFER_HPP__
