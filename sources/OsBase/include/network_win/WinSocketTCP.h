#ifndef __WINSOCKETTCP_H__
#define __WINSOCKETTCP_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <network_win/WinSocket.h>
#include <thread/thread.h>

namespace OS_Win32
{
    class WinSocketTCP : public ICommunicator,public WinSocket
    {   
    public:
        enum {RecvBufSize=128};
        WinSocketTCP();
        WinSocketTCP(SOCKET& s);

        virtual ~WinSocketTCP(void);

        virtual bool isConnected()  const;

        virtual int  send( void* pBuf,unsigned iLen );
        virtual bool transmitFile(  HANDLE hFile,DWORD nNumberOfBytesToWrite);//prove performance
        
        virtual int  recv( CCommBuffer& rBuf );
        virtual bool recv();

    protected:
        bool         startRecvThread();
        bool         stopRecvThread();
        void         recvThreadLoop();

    protected:
        bool         createSocket();

    public:
        static bool setIP(stlStringA const& sIP, sockaddr_in& rAddr);
        static bool getIP(sockaddr_in const& rAddr, stlStringA& sIP);
        static bool setPort(unsigned short port, sockaddr_in& rAddr);
        static bool getPort(sockaddr_in const& rAddr, unsigned short& port);
        static bool setTcpAddr(char const* pIp,unsigned sPort, sockaddr_in& addr);
        static addrinfo * getAddrInfo(char const* pIp);

    protected:
        TpThread            m_pThread;
    };
}


#endif // __WINSOCKETTCP_H__
