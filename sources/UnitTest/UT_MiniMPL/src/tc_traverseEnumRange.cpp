#include "../testconfig_MiniMPL.h"
#include <ut_material/tc_def_enumRange.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\traverseEnumRange.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_TRAVERSEENUMRANGE to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_TRAVERSEENUMRANGE

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_TRAVERSEENUMRANGE
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_TRAVERSEENUMRANGE
#endif

#if defined(RUN_EXAMPLE_TRAVERSEENUMRANGE) && !defined(COMPILE_EXAMPLE_TRAVERSEENUMRANGE)
    #define COMPILE_EXAMPLE_TRAVERSEENUMRANGE
#endif

//#undef RUN_EXAMPLE_TRAVERSEENUMRANGE
//#undef COMPILE_EXAMPLE_TRAVERSEENUMRANGE

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_TRAVERSEENUMRANGE

#include <MiniMPL/traverseTypeContainer.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <ut_material/td_def_callbackTemplate.h>
#include <UT_material/tc_def_enum.h>
#include <time.h>

namespace UnitTest
{
    typedef MiniMPL::CTraverseTypeContainer<SeqEnumRange,false>       SeqEnumRange0;
    typedef MiniMPL::CTraverseTypeContainer<SeqEnumRange,true>        SeqEnumRange1;
    typedef MiniMPL::CTraverseTypeContainer<NonSeqEnumRange,false>    NonSeqEnumRange0;
    typedef MiniMPL::CTraverseTypeContainer<NonSeqEnumRange,true>     NonSeqEnumRange1;

