#ifndef __WINSOCKDELEGATERECEIVER_H__
#define __WINSOCKDELEGATERECEIVER_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <network_win/WinSocketTcpClientPeer.h>

namespace OS_Win32
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct IWinSockDelegateReceiver
    {
        virtual ~IWinSockDelegateReceiver(){}
        virtual bool delegateRecv(WinSocketTcpClientPeer& rClientPeer)=0;
        virtual bool undelegateRecv(WinSocketTcpClientPeer& rClientPeer)=0;
    };

    typedef stlSmartptr<IWinSockDelegateReceiver> TpWinSockDelegateReceiver;
}

#endif // __WINSOCKDELEGATERECEIVER_H__
