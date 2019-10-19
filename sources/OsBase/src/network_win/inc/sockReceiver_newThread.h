#ifndef __OSBASE_SOCKRECEIVER_NEWTHREAD_H__
#define __OSBASE_SOCKRECEIVER_NEWTHREAD_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong (at Fri 10/18/2019) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <network_win/WinSockDelegateReceiver.h>
#include <atomic>

namespace OS_Win32
{
	class CWinSockDelegateReceiver_newThread : public IWinSockDelegateReceiver
	{		
		std::atomic_bool			m_bLoop=false;
		CThread						m_thread;
		WinSocketTcpClientPeer*		m_pSockPeer;

	public:
		CWinSockDelegateReceiver_newThread();

		virtual ~CWinSockDelegateReceiver_newThread();

		virtual bool delegateRecv(WinSocketTcpClientPeer& rClientPeer);
		virtual bool undelegateRecv(WinSocketTcpClientPeer& rClientPeer);

	protected:
		void         recvThreadLoop();
	};
}

#endif // __OSBASE_SOCKRECEIVER_NEWTHREAD_H__
