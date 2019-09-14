#ifndef __TEST_SWAP_HPP__
#define __TEST_SWAP_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\swap.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SWAP to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_SWAP

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SWAP
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SWAP
#endif

#if defined(RUN_EXAMPLE_SWAP) && !defined(COMPILE_EXAMPLE_SWAP)
    #define COMPILE_EXAMPLE_SWAP
#endif

//#undef RUN_EXAMPLE_SWAP
//#undef COMPILE_EXAMPLE_SWAP

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SWAP
#include <MiniMPL/swap.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>
#include <MiniMPL/productSpecialDef.h>
#include <list>

namespace UnitTest
{
    template<typename TP>
    void testSwap(TP& p1,TP& p2)
    {
        MiniMPL::swap(p1,p2);
    }

    inline void TestCase_swap()
    {
        PrintTestcase();
        using namespace MiniMPL;

        //test swap with vector
        stlVector<int> rVect;
        rVect.push_back(1);
        rVect.push_back(2);
        testSwap(rVect[0],rVect[1]);

        stlVector<int>::iterator   itVect1 = rVect.begin();
        stlVector<int>::iterator   itVect2=itVect1;
        itVect2++;
        testSwap(itVect1,itVect2);

        //test swap with list
        std::list<int> rList;
        rList.push_back(1);
        rList.push_back(2);

        std::list<int> rList2;
        rList2.push_back(3);
        rList2.push_back(4);
        testSwap(rList,rList2);         

        //test swap with array
        int rArr1[] = {1,2};
        int rArr2[] = {3,4};
        testSwap(rArr1[0],rArr1[1]);
        testSwap(rArr1,rArr2);
    }

#ifdef RUN_EXAMPLE_SWAP
    InitRunFunc(TestCase_swap);
#else //else of RUN_EXAMPLE_SWAP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_SWAP)=(outputTxtV(TXT("[Unit test run disabled] swap.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"swap.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_SWAP
}

#else //else of COMPILE_EXAMPLE_SWAP
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_SWAP)=(outputTxtV(TXT("[Unit test compile disabled] swap.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"swap.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_SWAP

#endif // __TEST_SWAP_HPP__
