#ifndef __TEST_MACRO_LOOP_HPP__
#define __TEST_MACRO_LOOP_HPP__
#include "../testconfig_MiniMPL.h"
#include "MiniMPL/macro_assert.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\macroLoop.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_MACRO_LOOP to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_MACRO_LOOP

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_MACRO_LOOP
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_MACRO_LOOP
#endif

#if defined(RUN_EXAMPLE_MACRO_LOOP) && !defined(COMPILE_EXAMPLE_MACRO_LOOP)
    #define COMPILE_EXAMPLE_MACRO_LOOP
#endif

//#undef RUN_EXAMPLE_MACRO_LOOP
//#undef COMPILE_EXAMPLE_MACRO_LOOP

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_MACRO_LOOP
#include <MiniMPL/macro_Loop.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <MiniMPL/arrayTrait.hpp>

#define key_0       0
#define key_1       1    
#define key_2       2
#define key_3       3
#define key_4       4
#define key_5       5
#define key_6       6
#define key_7       7    
#define key_8       8
#define key_9       9
#define key_10      10
#define key_11      11
#define key_12      12
#define key_13      13    
#define key_14      14
#define key_15      15
#define key_16      16
#define key_17      17
#define key_18      18
#define key_19      19
#define key_20      20

#define val_0       0
#define val_1       1    
#define val_2       2
#define val_3       3
#define val_4       4
#define val_5       5
#define val_6       6
#define val_7       7    
#define val_8       8
#define val_9       9
#define val_10      10
#define val_11      11
#define val_12      12
#define val_13      13    
#define val_14      14
#define val_15      15
#define val_16      16
#define val_17      17
#define val_18      18
#define val_19      19
#define val_20      20

namespace UnitTest
{
#define IntInt(i)           {key_##i,val_##i}
#define ItemInt(i)          val_##i

#define ItemPtr(i,x)        &x::m_iVal##i
#define ItemAssign(i,N)     N.m_iVal##i = rand()%100

#define ItemAssert1(i,x)    ASSERT_AND_LOG(x.m_iVal##i == x.*pMemptr[i-1])
#define ItemAssert0(i,x)    ASSERT_AND_LOG(x.m_iVal##i == x.*pMemptr[i])

    struct SIntInt
    {
        int m_a;
        int m_b;
    };

    struct SMemPtr
    {
        int m_iVal1;
        int m_iVal2;
        int m_iVal3;
        int m_iVal4;
        int m_iVal5;
    };
    struct SMemPtr0
    {
        int m_iVal0;
        int m_iVal1;
        int m_iVal2;
        int m_iVal3;
        int m_iVal4;
        int m_iVal5;
    };

