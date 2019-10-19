#include <network_win/clientPeerManager.h>
#include <network_win/WinSocketTcpClientPeer.h>
#include <thread/asyncCall.h>
#include <MiniMPL/stdAlgorithmEx.hpp>
#include <MiniMPL/tester.hpp>
#include "MiniMPL/unaryFunctionCreater.hpp"
#include "inc/sockReceiver_newThread.h"
#include "inc/sockReceiver_completePort.h"
#include "inc/sockReceiver_overlapPort.h"

namespace OS_Win32
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CClientPeerManager::CClientPeerManager()
    {

    }

    CClientPeerManager::~CClientPeerManager()
    {
        m_clientPeerMonitors.clear();

        if (m_clientPeers.size()>0)
        {
            TPeerArray tmp;
            std::swap(tmp,m_clientPeers);
            for (TPeerArray::iterator it=tmp.begin();it!=tmp.end();++it)
            {
                delete it->first;
            }
            tmp.clear();
        }
        
    }

    bool CClientPeerManager::registerMonitor( IClientPeerMonitor& rMonitor )
    {
        using namespace MiniMPL;
        CHECK_TRUE_ELSE_RETURN_VAL(NULL!=MiniMPL::find(m_clientPeerMonitors,makeUnaryTester(&rMonitor,CEqual())),true);
        m_clientPeerMonitors.push_back(&rMonitor);
        return true;
    }

    bool CClientPeerManager::unregisterMonitor( IClientPeerMonitor& rMonitor )
    {
        IClientPeerMonitor* p=&rMonitor;
        MiniMPL::eraseUnsortedArray(m_clientPeerMonitors,p);
        return true;
    }

    bool CClientPeerManager::registerClientPeer( WinSocketTcpClientPeer& rPeer,WinSocketTCPServer* pOwnerServer )
    {
        using namespace MiniMPL;

        CHECK_TRUE_ELSE_RETURN_VAL(NULL==MiniMPL::find(m_clientPeers,makeUnaryTester_Result(&TPeerInfo::first,&rPeer,CEqual())),false);

        for (stlVector<IClientPeerMonitor*>::iterator it=m_clientPeerMonitors.begin();
            it != m_clientPeerMonitors.end();++it)
        {
            if (NULL == (*it)->m_pServer || pOwnerServer==(*it)->m_pServer)
            {
                (*it)->onClientConnected(rPeer);
            }
        }

        m_clientPeers.push_back(std::make_pair(&rPeer,pOwnerServer));
        return true;
    }

    bool CClientPeerManager::unregisterClientPeer( WinSocketTcpClientPeer& rPeer )
    {
        for (TPeerArray::iterator it1=m_clientPeers.begin();it1!=m_clientPeers.end();++it1)
        {
            if ((*it1).first==&rPeer)
            {           
                for (stlVector<IClientPeerMonitor*>::iterator it2=m_clientPeerMonitors.begin();
                    it2 != m_clientPeerMonitors.end();++it2)
                {
                    if (NULL ==(*it2)->m_pServer ||  (*it1).second == (*it2)->m_pServer)
                    {
                        (*it2)->onClientDisconnected(rPeer);
                    }
                }

                MiniMPL::eraseUnsortedArray(m_clientPeers,*it1);
                break;
            }
        }
        return true;
    }

    bool CClientPeerManager::delegateRecv( WinSocketTcpClientPeer& rPeer, DelegateMode iMode)
    {
		if (m_delegateReceivers.find(&rPeer)!= m_delegateReceivers.end())
		{
			return false;
		}

		TpWinSockDelegateReceiver pReceiver;
		switch (iMode)
		{
		case Delegate_newThread:
			pReceiver = TpWinSockDelegateReceiver(new CWinSockDelegateReceiver_newThread());
			break;
		case Delegate_IOCP:
			pReceiver = TpSharedRecvThread(new CWinSockDelegateReceiver_IOCP());
			break;
		case Delegate_Overlap:
			pReceiver = TpSharedRecvThread(new CWinSockDelegateReceiver_EventSelect());
			break;
		default:
			break;
		}
		if (pReceiver)
		{
			pReceiver->delegateRecv(rPeer);
		}
		m_delegateReceivers.insert_or_assign(&rPeer,pReceiver);
        return true;
    }

    bool CClientPeerManager::undelegateRecv( WinSocketTcpClientPeer& rPeer )
    {
		auto pReceiver = m_delegateReceivers.find(&rPeer);
		if (pReceiver == m_delegateReceivers.end())
		{
			return false;
		}
		pReceiver->second->undelegateRecv(rPeer);
		m_delegateReceivers.erase(pReceiver);
        return true;
    }

}

