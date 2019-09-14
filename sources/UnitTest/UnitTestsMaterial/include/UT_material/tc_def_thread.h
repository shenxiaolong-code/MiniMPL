#ifndef TC_DEF_THREAD_H__
#define TC_DEF_THREAD_H__
/************************************************************************************
author  :	Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
purpose :	
*************************************************************************************/
#include <thread/thread.h>

namespace UnitTest
{
    struct tc_thread: public CThreadBase
    {
        virtual void run();

        CSyncNotifier     m_wait;
        int m_number;
    };

    void waitAllThreadExit(unsigned iLocalThreadNum);
}

#endif // TC_DEF_THREAD_H__
