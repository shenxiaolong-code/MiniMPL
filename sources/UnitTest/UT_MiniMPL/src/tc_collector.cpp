#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\collector.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_COLLECTOR to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_COLLECTOR

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_COLLECTOR
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_COLLECTOR
#endif

#if defined(RUN_EXAMPLE_COLLECTOR) && !defined(COMPILE_EXAMPLE_COLLECTOR)
    #define COMPILE_EXAMPLE_COLLECTOR
#endif

//#undef RUN_EXAMPLE_COLLECTOR
//#undef COMPILE_EXAMPLE_COLLECTOR

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_COLLECTOR
#include <MiniMPL/collector.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>
#include <MiniMPL/container.hpp>
#include <UnitTestKit/tc_print.h>
#include <MiniMPL/tester.hpp>
#include <list>

namespace UnitTest
{
    template<typename C,typename CR,typename TMPtr>
    inline void TestCase_collect(C& rInput,CR& rOutput,TMPtr ptr)
    {
        using namespace MiniMPL;

        typedef typename CGetType::TContainer<C>::type      TContainerIn;
        typedef typename CGetType::TContainer<CR>::type     TContainerOut;

        typedef typename CGetType::TMemberPtr<TMPtr>::type  TMemberPtr;
        TMemberPtr          oUf(ptr);
        TContainerIn&     oIn=makeContainer(rInput);
        TContainerOut&    oOut=makeContainer(rOutput);

        collect(oIn,makeUnaryTester_Result(ptr,oUf(oIn[0]),CGreater(),true),makeCollector(oOut,ptr));
    }

    template<typename C,typename CR,typename TMPtr>
    inline void TestCase_collectorWithContainer(C& rInput,CR& rOutput,TMPtr ptr)
    {
        using namespace MiniMPL;
        TestCase_collect(rInput,rOutput,ptr);
        rOutput.clear();

        typedef typename CGetType::TContainer<C>::type      TContainerIn;
        typedef typename CGetType::TContainer<CR>::type     TContainerOut;
        TContainerIn&   rIn = makeContainer(rInput);
        TContainerOut& rOut = makeContainer(rOutput);

        CDataMemberPtr<TMPtr>& rCPtr = makeMemberPtr(ptr);
        Collector<TContainerOut,CDataMemberPtr<TMPtr> >& rResult = makeCollector(rOut,ptr);
        
        TContainerIn::iterator it = rIn.begin();
        TContainerIn::iterator guard = rIn.end();
        while (it != guard)
        {
            rResult(*it++);
        }

        size_t iSize= rIn.size();
        ASSERT_AND_LOG(iSize==rOut.size());
        for (size_t i=0;i<iSize;++i)
        {
            ASSERT_AND_LOG(rCPtr(rIn[i])==Get::value(randomAccess(rOut,i)/* rResult[i]*/));
        }
    }

    template<typename C,typename CR>
    inline void TestCase_collectorSelf(C& rInput,CR& rOutput)
    {
        using namespace MiniMPL;
        typedef typename CGetType::TContainer<C>::type      TContainerIn;
        typedef typename CGetType::TContainer<CR>::type     TContainerOut;


        typedef typename TContainerIn::value_type    value_type;
        TestCase_collect(rInput,rOutput,makeMemberPtr<value_type>());
        rOutput.clear();

        TContainerIn&   rIn = makeContainer(rInput);
        TContainerOut&  rOut = makeContainer(rOutput);

        Collector<TContainerOut,CDataMemberPtr<value_type> >& rResult = makeCollector(makeContainer(rOutput),makeMemberPtr<value_type>());

        TContainerIn::iterator it = rIn.begin();
        TContainerIn::iterator guard = rIn.end();
        while (it != guard)
        {
            rResult(*it++);
        }


        size_t iSize= rIn.size();
        ASSERT_AND_LOG(iSize==rOut.size());
        for (size_t i=0;i<iSize;++i)
        {
            ASSERT_AND_LOG(rIn[i]==Get::value(randomAccess(rOut,i)/* rResult[i]*/));
        }
    }


    inline void TestCase_collector()
    {
        PrintTestcase();
        using namespace MiniMPL;

        S4      arr[ContainerSize20];

        stlVector<S3> vs3o;
        TestCase_collectorWithContainer(makeContainer(arr,ContainerSize20),vs3o,&S4::m_ss3);
        stlVector<S4> vs4o;
        TestCase_collectorSelf(makeContainer(arr,ContainerSize20),vs4o);

        stlVector<S3*> vs3p;
        TestCase_collectorWithContainer(makeContainer(arr,ContainerSize20),vs3p,&S4::m_ss3);
        stlVector<S4*> vs4p;
        TestCase_collectorSelf(makeContainer(arr,ContainerSize20),vs4p);

        S3      arrS3o[ContainerSize20];
        TestCase_collectorWithContainer(makeContainer(arr,ContainerSize20),makeContainer(arrS3o,0),&S4::m_ss3);
        S4      arrS4o[ContainerSize20];
        TestCase_collectorSelf(makeContainer(arr,ContainerSize20),makeContainer(arrS4o,0));

        S3*     arrS3p[ContainerSize20];
        TestCase_collectorWithContainer(makeContainer(arr,ContainerSize20),makeContainer(arrS3p,0),&S4::m_ss3);
        S4*     arrS4p[ContainerSize20];
        TestCase_collectorSelf(makeContainer(arr,ContainerSize20),makeContainer(arrS4p,0));

        std::list<S3>  lS3;
        TestCase_collectorWithContainer(makeContainer(arr,ContainerSize20),lS3,&S4::m_ss3);
        std::list<S4>  lS4;
        TestCase_collectorSelf(makeContainer(arr,ContainerSize20),lS4);

    }

#ifdef RUN_EXAMPLE_COLLECTOR
    InitRunFunc(TestCase_collector);
#else //else of RUN_EXAMPLE_COLLECTOR

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_COLLECTOR)=(outputTxtV(TXT("[Unit test run disabled] collector.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"collector.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_COLLECTOR
}

#else //else of COMPILE_EXAMPLE_COLLECTOR
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_COLLECTOR)=(outputTxtV(TXT("[Unit test compile disabled] collector.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"collector.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_COLLECTOR

