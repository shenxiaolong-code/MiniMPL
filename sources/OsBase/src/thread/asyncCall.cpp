#include <thread\asyncCall.h>
#include <thread\thread.h>
#include <MiniMPL\productSpecialDef.h>
#include <thread\sync.h>
#include <queue>

struct AsyncExecutor : protected std::queue<MiniMPL::TpCallbacker>,public CThreadBase
{
    AsyncExecutor()
    {
        start();
    }
    ~AsyncExecutor()
    {   
        m_jobNotifier.shutdown();  //generate eventWaitResultError
        stop();
        clearJobs();
    }

    virtual void run()
    {
        while(eventWaitResultError != m_jobNotifier.waitNotification())
        {
            while(size()>0)
            {
                MiniMPL::TpCallbacker pJob = getJob();
                if (pJob)
                {
                    pJob->execute();
                }
            }
        }
    }

    MiniMPL::TpCallbacker getJob()
    {     
        MiniMPL::TpCallbacker pJob;
        LockHere(m_queueUpdate);
        size_type iSize = size();
        if (iSize>0)
        {
            pJob = front();
            pop();
        }

        if (1==iSize)
        {
            m_jobNotifier.resetNotification();
        }

        return pJob;
    }

    void addJob(MiniMPL::TpCallbacker const& pCallback)
    {
        LockHere(m_queueUpdate);
        push(pCallback);
        if (1==size())
        {
            m_jobNotifier.sendNotification();
        }
    }

    void clearJobs()
    {
       LockHere(m_queueUpdate);
       while(!empty())
       {
           pop();
       }       
    }

    CSyncThread             m_queueUpdate;
    CSyncNotifier           m_jobNotifier;
};

stlSmartptr<AsyncExecutor> g_asyncExecutor;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CNewThread should be created by new operator , it will be deleted by itself after thread function complete
//user shouldn't delete it explicitly.
class CNewThread : public CThread
{
protected:
    virtual void threadRun()
    {
        CThread::threadRun();
        delete this;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void asyncExecute( MiniMPL::TpCallbacker const& pCallback,EAsyncMode eMode/*=EAsync_ShareAuto*/ )
{
    CHECK_NULL_ELSE_RETURN_VAL(pCallback,);
    if (eMode<EAsync_NewThread || eMode > EAsync_ShareMaxThreadIdx)
    {
        ASSERT_AND_LOG_INFO(0,(TXT("wrong EAsyncMode value=%d"),eMode));
        eMode = EAsync_ShareAuto;
    }

    if (EAsync_NewThread == eMode)
    {  
        CNewThread* pNewThread = new CNewThread();
        pNewThread->setCallback(pCallback);
        pNewThread->start();
    }
    else
    {   
        if (EAsync_ShareAuto==eMode)
        {
            if (!g_asyncExecutor)
            {
                g_asyncExecutor.reset(new AsyncExecutor());
            }

            g_asyncExecutor->addJob(pCallback); 
        }
        else
        {
            //unsigned thrdIdx = eMode-EAsync_ShareFixTheadIdx;
            ASSERT_AND_LOG_INFO(0,(TXT("TODO")));
            ALWAYS_COMPILE_MSG("TODO : EAsync_ShareFixTheadIdx is not implemented");
        }         
    }       
}

void discardJobs()
{
    if (g_asyncExecutor)
    {
        g_asyncExecutor->clearJobs();
    }
}

