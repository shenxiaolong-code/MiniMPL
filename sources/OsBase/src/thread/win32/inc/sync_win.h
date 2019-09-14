#ifndef SYNC_WIN_H__
#define SYNC_WIN_H__
#ifdef WIN32
/***********************************************************************************************************************
Description         : implement of synchronize based on windows platform
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <wtypes.h>
#include <thread\sync.h>
#include <MiniMPL\productSpecialDef.h>

namespace OS_Win32
{
    class CSyncNotifier_Win : public CSyncNotifier
    {
    protected:
        HANDLE m_hEvent;

    public:
        CSyncNotifier_Win( stlChar const* pName=NULL );

        virtual ~CSyncNotifier_Win();

        bool sendNotification();

        bool resetNotification();

        EEventWaitResult waitNotification( unsigned int timeout = INFINITE );

        virtual bool shutdown(); 
    };

    typedef stlSmartptr<CSyncNotifier_Win> TpSyncNotifier_Win;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CSyncThread_Win : public CSyncThread
    {
    public:
        CSyncThread_Win();

        virtual ~CSyncThread_Win();

        virtual void lock();

        virtual void unlock();

    protected:
        CRITICAL_SECTION m_CriticalSection;
    };
    typedef stlSmartptr<CSyncThread_Win> TpSyncThread_Win;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CSyncProcess_Win : public CSyncProcess
    {
    public:
        CSyncProcess_Win(stlChar const* pName);

        virtual ~CSyncProcess_Win();

        virtual void lock(unsigned long timeout);
        virtual void unlock();

    protected:
        HANDLE              m_hMutex;
    };
    typedef stlSmartptr<CSyncProcess_Win> TpSyncProcess_Win;
}

#endif // WIN32
#endif // SYNC_WIN_H__
