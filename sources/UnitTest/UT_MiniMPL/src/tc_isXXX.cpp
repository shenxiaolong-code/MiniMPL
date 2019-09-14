#ifndef __TEST_ISXXX_HPP__
#define __TEST_ISXXX_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\isXXX.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_ISXXX to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_ISXXX

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_ISXXX
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_ISXXX
#endif

#if defined(RUN_EXAMPLE_ISXXX) && !defined(COMPILE_EXAMPLE_ISXXX)
    #define COMPILE_EXAMPLE_ISXXX
#endif

//#undef RUN_EXAMPLE_ISXXX
//#undef COMPILE_EXAMPLE_ISXXX

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_ISXXX
#include <MiniMPL/isXXX.hpp>
#include <UT_material/tc_def_typeClass.h>
#include <UT_material/tc_def_typeStruct.h>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{
    template<typename T>
    void testConstCompile(char* msg)
    {      
        outputTxtStreamA(msg << "[VS:" << typeid(T).name() << "] is const.\r\n");
        T p=0;        
        ++p;
    }

    template<typename T>
    void testConst(char* msg,ENABLE_IF(MiniMPL::IsConst<T>::value))
    {  
        outputTxtStreamA(msg << "[VS:" << typeid(T).name() << "] is const.\r\n");
        typedef typename MiniMPL::GetRawType<T>::type _RT;
        _RT a;
        a;
        /*/ expected compile error : you cannot assign to a variable that is const
        T b=a;
        ++b;
        //*/
    }

    template<typename T>
    void testConst(char* msg,ENABLE_NOT(MiniMPL::IsConst<T>::value))
    { 
        outputTxtStreamA(msg << "[VS:" << typeid(T).name() << "] is NOT const.\r\n");
        typedef typename MiniMPL::GetRawType<T>::type _RT;
        _RT a;
        T b=a;
        ++b; 
    }

    template<typename T>
    void testConstP(char* msg,ENABLE_IF(MiniMPL::IsConst<T>::value))
    {    
        outputTxtStreamA(msg << "[VS:" << typeid(T).name() << "] is const.\r\n");
        /*/ expected compile error
        T p=0;        
        ++p;
        //*/
    }

    template<typename T>
    void testConstP(char* msg,ENABLE_NOT(MiniMPL::IsConst<T>::value))
    { 
        outputTxtStreamA(msg << "[" << typeid(T).name() << "] is NOT const.\r\n");
        T p=0;        
        ++p;
    }

    inline void TestCase_isXXX()
    {
        PrintTestcase();

        using namespace MiniMPL;

        //const IsConst 
        int a[5];
        int *pA=a;
        testConstCompile<int const*>("int const*");     //compile OK : OK , int const* is not const
        //testConstCompile<int* const>("int* const");   //compile error : OK , int* const is const
        testConstP<int>("int");
        testConstP<int const>("int const");
        testConstP<int const*>("int const*");            //int const* is not const
        testConstP<int* const>("int* const");            //compile error : OK , int* const is const
        testConstP<int* const*>("int* const*");     

        testConst<int&>("int&");
        testConst<int const&>("int const&");
        testConst<int const&>("int const&");            //int const* is not const
        testConst<int const>("int const");            //compile error : OK , int* const is const

        Static_Assert((MiniMPL::IsConst<const int>::value));        
        Static_Assert((MiniMPL::IsConst<const int&>::value));        
        Static_Assert((MiniMPL::IsConst<int const&>::value));        
        Static_Assert((MiniMPL::IsConst<const int&>::value));                
        Static_Assert((MiniMPL::IsConst<const int&>::value));
        Static_Assert((!MiniMPL::IsConst<const int*>::value));
        Static_Assert((!MiniMPL::IsConst<int const*>::value));
        Static_Assert((MiniMPL::IsConst<int* const>::value));
        Static_Assert((MiniMPL::IsConst<const volatile int>::value));
        Static_Assert((MiniMPL::IsConst<volatile const int>::value));
        Static_Assert((!MiniMPL::IsConst<volatile CDemoBase*>::value));
        Static_Assert((MiniMPL::IsConst<int[20]>::value==false));
        Static_Assert((MiniMPL::IsConst<const int[15]>::value));
        Static_Assert((MiniMPL::IsConst<char(&)[2]>::value==false));
        Static_Assert((MiniMPL::IsConst<const char(&)[2]>::value));	
        Static_Assert((!MiniMPL::IsConst<const UnitTest::S4 *>::value)); 
        Static_Assert((!MiniMPL::IsConst<const S3**>::value));
        Static_Assert((!MiniMPL::IsConst<const S3*>::value));
        Static_Assert((!MiniMPL::IsConst<S3 const*>::value));

        Static_Assert((!MiniMPL::IsConst<void (*)()>::value));
        Static_Assert((!MiniMPL::IsConst<void (S3::*)()>::value));
        //test const member function by IsConstMemberFunctionPointer because member function can't use AddConst/RemoveConst
        Static_Assert((!MiniMPL::IsConst<void (S3::*)() const>::value)); 

        //demo IsVolatile
        Static_Assert((MiniMPL::IsVolatile<volatile int>::value));
        Static_Assert((!MiniMPL::IsVolatile<const int>::value));
        Static_Assert((!MiniMPL::IsVolatile<const int&>::value));
        Static_Assert((MiniMPL::IsVolatile<const volatile int>::value));
        Static_Assert((MiniMPL::IsVolatile<volatile const int>::value));

        //demo IsRef
        Static_Assert((!MiniMPL::IsRef<void>::value));
        Static_Assert((!MiniMPL::IsRef<void*>::value));
        Static_Assert((MiniMPL::IsRef<void*&>::value));
        Static_Assert((MiniMPL::IsRef<const volatile int&>::value));
        Static_Assert((!MiniMPL::IsRef<const volatile CDemoBase*>::value));
        Static_Assert((MiniMPL::IsRef<char&>::value));
        Static_Assert((MiniMPL::IsRef<char const&>::value));
        Static_Assert((MiniMPL::IsRef<const char&>::value));
        Static_Assert((MiniMPL::IsRef<char const*&>::value));
        Static_Assert((MiniMPL::IsRef<char*&>::value));
        Static_Assert((!MiniMPL::IsRef<char[2]>::value));
        Static_Assert((MiniMPL::IsRef<char(&)[2]>::value));
        Static_Assert((!MiniMPL::IsRef<char(*)[2]>::value));

        Static_Assert((IsCPointer<int*>::value));
        Static_Assert((IsCPointer<int const *>::value));
        Static_Assert((IsCPointer<int const * const>::value));
        Static_Assert(!(IsCPointer<int>::value));
        Static_Assert(!(IsCPointer<int S4::*>::value));
        Static_Assert(!(IsCPointer<int S4::* const>::value));
        Static_Assert(!(IsCPointer<void (*)(int)>::value));
        Static_Assert(!(IsCPointer<void (S4::*)(int)>::value));
        Static_Assert(!(IsCPointer<void (S4::*)(int) const >::value));
        Static_Assert(!(IsCPointer<void (S4::*)(int)>::value));
    }

#ifdef RUN_EXAMPLE_ISXXX
    InitRunFunc(TestCase_isXXX);
#else //else of RUN_EXAMPLE_ISXXX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_ISXXX)=(outputTxtV(TXT("[Unit test run disabled] isXXX.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"isXXX.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_ISXXX
}

#else //else of COMPILE_EXAMPLE_ISXXX
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_ISXXX)=(outputTxtV(TXT("[Unit test compile disabled] isXXX.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"isXXX.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_ISXXX

#endif // __TEST_ISXXX_HPP__