    //test member function
    void TestCase_traverseEnumRange_MF()
    {
        using namespace MiniMPL;
        PrintTitle1(TXT("TestCase_traverseEnumRange_MF"));

        int a = 5;
        char* pStr = "in testEntry";
        srand( (unsigned)time( NULL ) );            

        CTestEnumSuite obj;
        ASSERT_AND_LOG((NonSeqEnumRange0::applyTester<>::execute<CallBackT(printEnum)>(NS_Val_5,makeParamPackage_Ref(obj))));
        ASSERT_AND_LOG((NonSeqEnumRange1::applyTester<>::execute<CallBackT(printEnum)>(NS_Val_5,makeParamPackage_Ref(obj))));
        ASSERT_AND_LOG((SeqEnumRange0::applyTester<>::execute<CallBackT(printNext)>(S_Val_3,makeParamPackage_Ref(obj))));

        ParamPackageCall<CTestEnumSuite&,int,char*>  params_print2Param(obj,a,pStr);
        ASSERT_AND_LOG((SeqEnumRange1::applyTester<>::execute<CallBackT(print2Param)>(S_Val_6,params_print2Param)));

        //test foreach
        SeqEnumRange1::forEach<CallBackT(print2Param)>(params_print2Param);

        //test in-out parameter            
        char p1 = 3;
        int outP = 6;
        
        ParamPackageCall<CTestEnumSuite&,char,int&>  params_inOutParam(obj,p1,outP);
        ASSERT_AND_LOG((SeqEnumRange0::applyTester<>::execute<CallBackT(inOutParam)>(S_Val_5,params_inOutParam)));
        ASSERT_AND_LOG((p1+2)==outP);
        ASSERT_AND_LOG(SeqEnumRange1::applyTester<>::execute<CallBackT(inOutParam)>(S_Val_5,makeParamPackage_Ref(obj,p1,outP)));
        ASSERT_AND_LOG((p1+2)==outP);

        ASSERT_AND_LOG((p1+outP+S_Val_5+4)==SeqEnumRange1::applyTester<>::execute<CallBackT(getReturnValue)>(S_Val_5,params_inOutParam,-1));

        typedef int (CTestEnumSuite::*pGetRetVal)(char,int);
        pGetRetVal pf=SeqEnumRange1::applyTester<>::getFuncAddr<CallBackT(getReturnValue)>(S_Val_5);
        ASSERT_AND_LOG(pf);
        pf=SeqEnumRange1::applyTester<>::getFuncAddr<CallBackT(getReturnValue)>(S_Val_4);
        ASSERT_AND_LOG(!pf);   //S_Val_4 is skipped

        typedef bool (CTestEnumSuite::*pNoParam)();
        stlMap<NonSeqEunm,pNoParam> rMap10;
        ASSERT_AND_LOG((NonSeqEnumRange0::applyFuncIdGenerator<>::getAllFuncAddr<CallBackT(printEnum)>(rMap10)));
        ASSERT_AND_LOG(CGetEnumRangeSize<NonSeqEnumRange>::value==rMap10.size());

        stlMap<NonSeqEunm,pNoParam> rMap11;
        ASSERT_AND_LOG((NonSeqEnumRange1::applyFuncIdGenerator<>::getAllFuncAddr<CallBackT(printEnum)>(rMap11)));
        ASSERT_AND_LOG(rMap10 ==rMap11 );

        typedef void (CTestEnumSuite::*pParam2ci)(char,int&);
        stlMap<SeqEunm,pParam2ci> rMap20;
        ASSERT_AND_LOG((SeqEnumRange0::applyFuncIdGenerator<>::getAllFuncAddr<CallBackT(inOutParam)>(rMap20)));

        stlMap<SeqEunm,pParam2ci> rMap21;
        ASSERT_AND_LOG((SeqEnumRange1::applyFuncIdGenerator<>::getAllFuncAddr<CallBackT(inOutParam)>(rMap21)));
        ASSERT_AND_LOG(rMap20 ==rMap21 );

        stlMap<SeqEunm,pParam2ci> rMap21New;
        ASSERT_AND_LOG((SeqEnumRange1::applyFuncIdGenerator<>::getAllFuncAddr<CallBackT(inOutParam)>(rMap21New)));
        ASSERT_AND_LOG(rMap20 ==rMap21New );

        ASSERT_AND_LOG((NonSeqEnumRange0::applyTester<>::execute<CallBackT(printEnum)>(NS_Val_5,makeParamPackage_Ref(obj))));
        ASSERT_AND_LOG((NonSeqEnumRange1::applyTester<>::execute<CallBackT(printEnum)>(NS_Val_5,makeParamPackage_Ref(obj))));

        //test global function
        typedef bool (*pGlobalParam2)(int,char*);
        ParamPackageCall<int,char*>  params_globalEnumFunc(a,pStr);
        ASSERT_AND_LOG((SeqEnumRange0::applyTester<>::execute<CallBackT(globalEnumFunc)>(S_Val_Min,params_globalEnumFunc)));
        ASSERT_AND_LOG((SeqEnumRange1::applyTester<>::execute<CallBackT(globalEnumFunc)>(S_Val_Max,makeParamPackage_Ref(a,pStr))));
        ASSERT_AND_LOG(!(SeqEnumRange0::applyTester<>::execute<CallBackT(globalEnumFunc)>(SeqEunm(S_Val_Max+1),params_globalEnumFunc)));
    }

