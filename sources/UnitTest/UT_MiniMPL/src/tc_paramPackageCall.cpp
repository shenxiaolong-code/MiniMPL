#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\paramPackageCall.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_PARAMPACKAGECALL to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_PARAMPACKAGECALL

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_PARAMPACKAGECALL
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_PARAMPACKAGECALL
#endif

#if defined(RUN_EXAMPLE_PARAMPACKAGECALL) && !defined(COMPILE_EXAMPLE_PARAMPACKAGECALL)
    #define COMPILE_EXAMPLE_PARAMPACKAGECALL
#endif

//#undef RUN_EXAMPLE_PARAMPACKAGECALL
//#undef COMPILE_EXAMPLE_PARAMPACKAGECALL

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_PARAMPACKAGECALL
#include <MiniMPL/paramPackageCall.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_paramPackage.h>
#include <UT_material/tc_def_globalFunc.h>

namespace UnitTest
{
    void TestCase_callParamPackageStatic()
    {
        PrintTestcaseSub();
        using namespace MiniMPL;
        //test non-member function
        typedef TAddTClassToPack<void (*)(int, char)>::type  TPS2IC;
        TPS2IC oTPS2IC(5,'c'); 

        typedef TAddTClassToPack<int (*)()>::type  TPS0;
        TPS0  oTPS0;
        doPackCall(testParam0,oTPS0);

        typedef TAddTClassToPack<int (*)(MFStruct0_6&)>::type  TPS1S;
        MFStruct0_6 mfs;
        TPS1S oTPS1S(mfs);
        doPackCall(testParam1,oTPS1S);

        typedef TAddTClassToPack<int (*)(MFStruct0_6&,char)>::type  TPS2SC;
        TPS2SC oTPS2SC(mfs,'c');
        doPackCall(testParam2,oTPS2SC);

        //test member function
        S4 os4;
        S4 const os4c;

        typedef TAddTClassToPack<void (S4::*)()>::type  TPSO0;
        TPSO0 oTPSO0(os4);
        doPackCall(&S4::printNoParam,oTPSO0);

        typedef TAddTClassToPack<int (S4::*)() const>::type  TPSOC0;
        TPSOC0 oTPSOC0(os4);
        doPackCall(&S4::total,oTPSOC0);

        typedef TAddTClassToPack<void (S4::*)(int, char*)>::type  TPS2OIC;        
        TPS2OIC oTPS2OIC(os4,6,HEREINFO_POSA());
        doPackCall(&S4::print2Params,oTPS2OIC);

        typedef TAddTClassToPack<void (S4::*)(int, char*) const>::type  TPS2OCIC;        
        TPS2OCIC oTPS2OCIC(os4c,7,HEREINFO_POSA());
        doPackCall(&S4::print2ParamsConst,oTPS2OCIC);

        TPS2OCIC oTPS2OCIC1(os4,8,HEREINFO_POSA());
        doPackCall(&S4::print2ParamsConst,oTPS2OCIC1);
    }

    inline void TestCase_ParamPackageCallF()
    {
        PrintTestcaseSub();
        using namespace MiniMPL;
        S4      s4Obj;
        typedef ParamPackageCall<>                  TPPC_NoRef0;
        typedef ParamPackageCall<S4> const          TPPC_NoRef1;
        typedef ParamPackageCall<S4,int>            TPPC_NoRef2;
        typedef ParamPackageCall<S4,int,char*>      TPPC_NoRef3;
        TPPC_NoRef0().packCall(CallBackRoutineF);
        TPPC_NoRef1(s4Obj).packCall(CallBackRoutineF1);
        TPPC_NoRef2(s4Obj,6).packCall(CallBackRoutineF2);
        TPPC_NoRef3(s4Obj,6,"hi").packCall(CallBackRoutineF3);

        typedef ParamPackageCall<S4&>                   TPPC_Ref1;
        typedef ParamPackageCall<S4&,int>               TPPC_Ref2;
        typedef ParamPackageCall<S4&,int,char*>         TPPC_Ref3;
        TPPC_Ref1(s4Obj).packCall(CallBackRoutineF1);
        TPPC_Ref2(s4Obj,6).packCall(CallBackRoutineF2);
        TPPC_Ref3(s4Obj,6,"hi").packCall(CallBackRoutineF3);
    }

