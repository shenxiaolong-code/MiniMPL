#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macroDef.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\macro_class.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MACRO_CLASS to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MACRO_CLASS

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MACRO_CLASS
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MACRO_CLASS
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_MACRO_CLASS
#endif

//#undef RUN_EXAMPLE_MACRO_CLASS
//#undef COMPILE_EXAMPLE_MACRO_CLASS

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MACRO_CLASS
#include <MiniMPL/macro_class.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    class CTestClassDisable_NoDefaultConstructor
    {
    public:
        CTestClassDisable_NoDefaultConstructor(char*){};
        Disable_Class_Default_Constructor(CTestClassDisable_NoDefaultConstructor);
    };

    class CTestClassDisable_NoCopyConstructor
    {
    public:
        CTestClassDisable_NoCopyConstructor(){};
        Disable_Class_Copy_Constructor(CTestClassDisable_NoCopyConstructor);
    };

    class CTestClassDisable_NoAssign
    {
    public:
        Disable_Class_Assign(CTestClassDisable_NoAssign);
    };

    inline void TestCase_macro_class()
    {
        PrintTestcase();

        //CTestClassDisable_NoDefaultConstructor o_nodefCtor; //fails, OK
        CTestClassDisable_NoDefaultConstructor o_normal(NULL);

        CTestClassDisable_NoCopyConstructor o_noCopyCtor;
        //CTestClassDisable_NoCopyConstructor o_noCopyCtor1(o_noCopyCtor);   //fails,OK

        CTestClassDisable_NoAssign od,oc;
        od,oc;
        //od =oc;        //fails , OK
    }

#ifdef RUN_EXAMPLE_MACRO_CLASS
    InitRunFunc(TestCase_macro_class);
#else //else of RUN_EXAMPLE_MACRO_CLASS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] macro_class.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"macro_class.h\".")
    #endif
#endif  	// RUN_EXAMPLE_MACRO_CLASS
}

#else //else of COMPILE_EXAMPLE_MACRO_CLASS
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] macro_class.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"macro_class.h\".")
    #endif
#endif // COMPILE_EXAMPLE_MACRO_CLASS

