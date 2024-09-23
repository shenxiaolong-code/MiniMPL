#include <UT_material/tc_def_thread.h>
#include <thread/threadManager.h>
#include <thread/asyncCall.h>
#include <Windows.h>

void UnitTest::tc_thread::run()
{
    ALWAYS_LOG_HERE();
    m_number +=1;
    m_wait.sendNotification();
}

void UnitTest::waitAllThreadExit( unsigned iLocalThreadNum )
{
    CThreadMananger &rInst= CThreadMananger::getInstance();
    while( rInst.size() >iLocalThreadNum+THREAD_NUMBER_IN_POOL) //local thread object + g_asyncExecutor
    {
        Sleep(500);
        iLocalThreadNum++;  //TODO fix
    }
}
