#ifndef __ATOMIC_COUNTER_H__
#define __ATOMIC_COUNTER_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/

namespace MiniMPL
{
#ifdef _WIN32
    class  atomic_counter
    {
    public:
        atomic_counter(long lOri=0);

        ~atomic_counter();

        operator long() const;

        long operator--();

        long operator++();

        long operator-=(long lDiff);

        long operator+=(long lDiff);

        long reset();

    protected:
        long exchangeAdd(long lDiff);

    private:
        atomic_counter(atomic_counter const& rOther);
        atomic_counter& operator=(atomic_counter const& rOther);

    public:
        volatile	long m_count;
    };
#else  // _WIN32 else
    ALWAYS_COMPILE_MSG("************** Waring : atomic_counter is not implemented! **************")
        typedef long atomic_counter;
#endif // _WIN32
}


#endif // __ATOMIC_COUNTER_H__
