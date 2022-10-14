#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\any_cast.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_ANY_CAST to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_ANY_CAST

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_ANY_CAST
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_ANY_CAST
#endif

#if defined(RUN_EXAMPLE_ANY_CAST) && !defined(COMPILE_EXAMPLE_ANY_CAST)
    #define COMPILE_EXAMPLE_ANY_CAST
#endif

//#undef RUN_EXAMPLE_ANY_CAST
//#undef COMPILE_EXAMPLE_ANY_CAST

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_ANY_CAST
#include <MiniMPL/any_cast.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{
    typedef     int MFStruct0_6::* PMemData_T;
    typedef     int(__stdcall* PMemFunc_T)(int, char);

    inline void TestCase_any_cast_func()
    {
        PrintTestcase();
        PMemData_T  pData = MiniMPL::any_cast(11);
        PMemFunc_T  pFunc = MiniMPL::any_cast(22);
        // float/double and int/int-similar cast will cause the wrong result because of their different storage mechanism.
        // PMemFunc_T  pFunc = MiniMPL::any_cast<PMemFunc_T>(33.33);        // wrong result , although compile pass

        long  lData = MiniMPL::any_cast(pData);
        Assertb(11==lData);
        int   iData = MiniMPL::CAnyCast::make(pData);
        Assertb(11 == iData);
        long  lFunc = MiniMPL::any_cast(pFunc);
        Assertb(22==lFunc);

        // float  fData = MiniMPL::any_cast<float>(pData);                  // wrong result , although compile pass
    }

    inline void TestCase_any_cast_object()
    {
        PrintTestcase();

        PMemData_T  pData  = _anycast(44);
        PMemFunc_T  pFunc  = _anycast(55);
        // float/double and int/int-similar cast will cause the wrong result because of their different storage mechanism.
        // PMemFunc_T  pFunc  = _anycast(66.66);                            // wrong result , although compile pass

        long        dData = _anycast(pData);
        Assertb(44==dData);
        long        dFunc = _anycast(pFunc);
        Assertb(55==dFunc);

        // double   dFunc  = _anycast(pData);                              // wrong result , although compile pass
    }

#ifdef RUN_EXAMPLE_ANY_CAST
    InitRunFunc(TestCase_any_cast_func);
    InitRunFunc(TestCase_any_cast_object);
#else //else of RUN_EXAMPLE_ANY_CAST

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_ANY_CAST)=(outputTxtV(TXT("[Unit test run disabled] any_cast.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"any_cast.hpp\".")
    #endif
#endif      // RUN_EXAMPLE_ANY_CAST
}

#else //else of COMPILE_EXAMPLE_ANY_CAST
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_ANY_CAST)=(outputTxtV(TXT("[Unit test compile disabled] any_cast.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"any_cast.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_ANY_CAST

