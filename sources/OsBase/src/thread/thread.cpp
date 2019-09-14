#include <thread/thread.h>

CThread::CThread() : CThreadBase()
{   
}

CThread::~CThread()
{
}

bool CThread::setCallback( MiniMPL::TpCallbacker const& pCallee )
{
    if (isRunning())
    {
        stop();
    }

    m_callee = pCallee;
    return true;
}

void CThread::run()
{
    if (m_callee)
    {
        m_callee->execute();
    }
}
