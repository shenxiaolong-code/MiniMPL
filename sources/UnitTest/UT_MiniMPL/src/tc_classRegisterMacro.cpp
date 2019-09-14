#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\classRegisterMacro.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_CLASSREGISTERMACRO to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_CLASSREGISTERMACRO

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_CLASSREGISTERMACRO
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_CLASSREGISTERMACRO
#endif

#if defined(RUN_EXAMPLE_CLASSREGISTERMACRO) && !defined(COMPILE_EXAMPLE_CLASSREGISTERMACRO)
    #define COMPILE_EXAMPLE_CLASSREGISTERMACRO
#endif

//#undef RUN_EXAMPLE_CLASSREGISTERMACRO
//#undef COMPILE_EXAMPLE_CLASSREGISTERMACRO

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_CLASSREGISTERMACRO
#include <MiniMPL/classRegisterMacro.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
#define Link_ClassRegister_Symbol_UnitTest(X)  Link_ClassRegister_Symbol_N1(UnitTest,X)
    
    inline void TestCase_classRegisterMacro()
    {
        PrintTestcase();

        //S1,S2 has not user deconstruction
        Link_ClassRegister_Symbol_N1(UnitTest,S1);
        Link_ClassRegister_Symbol_UnitTest(S1);

        Link_ClassRegister_Symbol_N1(UnitTest,S2);
        Link_ClassRegister_Symbol_UnitTest(S2);

        Link_ClassRegister_Symbol_N1(UnitTest,S3);
        Link_ClassRegister_Symbol_UnitTest(S3);

        Link_ClassRegister_Symbol_N1(UnitTest,S4);
        Link_ClassRegister_Symbol_UnitTest(S4);
    }

#ifdef RUN_EXAMPLE_CLASSREGISTERMACRO
    InitRunFunc(TestCase_classRegisterMacro);
#else //else of RUN_EXAMPLE_CLASSREGISTERMACRO

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_CLASSREGISTERMACRO)=(outputTxtV(TXT("[Unit test run disabled] classRegisterMacro.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"classRegisterMacro.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_CLASSREGISTERMACRO
}

#else //else of COMPILE_EXAMPLE_CLASSREGISTERMACRO
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_CLASSREGISTERMACRO)=(outputTxtV(TXT("[Unit test compile disabled] classRegisterMacro.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"classRegisterMacro.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_CLASSREGISTERMACRO

