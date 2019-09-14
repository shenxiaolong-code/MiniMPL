#ifndef __WINSERIALPORT_H__
#define __WINSERIALPORT_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <wtypes.h>
#include <communicator/ICommunicator.h>
#include <thread/thread.h>
#include <serialport_win/WinSerialPortDef.h>
#include <thread/sync.h>

namespace OS_Win32
{
    class CSerialPort : public ICommunicator
     {
     public:
         enum {RecvBufSize=128};

         CSerialPort(unsigned char portNum);
         virtual ~CSerialPort();

         bool setup(EBaundRate eBaudrate,EDataBits eDataBits = EDataBits_8,
             EParity eParity= EParity_None,EStopBits eStopBits = EStopBits_1);

         bool   monitorEvent(DWORD dwComEvents=EEvent_RXCHAR);

         virtual bool start();

         virtual bool stop();

         virtual int send( CCommBuffer const& rBuf );

         virtual int recv( CCommBuffer& rBuf );

     protected:
         bool   handCommMask(DWORD dwComEvent);
         bool   onSerialPortEvent(ESerialPortEvent evt);

         virtual bool innerRecv();
         virtual bool onReceive(CCommBuffer const& rBuffer);

         bool   thrdEventLoop();

     protected:
         CSyncNotifier  m_hCloser;

         unsigned char  m_portNum;
         HANDLE         m_hFile;         
         CThread        m_thrd;
     };

}


#endif // __WINSERIALPORT_H__
