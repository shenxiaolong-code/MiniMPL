#ifndef __CLIENTPEERMANAGER_H__
#define __CLIENTPEERMANAGER_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <utility/singleton.hpp>
#include <network_win/WinSockDelegateReceiver.h>

namespace OS_Win32
{
    class   WinSocketTcpClientPeer;
    class   WinSocketTCPServer;

    struct  IWinSockDelegateReceiver;
    typedef stlSmartptr<IWinSockDelegateReceiver>      TpSharedRecvThread;
    typedef stlSmartptr<WinSocketTcpClientPeer> TpWinSocketTcpClientPeer;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct IClientPeerMonitor
    {
        WinSocketTCPServer*  m_pServer;

        IClientPeerMonitor(WinSocketTCPServer* pSvr)
            :m_pServer(pSvr){};

        virtual void onClientConnected(WinSocketTcpClientPeer& rClientPeer)=0;
        virtual void onClientDisconnected(WinSocketTcpClientPeer& rClientPeer)=0;
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	enum DelegateMode { Delegate_newThread, Delegate_IOCP, Delegate_Overlap };
	class CClientPeerManager 
        : public SingletonMultiInstance<CClientPeerManager>
    {
        typedef std::pair<WinSocketTcpClientPeer*,WinSocketTCPServer*>		TPeerInfo;
        typedef stlVector<TPeerInfo>										TPeerArray;
    public:
        CClientPeerManager();
        virtual ~CClientPeerManager();

        bool registerMonitor(IClientPeerMonitor& rMonitor); 
        bool unregisterMonitor(IClientPeerMonitor& rMonitor);

        bool registerClientPeer(WinSocketTcpClientPeer& rPeer,WinSocketTCPServer* pOwnerServer); 
        bool unregisterClientPeer(WinSocketTcpClientPeer& rPeer);
				
        bool delegateRecv(WinSocketTcpClientPeer& rPeer, DelegateMode iMode= Delegate_newThread);
        bool undelegateRecv(WinSocketTcpClientPeer& rPeer);

    protected:
        CSyncThread									m_lock;
        bool										m_bIOCPMode;
		std::map<WinSocketTcpClientPeer*, TpWinSockDelegateReceiver>		m_delegateReceivers;
        TPeerArray									m_clientPeers;
        stlVector<IClientPeerMonitor*>				m_clientPeerMonitors;
    };

}








#endif // __CLIENTPEERMANAGER_H__
