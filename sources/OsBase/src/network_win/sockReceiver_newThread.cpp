#include "./inc/sockReceiver_newThread.h"
#include "MiniMPL/macro_assert.h"

namespace OS_Win32
{



	CWinSockDelegateReceiver_newThread::CWinSockDelegateReceiver_newThread()
	{

	}

	CWinSockDelegateReceiver_newThread::~CWinSockDelegateReceiver_newThread()
	{

	}

	bool CWinSockDelegateReceiver_newThread::delegateRecv(WinSocketTcpClientPeer& rClientPeer)
	{
		m_pSockPeer = &rClientPeer;
		m_thread.setCallback(&CWinSockDelegateReceiver_newThread::recvThreadLoop, *this);
		return m_thread.start();
	}

	bool CWinSockDelegateReceiver_newThread::undelegateRecv(WinSocketTcpClientPeer& rClientPeer)
	{
		m_bLoop = false;
		return m_thread.stop();
	}

	void CWinSockDelegateReceiver_newThread::recvThreadLoop()
	{
		CHECK_TRUE_ELSE_RETURN_VAL(m_pSockPeer->isAvailableSock(), );
		CCommBuffer buf;
		buf.getBuffer(4096);
		m_bLoop = true;
		while (m_bLoop)
		{
			int nRecv = m_pSockPeer->recv(buf);
			if (nRecv > 0)
			{
				m_pSockPeer->onDataReceivced(buf);
			}
			else if (0 == nRecv || WSAEMSGSIZE != WSAGetLastError())
			{
				break;
			}
		}
		if (m_bLoop)
		{
			m_pSockPeer->onDisconnected();
		}
		m_bLoop = false;
	}
}
