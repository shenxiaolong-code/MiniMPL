#include <network_win/WinSockDelegateReceiver.h>
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
            ZeroMemory(&overlapped,sizeof(overlapped));
            databuff.buf = m_realBuf.getCharBuf(1024);
            databuff.len = m_realBuf.getCapacity();
            //GlobalAlloc(GPTR,sizeof(PER_IO_OPERATEION_DATA))
        }

        OVERLAPPED  overlapped;
        WSABUF      databuff;
        CCommBuffer m_realBuf;
        WinSocketTcpClientPeer* m_pClientPeer;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CWinSockDelegateReceiver_IOCP::CWinSockDelegateReceiver_IOCP()
    {   //http://blog.csdn.net/neicole/article/details/7549497
        //http://baike.baidu.com/view/1256215.htm#1
        //http://blog.csdn.net/PiggyXP/article/details/6922277
        m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,0);
        m_thread.setCallback(&CWinSockDelegateReceiver_IOCP::IOCPThread,*this);
        m_thread.start();
    }

    CWinSockDelegateReceiver_IOCP::~CWinSockDelegateReceiver_IOCP()
    {

            PostQueuedCompletionStatus(m_hIOCP,0,NULL,NULL);
        m_thread.stop();
        }

    void CWinSockDelegateReceiver_IOCP::IOCPThread()
    {
        DWORD RecvBytes=0;  
        DWORD Flags = 0;
        PER_IO_OPERATEION_DATA* pIo=NULL;
        OVERLAPPED* IpOverlapped=NULL;
        DWORD BytesTransferred = 0;
        while(1)
        {
            BOOL bRet=GetQueuedCompletionStatus(m_hIOCP,&BytesTransferred,(PULONG_PTR)&pIo,(LPOVERLAPPED*)&IpOverlapped,WSA_INFINITE);
            if (0==bRet)
            {
                if (pIo)
                {
                    pIo->m_pClientPeer->close();
                    delete pIo;
                }

                return;
            }

            pIo=(PER_IO_OPERATEION_DATA*)CONTAINING_RECORD(IpOverlapped,PER_IO_OPERATEION_DATA,overlapped);
            if(0==BytesTransferred)
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
            asyncExecute(TpCallbacker(makeCallbackerDirect(&WinSocketTcpClientPeer::onDataReceivced,ParamPackageCall<WinSocketTcpClientPeer&,CCommBuffer>(*pIo->m_pClientPeer,pIo->m_realBuf))));

            pIo->reset();
            WSARecv(pIo->m_pClientPeer->getSock(),&(pIo->databuff),1,&RecvBytes,&Flags,&(pIo->overlapped),NULL);
        }
    }

    bool CWinSockDelegateReceiver_IOCP::delegateRecv( WinSocketTcpClientPeer& rClientPeer )
    {
        DWORD RecvBytes=0;;
        DWORD Flags=0;
        PER_IO_OPERATEION_DATA* pIo=new PER_IO_OPERATEION_DATA(rClientPeer);
        CreateIoCompletionPort((HANDLE)(rClientPeer.getSock()), m_hIOCP, (DWORD)pIo, 0);
        if (0!=WSARecv(rClientPeer.getSock(),&(pIo->databuff),1,&RecvBytes,&Flags,&(pIo->overlapped),NULL))
        {
            if (WSA_IO_PENDING==WSAGetLastError())
            {
                return true;
            }
            delete pIo;
            pIo = NULL;
            return false;
        }
        return true;
    }

    bool CWinSockDelegateReceiver_IOCP::undelegateRecv( WinSocketTcpClientPeer& rClientPeer )
    {
        return true;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool CWinSockDelegateReceiver_EventSelect::remove( WinSocketTcpClientPeer& rClientPeer )
    {
        LockHere(m_locker);
        for (stlVector<WinSocketTcpClientPeer*>::iterator it=m_clientPeers.begin()
            ;it!=m_clientPeers.end();++it)
        {
            if (*it==&rClientPeer)
            {
                remove(it-m_clientPeers.begin());
                break;
            }
        }
        return true;
    }

    bool CWinSockDelegateReceiver_EventSelect::remove( int idx )
    {
        LockHere(m_locker);
        if (idx<m_eventNumber)
        {
            MiniMPL::swap(m_event[idx],m_event[m_eventNumber-1]);
            CloseHandle(m_event[m_eventNumber-1]);
            m_eventNumber--; 

            MiniMPL::swap(*(m_clientPeers.begin()+idx),m_clientPeers.back());
            m_clientPeers.erase(--m_clientPeers.end());
            return true;
        }
        return false;
    }

    bool CWinSockDelegateReceiver_EventSelect::add( WinSocketTcpClientPeer& rClientPeer )
    {
        LockHere(m_locker);
        m_event[m_eventNumber++]=WSACreateEvent();
        m_clientPeers.push_back(&rClientPeer);
        return true;
    }

    CWinSockDelegateReceiver_EventSelect::CWinSockDelegateReceiver_EventSelect()
    {   //http://blog.csdn.net/wanjingwei/article/details/4306609#
        m_event[0] = WSACreateEvent();
    }

    CWinSockDelegateReceiver_EventSelect::~CWinSockDelegateReceiver_EventSelect()
    {
        SetEvent(m_event[0]);
        m_recvThread.stop();
        CloseHandle(m_event[0]);
    }

    bool CWinSockDelegateReceiver_EventSelect::onClientNetworkEvent( unsigned idx, WSANETWORKEVENTS const& evt )
    {
        if (evt.lNetworkEvents & FD_CLOSE)
        {
            if (evt.iErrorCode[FD_CLOSE_BIT] == 0)
            {
                return false;
            }
        } else if (evt.lNetworkEvents & FD_READ)
        {
            if(evt.iErrorCode[FD_READ_BIT] == 0)  
            {  
                using namespace MiniMPL;
                asyncExecute(TpCallbacker(makeCallbacker(&WinSocketTcpClientPeer::recv,*m_clientPeers[idx])));
            }  
        }
        return true;
    }

    void CWinSockDelegateReceiver_EventSelect::recvThreadFunc()
    {
        ResetEvent(m_event[0]);
        while(true)
        {         
            int nIndex = WSAWaitForMultipleEvents(m_eventNumber,m_event,FALSE,WSA_INFINITE,TRUE);
            nIndex = nIndex-WSA_WAIT_EVENT_0;
            if (0==nIndex)
            {
                break;
            } 

            for(int i=nIndex; i<m_eventNumber; i++)  
            {  
                int ret;  
                ret = ::WSAWaitForMultipleEvents(1, &m_event[i], TRUE, 1000, FALSE);  
                if(ret == WSA_WAIT_FAILED || ret == WSA_WAIT_TIMEOUT)  
                {  
                    continue;  
                }  
                else  
                {  
                    WSANETWORKEVENTS ne;  
                    ::WSAEnumNetworkEvents(m_clientPeers[i]->getSock(), m_event[i], &ne);
                    if (!onClientNetworkEvent(i,ne))
                    {
                        WinSocketTcpClientPeer* tmp=m_clientPeers[i];
                        remove(i--);
                        tmp->onDisconnected();
                    }
                }  
            }
        }
    }

    bool CWinSockDelegateReceiver_EventSelect::delegateRecv( WinSocketTcpClientPeer& rClientPeer )
    {
        CHECK_TRUE_ELSE_RETURN_VAL(m_eventNumber<arraySize(m_event),false);

        add(rClientPeer);
        WSAEventSelect(rClientPeer.getSock(),m_event[m_eventNumber-1],FD_CLOSE|FD_READ);

        if (!m_recvThread.isRunning())
        {
            m_recvThread.setCallback(&CWinSockDelegateReceiver_EventSelect::recvThreadFunc,*this);
            m_recvThread.start();
        }
        return true;
    }

    bool CWinSockDelegateReceiver_EventSelect::undelegateRecv( WinSocketTcpClientPeer& rClientPeer )
    {
        return remove(rClientPeer);
    }

}


