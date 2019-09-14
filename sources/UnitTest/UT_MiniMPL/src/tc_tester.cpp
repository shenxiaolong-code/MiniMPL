#include "../testconfig_MiniMPL.h"
#include "UT_material/tc_def_globalFunc.h"
#include "MiniMPL/unaryFunctionCreater.hpp"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\tester.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_TESTER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_TESTER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_TESTER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_TESTER
#endif

#if defined(RUN_EXAMPLE_TESTER) && !defined(COMPILE_EXAMPLE_TESTER)
    #define COMPILE_EXAMPLE_TESTER
#endif

//#undef RUN_EXAMPLE_TESTER
//#undef COMPILE_EXAMPLE_TESTER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_TESTER
#include <MiniMPL/tester.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{
    inline void  TestCase_UnaryTester()
    {
        PrintTestcaseSub();
        using namespace MiniMPL;
        S4  rObj;

        //test UnaryTester
        ASSERT_AND_LOG(makeUnaryTester(rObj.m_ss3,CEqual(),true)(rObj.m_ss3));
        ASSERT_AND_LOG(!makeUnaryTester(rObj.m_ss3,CNotEqual(),true)(rObj.m_ss3));
        ASSERT_AND_LOG(!makeUnaryTester(rObj.m_ss3,CLesser(),true)(rObj.m_ss3));
        ASSERT_AND_LOG(makeUnaryTester(rObj.m_ss3,CLesserEqual(),true)(rObj.m_ss3));
        ASSERT_AND_LOG(!makeUnaryTester(rObj.m_ss3,CGreater(),true)(rObj.m_ss3));
        ASSERT_AND_LOG(makeUnaryTester(rObj.m_ss3,CGreaterEqual(),true)(rObj.m_ss3));

        //test UnaryTester_Result
        ASSERT_AND_LOG(makeUnaryTester_Result(&S4::m_ss3,rObj.m_ss3,CEqual(),true)(rObj));
        ASSERT_AND_LOG(!makeUnaryTester_Result(&S4::m_ss3,rObj.m_ss3,CLesser(),true)(rObj));
        ASSERT_AND_LOG(makeUnaryTester_Result(getS3FromS4Ref,rObj.m_ss3,CEqual(),true)(rObj));
        ASSERT_AND_LOG(!makeUnaryTester_Result(getS3FromS4Ref,rObj.m_ss3,CGreater(),true)(rObj));

        //test UnaryTester_Combined
        ASSERT_AND_LOG(makeUnaryTester_Combined<'&'>(makeUnaryTester_Result(&S4::m_ss3,rObj.m_ss3,CEqual(),true),makeUnaryTester_Result(getS3FromS4Ref,rObj.m_ss3,CEqual(),true))(rObj));
        ASSERT_AND_LOG(makeUnaryTester_Combined<'|'>(makeUnaryTester_Result(&S4::m_ss3,rObj.m_ss3,CLesser(),true),makeUnaryTester_Result(getS3FromS4Ref,rObj.m_ss3,CEqual(),true))(rObj));
        ASSERT_AND_LOG(makeUnaryTester_Combined<'^'>(makeUnaryTester_Result(&S4::m_ss3,rObj.m_ss3,CLesser(),true),makeUnaryTester_Result(getS3FromS4Ref,rObj.m_ss3,CEqual(),true))(rObj));
    }

    inline void  TestCase_UnaryTester_Combined()
    {
        using namespace MiniMPL;
        S4 obj;

        typedef CDataMemberPtr<int S4::*>                           TUF1_T;
        TUF1_T                                                  rUf1=linkMemberPtr(&S4::m_ss3,&S3::m_s3);
        //test ranger tester
        typedef UnaryTester_Result<TUF1_T,int,TComparer<'('> >          UT1_T;
        typedef UnaryTester_Result<TUF1_T,int,TComparer<')'> >          UT2_T;
        typedef UnaryTester_Combined<'&',UT1_T,UT2_T>                   TCombineTester;
        TCombineTester combineTester = makeUnaryTester_Range<'(','&',')'>(obj.m_ss3.m_s3-2,obj.m_ss3.m_s3+2,rUf1);
        ASSERT_AND_LOG((combineTester(obj)));

        //test combine tester
        typedef S3& (*TFgetS3FromS4Ref)(S4&);
        typedef UnaryFunction<TFgetS3FromS4Ref,1>                       TUF2_T1;
        TUF2_T1 rUf21=makeUnaryFunction(getS3FromS4Ref,_$);
        typedef CDataMemberPtr<int S3::*>                                   TUF2_T2;
        TUF2_T2 rUf22 = makeMemberPtr(&S3::m_s3);
        typedef UnaryFunctionPipe<TUF2_T1,TUF2_T2>                      TUF2_T;
        TUF2_T ruf2 = makeUnaryFunctionPipe(rUf21,rUf22);

        typedef CGetType::TRangeTesterUF<'(','&',')',TUF2_T,int>::type    RangeTesterUF_T1;
        RangeTesterUF_T1 rangeTesterUf1= makeUnaryTester_Range<'(','&',')'>(obj.m_ss3.m_s3-2,obj.m_ss3.m_s3+2,ruf2); 
        ASSERT_AND_LOG((rangeTesterUf1(obj)));

        typedef CGetType::TRangeTesterUF<')','|','(',TUF2_T,int>::type    RangeTesterUF_T2;
        RangeTesterUF_T2 rangeTesterUf2= makeUnaryTester_Range<')','|','('>(obj.m_ss3.m_s3-2,obj.m_ss3.m_s3+2,ruf2); 
        ASSERT_AND_LOG(!(rangeTesterUf2(obj)));

        typedef CGetType::TRangeTesterUF<']','|','(',TUF2_T,int>::type    RangeTesterUF_T21;
        RangeTesterUF_T21 rangeTesterUf21= makeUnaryTester_Range<']','|','('>(obj.m_ss3.m_s3,obj.m_ss3.m_s3+2,ruf2); 
        ASSERT_AND_LOG((rangeTesterUf21(obj)));

        typedef CGetType::TRangeTesterUF<')','|','(',TUF2_T,int>::type    RangeTesterUF_T3;
        RangeTesterUF_T3 rangeTesterUf3= makeUnaryTester_Range<')','|','('>(obj.m_ss3.m_s3+5,obj.m_ss3.m_s3+10,ruf2); 
        ASSERT_AND_LOG((rangeTesterUf3(obj)));

        //test range tester
        int val = 3;
        ASSERT_AND_LOG((makeUnaryTester_Range<'(','&',')'>(2,8)(val)));
        ASSERT_AND_LOG((makeUnaryTester_Range<'[','&',']'>(2,8)(val)));
        ASSERT_AND_LOG(!(makeUnaryTester_Range<'(','&',')'>(3,8)(val)));
        ASSERT_AND_LOG((makeUnaryTester_Range<'[','&',')'>(3,8)(val)));
        ASSERT_AND_LOG(!(makeUnaryTester_Range<'(','&',']'>(3,8)(val)));
        ASSERT_AND_LOG((makeUnaryTester_Range<'(','|',']'>(3,8)(val)));
        ASSERT_AND_LOG((makeUnaryTester_Range<'[','|',']'>(3,8)(val)));
        ASSERT_AND_LOG(!(makeUnaryTester_Range<'[','^',']'>(3,8)(val)));
    }

    inline void TestCase_tester()
    {
        PrintTestcase();
        TestCase_UnaryTester();
        TestCase_UnaryTester_Combined();
    }

#ifdef RUN_EXAMPLE_TESTER
    InitRunFunc(TestCase_tester);
#else //else of RUN_EXAMPLE_TESTER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_TESTER)=(outputTxtV(TXT("[Unit test run disabled] tester.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"tester.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_TESTER
}

#else //else of COMPILE_EXAMPLE_TESTER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_TESTER)=(outputTxtV(TXT("[Unit test compile disabled] tester.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"tester.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_TESTER

