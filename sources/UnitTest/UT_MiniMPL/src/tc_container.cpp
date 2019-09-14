#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\container.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_CONTAINER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_CONTAINER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_CONTAINER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_CONTAINER
#endif

#if defined(RUN_EXAMPLE_CONTAINER) && !defined(COMPILE_EXAMPLE_CONTAINER)
    #define COMPILE_EXAMPLE_CONTAINER
#endif

//#undef RUN_EXAMPLE_CONTAINER
//#undef COMPILE_EXAMPLE_CONTAINER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_CONTAINER

// #ifdef CONST_CONTAINER_HAS_ITERATOR
//     #undef CONST_CONTAINER_HAS_ITERATOR
//     #define CONST_CONTAINER_HAS_ITERATOR 1         //for test const S4 arrc[ContainerSize20];
// #endif // CONST_CONTAINER_HAS_ITERATOR

#include <MiniMPL/container.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>
#include <UnitTestKit/tc_dump.h>
#include <UnitTestKit/tc_print.h>

namespace UnitTest
{
    HasXXXType(iterator);
    HasXXXType(const_iterator);

    template<typename T>
    void TestAddRemoceCArrContainer(T& rArr)
    {
        PrintTestcase();
        using namespace MiniMPL;

        Static_Assert(IsConst<typename AddConst<T>::type>::value);
        Static_Assert(!IsConst<typename RemoveConst<T>::type>::value);

        Static_Assert(IsRef<typename AddRef<T>::type>::value);
        Static_Assert(!IsRef<typename RemoveRef<T>::type>::value);

        showType<typename AddVolatile<int[5]>::type>();

        //Static_Assert(IsVolatile<typename AddVolatile<int[5]>::type>::value);
        Static_Assert(!IsVolatile<typename RemoveVolatile<T>::type>::value);

        Static_Assert(IsCPointer<typename AddCPointer<T>::type>::value);
        Static_Assert(!IsCPointer<typename RemoveCPointer<T>::type>::value);
    }

    template<typename T>
    void TestCArrContainer(T& rArr)
    {
        PrintTestcase();
        using namespace MiniMPL;
        Static_Assert(!IsConst<T>::value);
        Static_Assert(HasType_iterator<T>::value);
        Static_Assert(HasType_const_iterator<T>::value);

        TestAddRemoceCArrContainer(rArr);
    }
    template<typename T>
    void TestCArrContainer_const(T& rArr)
    {
        PrintTestcase();
        using namespace MiniMPL;
        Static_Assert(IsConst<T>::value);
#if CONST_CONTAINER_HAS_ITERATOR
        Static_Assert(HasType_iterator<T>::value);
#else
        Static_Assert(!HasType_iterator<T>::value);
#endif          
        Static_Assert(HasType_const_iterator<T>::value);

        //TestAddRemoceCArrContainer(rArr);
    }

    template<typename T>
    unsigned TestStdContainer(T& rArr)
    {
        PrintTestcase();
        using namespace MiniMPL;

        T& tc = makeContainer(rArr);
        for (unsigned idx=0;idx<6;++idx)
        {
            tc.push_back(idx);
        }
        outputTxtV(TXT("std container capacity:%d\n"),tc.capacity());
        outputTxtV(TXT("std container size:%d\n"),tc.size());        

        for (TContainer<T>::iterator it=tc.begin();it!=tc.end();++it)
        {
            it->func();
            outputTxtV(TXT("%d "),*it);
        }

        tc.insert(tc.end()-2,44);

        return tc.size();
    }

