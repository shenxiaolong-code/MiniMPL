#include <MiniMPL/atomic_counter.h>
#ifdef _WIN32
#include <windows.h>
#endif 

namespace MiniMPL
{
#if _WIN32
    atomic_counter::atomic_counter( long lOri/*=0*/ ) 
        : m_count(lOri)
    {
    }

    atomic_counter::~atomic_counter()
    {
    }

    atomic_counter::operator long() const
    {
        return m_count;
    }

    long atomic_counter::operator--()
    {
        return InterlockedDecrement(&m_count);
    }

    long atomic_counter::operator++()
    {
        return InterlockedIncrement(&m_count);
    }

    long atomic_counter::operator+=( long lDiff )
    {
        return exchangeAdd(lDiff)+lDiff;
    }

    long atomic_counter::operator-=( long lDiff )
    {
        return exchangeAdd(-lDiff)-lDiff;
    }

    long atomic_counter::reset()
    {
        return InterlockedExchange(&m_count,0);
    }

    long atomic_counter::exchangeAdd( long lDiff )
    {
        return InterlockedExchangeAdd(&m_count,lDiff);
    }
#endif // _WIN32  

}
