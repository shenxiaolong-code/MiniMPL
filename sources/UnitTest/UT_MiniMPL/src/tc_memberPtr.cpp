#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\memberPtr.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MEMBERPTR to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MEMBERPTR

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MEMBERPTR
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MEMBERPTR
#endif

#if defined(RUN_EXAMPLE_MEMBERPTR) && !defined(COMPILE_EXAMPLE_MEMBERPTR)
    #define COMPILE_EXAMPLE_MEMBERPTR
#endif

//#undef RUN_EXAMPLE_MEMBERPTR
//#undef COMPILE_EXAMPLE_MEMBERPTR

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MEMBERPTR
#include <MiniMPL/memberPtr.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{
    inline void TestCase_memberPtr()
    {
        PrintTestcase();
        using namespace MiniMPL;
        S4  s4Obj;
        S3  s3Obj;
        S2  s2Obj;
        S1  s1Obj;

        typedef int S4::*TPS4Int;
        typedef S3  S4::*TPS4S3;
        typedef S2  S4::*TPS4S2;
        typedef S1  S4::*TPS4S1;

        typedef int S3::*TPS3Int;
        typedef S2  S3::*TPS3S2;

        typedef int S2::*TPS2Int;
        typedef S1  S2::*TPS2S1;

        typedef int S1::*TPS1Int;

        typedef S4  S4::*TPS4;
        typedef S3  S3::*TPS3;
        typedef S2  S2::*TPS2;
        typedef S1  S1::*TPS1;

        //test makePtrToSelf
        Assertb(s4Obj==s4Obj.*makePtrToSelf(S4));
        Assertb(&s4Obj==&(s4Obj.*makePtrToSelf(S4)));

        //test makePtrToMember
        TPS4Int pS4Int = NULL;        
        pS4Int=makePtrToMember(S4,int,m_ss3.m_ss2.m_ss1.m_s1);
        Assertb(s4Obj.*pS4Int==s4Obj.m_ss3.m_ss2.m_ss1.m_s1);
        Assertb(&(s4Obj.*pS4Int)==&s4Obj.m_ss3.m_ss2.m_ss1.m_s1);
        Assertb(pS4Int != &S4::m_s4);

        pS4Int=makePtrToMember(S4,int,m_ss3.m_ss2.m_s2);
        Assertb(s4Obj.*pS4Int==s4Obj.m_ss3.m_ss2.m_s2);
        Assertb(&(s4Obj.*pS4Int)==&s4Obj.m_ss3.m_ss2.m_s2);

        pS4Int=makePtrToMember(S4,int,m_ss3.m_s3);
        Assertb(s4Obj.*pS4Int==s4Obj.m_ss3.m_s3);
        Assertb(&(s4Obj.*pS4Int)==&s4Obj.m_ss3.m_s3);

        pS4Int=makePtrToMember(S4,int,m_s4);
        pS4Int=&S4::m_s4;
        Assertb(s4Obj.*pS4Int==s4Obj.m_s4);

        TPS3Int pS3Int = NULL;
        pS3Int = makePtrToMember(S3,int,m_ss2.m_s2);
        Assertb(s3Obj.*pS3Int==s3Obj.m_ss2.m_s2);

        TPS4S2 pS4S2 = NULL;
        pS4S2  = makePtrToMember(S4,S2,m_ss3.m_ss2);
        Assertb(s4Obj.*pS4S2==s4Obj.m_ss3.m_ss2);

        //test makePtrToMemberT
        pS4Int=makePtrToMemberT(TPS4Int,m_ss3.m_ss2.m_ss1.m_s1);
        Assertb(s4Obj.*pS4Int==s4Obj.m_ss3.m_ss2.m_ss1.m_s1);
        Assertb(&(s4Obj.*pS4Int)==&s4Obj.m_ss3.m_ss2.m_ss1.m_s1);
        Assertb(pS4Int != &S4::m_s4);

        pS4Int=makePtrToMemberT(TPS4Int,m_ss3.m_ss2.m_s2);
        Assertb(s4Obj.*pS4Int==s4Obj.m_ss3.m_ss2.m_s2);

        pS4Int=makePtrToMemberT(TPS4Int,m_ss3.m_s3);
        Assertb(s4Obj.*pS4Int==s4Obj.m_ss3.m_s3);

        pS4Int=makePtrToMemberT(TPS4Int,m_s4);
        pS4Int=&S4::m_s4;
        Assertb(s4Obj.*pS4Int==s4Obj.m_s4);

        pS3Int = NULL;
        pS3Int = makePtrToMemberT(TPS3Int,m_ss2.m_s2);
        Assertb(s3Obj.*pS3Int==s3Obj.m_ss2.m_s2);

        pS4S2 = NULL;
        pS4S2 = makePtrToMemberT(TPS4S2,m_ss3.m_ss2);
        Assertb(s4Obj.*pS4S2==s4Obj.m_ss3.m_ss2);        

        //test MMP...
        Assertb(MMP2(&S4::m_ss3,&S3::m_ss2)==makePtrToMember(S4,S2,m_ss3.m_ss2));
        Assertb(MMP3(&S4::m_ss3,&S3::m_ss2,&S2::m_ss1)==makePtrToMember(S4,S1,m_ss3.m_ss2.m_ss1));
        Assertb(MMP4(&S4::m_ss3,&S3::m_ss2,&S2::m_ss1,&S1::m_s1)==makePtrToMember(S4,int,m_ss3.m_ss2.m_ss1.m_s1));

        Assertb(&S4::m_s4!=makePtrToMember(S4,int,m_ss3.m_ss2.m_ss1.m_s1));
        Assertb(MMP2(&S4::m_ss3,&S3::m_s3)!=makePtrToMember(S4,int,m_ss3.m_ss2.m_s2));
        Assertb(MMP3(&S4::m_ss3,&S3::m_ss2,&S2::m_s2)!=makePtrToMember(S4,int,m_ss3.m_ss2.m_ss1.m_s1));
        Assertb(MMP4(&S4::m_ss3,&S3::m_ss2,&S2::m_ss1,&S1::m_s1)!=makePtrToMember(S4,int,m_ss3.m_ss2.m_s2));

        Assertb(MMP2(&S4::m_ss3,&S3::m_ss2)==makePtrToMemberT(S2 S4::*,m_ss3.m_ss2));
        Assertb(MMP3(&S4::m_ss3,&S3::m_ss2,&S2::m_ss1)==makePtrToMemberT(S1 S4::*,m_ss3.m_ss2.m_ss1));
        Assertb(MMP4(&S4::m_ss3,&S3::m_ss2,&S2::m_ss1,&S1::m_s1)==makePtrToMemberT(int S4::*,m_ss3.m_ss2.m_ss1.m_s1));

        Assertb(&S4::m_s4!=makePtrToMemberT(int S4::*,m_ss3.m_ss2.m_ss1.m_s1));
        Assertb(MMP2(&S4::m_ss3,&S3::m_s3)!=makePtrToMemberT(int S4::*,m_ss3.m_ss2.m_s2));
        Assertb(MMP3(&S4::m_ss3,&S3::m_ss2,&S2::m_s2)!=makePtrToMemberT(int S4::*,m_ss3.m_ss2.m_ss1.m_s1));
        Assertb(MMP4(&S4::m_ss3,&S3::m_ss2,&S2::m_ss1,&S1::m_s1)!=makePtrToMemberT(int S4::*,m_ss3.m_ss2.m_s2));

        //test CDataMemberPtr and makeMemberPtr
        int S4::*        pSM    = makeMemberPtr(&S4::m_s4);
        CDataMemberPtr<int S4::*> rFunctor = pSM;
        Assertb(&(s4Obj.*pSM)==&s4Obj.m_s4);
        Assertb(&rFunctor(s4Obj)==&s4Obj.m_s4);

        int rInt = rand();
        CDataMemberPtr<int> rSelfFunctor  = makeMemberPtr<int>();
        Assertb(&rSelfFunctor(rInt)==&rInt);

        //test linkMemberPtr
        pS4Int = linkMemberPtr(makePtrToMember(S4,S2,m_ss3.m_ss2),makePtrToMember(S2,int,m_ss1.m_s1));
        Assertb(s4Obj.*pS4Int==s4Obj.m_ss3.m_ss2.m_ss1.m_s1);
    }

#ifdef RUN_EXAMPLE_MEMBERPTR
    InitRunFunc(TestCase_memberPtr);
#else //else of RUN_EXAMPLE_MEMBERPTR

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_MEMBERPTR)=(outputTxtV(TXT("[Unit test run disabled] memberPtr.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"memberPtr.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_MEMBERPTR
}

#else //else of COMPILE_EXAMPLE_MEMBERPTR
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_MEMBERPTR)=(outputTxtV(TXT("[Unit test compile disabled] memberPtr.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"memberPtr.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_MEMBERPTR

