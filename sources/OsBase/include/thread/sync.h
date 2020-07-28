#ifndef SYNC_H__
#define SYNC_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	event synchronize
*************************************************************************************/
#include <MiniMPL\productSpecialDef.h>
#include <MiniMPL\macro_class.h>
#include <MiniMPL\macro_makeVar.h>
#include <MiniMPL/macro_traceLog.h>

#ifndef INFINITE
  #define INFINITE            0xFFFFFFFF  // Infinite timeout
#endif

enum EEventWaitResult
{
    eventWaitResultOk       = 1 ,   //!< waiting thread was release because the event was signaled.
    eventWaitResultTimeout      ,   //!< waiting thread was released but event was not signaled
    eventWaitResultError            //!< unspecified error
};

class CSyncNotifier
{
public:
    CSyncNotifier(stlChar const* pName=NULL);
    virtual ~CSyncNotifier();

    virtual bool sendNotification();
    virtual bool resetNotification();

    virtual bool shutdown();

    virtual EEventWaitResult waitNotification(unsigned int timeout = INFINITE);

protected:
    //derive class call to avoid endless loop
    CSyncNotifier(CSyncNotifier* pImpl);

private:
    stlSmartptr<CSyncNotifier>  m_impl;

private:
    Disable_Class_Copy_Constructor(CSyncNotifier);
    Disable_Class_Assign(CSyncNotifier);
}; // win32event  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSyncThread
{
public:
    CSyncThread(stlChar const* pName=NULL);
    virtual ~CSyncThread();
    virtual void lock();
    virtual void unlock();

protected:
    CSyncThread(CSyncThread* pImpl);

    Disable_Class_Copy_Constructor(CSyncThread);
    Disable_Class_Assign(CSyncThread);

protected:
    stlSmartptr<CSyncThread> m_impl;;
};

CSyncThread& getGlobalThreadLock(); //for rarely exclusion
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSyncProcess
{
public:
    CSyncProcess(stlChar const* pName=NULL);
    virtual ~CSyncProcess();
    virtual void lock(unsigned long timeout=INFINITE);
    virtual void unlock();

protected:
    CSyncProcess(CSyncProcess* pImpl);

private:
    Disable_Class_Copy_Constructor(CSyncProcess);
    Disable_Class_Assign(CSyncProcess);

protected:
    stlSmartptr<CSyncProcess> m_impl;;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CSyncLockerBase 
{
	virtual ~CSyncLockerBase	() {};
};
typedef const CSyncLockerBase&    CLocker;

template<typename T=CSyncThread>
class CSyncLocker  : public CSyncLockerBase
{
public:
    CSyncLocker(T& synchronizer): m_synchronizer(synchronizer)
    {
        TRACE_INFO(("lock\n"));
        m_synchronizer.lock();
    }
    ~CSyncLocker()
    {
        TRACE_INFO(("unlock\n\n"));
        m_synchronizer.unlock();
    }

private:
    //Disable_Class_Copy_Constructor(CSyncLocker);
    Disable_Class_Assign(CSyncLocker);

protected:
    T& m_synchronizer;
};

template<typename T> inline CSyncLocker<T> makeLocker(T& locker)
{
    return CSyncLocker<T>(locker);
}

#define LockHere(x) CLocker MAKEVAR2(guard,__LINE__)=makeLocker( x );MAKEVAR2(guard,__LINE__)

#endif // SYNC_H__