    inline void TestCase_traverseTypeSet_global()
    {
        PrintTitle1(TXT("TestCase_traverseTypeSet_global"));
        using namespace MiniMPL;

        CNonSeqEunmInterface_1 nsCallObj_1(rand()%NS_Val_Max);
        CNonSeqEunmInterface_2 nsCallObj_2(TXT("I am CEnumInterface_2 :"));
        CSeqEunmInterface_1 sCallObj_1(rand()%S_Val_Max);
        CSeqEunmInterface_2 sCallObj_2(TXT("I am CSeqEunmInterface_2 :"));

        //test MiniMPL.CTraverseEnum.execute
        typedef void (CNonSeqEunmInterface_1::*pNoParamN11)();
        typedef void (CSeqEunmInterface_1::*pNoParamS11)();

        pNoParamS11 pf = SeqEnumRange1::applyTester<>::getFuncAddr<CallBackT(CSeqEunmInterface_1)>(S_Val_5);
        ASSERT_AND_LOG( &CSeqEunmInterface_1::execute<S_Val_5> == SeqEnumRange1::applyTester<>::getFuncAddr<CallBackT(CSeqEunmInterface_1)>(S_Val_5));
        ASSERT_AND_LOG( &CSeqEunmInterface_1::execute<S_Val_3> != SeqEnumRange1::applyTester<>::getFuncAddr<CallBackT(CSeqEunmInterface_1)>(S_Val_5));

        ASSERT_AND_LOG((NonSeqEnumRange1::applyTester<>::execute<CallBackT(CNonSeqEunmInterface_1)>(NS_Val_5,makeParamPackage_Ref(nsCallObj_1))));                    //test OK case
        ASSERT_AND_LOG((NonSeqEnumRange0::applyTester<>::execute<CallBackT(CNonSeqEunmInterface_1)>(NS_Val_5,makeParamPackage_Ref(nsCallObj_1))));                   //test OK case
        ASSERT_AND_LOG((SeqEnumRange1::applyTester<>::execute<CallBackT(CSeqEunmInterface_1)>(S_Val_5,makeParamPackage_Ref(sCallObj_1))));                               //test OK case
        ASSERT_AND_LOG((SeqEnumRange0::applyTester<>::execute<CallBackT(CSeqEunmInterface_1)>(S_Val_5,makeParamPackage_Ref(sCallObj_1))));                               //test OK case

        //test MiniMPL.CTraverseEnum.executeFrom 
        typedef void (CNonSeqEunmInterface_2::*pNoParamN21)();
        typedef void (CSeqEunmInterface_2::*pNoParamS21)();

        ASSERT_AND_LOG((NonSeqEnumRange1::applyTester<>::executeFrom<NonSeqEunm,NS_Val_1,CallBackT(CNonSeqEunmInterface_2)>(NS_Val_3,makeParamPackage_Ref(nsCallObj_2))));      //test OK case
        ASSERT_AND_LOG((NonSeqEnumRange0::applyTester<>::executeFrom<NonSeqEunm,NS_Val_5,CallBackT(CNonSeqEunmInterface_2)>(NS_Val_3,makeParamPackage_Ref(nsCallObj_2))));     //test OK case
        ASSERT_AND_LOG((SeqEnumRange1::applyTester<>::executeFrom<SeqEunm,S_Val_1,CallBackT(CSeqEunmInterface_2)>(S_Val_3,makeParamPackage_Ref(sCallObj_2))));                  //test OK case
        ASSERT_AND_LOG((SeqEnumRange0::applyTester<>::executeFrom<SeqEunm,S_Val_5,CallBackT(CSeqEunmInterface_2)>(S_Val_3,makeParamPackage_Ref(sCallObj_2))));                 //test OK case

#if defined(_MSC_VER) && (WINVER >= 0x0500)
        #pragma push_macro("Assert_Trigger")
        #pragma push_macro("ChkExceptionThrow")
        #undef	Assert_Trigger
        #define Assert_Trigger()          0
        #undef	ChkExceptionThrow
        #define ChkExceptionThrow()       0
#endif	//end defined(_MSC_VER)

        ASSERT_AND_LOG((NonSeqEnumRange1::applyTester<>::execute<CallBackT(CNonSeqEunmInterface_1)>(NonSeqEunm(NS_Val_Max+2),makeParamPackage_Ref(nsCallObj_1))));   //test Failure case because DemoEunm(NS_Val_Max+2) is not in range
        ASSERT_AND_LOG((NonSeqEnumRange0::applyTester<>::execute<CallBackT(CNonSeqEunmInterface_1)>(NonSeqEunm(NS_Val_Min-2),makeParamPackage_Ref(nsCallObj_1))));  //test Failure case because DemoEunm(NS_Val_Min-2) is not in range
        ASSERT_AND_LOG((SeqEnumRange1::applyTester<>::execute<CallBackT(CSeqEunmInterface_1)>(SeqEunm(S_Val_Max+2),makeParamPackage_Ref(sCallObj_1))));                  //test Failure case because DemoEunm(S_Val_Max+2) is not in range
        ASSERT_AND_LOG((SeqEnumRange0::applyTester<>::execute<CallBackT(CSeqEunmInterface_1)>(SeqEunm(S_Val_Min-2),makeParamPackage_Ref(sCallObj_1))));                 //test Failure case because DemoEunm(S_Val_Min-2) is not in range

        ASSERT_AND_LOG((NonSeqEnumRange1::applyTester<>::executeFrom<NonSeqEunm,NS_Val_5,CallBackT(CNonSeqEunmInterface_2)>(NS_Val_3,makeParamPackage_Ref(nsCallObj_2))));      //test Failure case because traverse from NS_Val_5. (NS_Val_3 < NS_Val_5)
        ASSERT_AND_LOG((NonSeqEnumRange0::applyTester<>::executeFrom<NonSeqEunm,NS_Val_1,CallBackT(CNonSeqEunmInterface_2)>(NS_Val_3,makeParamPackage_Ref(nsCallObj_2))));     //test Failure case because reversed traverse from NS_Val_1. (NS_Val_1 < NS_Val_3)
        ASSERT_AND_LOG((SeqEnumRange1::applyTester<>::executeFrom<SeqEunm,S_Val_5,CallBackT(CSeqEunmInterface_2)>(S_Val_3,makeParamPackage_Ref(sCallObj_2))));                  //test Failure case because traverse from S_Val_5. (S_Val_3 < S_Val_5)
        ASSERT_AND_LOG((SeqEnumRange0::applyTester<>::executeFrom<SeqEunm,S_Val_1,CallBackT(CSeqEunmInterface_2)>(S_Val_3,makeParamPackage_Ref(sCallObj_2))));                 //test Failure case because reversed traverse from S_Val_1. (S_Val_1 < S_Val_3)

#if defined(_MSC_VER) && (WINVER >= 0x0500)
        #pragma pop_macro("Assert_Trigger")
        #pragma pop_macro("ChkExceptionThrow")
#endif	//end defined(_MSC_VER)
    }

