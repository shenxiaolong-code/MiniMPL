#ifndef THREADBASE_H__
#define THREADBASE_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	Thread base class , provide base thread interface
*************************************************************************************/
#include <MiniMPL\productSpecialDef.h>
#include <thread/sync.h>

typedef unsigned long   ThreadID;

struct IOSThreadCreater;
class   CThreadBase
{
public:
	CThreadBase();
	virtual ~CThreadBase();

    virtual bool    start(); 
    virtual bool    stop(unsigned int timeout=0xFFFFFFFE);
    virtual void    threadRun();

    ThreadID getThreadId() const;

    virtual bool isRunning() const;

protected:
    virtual void run()=0;    //override me or use CThread

protected:
    CSyncThread                         m_lock;
    stlSmartptr<IOSThreadCreater>       m_pThrdFunc;
};
typedef stlSmartptr<CThreadBase>        TpThreadBase;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct IOSThreadCreater
{
    virtual ~IOSThreadCreater(){};
    virtual bool startThread(CThreadBase& rCallee)=0;
    virtual bool waitThreadExit(unsigned timeoutMs=0xFFFFFFFE,bool bKillAfterTimeout=true)
    {return false;};
};

typedef stlSmartptr<IOSThreadCreater>   TpOSThreadCreater;
typedef TpOSThreadCreater               (*pThreadCreater)();
typedef pThreadCreater                  TpThreadCreater;

#endif // THREADBASE_H__
