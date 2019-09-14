#ifndef __WINSOCKETTCPSERVER_H__
#define __WINSOCKETTCPSERVER_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <network_win/WinSocketTCP.h>
#include <MiniMPL/productSpecialDef.h>
#include <network_win/WinSocketTcpClientPeer.h>
#include <thread/thread.h>

namespace OS_Win32
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class WinSocketTCPServer : public WinSocket
    {
        enum {Evt_Listen=0,Evt_Close};
    public:
        WinSocketTCPServer(short port);
        virtual ~WinSocketTCPServer(void);

        bool                setBindIP(char const* pIp);
        virtual HostAddr    getAddr() const;

        virtual bool        start();
        virtual bool        stop();

    protected:
        virtual WinSocketTcpClientPeer* createClient(SOCKET s, sockaddr const& sa);
        bool                onListenNetworkEvent(WSANETWORKEVENTS const& evt);

        void                listenClient();

        virtual EConnect getConnectType();

    protected:
        WSAEVENT                                m_event[2];
        volatile bool                           m_bCloseFlag;
        sockaddr_in                             m_bindAddr;
        CThread                                 m_listenThread;
    };

    typedef stlSmartptr<WinSocketTCPServer> TpWinSocketTCPServer;
}


#endif // __WINSOCKETTCPSERVER_H__
