#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\comparer.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_COMPARER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_COMPARER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_COMPARER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_COMPARER
#endif

#if defined(RUN_EXAMPLE_COMPARER) && !defined(COMPILE_EXAMPLE_COMPARER)
    #define COMPILE_EXAMPLE_COMPARER
#endif

//#undef RUN_EXAMPLE_COMPARER
//#undef COMPILE_EXAMPLE_COMPARER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_COMPARER

#ifdef CONST_CONTAINER_HAS_ITERATOR
    #undef CONST_CONTAINER_HAS_ITERATOR
    #define CONST_CONTAINER_HAS_ITERATOR 1         //for test const S4 arrc[ContainerSize20];
#endif // CONST_CONTAINER_HAS_ITERATOR

#include <MiniMPL/comparer.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>
#include <MiniMPL/container.hpp>
#include <UnitTestKit/tc_print.h>
#include <list>

namespace UnitTest
{
    template<typename C,typename F,typename S,typename M>
    void ComparerByMember(C& rC, F f,M S::* pMemPtr)
    {
        PrintTestcase();
        using namespace MiniMPL;

        typedef MiniMPL::ResultComparer<CDataMemberPtr<M S::*>,F> Cmp_T;
        Cmp_T&  rCmp    = MiniMPL::makeComparerByMember(pMemPtr,f);
        Cmp_T&  rCmp2   = MiniMPL::makeComparerByMember(pMemPtr,f);

        typedef typename CGetType::TContainer<C>::type    DataSet_T;
        typedef typename MiniMPL::If_Evl<MiniMPL::IsConst<C>, DataSet_T::const_iterator, DataSet_T::iterator>::type   myIterator;
        typedef typename MiniMPL::SameConst<DataSet_T::value_type,C>::type    value_type;

        DataSet_T  rSet = makeContainer(rC);
        myIterator pHead = rSet.begin();
        myIterator pEnd  = rSet.end();
        DataSet_T::size_type iSize=rSet.size();
        value_type& midVal= randomAccess(rSet,iSize/2);
        while(pHead != pEnd)
        {
            rCmp(*pHead,midVal);
            rCmp2(*pHead,midVal);
            pHead++;
        };

    }

    template<typename C,typename F,typename S>
    void ComparerByObjMember(C& rC, F f,int S::* pMemPtr)
    {
        PrintTestcaseSub();

        using namespace MiniMPL;
        typedef typename CGetType::TContainer<C>::type      TContainer;
        typedef CDataMemberPtr<int S::*>                    TUnaryFunc;
        typedef BinaryFunction<F>                           TBinaryFunc;
        typedef typename GetBinaryFunctionParam<F,1>::type  TP1;
        typedef typename GetBinaryFunctionParam<F,2>::type  TP2;
        typedef typename MiniMPL::If_Evl<MiniMPL::IsConst<C>, TContainer::const_iterator, TContainer::iterator>::type   myIterator;

        TContainer  rSet = makeContainer(rC);        
        myIterator pHead = rSet.begin();
        myIterator pEnd  = rSet.end();

        TP1 iL = rand()/1000;
        TP2 iR = rand()/1000;
        while(pHead != pEnd)
        {
            bool bRet = (iL+*pHead.*pMemPtr) >= iR;     //S4::compareBinaryFunction impl
            TBinaryFunc& rBf = makeBinaryFunction(*pHead,f);
            Assertb(makeComparer(rBf)(iL,iR) == bRet);  //TBinaryFunc& makeComparer(TBinaryFunc& f)
            ++pHead;
        };
    }

    template<typename C,typename F>
    void testDirectCompare(C& rC, F f)
    {   
        PrintTestcase();
        using namespace MiniMPL;

        typedef typename CGetType::TContainer<C>::type    TContainer;
        typedef typename MiniMPL::If_Evl<MiniMPL::IsConst<C>, TContainer::const_iterator, TContainer::iterator>::type   myIterator;
        typedef typename MiniMPL::SameConst<C::value_type,C>::type    value_type;

        TContainer  rSet = makeContainer(rC); 
        myIterator pHead = rSet.begin();
        myIterator pEnd  = rSet.end();
        TContainer::size_type iSize=rSet.size();
        value_type& midVal= randomAccess(rSet,iSize/2);
        while(pHead != pEnd)
        {
            makeComparer(f)(*pHead,midVal);
            pHead++;
        };
    } ;

