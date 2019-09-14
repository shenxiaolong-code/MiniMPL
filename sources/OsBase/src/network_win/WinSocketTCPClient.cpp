#include <network_win/WinSocketTCPClient.h>

#include <errno.h>

namespace OS_Win32
{
    WinSocketTCPClient::WinSocketTCPClient(stlStringA srvAddr,short port )
        : WinSocketTCP()
    {    
        m_addr.m_ip = srvAddr;
        m_addr.m_port = port;
    }

    WinSocketTCPClient::~WinSocketTCPClient(void)
    { 
        stop();
    }

    bool WinSocketTCPClient::connectServer()
    {
        struct sockaddr_in addr;
        setTcpAddr(m_addr.m_ip.c_str(), m_addr.m_port, addr);

        u_long iMode =0;
        ioctlsocket(m_sock, FIONBIO, &iMode);    //disable nonblocking mode
        if (::connect(m_sock, (struct sockaddr *)&addr, sizeof(addr)))
        {
            int conState = WSAGetLastError();
            switch(conState)
            {   //winerror.h
            case ERROR_SUCCESS:
                break;
            case WSAEWOULDBLOCK:
            case WSAEINPROGRESS:
                {
                    outputTxt(TXT("connecting server...."));
                    char errbuf[256]={0};
                    timeval tv;
                    tv.tv_sec = 15; 
                    tv.tv_usec = 0; 
                    fd_set  myset;
                    FD_ZERO(&myset); 
                    FD_SET(m_sock, &myset); 

                    int res = select(0, NULL, &myset, NULL, &tv);
                    if (res < 0 && errno != EINTR) 
                    { 
                        strerror_s(errbuf,256,errno);
                        outputTxtV("Error connecting %d - %s\n", errno, errbuf);
                        return false;
                    } 
                    else if (res > 0) 
                    { 
                        // Socket selected for write 
                        int lon = sizeof(int);
                        int valopt = 0;
                        if (getsockopt(m_sock, SOL_SOCKET, SO_ERROR, (char*)(&valopt), &lon) < 0) 
                        { 
                            strerror_s(errbuf,256,errno);
                            outputTxtV("Error in getsockopt() %d - %s\n", errno, errbuf);
                            return false;
                        } 
                        // Check the value returned... 
                        if (valopt) 
                        { 
                            strerror_s(errbuf,256,errno);
                            outputTxtV("Error in delayed connection() %d - %s\n", errno, errbuf);
                            return false;
                        } 
                    } 
                    else 
                    { 
                        outputTxt("Timeout in select() - Cancelling!\n");
                        return false;
                    } 
                }
                break;
            case WSAECONNREFUSED:
                outputTxt("No Server is running or firmware is blocking current connection.\n");
            default:
                {
                    return false;
                }
                break;
            }
        }

        return true;;
    }

    bool WinSocketTCPClient::start()
    {
        if (connectServer())
        {
            onConnected();
            return startRecvThread();
        }
        return false;
    }

    bool WinSocketTCPClient::stop()
    {
        return stopRecvThread();
    }

}