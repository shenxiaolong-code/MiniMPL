#include ".../../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <network_win/inc/sockReceiver_completePort.h>
* Author              : Shen.Xiaolong (at Fri 10/18/2019) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SOCKRECEIVER_COMPLETEPORT to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_SOCKRECEIVER_COMPLETEPORT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SOCKRECEIVER_COMPLETEPORT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SOCKRECEIVER_COMPLETEPORT
#endif

#if defined(RUN_EXAMPLE_SOCKRECEIVER_COMPLETEPORT) && !defined(COMPILE_EXAMPLE_SOCKRECEIVER_COMPLETEPORT)
    #define COMPILE_EXAMPLE_SOCKRECEIVER_COMPLETEPORT
#endif

//#undef RUN_EXAMPLE_SOCKRECEIVER_COMPLETEPORT
//#undef COMPILE_EXAMPLE_SOCKRECEIVER_COMPLETEPORT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SOCKRECEIVER_COMPLETEPORT
#include <network_win/inc/sockReceiver_completePort.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_sockReceiver_completePort()
    {
        PrintTestcase();
        //ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        
        ALWAYS_COMPILE_MSG("NO Test context for <network_win/inc/sockReceiver_completePort.h>");

    }

#ifdef RUN_EXAMPLE_SOCKRECEIVER_COMPLETEPORT
    InitRunFunc(TestCase_sockReceiver_completePort);
#else //else of RUN_EXAMPLE_SOCKRECEIVER_COMPLETEPORT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_SOCKRECEIVER_COMPLETEPORT)=(outputTxtV(TXT("[Unit test run disabled] sockReceiver_completePort.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"sockReceiver_completePort.h\".")
    #endif
#endif  	// RUN_EXAMPLE_SOCKRECEIVER_COMPLETEPORT
}

#else //else of COMPILE_EXAMPLE_SOCKRECEIVER_COMPLETEPORT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_SOCKRECEIVER_COMPLETEPORT)=(outputTxtV(TXT("[Unit test compile disabled] sockReceiver_completePort.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"sockReceiver_completePort.h\".")
    #endif
#endif // COMPILE_EXAMPLE_SOCKRECEIVER_COMPLETEPORT

