#ifndef __WINSOCKETTCPCLIENT_H__
#define __WINSOCKETTCPCLIENT_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/

#include <network_win/WinSocketTCP.h>

namespace OS_Win32
{
    class WinSocketTCPClient :	public WinSocketTCP
    {
    public:
        WinSocketTCPClient(stlStringA srvAddr,short port);
        virtual ~WinSocketTCPClient(void);

        bool connectServer();        

        virtual bool start();

        virtual bool stop();

    protected:
    };
    typedef stlSmartptr<WinSocketTCPClient>  TpWinSocketTCPClient;
}


#endif // __WINSOCKETTCPCLIENT_H__
