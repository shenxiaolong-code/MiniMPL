#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL/stdwrapper.hpp>
* Author              : Shen.Xiaolong (2009-Tue ) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_STDWRAPPER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_STDWRAPPER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_STDWRAPPER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_STDWRAPPER
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_STDWRAPPER
#endif

//#undef RUN_EXAMPLE_STDWRAPPER
//#undef COMPILE_EXAMPLE_STDWRAPPER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_STDWRAPPER
#include <MiniMPL/stdwrapper.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <MiniMPL/macro_makeVar.h>
#include <UT_material/tc_def_typeStruct.h>

#pragma comment(lib,"MiniMPL.lib")

namespace UnitTest
{
    using namespace MiniMPL;

	DECLARE_PTRS_STRUCT(S3);
	DECLARE_PTRS_STRUCT(S4);
	DECLARE_PTRS_STRUCT(CParameters1);

    inline void TestCase_stdwrapper()
    {
		PrintTestcase();

		S3Ptr	pS3 = _sharedPtrGenerater;
		S4Ptr	pS4 = _sharedPtrGenerater;
		CParameters1Ptr	pCParameters1 = _sharedPtrGenerater;

		int val = 5;
		CParameters1Ptr pCParameters2 = _sharedPtrGenerater(val);
		AssertB((5== val));
		CParameters1Ptr pCParameters2_1 = _sharedPtrGenerater(55);
		CParameters1Ptr pCParameters3 = _sharedPtrGenerater(*pS4);
		CParameters1Ptr pCParameters4 = _sharedPtrGenerater(val, '6');
		AssertB((7 == val));

		const int iMax = _maxValue;
		AssertB((iMax == 0x7fffffff));
		const unsigned int iuMax = _maxValue;
		AssertB((iuMax == 0xffffffff));

		const int iMin = _minValue;
		AssertB((iMin == 0x80000000));
		const unsigned int iuMin = _minValue;
		AssertB((iuMin == 0));

		std::shared_ptr<int> p = _sharedPtrArray(3);
		int* pi = &*p;
		p.get()[0] = 1;
		p.get()[1] = 2;
		p.get()[2] = 3;
		p.reset();
    }

#ifdef RUN_EXAMPLE_STDWRAPPER
    InitRunFunc(TestCase_stdwrapper);
#else //else of RUN_EXAMPLE_STDWRAPPER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] stdwrapper.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"stdwrapper.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_STDWRAPPER
}

#else //else of COMPILE_EXAMPLE_STDWRAPPER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] stdwrapper.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"stdwrapper.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_STDWRAPPER