    inline void TestCase_ParamPackageCallMF()
    {
        using namespace MiniMPL;
        PrintTestcaseSub();

        S4      s4Obj;
        typedef stlSmartptr<S4>             TpS4;
        TpS4    pS4(new S4());

        typedef ParamPackageCall<S4&>                   TPPC_Ref0;
        typedef ParamPackageCall<S4&,int>               TPPC_Ref1;
        typedef ParamPackageCall<S4&,int,char*>         TPPC_Ref2;
        typedef ParamPackageCall<S4&,int,char*,S3>      TPPC_Ref3;
        TPPC_Ref0(s4Obj).packCall(&S4::print);
        TPPC_Ref1(s4Obj,6).packCall(&S4::print1Param);
        TPPC_Ref2(s4Obj,6,"hi").packCall(&S4::print2Params);
        TPPC_Ref3(s4Obj,6,"hi",S3()).packCall(&S4::print3Params);

        typedef ParamPackageCall<TpS4&>                   TPPC_RefP0;
        typedef ParamPackageCall<TpS4&,int>               TPPC_RefP1;
        typedef ParamPackageCall<TpS4&,int,char*>         TPPC_RefP2;
        typedef ParamPackageCall<TpS4&,int,char*,S3>      TPPC_RefP3;
        TPPC_RefP0(pS4).packCall(&S4::print);
        TPPC_RefP1(pS4,6).packCall(&S4::print1Param);
        TPPC_RefP2(pS4,6,"hi").packCall(&S4::print2Params);
        TPPC_RefP3(pS4,6,"hi",S3()).packCall(&S4::print3Params);

        typedef ParamPackageCall<S4>                    TPPC_NoRef0;
        typedef ParamPackageCall<S4,int>                TPPC_NoRef1;
        typedef ParamPackageCall<S4,int,char*>          TPPC_NoRef2;
        typedef ParamPackageCall<S4,int,char*,S3>       TPPC_NoRef3;
        TPPC_NoRef0(s4Obj).packCall(&S4::print);
        TPPC_NoRef1(s4Obj,6).packCall(&S4::print1Param);
        TPPC_NoRef2(s4Obj,6,"hi").packCall(&S4::print2Params);
        TPPC_NoRef3(s4Obj,6,"hi",S3()).packCall(&S4::print3Params);

        typedef ParamPackageCall<TpS4>                    TPPC_NoRefP0;
        typedef ParamPackageCall<TpS4,int>                TPPC_NoRefP1;
        typedef ParamPackageCall<TpS4,int,char*>          TPPC_NoRefP2;
        typedef ParamPackageCall<TpS4,int,char*,S3>       TPPC_NoRefP3;
        TPPC_NoRefP0(pS4).packCall(&S4::print);
        TPPC_NoRefP1(pS4,6).packCall(&S4::print1Param);
        TPPC_NoRefP2(pS4,6,"hi").packCall(&S4::print2Params);
        TPPC_NoRefP3(pS4,6,"hi",S3()).packCall(&S4::print3Params); 
    }

    inline void TestCase_paramPackageCall_Constcall()
    {
        PrintTestcaseSub();

        MFStruct0_6   obj;
        MFStruct0_6*  pObj = NULL;

        const TParamPackageCall0      ps0; 
        ASSERT_AND_LOG(ps0.packCall(testParam0)==0);        
        pObj = ps0.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==0);
        delete pObj;

