#ifndef __SOCKETEVENTMONITOR_H__
#define __SOCKETEVENTMONITOR_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/functionParams.hpp>

namespace OS_Win32
{
    class   WinSocket;
    struct  ISocketEventMonitor
    {
        virtual void onConnected(WinSocket* pConnection)=0;
        virtual void onDisconnected(WinSocket* pConnection)=0;
    };
    typedef stlSmartptr<ISocketEventMonitor> TpSocketEventMonitor;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename FCon,typename FDisCon>
    struct ISocketEventMonitorImpl : public ISocketEventMonitor
    {
        ISocketEventMonitorImpl(FCon fConnect,FDisCon fDisconnect)
            : m_fConnect(fConnect),m_fDisconnect(fDisconnect){};

        virtual void onConnected(WinSocket* pConnection)
        {
            if (m_fConnect)
            {
                m_fConnect(pConnection);
            }
        }

        virtual void onDisconnected(WinSocket* pConnection)
        {
            if (m_fDisconnect)
            {
                m_fDisconnect(pConnection);
            }
        }

        FCon        m_fConnect;
        FDisCon     m_fDisconnect;
    };

    template<typename FCon,typename FDisCon>
    TpSocketEventMonitor makeSocketEventMonitor(FCon fConnect,FDisCon fDisconnect)
    {
        return TpSocketEventMonitor(new ISocketEventMonitorImpl<FCon,FDisCon>(fConnect,fDisconnect));
    }

    template<typename FCon,typename FDisCon>
    struct ISocketEventMonitorImpl_Obj : public ISocketEventMonitor
    {
        ISocketEventMonitorImpl_Obj(FOR(FCon) rObj,FCon fConnect,FDisCon fDisconnect)
            : m_pObj(&rObj),m_fConnect(fConnect),m_fDisconnect(fDisconnect){};

        virtual void onConnected(WinSocket* pConnection)
        {
            if (m_pObj && m_fConnect)
            {
                (m_pObj->*m_fConnect)(pConnection);
            }
        }

        virtual void onDisconnected(WinSocket* pConnection)
        {
            if (m_pObj && m_fDisconnect)
            {
                (m_pObj->*m_fDisconnect)(pConnection);
            }
        }

        FO(FCon)*       m_pObj;
        FCon            m_fConnect;
        FDisCon         m_fDisconnect;
    };
    template<typename FCon,typename FDisCon>
    TpSocketEventMonitor makeSocketEventMonitor(FOR(FCon) rObj,FCon fConnect,FDisCon fDisconnect)
    {
        return TpSocketEventMonitor(new ISocketEventMonitorImpl_Obj<FCon,FDisCon>(rObj,fConnect,fDisconnect));
    }


}


#endif // __SOCKETEVENTMONITOR_H__