    template<typename C>
    void testDataSet_S4_ByMember(C& rC)
    {
        using namespace MiniMPL;
        Static_Assert((!IsConst<C>::value));
        Static_Assert((IsStlContainer<C>::value));

        ComparerByMember(rC,binSN1N2<S3>,&S4::m_ss3);
        ComparerByMember(rC,binSN1R2<S3>,&S4::m_ss3);
        ComparerByMember(rC,binSR1R2<S3>,&S4::m_ss3);
        ComparerByMember(rC,binSCR1R2<S3>,&S4::m_ss3);
        ComparerByMember(rC,binSCR1C2<S3>,&S4::m_ss3);

        ComparerByObjMember(rC,&S4::compareBinaryFunction,&S4::m_s4);
        ComparerByObjMember(rC, &S4::compareBinaryFunction_const, &S4::m_s4);

        typedef typename CGetType::TContainer<C>::type  TContainer;
        typedef ET(TContainer)       ST;
        testDirectCompare(rC,binSN1N2<ST>);
        testDirectCompare(rC,binSN1N2<ST>);
        testDirectCompare(rC,binSN1R2<ST>);
        testDirectCompare(rC,binSR1R2<ST>);
        testDirectCompare(rC,binSCR1R2<ST>);
        testDirectCompare(rC,binSCR1C2<ST>);
    }

    template<typename C>
    void testDataSet_S4_ByMember_Const(C& rC)
    {
        using namespace MiniMPL;
        Static_Assert((IsStlContainer<C>::value));
        ComparerByMember(rC, binSN1N2<S3>, &S4::m_ss3);
        //below function parameter T& need non-const object , here C is const
        //ComparerByMember(rC, binSN1R2<S3>, &S4::m_ss3);  //binSN1R2 need non-const object
        //ComparerByMember(rC, binSR1R2<S3>, &S4::m_ss3);  //binSR1R2 need non-const object
        //ComparerByMember(rC, binSCR1R2<S3>, &S4::m_ss3);  //binSCR1R2 need non-const object
        ComparerByMember(rC, binSCR1C2<S3>, &S4::m_ss3);

        //ComparerByObjMember(rC,&S4::compareBinaryFunction,&S4::m_s4); //compareBinaryFunction need non-const object
        ComparerByObjMember(rC, &S4::compareBinaryFunction_const, &S4::m_s4);

        typedef typename CGetType::TContainer<C>::type  TContainer;
        typedef ET(TContainer)       ST;
        testDirectCompare(rC, binSN1N2<ST>);
        testDirectCompare(rC, binSN1N2<ST>);
        //testDirectCompare(rC, binSN1R2<ST>);          //binSN1R2 need non-const object
        //testDirectCompare(rC, binSR1R2<ST>);          //binSR1R2 need non-const object
        //testDirectCompare(rC, binSCR1R2<ST>);         //binSCR1R2 need non-const object
        testDirectCompare(rC, binSCR1C2<ST>);
    }

    void TestCase_S4()
    {
        using namespace MiniMPL;

        S4     arr[ContainerSize20];
        testDataSet_S4_ByMember(makeContainer(arr,ContainerSize20));
        testDataSet_S4_ByMember_Const(makeContainer(arr,ContainerSize20)); //for non-const object, the const func or T& all are OK

        const S4 arrc[ContainerSize20];
        //testDataSet_S4_ByMember(makeContainer(arrc,ContainerSize20)); //non-const function or T& needs non-const object
        testDataSet_S4_ByMember_Const(makeContainer(arrc,ContainerSize20));

        std::vector<S4> vVect(&arr[0],&arr[ContainerSize20]);
        testDataSet_S4_ByMember(vVect);
        testDataSet_S4_ByMember_Const(vVect);

        const std::vector<S4> vVectc(&arr[0],&arr[ContainerSize20]);
        //testDataSet_S4_ByMember(vVectc);      //non-const function or T& needs non-const object
        testDataSet_S4_ByMember_Const(vVectc);
             
        std::list<S4> vlist(&arr[0],&arr[ContainerSize20]);
        testDataSet_S4_ByMember(vlist);          
        testDataSet_S4_ByMember_Const(vlist);    //for non-const object, the const func or T& all are OK

        const std::list<S4> vlistc(&arr[0],&arr[ContainerSize20]);
        //testDataSet_S4_ByMember(vlistc);       //non-const function or T& needs non-const object
        testDataSet_S4_ByMember_Const(vlistc);
    }

    inline void TestCase_comparer()
    {
        PrintTestcase();
        TestCase_S4();
    }

#ifdef RUN_EXAMPLE_COMPARER
    InitRunFunc(TestCase_comparer);
#else //else of RUN_EXAMPLE_COMPARER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_COMPARER)=(outputTxtV(TXT("[Unit test run disabled] comparer.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"comparer.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_COMPARER
}

#else //else of COMPILE_EXAMPLE_COMPARER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_COMPARER)=(outputTxtV(TXT("[Unit test compile disabled] comparer.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"comparer.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_COMPARER

