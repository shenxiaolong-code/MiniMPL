#include <thread\thread.h>
#include <thread\threadManager.h>
#include <MiniMPL\macroDef.h>

extern TpOSThreadCreater getNewThreadFunction();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CThreadBase::CThreadBase()
{
    CThreadMananger::getInstance().registerThread(*this);
}

CThreadBase::~CThreadBase()
{
    CThreadMananger::getInstance().unregisterThread(*const_cast<CThreadBase*>(this)); 
    if (isRunning())
    {
        stop();
    }
}

bool CThreadBase::start()
{
    ASSERT_AND_LOG(!m_pThrdFunc);
    m_pThrdFunc = getNewThreadFunction();
    ASSERT_AND_LOG(m_pThrdFunc);
    if (m_pThrdFunc)
    {
        return m_pThrdFunc->startThread(*this);
    }
    return false;    
}

bool CThreadBase::stop( unsigned int timeout/*=0xFFFFFFFE*/ )
{   
    TpOSThreadCreater pTmp ;
    {
        LockHere(m_lock);
        pTmp = m_pThrdFunc;
    }
    if (isRunning())
    {
        pTmp->waitThreadExit(timeout);
    }
    return true;
}

void CThreadBase::threadRun()
{
    run();
    LockHere(m_lock);
    m_pThrdFunc.reset();
}

ThreadID CThreadBase::getThreadId() const
{
    return (ThreadID)this;
}

bool CThreadBase::isRunning() const
{
    return NULL!=m_pThrdFunc.get();
}

void CThreadBase::run()
{
    ALWAYS_LOG_HERE_INFO(("CThreadBase::run is not overrieded!\n"));
}
