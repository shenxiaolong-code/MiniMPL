#include "./inc/sockReceiver_completePort.h"
#include <thread/asyncCall.h>

namespace OS_Win32
{
	struct PER_IO_OPERATEION_DATA
	{
		PER_IO_OPERATEION_DATA(WinSocketTcpClientPeer& rClientPeer)
			: m_pClientPeer(&rClientPeer)
		{
			reset();
		}

		~PER_IO_OPERATEION_DATA()
		{
		}

		void reset()
		{
			ZeroMemory(&overlapped, sizeof(overlapped));
			databuff.buf = m_realBuf.getCharBuf(1024);
			databuff.len = m_realBuf.getCapacity();
			//GlobalAlloc(GPTR,sizeof(PER_IO_OPERATEION_DATA))
		}

		OVERLAPPED  overlapped;
		WSABUF      databuff;
		CCommBuffer m_realBuf;
		WinSocketTcpClientPeer* m_pClientPeer;
	};

	//////////////////////////////////////////////////////////////////////////
	CWinSockDelegateReceiver_IOCP::CWinSockDelegateReceiver_IOCP()
	{   //http://blog.csdn.net/neicole/article/details/7549497
		//http://baike.baidu.com/view/1256215.htm#1
		//http://blog.csdn.net/PiggyXP/article/details/6922277
		m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
		m_thread.setCallback(&CWinSockDelegateReceiver_IOCP::IOCPThread, *this);
		m_thread.start();
	}

	CWinSockDelegateReceiver_IOCP::~CWinSockDelegateReceiver_IOCP()
	{
		PostQueuedCompletionStatus(m_hIOCP, 0, NULL, NULL);
		m_thread.stop();
	}

	void CWinSockDelegateReceiver_IOCP::IOCPThread()
	{
		DWORD RecvBytes = 0;
		DWORD Flags = 0;
		PER_IO_OPERATEION_DATA* pIo = NULL;
		OVERLAPPED* IpOverlapped = NULL;
		DWORD BytesTransferred = 0;
		while (1)
		{
			BOOL bRet = GetQueuedCompletionStatus(m_hIOCP, &BytesTransferred, (PULONG_PTR)&pIo, (LPOVERLAPPED*)&IpOverlapped, WSA_INFINITE);
			if (0 == bRet)
			{
				if (pIo)
				{
					pIo->m_pClientPeer->close();
					delete pIo;
				}

				return;
			}

			pIo = (PER_IO_OPERATEION_DATA*)CONTAINING_RECORD(IpOverlapped, PER_IO_OPERATEION_DATA, overlapped);
			if (0 == BytesTransferred)
			{
				if (pIo)
				{
					pIo->m_pClientPeer->close();
					delete pIo;
				}
				continue;
			}

			pIo->m_realBuf.setSize(pIo->databuff.len);
			using namespace MiniMPL;
			asyncExecute(TpCallbacker(makeCallbackerDirect(&WinSocketTcpClientPeer::onDataReceivced, ParamPackageCall<WinSocketTcpClientPeer&, CCommBuffer>(*pIo->m_pClientPeer, pIo->m_realBuf))));

			pIo->reset();
			WSARecv(pIo->m_pClientPeer->getSock(), &(pIo->databuff), 1, &RecvBytes, &Flags, &(pIo->overlapped), NULL);
		}
	}

	bool CWinSockDelegateReceiver_IOCP::delegateRecv(WinSocketTcpClientPeer& rClientPeer)
	{
		DWORD RecvBytes = 0;;
		DWORD Flags = 0;
		PER_IO_OPERATEION_DATA* pIo = new PER_IO_OPERATEION_DATA(rClientPeer);
		CreateIoCompletionPort((HANDLE)(rClientPeer.getSock()), m_hIOCP, (DWORD)pIo, 0);
		if (0 != WSARecv(rClientPeer.getSock(), &(pIo->databuff), 1, &RecvBytes, &Flags, &(pIo->overlapped), NULL))
		{
			if (WSA_IO_PENDING == WSAGetLastError())
			{
				return true;
			}
			delete pIo;
			pIo = NULL;
			return false;
		}
		return true;
	}

	bool CWinSockDelegateReceiver_IOCP::undelegateRecv(WinSocketTcpClientPeer& rClientPeer)
	{
		return true;
	}


}