    inline void TestCase_macroLoop()
    {
        PrintTestcase();
        
        int k0_20[] = {LOOP_0ToN(20,ItemInt)};
        Static_Assert(arraySize(k0_20)==21);
        ASSERT_AND_LOG(0==k0_20[0]);
        ASSERT_AND_LOG(20==k0_20[arraySize(k0_20)-1]);

        int k1_20[] = {LOOP_1ToN(20,ItemInt)};
        Static_Assert(arraySize(k1_20)==20);
        ASSERT_AND_LOG(1==k1_20[0]);
        ASSERT_AND_LOG(20==k1_20[arraySize(k1_20)-1]);

        int k20_0[] = {LOOP_NTo0(20,ItemInt)};
        Static_Assert(arraySize(k20_0)==21);
        ASSERT_AND_LOG(20==k20_0[0]);
        ASSERT_AND_LOG(0==k20_0[arraySize(k20_0)-1]);

        int k20_1[] = {LOOP_NTo1(20,ItemInt)};
        Static_Assert(arraySize(k20_1)==20);
        ASSERT_AND_LOG(20==k20_1[0]);
        ASSERT_AND_LOG(1==k20_1[arraySize(k20_1)-1]);

        SIntInt arr1_5[] = { LOOP_1ToN(5,IntInt) };
        Static_Assert(arraySize(arr1_5)==5);
        ASSERT_AND_LOG(1==arr1_5[0].m_a);
        ASSERT_AND_LOG(5==arr1_5[arraySize(arr1_5)-1].m_a);
        ASSERT_AND_LOG(1==arr1_5[0].m_b);
        ASSERT_AND_LOG(5==arr1_5[arraySize(arr1_5)-1].m_b);
        AssertB(arr1_5[0].m_a == 1);
        AssertB(arr1_5[3].m_b == 4);

        SIntInt arr0_5[] = { LOOP_0ToN(5,IntInt) };
        Static_Assert(arraySize(arr0_5)==6);
        ASSERT_AND_LOG(0==arr0_5[0].m_a);
        ASSERT_AND_LOG(5==arr0_5[arraySize(arr0_5)-1].m_a);
        ASSERT_AND_LOG(0==arr0_5[0].m_b);
        ASSERT_AND_LOG(5==arr0_5[arraySize(arr0_5)-1].m_b);
        AssertB(arr0_5[0].m_a == 0);
        AssertB(arr0_5[3].m_b == 3);

        SIntInt arr3_1[] = { LOOP_NTo1(3,IntInt) };
        Static_Assert(arraySize(arr3_1)==3);
        ASSERT_AND_LOG(3==arr3_1[0].m_a);
        ASSERT_AND_LOG(1==arr3_1[arraySize(arr3_1)-1].m_a);
        ASSERT_AND_LOG(3==arr3_1[0].m_b);
        ASSERT_AND_LOG(1==arr3_1[arraySize(arr3_1)-1].m_b);
        AssertB(arr3_1[0].m_a == 3);
        AssertB(arr3_1[2].m_b == 1);

        SIntInt arr2_0[] = { LOOP_NTo0(2,IntInt) };
        Static_Assert(arraySize(arr2_0)==3);
        ASSERT_AND_LOG(2==arr2_0[0].m_a);
        ASSERT_AND_LOG(0==arr2_0[arraySize(arr2_0)-1].m_a);
        ASSERT_AND_LOG(2==arr2_0[0].m_b);
        ASSERT_AND_LOG(0==arr2_0[arraySize(arr2_0)-1].m_b);
        AssertB(arr2_0[0].m_a == 2);
        AssertB(arr2_0[2].m_b == 0);

        int int1_3[]= {LOOP_1ToN(3,ItemInt)};
        Static_Assert(arraySize(int1_3)==3);
        ASSERT_AND_LOG(1==int1_3[0]);
        ASSERT_AND_LOG(3==int1_3[arraySize(int1_3)-1]);
        AssertB(int1_3[0] == 1);
        AssertB(int1_3[2] == 3);

        int int0_3[]= {LOOP_0ToN(3,ItemInt)};
        Static_Assert(arraySize(int0_3)==4);
        ASSERT_AND_LOG(0==int0_3[0]);
        ASSERT_AND_LOG(3==int0_3[arraySize(int0_3)-1]);
        AssertB(int0_3[0] == 0);
        AssertB(int0_3[2] == 2);

        int int5_1[]= {LOOP_NTo1(5,ItemInt)};
        Static_Assert(arraySize(int5_1)==5);
        ASSERT_AND_LOG(5==int5_1[0]);
        ASSERT_AND_LOG(1==int5_1[arraySize(int5_1)-1]);
        AssertB(int5_1[0] == 5);
        AssertB(int5_1[4] == 1);

        int int5_0[]= {LOOP_NTo0(5,ItemInt)};
        Static_Assert(arraySize(int5_0)==6);
        ASSERT_AND_LOG(5==int5_0[0]);
        ASSERT_AND_LOG(0==int5_0[arraySize(int5_0)-1]);
        AssertB(int5_0[0] == 5);
        AssertB(int5_0[5] == 0);

        {
            int SMemPtr::*pMemptr[] = {LOOP_1ToNP(5,ItemPtr,SMemPtr)};
            Static_Assert(arraySize(pMemptr)==sizeof(SMemPtr)/sizeof(int));
            ASSERT_AND_LOG(&SMemPtr::m_iVal1==pMemptr[0]);
            ASSERT_AND_LOG(&SMemPtr::m_iVal5==pMemptr[arraySize(pMemptr)-1]);

            SMemPtr mObj;
            LOOP_1ToNP(5,ItemAssign,mObj);
            LOOP_1ToNP(5,ItemAssert1,mObj);
        }

        {
            int SMemPtr0::*pMemptr[] = {LOOP_0ToNP(5,ItemPtr,SMemPtr0)};
            Static_Assert(arraySize(pMemptr)==sizeof(SMemPtr0)/sizeof(int));
            SMemPtr0 mObj0;
            LOOP_0ToNP(5,ItemAssign,mObj0);
            LOOP_0ToNP(5,ItemAssert0,mObj0);
        }
    }

#ifdef RUN_EXAMPLE_MACRO_LOOP
    InitRunFunc(TestCase_macroLoop);
#else //else of RUN_EXAMPLE_MACRO_LOOP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_MACRO_LOOP)=(outputTxtV(TXT("[Unit test run disabled] macroLoop.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"macroLoop.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_MACRO_LOOP
}

#else //else of COMPILE_EXAMPLE_MACRO_LOOP
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_MACRO_LOOP)=(outputTxtV(TXT("[Unit test compile disabled] macroLoop.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"macroLoop.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_MACRO_LOOP

#endif // __TEST_MACRO_LOOP_HPP__
