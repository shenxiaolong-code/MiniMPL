#include <communicator/ICommunicator.h>
#include <MiniMPL/stdAlgorithmEx.hpp>
#include <MiniMPL/unaryFunctionCreater.hpp>
#include <thread/sync.h>

ICommunicator::~ICommunicator()
{
}

bool ICommunicator::registerReceiver( TpReceiver pReceiver )
{
    CSyncLocker<CSyncThread> guard(getGlobalThreadLock());
    push_back(pReceiver);
    return true;
}

bool ICommunicator::unregisterReceiver( IReceiver* pReceiver )
{
    for (iterator it=begin();it!=end();++it)
    {
        if (it->get()==pReceiver)
        {
            CSyncLocker<CSyncThread> guard(getGlobalThreadLock());
            MiniMPL::eraseUnsortedArray(*this,*it);
            return true;
        }
    }
    return false;
}

void ICommunicator::onConnected()
{
}

void ICommunicator::onDisconnected()
{
}

void ICommunicator::onDataReceivced( CCommBuffer const& rBuf )
{
    if (size()>0)
    {
        using namespace MiniMPL;
        MiniMPL::forEach(*this,makeUnaryFunction(&IReceiver::onReceive,_$,rBuf));
    }
}
