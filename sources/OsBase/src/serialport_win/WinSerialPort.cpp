#include <serialport_win/WinSerialPort.h>
#include <thread/asyncCall.h>

namespace OS_Win32
{
    CSerialPort::CSerialPort(unsigned char portNum)
        : m_portNum(0)
        , m_hFile(INVALID_HANDLE_VALUE)
    {
//         m_hCloser =  CreateEvent(NULL,TRUE,FALSE,NULL);
// 
        stlString comStr;
        if (portNum>=10)
        {
            comStr = TXT("////.//COM");
        }
        else
        {
            comStr=TXT("COM");
        }
        comStr += '0'+portNum;
        m_hFile   = ::CreateFile( comStr.c_str(),GENERIC_READ | GENERIC_WRITE,
            0 /* exclusive access */, NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
    }

    CSerialPort::~CSerialPort()
    {
        if (INVALID_HANDLE_VALUE!=m_hFile)
        {
            CloseHandle(m_hFile);
        }
    }

    bool CSerialPort::setup( EBaundRate eBaudrate,EDataBits eDataBits /*= EData8*/, EParity eParity/*= EParNone*/,EStopBits eStopBits /*= EStop1*/ )
    {
        CHECK_TRUE_ELSE_RETURN_VAL(INVALID_HANDLE_VALUE!=m_hFile,false);

        DCB dcb;
        dcb.DCBlength = sizeof(dcb);
        CHECK_TRUE_ELSE_RETURN_VAL(::GetCommState(m_hFile,&dcb),false);

        dcb.BaudRate = DWORD(eBaudrate);
        dcb.ByteSize = BYTE(eDataBits);
        dcb.Parity   = BYTE(eParity);
        dcb.StopBits = BYTE(eStopBits);
        dcb.fParity  = (eParity != EParity_None);    // Determine if parity is used
        return 0!=::SetCommState(m_hFile,&dcb);
    }

    bool CSerialPort::monitorEvent(DWORD dwComEvents)
    {
        CHECK_TRUE_ELSE_RETURN_VAL(INVALID_HANDLE_VALUE!=m_hFile,false);

        DWORD dwCurComEvent = 0;
        CHECK_TRUE_ELSE_RETURN_VAL(GetCommMask(m_hFile,&dwCurComEvent),false);

        dwCurComEvent |= dwComEvents;
        if (0==dwCurComEvent)
        {
            m_hCloser.sendNotification();
            return true;
        }

        CHECK_TRUE_ELSE_RETURN_VAL(SetCommMask(m_hFile,dwCurComEvent),false);

        m_thrd.setCallback(&CSerialPort::thrdEventLoop,*this);
        return m_thrd.start();
    }

    bool CSerialPort::thrdEventLoop()
    {
        OVERLAPPED ol;
        ZeroMemory(&ol,sizeof(ol));

        ol.hEvent =  CreateEvent(NULL,TRUE,FALSE,NULL);
        CHECK_NULL_ELSE_RETURN_VAL(ol.hEvent,false);

        m_hCloser.resetNotification();
        while(eventWaitResultOk != m_hCloser.waitNotification(500))
        {
            DWORD dwComEvent = 0;
            BOOL bCommState=WaitCommEvent(m_hFile,&dwComEvent,&ol);
            if (bCommState)
            {
                handCommMask(dwComEvent);
            }
            else if (ERROR_IO_PENDING==GetLastError())
            {
                if (eventWaitResultOk==WaitForSingleObject(ol.hEvent,2000))
                {
                    if (GetOverlappedResult(m_hFile,&ol,&dwComEvent,false))
                    {
                        handCommMask(dwComEvent);
                    }
                }
            }            
        }

        CloseHandle(ol.hEvent);
        return true;
    }

    bool CSerialPort::handCommMask( DWORD dwComEvent )
    {
        DWORD ev=EEvent_RXCHAR;
        while(eventWaitResultOk!=m_hCloser.waitNotification(0) && dwComEvent)
        {
            if (ev & dwComEvent)
            {
                onSerialPortEvent(ESerialPortEvent(ev));                    
            }
            dwComEvent &= ~ev;
            ev = ev << 1;
        }
        return true;
    }

    bool CSerialPort::onSerialPortEvent( ESerialPortEvent evt )
    {
        switch(evt)
        {
            case EEvent_RXCHAR:
                {
                    asyncExecute(MiniMPL::TpCallbacker(MiniMPL::makeCallbacker(&CSerialPort::innerRecv,*this)));
                }
                break;
            default:
                {
                }
                break;    
        }

        return true;    
    }

    bool CSerialPort::innerRecv()
    {
        CCommBuffer rBuf;
        if (recv(rBuf))
        {
            return onReceive(rBuf);
        }
        return true;
    }

    bool CSerialPort::onReceive( CCommBuffer const& rBuffer )
    {
        static CSyncThread sync;
        CSyncLocker<CSyncThread> guard(sync);

        return true;
    }

    bool CSerialPort::start()
    {
        return INVALID_HANDLE_VALUE !=m_hFile;
    }

    bool CSerialPort::stop()
    {
        if (INVALID_HANDLE_VALUE !=m_hFile)
        {
            m_hCloser.sendNotification();
            m_hCloser.waitNotification();
        }
        return true;;
    }

    int CSerialPort::send( CCommBuffer const& rBuf )
    {
        DWORD iWritten = 1;
        CCommBuffer::const_iterator it=rBuf.begin();
        for(;iWritten && it!=rBuf.end();++it)
        {
            ::WriteFile(m_hFile,&*it,1,&iWritten,NULL);
        }

        return it-rBuf.begin();
    }

    int CSerialPort::recv( CCommBuffer& rBuf )
    {
        DWORD iRecv = 0;
        stlVector<TCommBufferElement> tmpBuf;
        TCommBufferElement  buf[RecvBufSize]={0};
        iRecv=::ReadFile(m_hFile,buf,RecvBufSize,&iRecv,NULL);
        while(RecvBufSize==iRecv)
        {               
            tmpBuf.insert(tmpBuf.end(),buf,buf+iRecv);
            iRecv=::ReadFile(m_hFile,buf,RecvBufSize,&iRecv,NULL);
        }
        if (iRecv>0)
        {
            tmpBuf.insert(tmpBuf.end(),buf,buf+iRecv);
        }
        
        iRecv = tmpBuf.size();
        if (iRecv>0)
        {
            memcpy(rBuf.getBuffer(iRecv),&*tmpBuf.begin(),iRecv);
            rBuf.setSize(iRecv);
        }

        return rBuf.getSize();
    }

}