    inline void TestCase_traverseEnumRange_dump()
    {
        PrintTitle1(TXT("TestCase_traverseEnumRange_dump"));

        using namespace MiniMPL; 
        outputTxt( SeqEnumRange0::dump().c_str() );
        outputTxt( SeqEnumRange1::dump().c_str() );
        outputTxt( NonSeqEnumRange0::dump().c_str() );
        outputTxt( NonSeqEnumRange1::dump().c_str() );
        outputTxt( CTraverseTypeContainer<SeqEnumSkipOneRange,true>::dump().c_str() );
        outputTxt( CTraverseTypeContainer<SeqEnumSkipOneRange,false>::dump().c_str() );
        outputTxtV(TXT("EInt_0_9:%s\n"),CTraverseTypeContainer<EInt_0_9>::dump().c_str());
        outputTxtV(TXT("EInt_3_5:%s\n"),CTraverseTypeContainer<EInt_3_5>::dump().c_str());
    }

    inline void TestCase_traverseEnumRange()
    {
        PrintTestcase();
        TestCase_traverseEnumRange_MF();
        TestCase_traverseTypeSet_global();
        TestCase_traverseEnumRange_dump();
    }

#ifdef RUN_EXAMPLE_TRAVERSEENUMRANGE
    InitRunFunc(TestCase_traverseEnumRange);
#else //else of RUN_EXAMPLE_TRAVERSEENUMRANGE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_TRAVERSEENUMRANGE)=(outputTxtV(TXT("[Unit test run disabled] traverseEnumRange.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"traverseEnumRange.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_TRAVERSEENUMRANGE
}

#else //else of COMPILE_EXAMPLE_TRAVERSEENUMRANGE
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_TRAVERSEENUMRANGE)=(outputTxtV(TXT("[Unit test compile disabled] traverseEnumRange.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"traverseEnumRange.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_TRAVERSEENUMRANGE

