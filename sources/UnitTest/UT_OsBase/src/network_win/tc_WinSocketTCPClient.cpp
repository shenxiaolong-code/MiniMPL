#include "../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\WinSocketTCPClient.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_WINSOCKETTCPCLIENT to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_WINSOCKETTCPCLIENT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_WINSOCKETTCPCLIENT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_WINSOCKETTCPCLIENT
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_WINSOCKETTCPCLIENT
#endif

//#undef RUN_EXAMPLE_WINSOCKETTCPCLIENT
//#undef COMPILE_EXAMPLE_WINSOCKETTCPCLIENT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_WINSOCKETTCPCLIENT
#include <network_win/WinSocketTCPClient.h>
#include <UnitTestKit/tc_tracer.h>
#include <thread/asyncCall.h>

#pragma warning(disable:4075)
#pragma init_seg(".CRT$XCP")

namespace UnitTest
{
    CSyncNotifier   g_clientNotifier;

    struct testNetClient : public OS_Win32::WinSocketTCPClient
    {
        testNetClient()
            :OS_Win32::WinSocketTCPClient("127.0.0.1",8055)
        {}

        virtual void onConnected()
        {               
            char buf[]="hello , I am testNetClient.\n";
            send(buf,sizeof(buf));
        }

        virtual void onDataReceivced(CCommBuffer const& data)
        {
            MiniMPL::dbgOutputV("\n[coming data from client peer]:\n%s\n",data.getCharBuf());

            static int nTotal=0;
            if (nTotal++<5)
            {
                char buf[128]={0};
                sprintf_s(buf,sizeof(buf),"\n[No.%d]UnitTest.testNetClient.onDataReceivced is called.\n",nTotal);
                send(buf,sizeof(buf));
            }
            else
            {
                g_clientNotifier.sendNotification();
            }
        }

    };


    void test_WinSocketTCPClient()
    {
        testNetClient cli;
        cli.start();

        g_clientNotifier.waitNotification();
    }


    inline void TestCase_WinSocketTCPClient()
    {
        PrintTestcase();
        using namespace MiniMPL;
        asyncExecute(TpCallbacker(makeCallbacker(test_WinSocketTCPClient)),EAsync_NewThread);
    }

#ifdef RUN_EXAMPLE_WINSOCKETTCPCLIENT
    InitRunFunc(TestCase_WinSocketTCPClient);
#else //else of RUN_EXAMPLE_WINSOCKETTCPCLIENT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] WinSocketTCPClient.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"WinSocketTCPClient.h\".")
    #endif
#endif  	// RUN_EXAMPLE_WINSOCKETTCPCLIENT
}

#else //else of COMPILE_EXAMPLE_WINSOCKETTCPCLIENT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] WinSocketTCPClient.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"WinSocketTCPClient.h\".")
    #endif
#endif // COMPILE_EXAMPLE_WINSOCKETTCPCLIENT