        const TParamPackageCall1      ps1(obj);
        ASSERT_AND_LOG(ps1.packCall(testParam1)==1);
        ASSERT_AND_LOG(ps1.packCall(&MFStruct0_6::testMFParam0)==0);
        pObj = ps1.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==1);
        delete pObj;

        const TParamPackageCall2      ps2(obj,'c');
        ASSERT_AND_LOG(ps2.packCall(testParam2)==2);
        ASSERT_AND_LOG(ps2.packCall(&MFStruct0_6::testMFParam1)==1);
        pObj = ps2.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==2);
        delete pObj;

        const TParamPackageCall3      ps3(obj,'c',NULL);
        ASSERT_AND_LOG(ps3.packCall(testParam3)==3);
        ASSERT_AND_LOG(ps3.packCall(&MFStruct0_6::testMFParam2)==2);
        pObj = ps3.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==3);
        delete pObj;

        const TParamPackageCall4      ps4(obj,'c',NULL,5);
        ASSERT_AND_LOG(ps4.packCall(testParam4)==4);
        ASSERT_AND_LOG(ps4.packCall(&MFStruct0_6::testMFParam3)==3);
        pObj = ps4.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==4);
        delete pObj;

        const TParamPackageCall5      ps5(obj,'c',NULL,5,3.2f);
        ASSERT_AND_LOG(ps5.packCall(testParam5)==5);
        ASSERT_AND_LOG(ps5.packCall(&MFStruct0_6::testMFParam4)==4);
        pObj = ps5.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==5);
        delete pObj;
    }
    
    inline void TestCase_paramPackageCall_call()
    {
        PrintTestcaseSub();

        MFStruct0_6   obj;
        MFStruct0_6*  pObj = NULL;

        TParamPackageCall0      ps0; 
        ASSERT_AND_LOG(ps0.packCall(testParam0)==0);        
        pObj = ps0.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==0);
        delete pObj;

        TParamPackageCall1      ps1(obj);
        ASSERT_AND_LOG(ps1.packCall(testParam1)==1);
        ASSERT_AND_LOG(ps1.packCall(&MFStruct0_6::testMFParam0)==0);
        pObj = ps1.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==1);
        delete pObj;

        TParamPackageCall2      ps2(obj,'c');
        ASSERT_AND_LOG(ps2.packCall(testParam2)==2);
        ASSERT_AND_LOG(ps2.packCall(&MFStruct0_6::testMFParam1)==1);
        pObj = ps2.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==2);
        delete pObj;

        TParamPackageCall3      ps3(obj,'c',NULL);
        ASSERT_AND_LOG(ps3.packCall(testParam3)==3);
        ASSERT_AND_LOG(ps3.packCall(&MFStruct0_6::testMFParam2)==2);
        pObj = ps3.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==3);
        delete pObj;

        TParamPackageCall4      ps4(obj,'c',NULL,5);
        ASSERT_AND_LOG(ps4.packCall(testParam4)==4);
        ASSERT_AND_LOG(ps4.packCall(&MFStruct0_6::testMFParam3)==3);
        pObj = ps4.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==4);
        delete pObj;

        TParamPackageCall5      ps5(obj,'c',NULL,5,3.2f);
        ASSERT_AND_LOG(ps5.packCall(testParam5)==5);
        ASSERT_AND_LOG(ps5.packCall(&MFStruct0_6::testMFParam4)==4);
        pObj = ps5.newObject<MFStruct0_6>();
        ASSERT_AND_LOG(pObj->m_I==5);
        delete pObj;
    }

    inline void TestCase_paramPackageCall()
    {
        PrintTestcase();
        TestCase_callParamPackageStatic();
        TestCase_paramPackageCall_call();        
        TestCase_paramPackageCall_Constcall();
        TestCase_ParamPackageCallF();
        TestCase_ParamPackageCallMF();
    }

#ifdef RUN_EXAMPLE_PARAMPACKAGECALL
    InitRunFunc(TestCase_paramPackageCall);
#else //else of RUN_EXAMPLE_PARAMPACKAGECALL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_PARAMPACKAGECALL)=(outputTxtV(TXT("[Unit test run disabled] paramPackageCall.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"paramPackageCall.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_PARAMPACKAGECALL
}

#else //else of COMPILE_EXAMPLE_PARAMPACKAGECALL
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_PARAMPACKAGECALL)=(outputTxtV(TXT("[Unit test compile disabled] paramPackageCall.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"paramPackageCall.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_PARAMPACKAGECALL

