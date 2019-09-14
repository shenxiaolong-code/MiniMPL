#ifdef WIN32
#include "inc\sync_win.h"
#include <MiniMPL\macroDef.h>

CSyncNotifier* getNewSyncNotifier(stlChar const* pName=NULL)
{
    return new OS_Win32::CSyncNotifier_Win(pName);
};
CSyncThread* getNewThreadLock()
{
    return new OS_Win32::CSyncThread_Win();
};
CSyncProcess* getNewProcessLock(stlChar const* pName=NULL)
{
    return new OS_Win32::CSyncProcess_Win(pName);
};

namespace OS_Win32
{
#pragma warning(disable:4355)
    CSyncNotifier_Win::CSyncNotifier_Win( stlChar const* pName/*=NULL*/ )
        : CSyncNotifier(this)
    {
        m_hEvent = ::CreateEvent(NULL, TRUE, FALSE, pName);
        ASSERT_AND_LOG(m_hEvent != NULL);
    }

    CSyncNotifier_Win::~CSyncNotifier_Win()
    {
        if (m_hEvent)
        {
            shutdown();
        }
    }

    bool CSyncNotifier_Win::sendNotification()
    {
        ASSERT_AND_LOG(m_hEvent != NULL);
        return ::SetEvent(m_hEvent) ? true :false;
    }

    bool CSyncNotifier_Win::resetNotification()
    {
        ASSERT_AND_LOG(m_hEvent != NULL);
        return ::ResetEvent(m_hEvent) ? true :false;
    }

    EEventWaitResult CSyncNotifier_Win::waitNotification( unsigned int timeout /*= INFINITE*/ )
    {
        unsigned dwRetVal = ::WaitForSingleObject(m_hEvent,timeout);
        switch (dwRetVal)
        {
        case WAIT_OBJECT_0:
            return eventWaitResultOk;

        case WAIT_TIMEOUT:
            return eventWaitResultTimeout;

        case WAIT_FAILED:
        default:
            return eventWaitResultError;
        } // switch
    }

    bool CSyncNotifier_Win::shutdown()
    {
        ASSERT_AND_LOG(m_hEvent != NULL);
        if (m_hEvent != NULL)
        {
            //::SetEvent(m_hEvent);
            ::CloseHandle(m_hEvent);
        }
        m_hEvent = NULL;
        return true;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CSyncThread_Win::CSyncThread_Win()
        : CSyncThread(this)
    {
        ::InitializeCriticalSection(&m_CriticalSection);
    }

    CSyncThread_Win::~CSyncThread_Win()
    {
        ::DeleteCriticalSection(&m_CriticalSection);
    }

    void CSyncThread_Win::lock()
    {
        ::EnterCriticalSection(&m_CriticalSection);
    }

    void CSyncThread_Win::unlock()
    {
        ::LeaveCriticalSection(&m_CriticalSection);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CSyncProcess_Win::CSyncProcess_Win( stlChar const* pName )
        : CSyncProcess(this)
    {
        m_hMutex = ::CreateMutex(NULL, NULL, pName);
        ASSERT_AND_LOG(m_hMutex != NULL);
    }

    CSyncProcess_Win::~CSyncProcess_Win()
    {
        ::CloseHandle(m_hMutex);
        m_hMutex = NULL;
    }

    void CSyncProcess_Win::lock( unsigned long timeout )
    {
        ASSERT_AND_LOG(::WaitForSingleObject(m_hMutex, timeout) == WAIT_OBJECT_0);
    }

    void CSyncProcess_Win::unlock()
    {
        ASSERT_AND_LOG(::ReleaseMutex(m_hMutex) != 0);
    }
}

#endif //WIN32


