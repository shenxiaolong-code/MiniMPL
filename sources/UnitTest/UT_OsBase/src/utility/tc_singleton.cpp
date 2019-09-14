#include "../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\singleton.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SINGLETON to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_SINGLETON

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SINGLETON
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SINGLETON
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_SINGLETON
#endif

//#undef RUN_EXAMPLE_SINGLETON
//#undef COMPILE_EXAMPLE_SINGLETON

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SINGLETON
#if ENABLE_MACRO_DEMO_ASSERT_BREAK==0
    #if defined(_MSC_VER) && (WINVER >= 0x0500)
        #pragma push_macro("Assert_Trigger")
        #pragma push_macro("ChkExceptionThrow")

        #undef	Assert_Trigger
        #define Assert_Trigger()        0
        #undef	ChkExceptionThrow
        #define ChkExceptionThrow()     0
    #endif	//end defined(_MSC_VER)
#endif   //end ENABLE_MACRO_DEMO_ASSERT_BREAK==0

#include <utility/singleton.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    class CMultiInstanceOK : public SingletonMultiInstance<CMultiInstanceOK,true>
    {
    public:
        void print()
        {
            ALWAYS_LOG_HERE();
        }
    };

    class CMultiInstanceFail : public SingletonMultiInstance<CMultiInstanceFail,false>
    {
    public:
        void print()
        {
            ALWAYS_LOG_HERE();
        }
    };

    inline void TestCase_singleton()
    {
        PrintTestcase();

        CMultiInstanceOK::getInstance().print();
        CMultiInstanceOK oMultiObjOk;

        CMultiInstanceFail::getInstance().print();

        outputTxt(L"\nDemo not allowned multiple instances:");
        CMultiInstanceFail oMultiObjErr;

        //CSingletonDemo oAssign=CSingletonDemo::getInstance(); //OK : No Assign
        //CSingletonDemo oCopy(CSingletonDemo::getInstance());  //OK : No copy
    }

#if ENABLE_MACRO_DEMO_ASSERT_BREAK==0	
    #if defined(_MSC_VER) && (WINVER >= 0x0500)
        #pragma pop_macro("Assert_Trigger")
        #pragma pop_macro("ChkExceptionThrow")
    #endif	//end defined(_MSC_VER)
#endif   //end ENABLE_MACRO_DEMO_ASSERT_BREAK==0

#ifdef RUN_EXAMPLE_SINGLETON
    InitRunFunc(TestCase_singleton);
#else //else of RUN_EXAMPLE_SINGLETON

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] singleton.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"singleton.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_SINGLETON
}

#else //else of COMPILE_EXAMPLE_SINGLETON
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] singleton.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"singleton.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_SINGLETON

