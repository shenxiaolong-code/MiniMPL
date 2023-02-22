#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\paramPack.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_PARAMPACK to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_PARAMPACK

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_PARAMPACK
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_PARAMPACK
#endif

#if defined(RUN_EXAMPLE_PARAMPACK) && !defined(COMPILE_EXAMPLE_PARAMPACK)
    #define COMPILE_EXAMPLE_PARAMPACK
#endif

//#undef RUN_EXAMPLE_PARAMPACK
//#undef COMPILE_EXAMPLE_PARAMPACK

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_PARAMPACK
#include <MiniMPL/paramPack.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <ut_material/tc_def_paramPackage.h>
#include <MiniMPL/isXXXEx.hpp>

namespace UnitTest
{
#if CPP11_ENABLED
	inline void TestCase_paramPack_cpp11()
	{
		PrintTestcase();
		using namespace MiniMPL;

		ParamPackage11<int, char, int, char> oPP11(3, 4, 5, 6);
		oPP11 ;
	}

    template < typename TensorA, typename TensorB, typename TensorC, typename TensorD>  struct test_complex_type;
    template <typename T>  struct getType_TensorB: public MiniMPL::getFormalParamterType_t<T,1> {};
    template <typename T>  struct getType_TensorC: public MiniMPL::getFormalParamterType_t<T,2> {};

    inline void TestCase_getFormalParamterType_cpp11()
    {
        PrintTestcase();

        using namespace MiniMPL;

        typedef test_complex_type<int, char, float, double>             complex_type;
        typedef getType_TensorB<complex_type>::type                     TensorB_T;
        Static_Assert((IsSameType<TensorB_T,char>::value));

        typedef getType_TensorC<complex_type>::type                     TensorC_T;
        Static_Assert((IsSameType<TensorC_T,float>::value));
    }
#endif

    inline void TestCase_paramPack()
    {
        PrintTestcase();
       
        using namespace MiniMPL;

        Static_Assert((0==ParamPackageSize<ParamPackage0_T>::value));
        Static_Assert((1==ParamPackageSize<ParamPackage1_T>::value));
        Static_Assert((2==ParamPackageSize<ParamPackage2_T>::value));
        Static_Assert((3==ParamPackageSize<ParamPackage3_T>::value));
        Static_Assert((4==ParamPackageSize<ParamPackage4_T>::value));
        Static_Assert((5==ParamPackageSize<ParamPackage5_T>::value));
        Static_Assert((6==ParamPackageSize<ParamPackage6_T>::value));

        //Static_Assert((IsSameType<typename ParamPackageAt<ParamPackage6_T,0>::type,int>::value)); //0 doesn't exist

        Static_Assert((IsSameType<typename ParamPackageAt<ParamPackage6_T,1>::type,int>::value));
        Static_Assert(!(IsSameType<typename ParamPackageAt<ParamPackage6_T,1>::type,int*>::value));
        Static_Assert((IsSameType<typename ParamPackageAt<ParamPackage6_T,2>::type,char>::value));
        Static_Assert(!(IsSameType<typename ParamPackageAt<ParamPackage6_T,2>::type,char*>::value));
        Static_Assert((IsSameType<typename ParamPackageAt<ParamPackage6_T,3>::type,void>::value));
        Static_Assert(!(IsSameType<typename ParamPackageAt<ParamPackage6_T,3>::type,void*>::value));
        Static_Assert((IsSameType<typename ParamPackageAt<ParamPackage6_T,4>::type,void*>::value));
        Static_Assert(!(IsSameType<typename ParamPackageAt<ParamPackage6_T,4>::type,int*>::value));
        Static_Assert((IsSameType<typename ParamPackageAt<ParamPackage6_T,5>::type,float>::value));
        Static_Assert(!(IsSameType<typename ParamPackageAt<ParamPackage6_T,5>::type,int*>::value));
        Static_Assert((IsSameType<typename ParamPackageAt<ParamPackage6_T,6>::type,double>::value));
        Static_Assert(!(IsSameType<typename ParamPackageAt<ParamPackage6_T,6>::type,int*>::value));
        //Static_Assert((IsSameType<typename ParamPackageAt<ParamPackage6_T,7>::type,int>::value));  //max support 6,7 doesn't exist

        //test IsParamPackage
        Static_Assert(!(IsParamPackage<int>::value));
        Static_Assert(!(IsParamPackage<int*>::value));
        Static_Assert(!(IsParamPackage<void>::value));
        Static_Assert(!(IsParamPackage<void*>::value));
        Static_Assert(!(IsParamPackage<char*>::value));
        Static_Assert((IsParamPackage<ParamPackage0_T>::value));
        Static_Assert((IsParamPackage<ParamPackage1_T>::value));
        Static_Assert((IsParamPackage<ParamPackage2_T>::value));
        Static_Assert((IsParamPackage<ParamPackage3_T>::value));
        Static_Assert((IsParamPackage<ParamPackage4_T>::value));
        Static_Assert((IsParamPackage<ParamPackage5_T>::value));
    }

#ifdef RUN_EXAMPLE_PARAMPACK
    InitRunFunc(TestCase_paramPack);
#if CPP11_ENABLED
	InitRunFunc(TestCase_paramPack_cpp11);
    InitRunFunc(TestCase_getFormalParamterType_cpp11);
#endif
#else //else of RUN_EXAMPLE_PARAMPACK

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_PARAMPACK)=(outputTxtV(TXT("[Unit test run disabled] paramPack.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"paramPack.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_PARAMPACK
}

#else //else of COMPILE_EXAMPLE_PARAMPACK
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_PARAMPACK)=(outputTxtV(TXT("[Unit test compile disabled] paramPack.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"paramPack.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_PARAMPACK

