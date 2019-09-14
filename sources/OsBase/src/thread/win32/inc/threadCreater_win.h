#ifndef __THREADCREATER_WIN_H__
#define __THREADCREATER_WIN_H__
#ifdef WIN32
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	thread base-on windows platform
*************************************************************************************/
#include <thread/threadbase.h>
#include <Windows.h>

namespace OS_Win32
{
    extern  TpThreadCreater     g_userThreadCreater_win; //default is NULL
    typedef void*               ThreadHandle;

    class COSThreadCreater_Win : public IOSThreadCreater
    {
    public:
        COSThreadCreater_Win();
        virtual ~COSThreadCreater_Win();
        virtual bool startThread(CThreadBase& rCallee);
        virtual bool waitThreadExit( unsigned timeoutMs,bool bKillAfterTimeout );

    protected:
        static unsigned long __stdcall threadFunction(void far *LPVOID);

    protected:
        DWORD               m_thrdId;
        ThreadHandle        m_ThrdHandle;
    };
}

#endif // WIN32

#endif // __THREADCREATER_WIN_H__
