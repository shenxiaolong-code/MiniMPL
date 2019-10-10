#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL/tupleUnpacker.hpp>
* Author              : Shen.Xiaolong (at Mon 10/07/2019) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_TUPLEUNPACKER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_TUPLEUNPACKER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_TUPLEUNPACKER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_TUPLEUNPACKER
#endif

#if defined(RUN_EXAMPLE_TUPLEUNPACKER) && !defined(COMPILE_EXAMPLE_TUPLEUNPACKER)
    #define COMPILE_EXAMPLE_TUPLEUNPACKER
#endif

//#undef RUN_EXAMPLE_TUPLEUNPACKER
//#undef COMPILE_EXAMPLE_TUPLEUNPACKER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_TUPLEUNPACKER
#include <MiniMPL/tupleUnpacker.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    using namespace MiniMPL;

	struct demo_accept_functor
	{
		int operator()(int a, char b)
		{
			ALWAYS_LOG_HERE();
			return a + b;
		}
	};

	template<typename... TArgs>
	void f_tupleUnpacker(TArgs... args)
	{
		ALWAYS_LOG_HERE();
	}

	//variadic template function (f_tupleUnpacker) is not deduced type before it is called. it needs one wrapper.
	declare_variadic_template_function(f_tupleUnpacker);		

	void f_tupleUnpacker1(int a)
	{
		ALWAYS_LOG_HERE();
	}

	int f_tupleUnpacker2(int a, char b)
	{
		ALWAYS_LOG_HERE();
		return a + b;
	}

	float f_tupleUnpacker3(int a, char b,float c)
	{
		ALWAYS_LOG_HERE();
		return a + b+c;
	}


    inline void TestCase_tupleUnpacker()
    {
        PrintTestcase();

		unpackCall(f_tupleUnpacker_f(), std::make_tuple(1, 2, 3, "hello,test f_tupleUnpacker"));
		//unpackCall(f_tupleUnpacker, std::make_tuple(1));	//error : because f_tupleUnpacker is not actual real type before it is not instantiation
		unpackCall(demo_accept_functor(), std::make_tuple(1, 2));

		unpackCall(f_tupleUnpacker1, std::make_tuple(1));
		unpackCall(f_tupleUnpacker2, std::make_tuple(1,'c'));
		unpackCall(f_tupleUnpacker2, std::make_tuple(1, 22));
		//unpackCall(f_tupleUnpacker2, std::make_tuple(1, "error"));	//OK : expected compile error.
		unpackCall(f_tupleUnpacker3, std::make_tuple(1, 'c', 4.5f));

		//directly call
		f_tupleUnpacker_f							obj;
		tuple_Unpacker<f_tupleUnpacker_f>			unpacker(obj);
		unpacker.apply(std::make_tuple(1, 22));
		unpacker.apply(std::make_tuple(1, 22,"hello,here"));

		//friendly usage
		make_tuple_Unpacker(demo_accept_functor()).apply(std::make_tuple(1, 22));
    }

#ifdef RUN_EXAMPLE_TUPLEUNPACKER
    InitRunFunc(TestCase_tupleUnpacker);
#else //else of RUN_EXAMPLE_TUPLEUNPACKER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_TUPLEUNPACKER)=(outputTxtV(TXT("[Unit test run disabled] tupleUnpacker.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"tupleUnpacker.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_TUPLEUNPACKER
}

#else //else of COMPILE_EXAMPLE_TUPLEUNPACKER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_TUPLEUNPACKER)=(outputTxtV(TXT("[Unit test compile disabled] tupleUnpacker.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"tupleUnpacker.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_TUPLEUNPACKER

