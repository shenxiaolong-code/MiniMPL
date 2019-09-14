#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\containerInitializer.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_CONTAINERINITIALIZER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_CONTAINERINITIALIZER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_CONTAINERINITIALIZER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_CONTAINERINITIALIZER
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_CONTAINERINITIALIZER
#endif

//#undef RUN_EXAMPLE_CONTAINERINITIALIZER
//#undef COMPILE_EXAMPLE_CONTAINERINITIALIZER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_CONTAINERINITIALIZER
#include <MiniMPL/containerInitializer.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>
#include <MiniMPL/macro_Loop.hpp>
#include <UnitTestKit/tc_dump.h>
#include <UnitTestKit/tc_print.h>
#include <vector>
#include <list>

namespace UnitTest
{
#define  assertInitializer(i)   ASSERT_AND_LOG(randomAccess(initer.m_dSet,i)==rI[i])

    template<typename TDataset,typename TInitArray>
    bool testInitializer_impl(TDataset& enptyDataset,TInitArray& rI)
    {
        using namespace MiniMPL;

        stlChar buf[512]={0};
        PrintTitle2(getTypeName<TDataset>().c_str());

        typedef typename CGetType::TContainer<TDataset>::type TInner;
        ContainerInitializer<TDataset> initer = makeInitializer(enptyDataset);
        initer = rI[0],rI[1],rI[2],rI[3],rI[4];
        ASSERT_AND_LOG(5==initer.m_dSet.size());
        LOOP_1ToN(4,assertInitializer);
        initer += rI[0],rI[1],rI[2],rI[3],rI[4];
        ASSERT_AND_LOG(10==initer.m_dSet.size());
        LOOP_1ToN(4,assertInitializer);
        initer = rI[0],rI[1],rI[2],rI[3],rI[4];
        ASSERT_AND_LOG(5==initer.m_dSet.size());
        LOOP_1ToN(4,assertInitializer);
        initer = 1,2,3,4,5;
        ASSERT_AND_LOG(5==initer.m_dSet.size());
        return true;
    }

    template<typename TInitArray>
    bool testInitializer(TInitArray& rI)
    {
        using namespace MiniMPL;

        typedef typename CGetType::TContainer<TInitArray>::type   TDataset;
        typedef typename TDataset::value_type                   value_type;

        std::vector<value_type>  vectSet;
        testInitializer_impl(vectSet,rI);
        std::list<value_type>    listSet;
        testInitializer_impl(listSet,rI);
        value_type          arrSet[20]; 
        testInitializer_impl(arrSet,rI);
        return true;
    }

    template<typename TStlSet>
    bool testInitializer_stl(TStlSet& rI)
    {  
        using namespace MiniMPL;
        makeInitializer(rI)=1,2,34,5;
        return true;
    }

    inline void TestCase_containerInitializer()
    {
        PrintTestcase();

        int         intSet[]    = {12,33,4,56,3,13,4};
        testInitializer(intSet);
        float       floatSet[]  = {23.1f,4.2f,3.3f,1.4f,3.5f,51.6f,34.7f};
        testInitializer(floatSet);
        structData  structSet[] = {12,3,4,5,6};
        testInitializer(structSet);

        stlVector<int> vStl;
        testInitializer_stl(vStl);
        ASSERT_AND_LOG(4==vStl.size());
        ASSERT_AND_LOG(vStl[0]==1);
        ASSERT_AND_LOG(vStl[1]==2);
        ASSERT_AND_LOG(vStl[2]==34);
        ASSERT_AND_LOG(vStl[3]==5);

        std::list<int>  lStl;
        testInitializer_stl(lStl);
        ASSERT_AND_LOG(4==lStl.size());
        std::list<int>::const_iterator itList = lStl.begin();
        ASSERT_AND_LOG(*itList++==1);
        ASSERT_AND_LOG(*itList++==2);
        ASSERT_AND_LOG(*itList++==34);
        ASSERT_AND_LOG(*itList++==5);
    }

#ifdef RUN_EXAMPLE_CONTAINERINITIALIZER
    InitRunFunc(TestCase_containerInitializer);
#else //else of RUN_EXAMPLE_CONTAINERINITIALIZER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] containerInitializer.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"containerInitializer.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_CONTAINERINITIALIZER
}

#else //else of COMPILE_EXAMPLE_CONTAINERINITIALIZER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] containerInitializer.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"containerInitializer.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_CONTAINERINITIALIZER

