#include "../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\socket_opt_def.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SOCKET_OPT_DEF to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_SOCKET_OPT_DEF

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SOCKET_OPT_DEF
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SOCKET_OPT_DEF
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_SOCKET_OPT_DEF
#endif

//#undef RUN_EXAMPLE_SOCKET_OPT_DEF
//#undef COMPILE_EXAMPLE_SOCKET_OPT_DEF

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SOCKET_OPT_DEF
#include <network_win/socket_opt_def.h>
#include <UnitTestKit/tc_tracer.h>
#include <network_win/WinSocket.h>

using namespace OS_Win32;
namespace UnitTest
{
#define ESockOptArr(a,b) E##a,
    ESockOpt sockOptArr[] = {SOCKET_OPT_LIST(ESockOptArr)};

    struct TestSockOpt : public WinSocket
    {
        TestSockOpt()
        {
            m_sock = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,WSA_FLAG_OVERLAPPED);
        }
    };

    inline void TestCase_socket_opt_def()
    {
        PrintTestcase();

        TestSockOpt ss;
        CCommBuffer buf;
        for (unsigned idx=0;idx<arraySize(sockOptArr);++idx)
        {
            ss.getSocketOpt(sockOptArr[idx],buf);
        }

    }

#ifdef RUN_EXAMPLE_SOCKET_OPT_DEF
    InitRunFunc(TestCase_socket_opt_def);
#else //else of RUN_EXAMPLE_SOCKET_OPT_DEF

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] socket_opt_def.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"socket_opt_def.h\".")
    #endif
#endif  	// RUN_EXAMPLE_SOCKET_OPT_DEF
}

#else //else of COMPILE_EXAMPLE_SOCKET_OPT_DEF
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] socket_opt_def.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"socket_opt_def.h\".")
    #endif
#endif // COMPILE_EXAMPLE_SOCKET_OPT_DEF

