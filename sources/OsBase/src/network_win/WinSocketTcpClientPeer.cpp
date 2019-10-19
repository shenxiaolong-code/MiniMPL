#include <network_win/WinSocketTcpClientPeer.h>
#include <network_win/WinSocketTCPServer.h>
#include <MiniMPL/callbacker.hpp>
#include <network_win/clientPeerManager.h>
#include <thread/asyncCall.h>

namespace OS_Win32
{
    WinSocketTcpClientPeer::WinSocketTcpClientPeer(SOCKET s, sockaddr const& sa)
        : WinSocketTCP(s) , m_receiveMode(Delegate_newThread)
    {
        m_peerAddr  = sa;
        ASSERT_AND_LOG(INVALID_SOCKET != m_sock);
    }

    WinSocketTcpClientPeer::~WinSocketTcpClientPeer(void)
    {       
        if (isAvailableSock())
        {
            stop();
        }
        //WSACloseEvent(m_event);
        CClientPeerManager::getInstance().unregisterClientPeer(*this);
    }

    WinSocket::EConnect WinSocketTcpClientPeer::getConnectType()
    {
        return EConnect_Client_Peer;
    }

    bool WinSocketTcpClientPeer::getPeerIpPort( HostAddr& ha )
    {
        sockaddr_in sa;
        sa.sin_family =AF_INET;
        int iLen = sizeof(sa);
        if (0==getsockname(m_sock,(sockaddr*)&sa,&iLen))
        {
            unsigned short port;
            WinSocketTCP::getPort(sa, port);
            ha.m_port = port;
            WinSocketTCP::getIP(sa, ha.m_ip);
            return true;
        }
        return false;
    }

	bool WinSocketTcpClientPeer::setReceiveMode(DelegateMode recvMode)
	{
		m_receiveMode = recvMode;
		return true;
	}

	bool WinSocketTcpClientPeer::start()
    {
        onConnected();
		return CClientPeerManager::getInstance().delegateRecv(*this, m_receiveMode);
    }

    bool WinSocketTcpClientPeer::stop()
    {
        WinSocketTCP::close();
        return CClientPeerManager::getInstance().undelegateRecv(*this);
    }

    /*
    bool WinSocketTcpClientPeer::onClientNetworkEvent( WSANETWORKEVENTS const& evt )
    {
        if (evt.lNetworkEvents & FD_CLOSE)
        {
            if (evt.iErrorCode[FD_CLOSE_BIT] == 0)
            {
                WinSocket::close();
                onDisconnected();
                return false;
            }
        } else if (evt.lNetworkEvents & FD_READ)
        {
            if(evt.iErrorCode[FD_READ_BIT] == 0)  
            {  
                using namespace MiniMPL;
                asyncExecute(TpCallbacker(makeCallbacker(&WinSocketTCP::recv,*this)));
            }  
        }
        return true;
    }

    void WinSocketTcpClientPeer::recvThreadFunc()
    {
        WSAResetEvent(m_eventClose);
        WSAEVENT    events[2];
        events[0]=m_eventClose;
        events[1]=WSACreateEvent();
        WSAEventSelect(m_sock,events[1],FD_CLOSE|FD_READ);
        while(true)
        {         
            int nIndex = WSAWaitForMultipleEvents(arraySize(events),events,FALSE,WSA_INFINITE,TRUE);
            nIndex = nIndex-WSA_WAIT_EVENT_0;
            if (0==nIndex)
            {
                onDisconnected();
                break;
            } else if (1==nIndex)
            {
                WSANETWORKEVENTS ne;
                WSAEnumNetworkEvents(m_sock,events[1],&ne);
                WSAResetEvent(events[1]);
                if (!onClientNetworkEvent(ne))
                {
                    break;
                }
            }
        }
        WSACloseEvent(events[1]);        
    }
    */
    
}

