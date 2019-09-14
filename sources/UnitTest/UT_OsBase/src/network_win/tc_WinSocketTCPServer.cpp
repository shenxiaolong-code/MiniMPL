#include "../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>

/***********************************************************************************************************************
* Description         : test file for <OsBase\WinSocketTCPServer.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_WINSOCKETTCPSERVER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_WINSOCKETTCPSERVER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_WINSOCKETTCPSERVER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_WINSOCKETTCPSERVER
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_WINSOCKETTCPSERVER
#endif

//#undef RUN_EXAMPLE_WINSOCKETTCPSERVER
//#undef COMPILE_EXAMPLE_WINSOCKETTCPSERVER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_WINSOCKETTCPSERVER
#include <network_win/WinSocketTCPServer.h>
#include <UnitTestKit/tc_tracer.h>
#include <thread/asyncCall.h>

#pragma warning(disable:4075)
#pragma init_seg(".CRT$XCM")

namespace UnitTest
{
    using namespace OS_Win32;

    CSyncNotifier   g_clientPeerNotifier;

    struct TestNetClientPeer : public WinSocketTcpClientPeer
    {
        TestNetClientPeer(SOCKET s, sockaddr const& sa)
            :WinSocketTcpClientPeer(s,sa)
        {
            setIndependentRecvThread(false);
        }

        virtual ~TestNetClientPeer()
        {
            g_clientPeerNotifier.waitNotification();
        }

        virtual void onConnected()
        {
            __super::onConnected();

            char buf[]="UnitTest.TestNetClientPeer.onConnected .\n";
            send(buf,sizeof(buf));
        }

        virtual void onDisconnected()
        {
            MiniMPL::dbgOutput("client is disconnected.\n");
        }

        virtual void  onDataReceivced(CCommBuffer const& data)
        {
            MiniMPL::dbgOutputV("\n[coming data from client]:\n%s\n",data.getCharBuf());

            static int nTotal=0;
            if (nTotal++<5)
            {
                char buf[128]={0};
                sprintf_s(buf,sizeof(buf),"\n[No.%d]UnitTest.TestNetClientPeer.onDataReceivced is called .\n",nTotal);
                send(buf,sizeof(buf));
            }
            else
            {
                MiniMPL::dbgOutput("\ng_clientPeerNotifier.sendNotification\n");
                g_clientPeerNotifier.sendNotification();
            }
        }
    };

    struct TestNetServer : public WinSocketTCPServer
    {
        TestNetServer()
            :WinSocketTCPServer(8055){};

        virtual ~TestNetServer()
        {

        }

        virtual void onClientConnected( TpWinSocketTcpClientPeer const& pSlot )
        {
            MiniMPL::dbgOutput("client is connected on server.\n");
            pSlot->setIndependentRecvThread(true);

            char buf[]="UnitTest.TestNetServer.onClientConnected .\n";
            pSlot->send(buf,sizeof(buf));
        }

        virtual WinSocketTcpClientPeer* createClient( SOCKET s, sockaddr const& sa )
        {
            return new TestNetClientPeer(s,sa);
        }

    };

    void testWinSocketTCPServerThread()
    {
        using namespace OS_Win32;
        TestNetServer srv;
        srv.start();
        g_clientPeerNotifier.waitNotification();
    }

    inline void TestCase_WinSocketTCPServer()
    {
        PrintTestcase();
        using namespace MiniMPL;
        asyncExecute(TpCallbacker(makeCallbacker(testWinSocketTCPServerThread)),EAsync_NewThread);
    }

#ifdef RUN_EXAMPLE_WINSOCKETTCPSERVER
    InitRunFunc(TestCase_WinSocketTCPServer);
#else //else of RUN_EXAMPLE_WINSOCKETTCPSERVER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] WinSocketTCPServer.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"WinSocketTCPServer.h\".")
    #endif
#endif  	// RUN_EXAMPLE_WINSOCKETTCPSERVER
}

#else //else of COMPILE_EXAMPLE_WINSOCKETTCPSERVER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] WinSocketTCPServer.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"WinSocketTCPServer.h\".")
    #endif
#endif // COMPILE_EXAMPLE_WINSOCKETTCPSERVER

