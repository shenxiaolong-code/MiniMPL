#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macroDef.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\stdAlgorithmEx.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_STDALGORITHMEX to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_STDALGORITHMEX

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_STDALGORITHMEX
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_STDALGORITHMEX
#endif

#if defined(RUN_EXAMPLE_STDALGORITHMEX) && !defined(COMPILE_EXAMPLE_STDALGORITHMEX)
    #define COMPILE_EXAMPLE_STDALGORITHMEX
#endif

//#undef RUN_EXAMPLE_STDALGORITHMEX
//#undef COMPILE_EXAMPLE_STDALGORITHMEX

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_STDALGORITHMEX
#include <MiniMPL/stdAlgorithmEx.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <MiniMPL/innerDetail/valueCompare_detail.hpp>
#include <UT_material/tc_def_typeStruct.h>
#include <MiniMPL/memberPtr.hpp>
#include <UnitTestKit/tc_rand.h>
#include <MiniMPL/container.hpp>
#include <UnitTestKit/tc_print.h>
#include "MiniMPL/containerInitializer.hpp"
#include "MiniMPL/tester.hpp"
#include <list>

namespace UnitTest
{
    template<typename T,unsigned LEN>
    inline void TestCase_stdAlgorithmEx_Number(T (&rArr)[LEN])
    {
        using namespace MiniMPL;
        genRandSequence(rArr);
        printContainer(makeContainer(rArr,LEN),"before sort:\n");
        MiniMPL::sort(makeContainer(rArr,LEN),lesser<T,T>); 
        for (unsigned idx=0;idx<arraySize(rArr)-1;++idx)
        {
            ASSERT_AND_LOG(rArr[idx]<=rArr[idx+1]);
        }
        printContainer(makeContainer(rArr,LEN),"after sort:\n");
    }

    template<typename S,unsigned LEN, typename M>
    inline void TestCase_stdAlgorithmEx_struct(S (&rArr)[LEN], M S::* ptr)
    {
        using namespace MiniMPL;
        printContainer(makeContainer(rArr,LEN),"before sort:\n");
        MiniMPL::sort(makeContainer(rArr,LEN),ptr,true);
        for (unsigned idx=0;idx<arraySize(rArr)-1;++idx)
        {
            ASSERT_AND_LOG(rArr[idx].*ptr<=rArr[idx+1].*ptr);
        }
        printContainer(makeContainer(rArr,LEN),"after sort:\n");
    }

    inline void testFindWrapper()
    {
        using namespace MiniMPL;
        int arr[] = {1,2,3,54,5};
        int* pFindArr = MiniMPL::find(makeContainer(arr,arraySize(arr)),makeUnaryTester(3,CEqual(),true));
        ASSERT_AND_LOG(2==(pFindArr-arr));

        stlVector<int> rStlVect;
        makeInitializer(rStlVect)=23,34,5,3,42,1,3;
        int* pFindVect = MiniMPL::find(rStlVect,makeUnaryTester(3,CEqual(),true));
        ASSERT_AND_LOG(3==(pFindVect-&*rStlVect.begin()));

        std::list<int> rStlList;
        makeInitializer(rStlList)=23,34,5,3,42,1,3;
        int* pFindList = MiniMPL::find(rStlList,makeUnaryTester(3,CEqual(),true));
        ASSERT_AND_LOG(3==*pFindList);
    }

    inline void TestCase_stdAlgorithmEx()
    {
        PrintTestcase();

        testFindWrapper();

        int arrInt[30]={0};        
        TestCase_stdAlgorithmEx_Number(arrInt);

        float arrFloat[30]={0};        
        TestCase_stdAlgorithmEx_Number(arrFloat);
        long double arrLd[30]={0};        
        TestCase_stdAlgorithmEx_Number(arrLd);

        S4  arrS4[30];
        TestCase_stdAlgorithmEx_struct(arrS4,MMP3(&S4::m_ss3,&S3::m_ss2,&S2::m_s2));

        S3  arrS3[30];
        TestCase_stdAlgorithmEx_struct(arrS3,MMP2(&S3::m_ss2,&S2::m_s2));

        using namespace MiniMPL;
        stlVector<int> vectInt1;
        makeInitializer(vectInt1)=1,23,4,5,6,7;
        ASSERT_AND_LOG(NULL != MiniMPL::find(vectInt1,makeUnaryTester(5,CEqual())));
        ASSERT_AND_LOG(NULL == MiniMPL::find(vectInt1,makeUnaryTester(22,CEqual())));
    }

#ifdef RUN_EXAMPLE_STDALGORITHMEX
    InitRunFunc(TestCase_stdAlgorithmEx);
#else //else of RUN_EXAMPLE_STDALGORITHMEX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_STDALGORITHMEX)=(outputTxtV(TXT("[Unit test run disabled] stdAlgorithmEx.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"stdAlgorithmEx.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_STDALGORITHMEX
}

#else //else of COMPILE_EXAMPLE_STDALGORITHMEX
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_STDALGORITHMEX)=(outputTxtV(TXT("[Unit test compile disabled] stdAlgorithmEx.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"stdAlgorithmEx.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_STDALGORITHMEX

