#ifndef __OSBASE_SOCKRECEIVER_COMPLETEPORT_H__
#define __OSBASE_SOCKRECEIVER_COMPLETEPORT_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong (at Fri 10/18/2019) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <network_win/WinSockDelegateReceiver.h>

namespace OS_Win32
{
	class CWinSockDelegateReceiver_IOCP : public IWinSockDelegateReceiver
	{
		HANDLE      m_hIOCP;
		CThread     m_thread;

	public:
		CWinSockDelegateReceiver_IOCP();

		virtual ~CWinSockDelegateReceiver_IOCP();

		void IOCPThread();

		virtual bool delegateRecv(WinSocketTcpClientPeer& rClientPeer);
		virtual bool undelegateRecv(WinSocketTcpClientPeer& rClientPeer);
	};
}

#endif // __OSBASE_SOCKRECEIVER_COMPLETEPORT_H__
