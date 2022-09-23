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

#if defined(RUN_EXAMPLE_STDWRAPPER) && !defined(COMPILE_EXAMPLE_STDWRAPPER)
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

namespace UnitTest
{
    using namespace MiniMPL;

	DECLARE_PTRS_STRUCT(S3);
	DECLARE_PTRS_STRUCT(S4);
	DECLARE_PTRS_STRUCT(CParameters1);

	char				GetMaxChar()				{	return (std::numeric_limits<char>::max)();				}
	int					GetMaxInt()					{	return (std::numeric_limits<int>::max)();				}
	unsigned short		GetMaxUShort()				{	return (std::numeric_limits<unsigned short>::max)();	}
	char				GetMinChar()				{	return (std::numeric_limits<char>::min)();				}
	int					GetMinInt()					{	return (std::numeric_limits<int>::min)();				}
	unsigned short		GetMinUShort()				{	return (std::numeric_limits<unsigned short>::min)();	}

	inline void TestCase_maxMinValue()
	{
		PrintTestcase();
		
		const int iMax = _maxValue;
		AssertB((iMax == 0x7fffffff));
		const unsigned int iuMax = _maxValue;
		AssertB((iuMax == 0xffffffff));

		const int iMin = _minValue;
		AssertB((iMin == 0x80000000));
		const unsigned int iuMin = _minValue;
		AssertB((iuMin == 0));

		AssertB((_maxValue == GetMaxChar()));
		AssertB((_maxValue == GetMaxInt()));
		AssertB((_maxValue == GetMaxUShort()));
		AssertB((_minValue != GetMaxChar()));
		AssertB((_minValue != GetMaxInt()));
		AssertB((_minValue != GetMaxUShort()));
		AssertB((GetMaxChar()	== _maxValue));
		AssertB((GetMaxInt()	== _maxValue));
		AssertB((GetMaxUShort() == _maxValue));
		AssertB((GetMaxChar()	!= _minValue));
		AssertB((GetMaxInt()	!= _minValue));
		AssertB((GetMaxUShort() != _minValue));

		AssertB((_maxValue != GetMinChar()));
		AssertB((_maxValue != GetMinInt()));
		AssertB((_maxValue != GetMinUShort()));
		AssertB((_minValue == GetMinChar()));
		AssertB((_minValue == GetMinInt()));
		AssertB((_minValue == GetMinUShort()));
		AssertB((GetMinChar()	!= _maxValue));
		AssertB((GetMinInt()	!= _maxValue));
		AssertB((GetMinUShort() != _maxValue));
		AssertB((GetMinChar()	== _minValue));
		AssertB((GetMinInt()	== _minValue));
		AssertB((GetMinUShort() == _minValue));

#if CPP11_ENABLED
		AssertB(( Maxs(1,2,3,4,5) == 5));
		AssertB((Maxs(-1, -2, -3, -4, -5) == -1));
		AssertB((Maxs(-1, -2, 3, 4, 5) == 5));
		AssertB((Mins(1, 2, 3, 4, 5) == 1));
		AssertB((Mins(-1, -2, -3, -4, -5) == -5));
		AssertB((Mins(-1, -2, 3, 4, 5) == -2));
#endif		
	}

	inline void TestCase_sharedArrayGenerator()
	{
		PrintTestcase();

		std::shared_ptr<int> p = _sharedPtrArray(3);		
		int* pm = &*p;
		p.get()[0] = 1;
		AssertB((p.get()[0] == pm[0]));
		p.get()[1] = 2;
		AssertB((p.get()[1] == pm[1]));
		p.get()[2] = 3;
		AssertB((p.get()[2] == pm[2]));
		p.reset();
	}

	inline void TestCase_sharedGenerator()
    {
		PrintTestcase();

		S3Ptr	pS3							= _sharedPtrGenerater;
		S4Ptr	pS4							= _sharedPtrGenerater;
		CParameters1Ptr	pCParameters1		= _sharedPtrGenerater;

		int val = 5;
		CParameters1Ptr pCParameters2		= _sharedPtrGenerater(val);
		AssertB((5== val));
		CParameters1Ptr pCParameters2_1		= _sharedPtrGenerater(55);
		CParameters1Ptr pCParameters3		= _sharedPtrGenerater(*pS4);
		CParameters1Ptr pCParameters4		= _sharedPtrGenerater(val, '6');
		AssertB((7 == val));		
    }

#ifdef RUN_EXAMPLE_STDWRAPPER    
	InitRunFunc(TestCase_maxMinValue);
	InitRunFunc(TestCase_sharedArrayGenerator);
	InitRunFunc(TestCase_sharedGenerator);
#else //else of RUN_EXAMPLE_STDWRAPPER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_STDWRAPPER)=(outputTxtV(TXT("[Unit test run disabled] stdwrapper.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"stdwrapper.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_STDWRAPPER
}

#else //else of COMPILE_EXAMPLE_STDWRAPPER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_STDWRAPPER)=(outputTxtV(TXT("[Unit test compile disabled] stdwrapper.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"stdwrapper.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_STDWRAPPER

