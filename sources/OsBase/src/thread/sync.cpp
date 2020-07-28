#include <thread\sync.h>
#include <MiniMPL\macroDef.h>

CSyncNotifier*  getNewSyncNotifier(stlChar const* pName=NULL);
CSyncThread*    getNewThreadLock();
CSyncProcess*   getNewProcessLock(stlChar const* pName=NULL);

CSyncNotifier::CSyncNotifier( stlChar const* pName )
: m_impl(getNewSyncNotifier(pName))
{

}

CSyncNotifier::CSyncNotifier( CSyncNotifier* /*pImpl*/ )
{

}

CSyncNotifier::~CSyncNotifier()
{
}

bool CSyncNotifier::sendNotification()
{
    ASSERT_AND_LOG(m_impl);
    return m_impl->sendNotification();
}

bool CSyncNotifier::resetNotification()
{
    ASSERT_AND_LOG(m_impl);
    return m_impl->resetNotification();
}

bool CSyncNotifier::shutdown()
{
    if (m_impl)
    {
        return m_impl->shutdown();
    } 
    return true;
}

EEventWaitResult CSyncNotifier::waitNotification( unsigned int timeout /*= INFINITE*/ )
{
    ASSERT_AND_LOG(m_impl);
    return m_impl->waitNotification(timeout);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSyncThread& getGlobalThreadLock()
{  
    static CSyncThread  gs_serialLock(L"global CSyncThread");
    return gs_serialLock;
}

CSyncThread::CSyncThread( stlChar const* /*pName*/ )
: m_impl(getNewThreadLock())
{

}

CSyncThread::CSyncThread( CSyncThread* /*pImpl*/ )
{
}

CSyncThread::~CSyncThread()
{
}

void CSyncThread::lock()
{
    CHECK_NULL_ELSE_RETURN_VAL(m_impl,);
    m_impl->lock();
}

void CSyncThread::unlock()
{
    CHECK_NULL_ELSE_RETURN_VAL(m_impl,);
    m_impl->unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSyncProcess::CSyncProcess( stlChar const* pName )
: m_impl (getNewProcessLock(pName))
{

}

CSyncProcess::CSyncProcess( CSyncProcess* /*pImpl*/ )
{
}

CSyncProcess::~CSyncProcess()
{
}

void CSyncProcess::lock( unsigned long timeout )
{
    m_impl->lock(timeout);
}

void CSyncProcess::unlock()
{
    m_impl->unlock();
}
