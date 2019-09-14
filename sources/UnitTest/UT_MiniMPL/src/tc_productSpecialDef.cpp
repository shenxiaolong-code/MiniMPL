#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\productSpecialDef.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_PRODUCTSPECIALDEF to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_PRODUCTSPECIALDEF

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_PRODUCTSPECIALDEF
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_PRODUCTSPECIALDEF
#endif

#if defined(RUN_EXAMPLE_PRODUCTSPECIALDEF) && !defined(COMPILE_EXAMPLE_PRODUCTSPECIALDEF)
    #define COMPILE_EXAMPLE_PRODUCTSPECIALDEF
#endif

//#undef RUN_EXAMPLE_PRODUCTSPECIALDEF
#undef COMPILE_EXAMPLE_PRODUCTSPECIALDEF

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_PRODUCTSPECIALDEF
#include <MiniMPL/productSpecialDef.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    inline void TestCase_productSpecialDef()
    {
        PrintTestcase();
        ASSERT_AND_LOG_INFO(0,(TXT("Not implemented")));	
        Static_Assert(0);

    }

#ifdef RUN_EXAMPLE_PRODUCTSPECIALDEF
    InitRunFunc(TestCase_productSpecialDef);
#else //else of RUN_EXAMPLE_PRODUCTSPECIALDEF

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_PRODUCTSPECIALDEF)=(outputTxtV(TXT("[Unit test run disabled] productSpecialDef.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"productSpecialDef.h\".")
    #endif
#endif  	// RUN_EXAMPLE_PRODUCTSPECIALDEF
}

#else //else of COMPILE_EXAMPLE_PRODUCTSPECIALDEF
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_PRODUCTSPECIALDEF)=(outputTxtV(TXT("[Unit test compile disabled] productSpecialDef.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"productSpecialDef.h\".")
    #endif
#endif // COMPILE_EXAMPLE_PRODUCTSPECIALDEF

