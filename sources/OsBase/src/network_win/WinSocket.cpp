#include <network_win/WinSocket.h>
#include <MiniMPL/macroDef.h>
#include <MiniMPL/arrayTrait.hpp>
#include <win32/WinApiPack.h>

#pragma comment(lib,"Ws2_32.lib")

#pragma warning(disable:4073)
#pragma init_seg(lib)

namespace OS_Win32
{
    struct NetworkEnv
    {
        bool checkInit()
        {
            if (!m_OK)
            {
                WSADATA wsaData;
                m_OK = NO_ERROR==WSAStartup( MAKEWORD(2,2), &wsaData );
            }
            return m_OK;
        }

        NetworkEnv():m_OK(false)
        {
            checkInit();
        }
        ~NetworkEnv()
        {
            if (m_OK)
            {
                WSACleanup();
            }
        }

        bool m_OK;
    };

    NetworkEnv g_network; 

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    WinSocket::WinSocket()
        : m_sock(INVALID_SOCKET)
    {
        ZeroMemory(&m_addr,sizeof(m_addr));
    }

    WinSocket::~WinSocket(void)
    {
        close();
    }

    SOCKET& WinSocket::getSock()
    {
        return m_sock;
    }

    bool WinSocket::setBlockMode( bool bBlockMode )
    {
        if (!bBlockMode)
        {
            HANDLE tmpEventHandle = WSACreateEvent();
            WSAEventSelect(m_sock, tmpEventHandle, 0); //see ioctlsocket usage logic on MSDN
            CloseHandle(tmpEventHandle);

            //WSAAsyncSelect(m_sock,NULL,0,0);   //cancel WSAAsyncSelect
        }

        u_long iNonBlockMode = bBlockMode ? 0 : 1 ;
        return 0==ioctlsocket(m_sock, FIONBIO, &iNonBlockMode);  //disable nonblocking mode
    }

    bool WinSocket::close()
    {
        if (isAvailableSock())
        {
            //::shutdown(m_sock,SD_BOTH);
            closesocket(m_sock);
            m_sock = INVALID_SOCKET;  
        }
        return true;
    }


    int WinSocket::peekData( SOCKET& s )
    {
        char dummyBuf=0;
        return ::recv(s, &dummyBuf, 1, MSG_PEEK);
    }

    HostAddr WinSocket::getAddr() const
    {
        return m_addr;
    }

    bool WinSocket::isAvailableSock() const
    {
        return INVALID_SOCKET != m_sock;
    }

    WinSocket::EConnect WinSocket::getConnectType() const
    {
        return EConnect_Unkown;
    }

    bool WinSocket::getSocketOpt( ESockOpt opt,CCommBuffer& rOpt )
    {
        int len=0;
        char buf[sizeof(WSAPROTOCOL_INFO)]={0};//max option result
        if (SOCKET_ERROR!=::getsockopt(m_sock,SOL_SOCKET,opt,buf,&len))
        {
            memcpy(rOpt.getBuffer(len),buf,len);
            rOpt.setSize(len);
            return true;
        }
        else
        {
            outputTxtV(TXT("WinSocket::getSocketOpt fails,opt=%d\n"),opt);
            outputTxtV(GetLastErrorText(WSAGetLastError()).c_str());
        }
        return false;
    }

    /*
    bool WinSocket::setSocketEventMonitor( TpSocketEventMonitor const& pSocketMonitor )
    {
        push_back(pSocketMonitor);
        return true;
    }
    */

    bool WinSocket::enableLinger()
    {
        ASSERT_AND_LOG(isAvailableSock());

        linger lin;
        lin.l_onoff = 1;
        lin.l_linger = 60;
        return 0==setsockopt(m_sock, SOL_SOCKET, SO_LINGER, (char *)&lin, sizeof(lin));
    }
}