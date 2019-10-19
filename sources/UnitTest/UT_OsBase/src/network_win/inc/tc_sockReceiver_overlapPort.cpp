#include "../../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <network_win/inc/sockReceiver_overlapPort.h>
* Author              : Shen.Xiaolong (at Fri 10/18/2019) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SOCKRECEIVER_OVERLAPPORT to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_SOCKRECEIVER_OVERLAPPORT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SOCKRECEIVER_OVERLAPPORT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SOCKRECEIVER_OVERLAPPORT
#endif

#if defined(RUN_EXAMPLE_SOCKRECEIVER_OVERLAPPORT) && !defined(COMPILE_EXAMPLE_SOCKRECEIVER_OVERLAPPORT)
    #define COMPILE_EXAMPLE_SOCKRECEIVER_OVERLAPPORT
#endif

//#undef RUN_EXAMPLE_SOCKRECEIVER_OVERLAPPORT
//#undef COMPILE_EXAMPLE_SOCKRECEIVER_OVERLAPPORT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SOCKRECEIVER_OVERLAPPORT
#include <network_win/inc/sockReceiver_overlapPort.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_sockReceiver_overlapPort()
    {
        PrintTestcase();
        //ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        
        ALWAYS_COMPILE_MSG("NO Test context for <network_win/inc/sockReceiver_overlapPort.h>");

    }

#ifdef RUN_EXAMPLE_SOCKRECEIVER_OVERLAPPORT
    InitRunFunc(TestCase_sockReceiver_overlapPort);
#else //else of RUN_EXAMPLE_SOCKRECEIVER_OVERLAPPORT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_SOCKRECEIVER_OVERLAPPORT)=(outputTxtV(TXT("[Unit test run disabled] sockReceiver_overlapPort.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"sockReceiver_overlapPort.h\".")
    #endif
#endif  	// RUN_EXAMPLE_SOCKRECEIVER_OVERLAPPORT
}

#else //else of COMPILE_EXAMPLE_SOCKRECEIVER_OVERLAPPORT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_SOCKRECEIVER_OVERLAPPORT)=(outputTxtV(TXT("[Unit test compile disabled] sockReceiver_overlapPort.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"sockReceiver_overlapPort.h\".")
    #endif
#endif // COMPILE_EXAMPLE_SOCKRECEIVER_OVERLAPPORT

