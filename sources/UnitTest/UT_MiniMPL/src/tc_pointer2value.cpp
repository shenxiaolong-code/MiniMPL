#ifndef __TEST_POINTER2VALUE_HPP__
#define __TEST_POINTER2VALUE_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\pointer2value.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_POINTER2VALUE to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_POINTER2VALUE

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_POINTER2VALUE
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_POINTER2VALUE
#endif

#if defined(RUN_EXAMPLE_POINTER2VALUE) && !defined(COMPILE_EXAMPLE_POINTER2VALUE)
    #define COMPILE_EXAMPLE_POINTER2VALUE
#endif

//#undef RUN_EXAMPLE_POINTER2VALUE
//#undef COMPILE_EXAMPLE_POINTER2VALUE

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_POINTER2VALUE
#include <MiniMPL/pointer2value.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>
#include <vector>
#include <list>

namespace UnitTest
{
    inline void TestCase_pointer2value()
    {
        PrintTestcase();
        
        using namespace MiniMPL;
        //demo Pointer2Value and Pointer2ValueFinal
        Static_Assert(!(IsSameType<Pointer2Value<std::vector<int> >::type,int>::value));
        Static_Assert((IsSameType<Pointer2Value<std::vector<int>::iterator>::type,int>::value));
        Static_Assert(!(IsSameType<Pointer2Value<std::list<int> >::type,int>::value));
        Static_Assert((IsSameType<Pointer2Value<std::list<int>::iterator>::type,int>::value));
        Static_Assert((!IsSameType<Pointer2Value<int[12]>::type,int>::value));
        Static_Assert((!IsSameType<Pointer2Value<int(&)[12]>::type,int>::value));
        Static_Assert((IsSameType<Pointer2Value<int*>::type,int>::value));
        Static_Assert((IsSameType<Pointer2Value<int(*)[2]>::type,int[2]>::value));
        Static_Assert(!(IsSameType<Pointer2Value<int(&)[2]>::type,int[2]>::value));      //array is not same as array reference
        Static_Assert((IsSameType<Pointer2Value<int(&)[2]>::type,int(&)[2]>::value));    //array is not same as array reference
        Static_Assert((IsSameRawType<Pointer2Value<int(&)[2]>::type,int[2]>::value));    //original type of array reference is array type
        Static_Assert((!IsSameType<Pointer2Value<const int[12]>::type,int>::value));
        Static_Assert((!IsSameRawType<Pointer2Value<const int[12]>::type,int>::value));

        Static_Assert((IsSameType<Pointer2ValueFinal<int>::type,int>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<int*>::type,int>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<int**>::type,int>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<stlSmartptr<int*> >::type,int>::value));        
        Static_Assert((IsSameRawType<Pointer2ValueFinal<std::vector<stlSmartptr<int*> >::iterator>::type,int>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<std::list<std::vector<stlSmartptr<int*> >::iterator>::iterator>::type,int>::value));

        Static_Assert((IsSameRawType<Pointer2ValueFinal<S4>::type,S4>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<S4*>::type,S4>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<S4**>::type,S4>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<stlSmartptr<S4*> >::type,S4>::value));        
        Static_Assert((IsSameRawType<Pointer2ValueFinal<std::vector<stlSmartptr<S4*> >::iterator>::type,S4>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<std::list<std::vector<stlSmartptr<S4*> >::iterator>::iterator>::type,S4>::value));

        Static_Assert((IsSameRawType<Pointer2ValueFinal<std::vector<int*>::iterator>::type,int>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<std::list<std::vector<int*>::iterator>::iterator>::type,int>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<std::list<std::list<std::vector<int*>::iterator>::iterator>::iterator>::type,int>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<std::vector<std::list<std::list<std::vector<int*>::iterator>::iterator*>::iterator>::iterator>::type,int>::value));
        Static_Assert((IsSameRawType<Pointer2ValueFinal<std::vector<stlSmartptr<std::vector<std::list<std::list<std::vector<int*>::iterator>::iterator>::iterator>::iterator*> >::iterator >::type,int>::value));


        //demo Get::pointer and Get::value
        ConstStruct  rObj;
        ConstStruct* pObj11   = MiniMPL::Get::CPointer(rObj);
        ConstStruct* pObj12  = MiniMPL::Get::CPointer(pObj11);

        ConstStruct& rVal11   = MiniMPL::Get::value(rObj);
        ConstStruct& rVal12  = MiniMPL::Get::value(pObj12);  

        stlSmartptr<ConstStruct> pStlPtr(new ConstStruct());       //test smart pointer
        ConstStruct* pObj21  = MiniMPL::Get::CPointer(pStlPtr);
        ConstStruct& rVal21  = MiniMPL::Get::value(pObj21);
        ConstStruct& rVal22  = MiniMPL::Get::value(pStlPtr);
        ConstStruct& rVal23  = MiniMPL::Get::value(pObj21);

        stlVector<ConstStruct>  arr;
        arr.push_back(rObj);                                        //test iterator
        stlVector<ConstStruct>::iterator pIt = arr.begin(); 
        ConstStruct* pObj31 = MiniMPL::Get::CPointer(pIt); 
        ASSERT_AND_LOG((rObj.m_a == pObj31->m_a));
        ConstStruct& rVal32   = MiniMPL::Get::value(pObj31);
        ConstStruct& rVal33   = MiniMPL::Get::value(pIt);

        //demo  Get::finalValue
        S4                                     objs[ContainerSize10];
        std::vector<S4*>                       rArr;
        std::list<std::vector<S4*>::iterator>  rList;
        Static_Assert((IsSameType<Pointer2ValueFinal<std::list<std::vector<S4*>::iterator>::iterator>::type,S4>::value));        
    }

#ifdef RUN_EXAMPLE_POINTER2VALUE
    InitRunFunc(TestCase_pointer2value);
#else //else of RUN_EXAMPLE_POINTER2VALUE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_POINTER2VALUE)=(outputTxtV(TXT("[Unit test run disabled] pointer2value.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"pointer2value.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_POINTER2VALUE
}

#else //else of COMPILE_EXAMPLE_POINTER2VALUE
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_POINTER2VALUE)=(outputTxtV(TXT("[Unit test compile disabled] pointer2value.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"pointer2value.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_POINTER2VALUE

#endif // __TEST_POINTER2VALUE_HPP__