    template<typename T>
    unsigned TestNonConstArray(T& rArr,unsigned iSize)
    {    
        PrintTestcase();
        using namespace MiniMPL;

        TContainer<T> tc(rArr,iSize);
        for (unsigned idx=0;idx<6;++idx)
        {
            tc.push_back(idx);
        }
        outputTxtV(TXT("non-const array capacity:%d\n"),tc.capacity());
        outputTxtV(TXT("non-const array size:%d\n"),tc.size());        

        for (TContainer<T>::iterator it=tc.begin();it!=tc.end();++it)
        {
            it->func();
            outputTxtV(TXT("%d "),*it);
        }

        tc.insert(tc.end(),11);
        tc.insert(tc.size(),12);
        tc.insert(tc.end()-1,21);
        tc.insert(tc.size()-1,22);
        tc.insert(tc.end()-2,32);
        tc.insert(tc.size()-3,33);

        tc.erase(&rArr[2]);
        tc.erase(tc.begin());

        return tc.size();
    }

    template<typename T>
    void TestConstArray(T& rArr,unsigned iSize)
    {
        using namespace MiniMPL;

        TContainer<T> tc(rArr,iSize);
        outputTxt(TXT("const array has not capacity.\n"));
        //tc.capacity();   //compiler error : OK , const array has not capacity()
        outputTxtV(TXT("const array size:%d\n"),tc.size());

        //      tc.push_back(44);    //OK, const array has not member function "push_back"
        typename TContainer<T>::value_type a = tc.front();
        for (TContainer<T>::const_iterator it=tc.begin();it!=tc.end();++it)
        {
            outputTxtV(TXT("%d "),*it);
        }
    }

    bool TestCase_containerException()
    {
        PrintTestcase();

#define tstSize 8
        using namespace MiniMPL;

        std::vector<structData>         objStl;
        structData                      objArr[tstSize];
        typedef std::vector<int> vectorContainer_T;
        typedef std::map<int,int> mapContainer_T;
        typedef int(&arrContainer)[2];


        std::vector<structData>&   stl  = makeContainer(objStl);
        TContainer<structData[tstSize] >    rArr = makeContainer(objArr,0);

        //test push_back
        for (int i=0;i<tstSize;i++)
        {
            structData tmp;
            stl.push_back(tmp);
            rArr.push_back(tmp);
            Assertb(randomAccess(stl,i).m_a==randomAccess(rArr,i).m_a);
        }

        try
        {
            rArr.push_back(structData());    //test exception
        }
        catch (...)
        {
            ALWAYS_LOG_HERE_INFO((TXT("\nException occurs")));
        }

        std::vector<structData>& rStl       = objStl; 
        std::vector<structData>& rRefStl    = makeContainer(rStl);

        const std::vector<structData>::iterator pBegin = rRefStl.begin();
        const std::vector<structData>::iterator pEnd = rRefStl.end();

        const structData (&rConstArr)[tstSize]=objArr;
        TContainer<const structData[tstSize] > rRefArr = makeContainer(rConstArr,tstSize);
        rRefArr.begin();

        return true;
    }

    bool TestCase_container()
    {
        PrintTestcase();
        TestCase_containerException();

        int cArr[5]={0};
        TestCArrContainer(MiniMPL::makeContainer(cArr,5));
        const int cArrc[5]={0};
        TestCArrContainer_const(MiniMPL::makeContainer(cArrc,5));

        structData arr[15]={0};
        ASSERT_AND_LOG(MiniMPL::makeContainer_emptyArray(arr).size()==0);
        ASSERT_AND_LOG(MiniMPL::makeContainer_fullArray(arr).size()==15);

        arr[0]=111;
        unsigned iSize = TestNonConstArray(arr,1);
        TestConstArray<structData const [15]>(arr,iSize);

        std::vector<structData> stl;
        //MiniMPL::makeContainer_emptyArray(stl);    //Compile error : OK
        stl.push_back(3);
        TestStdContainer(stl);
        return true;
    }

#ifdef RUN_EXAMPLE_CONTAINER
    InitRunFunc(TestCase_container);
#else //else of RUN_EXAMPLE_CONTAINER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_CONTAINER)=(outputTxtV(TXT("[Unit test run disabled] container.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"container.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_CONTAINER
}

#else //else of COMPILE_EXAMPLE_CONTAINER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_CONTAINER)=(outputTxtV(TXT("[Unit test compile disabled] container.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"container.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_CONTAINER

