#ifndef __OSBASE_SOCKRECEIVER_OVERLAPPORT_H__
#define __OSBASE_SOCKRECEIVER_OVERLAPPORT_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong (at Fri 10/18/2019) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <network_win/WinSockDelegateReceiver.h>

namespace OS_Win32
{
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

		bool onClientNetworkEvent(unsigned idx, WSANETWORKEVENTS const& evt);

		void recvThreadFunc();

		virtual bool delegateRecv(WinSocketTcpClientPeer& rClientPeer);
		virtual bool undelegateRecv(WinSocketTcpClientPeer& rClientPeer);
	};
}

#endif // __OSBASE_SOCKRECEIVER_OVERLAPPORT_H__
