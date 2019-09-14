#ifndef __WINSOCKDELEGATERECEIVER_H__
#define __WINSOCKDELEGATERECEIVER_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <network_win/WinSocketTcpClientPeer.h>

namespace OS_Win32
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct IWinSockDelegateReceiver
    {
        virtual ~IWinSockDelegateReceiver(){}
        virtual bool delegateRecv(WinSocketTcpClientPeer& rClientPeer)=0;
        virtual bool undelegateRecv(WinSocketTcpClientPeer& rClientPeer)=0;
    };

    typedef stlSmartptr<IWinSockDelegateReceiver> TpWinSockDelegateReceiver;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CWinSockDelegateReceiver_IOCP : public IWinSockDelegateReceiver
    {   
        HANDLE      m_hIOCP;
        CThread     m_thread;

    public:
        CWinSockDelegateReceiver_IOCP();

        virtual ~CWinSockDelegateReceiver_IOCP();

        void IOCPThread();

        virtual bool delegateRecv( WinSocketTcpClientPeer& rClientPeer );
        virtual bool undelegateRecv(WinSocketTcpClientPeer& rClientPeer);
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CWinSockDelegateReceiver_EventSelect : public IWinSockDelegateReceiver
    {
        CSyncThread     m_locker;
        CThread         m_recvThread;
        stlVector<WinSocketTcpClientPeer*> m_clientPeers;
        WSAEVENT        m_event[WSA_MAXIMUM_WAIT_EVENTS];
        int             m_eventNumber;

        bool remove(int idx);

        bool remove(WinSocketTcpClientPeer& rClientPeer);

        bool add(WinSocketTcpClientPeer& rClientPeer);

    public:
        CWinSockDelegateReceiver_EventSelect();

        virtual ~CWinSockDelegateReceiver_EventSelect();

        bool onClientNetworkEvent(unsigned idx, WSANETWORKEVENTS const& evt );

        void recvThreadFunc();

        virtual bool delegateRecv( WinSocketTcpClientPeer& rClientPeer );
        virtual bool undelegateRecv(WinSocketTcpClientPeer& rClientPeer); 
    };

}




#endif // __WINSOCKDELEGATERECEIVER_H__
