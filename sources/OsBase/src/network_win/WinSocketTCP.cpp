#include <network_win/WinSocketTCP.h>
#include <MiniMPL/productSpecialDef.h>
#include <thread/asyncCall.h>
#include <win32/WinApiPack.h>
#include <ws2tcpip.h>

//used by transmitFile
#include <Mswsock.h>
#pragma comment(lib,"Mswsock.lib")

namespace OS_Win32
{
    WinSocketTCP::WinSocketTCP()
        : WinSocket()
    {
        createSocket();
        enableLinger();
    }

    WinSocketTCP::WinSocketTCP( SOCKET& s )
    {
        m_sock = s;
        enableLinger();
    }

    WinSocketTCP::~WinSocketTCP(void)
    {  
    }

    bool WinSocketTCP::createSocket()
    {
        //m_sock = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,WSA_FLAG_OVERLAPPED);
        m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        return isAvailableSock();
    }

    bool WinSocketTCP::setIP(stlStringA const& sIP, sockaddr_in& rAddr)
    {
        //RtlIpv4StringToAddressA(pIp, false, NULL, &addr.sin_addr);     //need VS2015
        //addr.sin_addr.s_addr = inet_addr(pIp);                          //deprecated function in vs2015
        return 0==inet_pton(AF_INET, sIP.c_str(), &rAddr.sin_addr.s_addr);
    }

    bool WinSocketTCP::getIP(sockaddr_in const& rAddr, stlStringA& sIP)
    {
        IN_ADDR  addr = rAddr.sin_addr;
        char buf[128] = { 0 };
        if (inet_ntop(AF_INET, &addr.s_addr, buf, 128))
        {
            sIP = buf;
            return true;
        }
        return false;
        //sIP = inet_ntoa(rAddr);                                   //deprecated function in vs2015;
        //RtlIpv4AddressToStringA(&rAddr, ipBuf);                   //need VS2015
    }

    bool WinSocketTCP::setPort(unsigned short port, sockaddr_in& rAddr)
    {
        rAddr.sin_port = htons(port);
        return true;
    }

    bool WinSocketTCP::getPort(sockaddr_in const& rAddr, unsigned short& port)
    {
        port = ntohs(rAddr.sin_port);
        return true;
    }

    bool WinSocketTCP::setTcpAddr(char const* pIp, unsigned sPort, sockaddr_in& addr)
    {
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        setIP(pIp, addr);
        setPort(sPort, addr);
        return true;
    }

    addrinfo * WinSocketTCP::getAddrInfo(char const* pIp)
    {
        struct addrinfo *pResult = NULL;
        struct addrinfo hints;
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        return 0 == getaddrinfo(pIp, NULL, &hints, &pResult) ? pResult : NULL;
    }

    bool WinSocketTCP::isConnected() const
    {
        return isAvailableSock();
    }
    int WinSocketTCP::send( void* pBuf,unsigned iLen )
    {
        if (isAvailableSock())
        {
            return ::send(m_sock,(const char *)pBuf,iLen,0);;
        }
        outputTxtV(TXT("Invalid socket! Fails to WinSocket::send."));
        return 0;
    }

    bool WinSocketTCP::transmitFile( HANDLE hFile,DWORD nNumberOfBytesToWrite )
    {
        if (isAvailableSock())
        {
            return TRUE==::TransmitFile(m_sock,hFile,nNumberOfBytesToWrite,0,NULL,NULL,TF_USE_KERNEL_APC);
        }

        return false;
    }

    int WinSocketTCP::recv( CCommBuffer& rBuf )
    {
        CHECK_TRUE_ELSE_RETURN_VAL(isAvailableSock(),0);
        /*
        unsigned iSize = peekData(m_sock);
        if (iSize<=0) { return 0; }
        */

        int iRead = ::recv(m_sock, rBuf.getCharBuf(4096/*iSize*/), rBuf.getCapacity(), 0);
        if (iRead>0)
        {
            rBuf.setSize(iRead);
        }
        else
        {
            MiniMPL::dbgOutput(GetLastErrorText(WSAGetLastError()).c_str());
        }
        return iRead;
    }

    bool WinSocketTCP::recv()
    {
        CCommBuffer rBuf;
        if (recv(rBuf))
        {
            onDataReceivced(rBuf);
        }
        return rBuf.getSize()>0;
    }

    void WinSocketTCP::recvThreadLoop()
    {
        CHECK_TRUE_ELSE_RETURN_VAL(isAvailableSock(),);
        CCommBuffer buf;
        buf.getBuffer(4096);
        while(1)
        {
            int nRecv = recv(buf);
            if (nRecv>0)
            {
                onDataReceivced(buf);
            } else if (0==nRecv || WSAEMSGSIZE!=WSAGetLastError())
            {
                break;
            }
        }
        onDisconnected();       
    }

    bool WinSocketTCP::startRecvThread()
    {
        if (!m_pThread)
        {
            m_pThread.reset(new CThread());
            m_pThread->setCallback(&WinSocketTCP::recvThreadLoop,*this);
            return m_pThread->start();
        }
        return true;
    }

    bool WinSocketTCP::stopRecvThread()
    {
        if (isConnected())
        {
            close();
            return m_pThread->stop();
        }
        return true;
    }
}