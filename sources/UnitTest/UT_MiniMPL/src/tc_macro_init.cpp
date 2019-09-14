#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macroDef.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\macro_init.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MACRO_INIT to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MACRO_INIT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MACRO_INIT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MACRO_INIT
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_MACRO_INIT
#endif

//#undef RUN_EXAMPLE_MACRO_INIT
//#undef COMPILE_EXAMPLE_MACRO_INIT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MACRO_INIT
#include <MiniMPL/macro_init.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    static std::vector<int> gs_testInitRunFunc1;
    static bool gs_testInitRunFunc = false;

    inline void testInitRunFunc()
    {
        gs_testInitRunFunc = true; 
    }

    inline void testInitRunFunc1( std::vector<int>& arr )
    {
        for(int i=0;i<20;i++)
        {
            arr.push_back(rand()%100);
        } 
    }

    inline void TestCase_macro_init()
    {
        PrintTestcase();

        InitRunFunc1(testInitRunFunc1,gs_testInitRunFunc1);
        Assertb(gs_testInitRunFunc1.size() !=0);

        InitRunFunc(testInitRunFunc);
        Assertb(gs_testInitRunFunc==true); 

    }

#ifdef RUN_EXAMPLE_MACRO_INIT
    InitRunFunc(TestCase_macro_init);
#else //else of RUN_EXAMPLE_MACRO_INIT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] macro_init.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"macro_init.h\".")
    #endif
#endif  	// RUN_EXAMPLE_MACRO_INIT
}

#else //else of COMPILE_EXAMPLE_MACRO_INIT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] macro_init.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"macro_init.h\".")
    #endif
#endif // COMPILE_EXAMPLE_MACRO_INIT

