#include "../../testconfig_OsBase.h"
#include <MiniMPL/macroDef.h>
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\registry.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_REGISTRY to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_REGISTRY

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_REGISTRY
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_REGISTRY
#endif

#if defined(RUN_EXAMPLE_REGISTRY) && !defined(COMPILE_EXAMPLE_REGISTRY)
    #define COMPILE_EXAMPLE_REGISTRY
#endif

//#undef RUN_EXAMPLE_REGISTRY
//#undef COMPILE_EXAMPLE_REGISTRY

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_REGISTRY
#include <win32/registry.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    struct tagTZREG {
        LONG Bias;
        LONG StandardBias;
        LONG DaylightBias;
        SYSTEMTIME StandardDate;
        SYSTEMTIME DaylightDate;
    };

    inline void TestCase_registry_binData()
    {
        PrintTestcase();
        using namespace OS_Win32;

        tagTZREG regTZI={0};
        stlString const TZI_Key = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones\\China Standard Time";
        CRegistry reg(HKEY_LOCAL_MACHINE);
        ULONG nBytes = sizeof(tagTZREG);
        ASSERT_AND_LOG(reg.open(TZI_Key));
        ASSERT_AND_LOG(reg.readBinaryValue(TXT("TZI"),(unsigned char *)(&regTZI),nBytes));
    }

    inline void TestCase_registry()
    {
        PrintTestcase();
        using namespace OS_Win32;

        stlString rootKey = TXT("Software\\Microsoft\\Windows");
        stlVector<stlString> subKeys;
        CRegistry reg(HKEY_LOCAL_MACHINE);
        reg.listSubKeys(rootKey,subKeys);
        ASSERT_AND_LOG(subKeys.size()>0);
        outputTxtV(TXT("key[%s] has %d subKeys."),rootKey.c_str(),subKeys.size());

        stlString keyPath=TXT("Software\\Microsoft\\Windows\\Windows Error Reporting");
        stlString keyVal;
        ASSERT_AND_LOG(reg.open(keyPath));  //open key
        reg.readStringValue(TXT("ErrorPort"),keyVal);
        ASSERT_AND_LOG(0!=keyVal.size());
        outputTxtV(TXT("\nvalue of [%s\\ErrorPort] is [%s]"),keyPath.c_str(),keyVal.c_str());
    }

#ifdef RUN_EXAMPLE_REGISTRY
    InitRunFunc(TestCase_registry);
    InitRunFunc(TestCase_registry_binData);
#else //else of RUN_EXAMPLE_REGISTRY

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_REGISTRY)=(outputTxtV(TXT("[Unit test run disabled] registry.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"registry.h\".")
    #endif
#endif  	// RUN_EXAMPLE_REGISTRY
}

#else //else of COMPILE_EXAMPLE_REGISTRY
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_REGISTRY)=(outputTxtV(TXT("[Unit test compile disabled] registry.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"registry.h\".")
    #endif
#endif // COMPILE_EXAMPLE_REGISTRY

