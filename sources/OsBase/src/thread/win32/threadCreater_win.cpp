#ifdef WIN32
#include "inc\threadCreater_win.h"
#include "inc\sync_win.h"

extern TpOSThreadCreater getNewThreadFunction()
{
    if (OS_Win32::g_userThreadCreater_win)
    {
        return OS_Win32::g_userThreadCreater_win();
    }
    return  TpOSThreadCreater(new OS_Win32::COSThreadCreater_Win());
}

namespace OS_Win32
{
    TpThreadCreater     g_userThreadCreater_win = NULL;
    struct ThreadParam
    {
        CSyncNotifier_Win   m_notify;
        CThreadBase*        m_threadBase;
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //reference API CreateThreadpool family in MSDN and its example.
    //consider below thread resource : TLS, security contexts, thread priority, and COM registration
    COSThreadCreater_Win::COSThreadCreater_Win()
        : m_thrdId(0)
        , m_ThrdHandle(INVALID_HANDLE_VALUE)
    {
    }

    COSThreadCreater_Win::~COSThreadCreater_Win()
    {

    }

    bool COSThreadCreater_Win::startThread( CThreadBase& rCallee )
    {
        ThreadParam oP;
        oP.m_threadBase = &rCallee;
        m_ThrdHandle = ::CreateThread(0, 0, COSThreadCreater_Win::threadFunction, &oP, CREATE_SUSPENDED, &m_thrdId );
        if (NULL != m_ThrdHandle)
        {
            ResumeThread(m_ThrdHandle);
            oP.m_notify.waitNotification();            
        }
        return NULL != m_ThrdHandle;
    }

    unsigned long __stdcall COSThreadCreater_Win::threadFunction( void far *LPVOID )
    {
        ThreadParam* pP = static_cast<ThreadParam*>(LPVOID);
        CThreadBase* pCallee = pP->m_threadBase;
        pP->m_notify.sendNotification();
        pCallee->threadRun();
        return 0;
    }

    bool COSThreadCreater_Win::waitThreadExit( unsigned timeoutMs,bool bKillAfterTimeout )
    {
        if (INVALID_HANDLE_VALUE==m_ThrdHandle)
        {
            return true;
        }

        if (WAIT_OBJECT_0!=::WaitForSingleObject(m_ThrdHandle,timeoutMs) && bKillAfterTimeout)
        {
            TerminateThread(m_ThrdHandle,-1);
            CloseHandle(m_ThrdHandle);      //free thread resource when terminate
            m_ThrdHandle = INVALID_HANDLE_VALUE;
            m_thrdId     = 0;
        }
        return true;
    }
}


#endif // WIN32



