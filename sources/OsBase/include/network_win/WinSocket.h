#ifndef __WINSOCKET_H__
#define __WINSOCKET_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <communicator/ICommunicator.h>
#include <winsock2.h>
#include <thread/sync.h>
#include <network_win/SocketEventMonitor.h>
#include <network_win/socket_opt_def.h>

namespace OS_Win32
{
    //     m_bindAddr.sin_family = AF_INET;
    //     m_bindAddr.sin_addr.s_addr = inet_addr(localIP);  //localIP is similar with 172.30.65.115 , it might be refused by gatway.
    //     //m_bindAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct HostAddr
    {   
        short           m_port;
        stlStringA      m_ip;
    };

    class WinSocket
    {
    public:
        //simply concept, don't provide EState_Listen,EState_Bind
        enum EConnect   {EConnect_Unkown,EConnect_Server,EConnect_Client,EConnect_Client_Peer};
    public:
        WinSocket();
        virtual ~WinSocket(void);

        SOCKET& getSock();
        bool setBlockMode( bool bBlockMode );
        virtual HostAddr getAddr() const;
        virtual bool isAvailableSock()  const;
        virtual EConnect getConnectType()   const;
        bool getSocketOpt(ESockOpt opt,CCommBuffer& rOpt);
        virtual bool close();

    protected:
        int peekData( SOCKET& s );
        bool         enableLinger();

    protected:
        HostAddr                m_addr;
        SOCKET		            m_sock;
    };
}  


#endif // __WINSOCKET_H__
