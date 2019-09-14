#include <network_win/WinSocketTCPServer.h>
#include <thread/asyncCall.h>
#include <MiniMPL/unaryFunctionCreater.hpp>
#include <MiniMPL/stdAlgorithmEx.hpp>
#include <MiniMPL/tester.hpp>
#include <network_win/clientPeerManager.h>

namespace OS_Win32
{
    WinSocketTCPServer::WinSocketTCPServer( short port )
        : WinSocket()
        , m_bCloseFlag(true)
    { 
        // Get the local host information
        struct addrinfo *result = WinSocketTCP::getAddrInfo("127.0.0.1");

        WinSocketTCP::setTcpAddr("127.0.0.1", port, m_bindAddr);  //localIP is similar with 172.30.65.115 , it might be refused by gateway.

        m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        enableLinger();

        m_event[Evt_Close] = WSACreateEvent();
    }

    WinSocketTCPServer::~WinSocketTCPServer(void)
    {
        stop();        
        WSACloseEvent(m_event[Evt_Close]);
    }

    bool WinSocketTCPServer::setBindIP( char const* pIp )
    {
        WinSocketTCP::setIP(pIp, m_bindAddr);

        stlStringA newIP;
        WinSocketTCP::getIP(m_bindAddr, newIP);
        return newIP ==pIp;
    }

    OS_Win32::HostAddr WinSocketTCPServer::getAddr() const
    {
        HostAddr ha;
        unsigned short port;
        WinSocketTCP::getPort(m_bindAddr, port);
        ha.m_port = port;
        WinSocketTCP::getIP(m_bindAddr, ha.m_ip);
        return ha;
    }

    WinSocket::EConnect WinSocketTCPServer::getConnectType()
    {
        return EConnect_Server;
    }

    bool WinSocketTCPServer::start()
    {
        // Bind the listening socket using the information in the sockaddr structure
        int opt = 1;
        setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
        if(0==bind(m_sock,(SOCKADDR*) &m_bindAddr, sizeof(m_bindAddr) ))
        {  
            if (0==listen(m_sock, SOMAXCONN))
            {
                WSAResetEvent(m_event[Evt_Close]);
                m_listenThread.setCallback(&WinSocketTCPServer::listenClient,*this);
                return m_listenThread.start();
            }
        }
        return false;
    }

    bool WinSocketTCPServer::stop()
    {
        WSASetEvent(m_event[Evt_Close]);

        m_bCloseFlag = true;
        if (m_listenThread.isRunning())
        {
            WinSocket::close();
            m_listenThread.stop();
        }
        return true;
    }

    WinSocketTcpClientPeer* WinSocketTCPServer::createClient( SOCKET s, sockaddr const& sa )
    {
        return new WinSocketTcpClientPeer(s,sa);
    }

    void WinSocketTCPServer::listenClient()
    {  
        m_bCloseFlag = false;
        m_event[Evt_Listen] = WSACreateEvent();
        ::WSAEventSelect(m_sock, m_event[Evt_Listen], FD_ACCEPT|FD_CLOSE);
        while(true)
        {
            int nIndex=WSAWaitForMultipleEvents(2,m_event,FALSE,WSA_INFINITE,FALSE);
            nIndex = nIndex - WSA_WAIT_EVENT_0;
            if (Evt_Close==nIndex)
            {
                break;
            }
            else
            {
                ASSERT_AND_LOG(Evt_Listen==nIndex);

                WSANETWORKEVENTS ne;  
                ::WSAEnumNetworkEvents(m_sock, m_event[Evt_Listen], &ne);
                WSAResetEvent(m_event[Evt_Listen]);
                if (!onListenNetworkEvent(ne))
                {
                    break;
                }
            }
        }
        WSACloseEvent(m_event[Evt_Listen]);
    }

    bool WinSocketTCPServer::onListenNetworkEvent( WSANETWORKEVENTS const& evt )
    {
        if (evt.lNetworkEvents & FD_ACCEPT)
        {
            if (evt.iErrorCode[FD_ACCEPT_BIT] == 0)
            {
                sockaddr sa;
                int iAddrLen = sizeof(sa);
                //AcceptEx
                SOCKET s = ::WSAAccept(m_sock,&sa,&iAddrLen,NULL,NULL);
                if (INVALID_SOCKET != s)
                {
                    WinSocketTcpClientPeer* pClientPeer=createClient(s,sa);
                    CClientPeerManager::getInstance().registerClientPeer(*pClientPeer,this);
                    pClientPeer->start();                
                } 
            } else if (evt.lNetworkEvents & FD_CLOSE)
            {
                if(evt.iErrorCode[FD_CLOSE_BIT] == 0)  
                {  
                    WinSocket::close();
                    return false;
                }  
            }
        }
        return true;
    }
}