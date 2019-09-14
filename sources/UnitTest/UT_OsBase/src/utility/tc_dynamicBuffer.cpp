#include "../../testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase\dynamicBuffer.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_DYNAMICBUFFER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_DYNAMICBUFFER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_DYNAMICBUFFER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_DYNAMICBUFFER
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_DYNAMICBUFFER
#endif

//#undef RUN_EXAMPLE_DYNAMICBUFFER
//#undef COMPILE_EXAMPLE_DYNAMICBUFFER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_DYNAMICBUFFER
#include <utility/dynamicBuffer.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    void testAlign()
    {
        PrintTestcase();
        outputTxt(TXT("Test align:\ndown\tnum\t\tup\n"));
        for (int i=-8;i<55;i++)
        {
            outputTxtV(TXT("%d\t\t%d\t\t%d\n"),AlignDown(i,8),i,AlignUp(i,8));
        }
    }

    inline void TestCase_dynamicBuffer()
    {
        PrintTestcase();

        testAlign();

        TDynamicBuffer<int>     bufInt;
        bufInt.getBuffer(55);
        ASSERT_AND_LOG(AlignUp(55,8)==bufInt.getCapacity());
        TDynamicBuffer<int*>    bufIntP;
        bufIntP.getBuffer(32);
        ASSERT_AND_LOG(AlignUp(32,8)==bufIntP.getCapacity());

        CRingBuf<double> bufDou(33);
        ASSERT_AND_LOG(33==bufDou.getCapacity());
        CRingBuf<double*> bufDouP(32);
        ASSERT_AND_LOG(32==bufDouP.getCapacity());
    }

#ifdef RUN_EXAMPLE_DYNAMICBUFFER
    InitRunFunc(TestCase_dynamicBuffer);
#else //else of RUN_EXAMPLE_DYNAMICBUFFER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] dynamicBuffer.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"dynamicBuffer.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_DYNAMICBUFFER
}

#else //else of COMPILE_EXAMPLE_DYNAMICBUFFER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] dynamicBuffer.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"dynamicBuffer.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_DYNAMICBUFFER

