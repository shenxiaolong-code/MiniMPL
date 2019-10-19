#ifndef __WINSOCKETSLOT_H__
#define __WINSOCKETSLOT_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <network_win/WinSocketTCP.h>
#include <thread/thread.h>

namespace OS_Win32
{
	enum  DelegateMode;
    class WinSocketTcpClientPeer : public WinSocketTCP
    {
    public:
        WinSocketTcpClientPeer(SOCKET s, sockaddr const& sa);
        virtual ~WinSocketTcpClientPeer(void);

        virtual EConnect getConnectType();

        bool    getPeerIpPort(HostAddr& ha);
		bool	setReceiveMode(DelegateMode recvMode);

        virtual bool start();
        virtual bool stop();

    protected:
        bool onClientNetworkEvent( WSANETWORKEVENTS const& evt );

    protected:
		DelegateMode		m_receiveMode;
        sockaddr            m_peerAddr;
        //WSAEVENT            m_event;
    };

    typedef stlSmartptr<WinSocketTcpClientPeer> TpWinSocketTcpClientPeer;
}

#endif // __WINSOCKETSLOT_H__
