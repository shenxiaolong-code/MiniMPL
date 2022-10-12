#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\hasXXX.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_HASXXX to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_HASXXX

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_HASXXX
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_HASXXX
#endif

#if defined(RUN_EXAMPLE_HASXXX) && !defined(COMPILE_EXAMPLE_HASXXX)
    #define COMPILE_EXAMPLE_HASXXX
#endif

//#undef RUN_EXAMPLE_HASXXX
//#undef COMPILE_EXAMPLE_HASXXX

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_HASXXX
#include <MiniMPL/hasXXX.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{
    HasXXXType(abc);
    HasXXXType(int_T);
    HasXXXType(type);

    HasXXXMethod(print,void (U::*)(),);
    HasXXXMethod(print,void (U::*)(),1);
    HasXXXMethod(print,void (U::*)(char*),2);
    HasXXXMethod(print,void (U::*)() const,3);

    HasXXXMethod(print1Param,void(U::*)(int),);

    HasXXXMember(m_a);

    inline void TestCase_hasXXX()
    {
        PrintTestcase();
        using namespace MiniMPL;

        Static_Assert((HasMethod_print<S4>::value));
        Static_Assert((HasMethod1_print<S4>::value));
        Static_Assert(!(HasMethod2_print<S4>::value));
        Static_Assert(!(HasMethod3_print<S4>::value));
        Static_Assert(!(HasMethod3_print<S3>::value));

        Static_Assert(!(HasMethod_print1Param<S3>::value));
        Static_Assert((HasMethod_print1Param<S4>::value));

        Static_Assert(!(HasMethod_print<bool>::value));
        Static_Assert(!(HasMethod_print<int>::value));
        Static_Assert(!(HasMethod_print<Type2Type<bool> >::value));
        Static_Assert(!(HasMethod_print<Type2Type<char> >::value));
        Static_Assert(!(HasMethod_print<Type2Type<S4> >::value));

        //////////////////////////////////////////////////////////////////////////
        Static_Assert(!(HasType_abc<bool>::value));
        Static_Assert(!(HasType_abc<char>::value));
        Static_Assert(!(HasType_abc<unsigned char>::value));
        Static_Assert(!(HasType_abc<short>::value));
        Static_Assert(!(HasType_abc<unsigned short>::value));
        Static_Assert(!(HasType_abc<int>::value));
        Static_Assert(!(HasType_abc<unsigned int>::value));
        Static_Assert(!(HasType_abc<long>::value));
        Static_Assert(!(HasType_abc<unsigned long>::value));
        Static_Assert(!(HasType_abc<float>::value));
        Static_Assert(!(HasType_abc<double>::value));
        Static_Assert(!(HasType_abc<__int64>::value));
        Static_Assert(!(HasType_abc<unsigned __int64>::value));

        Static_Assert((HasType_type<Type2Type<bool> >::value));
        Static_Assert((HasType_type<Type2Type<char> >::value));
        Static_Assert((HasType_type<Type2Type<unsigned char> >::value));
        Static_Assert((HasType_type<Type2Type<short> >::value));
        Static_Assert((HasType_type<Type2Type<unsigned short> >::value));
        Static_Assert((HasType_type<Type2Type<int> >::value));
        Static_Assert((HasType_type<Type2Type<unsigned int> >::value));
        Static_Assert((HasType_type<Type2Type<long> >::value));
        Static_Assert((HasType_type<Type2Type<unsigned long> >::value));
        Static_Assert((HasType_type<Type2Type<float> >::value));
        Static_Assert((HasType_type<Type2Type<double> >::value));
        Static_Assert((HasType_type<Type2Type<__int64> >::value));
        Static_Assert((HasType_type<Type2Type<unsigned __int64> >::value));

        Static_Assert(!(HasType_abc<S1>::value));
        Static_Assert(!(HasType_abc<S2>::value));
        Static_Assert(!(HasType_abc<S3>::value));
        Static_Assert(!(HasType_abc<S4>::value));

        Static_Assert((HasType_type<Type2Type<S1> >::value));
        Static_Assert((HasType_type<Type2Type<S2> >::value));
        Static_Assert((HasType_type<Type2Type<S3> >::value));
        Static_Assert((HasType_type<Type2Type<S4> >::value));

        Static_Assert((HasType_int_T<structData>::value));
        Static_Assert(!(HasType_abc<S4>::value));

        Static_Assert((HasMember_m_a<structData>::value));
        Static_Assert((HasMember_m_a<ConstStruct>::value));
        Static_Assert(!(HasMember_m_a<MFStruct0_6>::value));
        Static_Assert(!(HasMember_m_a<S2>::value));
    }

#ifdef RUN_EXAMPLE_HASXXX
    InitRunFunc(TestCase_hasXXX);
#else //else of RUN_EXAMPLE_HASXXX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_HASXXX)=(outputTxtV(TXT("[Unit test run disabled] hasXXX.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"hasXXX.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_HASXXX
}

#else //else of COMPILE_EXAMPLE_HASXXX
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_HASXXX)=(outputTxtV(TXT("[Unit test compile disabled] hasXXX.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"hasXXX.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_HASXXX

