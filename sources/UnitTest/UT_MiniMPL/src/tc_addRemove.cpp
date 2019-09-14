#ifndef __TEST_ADDREMOVE_HPP__
#define __TEST_ADDREMOVE_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\addRemove.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_ADDREMOVE to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_ADDREMOVE

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_ADDREMOVE
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_ADDREMOVE
#endif

#if defined(RUN_EXAMPLE_ADDREMOVE) && !defined(COMPILE_EXAMPLE_ADDREMOVE)
    #define COMPILE_EXAMPLE_ADDREMOVE
#endif

//#undef RUN_EXAMPLE_ADDREMOVE
//#undef COMPILE_EXAMPLE_ADDREMOVE

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_ADDREMOVE
#include <MiniMPL/addRemove.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>
#include <UT_material/tc_def_qualifier.hpp>
#include <MiniMPL/isXXXEx.hpp>

namespace UnitTest
{
    inline void TestCase_addCPointer()
    {
        PrintTestcase();
        using namespace MiniMPL;
        Static_Assert((IsSameType<AddCPointer<char>::type,char*>::value));
        Static_Assert((IsSameType<AddCPointer<char*>::type,char**>::value));
        Static_Assert((IsSameType<AddCPointer<char&>::type,char*&>::value));
        Static_Assert((IsSameType<AddCPointer<volatile char>::type,volatile char*>::value));
        Static_Assert((IsSameType<AddCPointer<volatile char*>::type,volatile char**>::value));

        Static_Assert((IsSameType<AddCPointer<char[4]>::type,char(*)[4]>::value));
        Static_Assert((IsSameType<AddCPointer<char(&)[4]>::type,char(*&)[4]>::value));
        Static_Assert((IsSameType<AddCPointer<const char(&)[4]>::type,const char(*&)[4]>::value));
        Static_Assert((IsSameType<AddCPointer<const char[4]>::type,const char(*)[4]>::value));
    }
    inline void TestCase_removeCPointer()
    {
        PrintTestcase();
        using namespace MiniMPL;
        Static_Assert((IsSameType<RemoveCPointer<char>::type,char>::value));
        Static_Assert((IsSameType<RemoveCPointer<char*>::type,char>::value));
        Static_Assert((IsSameType<RemoveCPointer<char*&>::type,char&>::value));

        Static_Assert((IsSameType<RemoveCPointer<char[4]>::type,char[4]>::value));
        Static_Assert((IsSameType<RemoveCPointer<char(*)[4]>::type,char[4]>::value));
        Static_Assert((IsSameType<RemoveCPointer<const char(*)[4]>::type,const char[4]>::value));
    }
    inline void TestCase_addRef()
    {
        PrintTestcase();
        using namespace MiniMPL;
    }
    inline void TestCase_removeRef()
    {
        PrintTestcase();
        using namespace MiniMPL;
    }
    inline void TestCase_addVolatile()
    {
        PrintTestcase();
        using namespace MiniMPL;
    }
    inline void TestCase_removeVolatile()
    {
        PrintTestcase();
        using namespace MiniMPL;
    }

    inline void TestCase_removeConst()
    {
        PrintTestcase();
        using namespace MiniMPL;

        //test C Pointer
        Static_Assert((IsSameType<RemoveConst<const char>::type,char>::value));
        Static_Assert((IsSameType<RemoveConst<const char*>::type,char*>::value));
        Static_Assert((IsSameType<RemoveConst<char* const>::type,char*>::value));
        Static_Assert(!(IsSameType<RemoveConst<const char*>::type,char>::value));

        //test reference
        Static_Assert((IsSameType<RemoveConst<const char&>::type,char&>::value));

        //test array
        Static_Assert((IsSameType<RemoveConst<const int[5]>::type,int[5]>::value));
        Static_Assert((IsSameType<RemoveConst<int[5]>::type,int[5]>::value));
        Static_Assert((IsSameType<RemoveConst<int(&)[5]>::type,int(&)[5]>::value));
        Static_Assert(!(IsSameType<RemoveConst<int(&)[5]>::type,int[5]>::value));
        Static_Assert((IsSameType<RemoveConst<const int(&)[5]>::type,int(&)[5]>::value));
        Static_Assert((IsSameType<RemoveConst<const int(*)[5]>::type,int(*)[5]>::value));
        Static_Assert((IsSameType<RemoveConst<const int(* const)[5]>::type,const int(*)[5]>::value));
    }

    inline void TestCase_addConst()
    {
        PrintTestcase();
        using namespace MiniMPL;

        //test C Pointer
        Static_Assert((IsSameType<AddConst<const char>::type,const char>::value));
        Static_Assert((IsSameType<AddConst<const char*>::type,const char* const>::value));
        Static_Assert((IsSameType<AddConst<char*>::type,char* const>::value));
        Static_Assert((IsSameType<AddConst<char*&>::type,char* const&>::value));
        Static_Assert(!(IsSameType<AddConst<const char*>::type,const char>::value));

        //test reference
        Static_Assert((IsSameType<AddConst<const char&>::type,const char&>::value));

        //test array
        Static_Assert((IsSameType<AddConst<const int[5]>::type,const int[5]>::value));
        Static_Assert((IsSameType<AddConst<int[5]>::type,const int[5]>::value));
        Static_Assert((IsSameType<AddConst<int(&)[5]>::type,const int(&)[5]>::value));
        Static_Assert(!(IsSameType<AddConst<int(&)[5]>::type,const int[5]>::value));
        Static_Assert((IsSameType<AddConst<const int(&)[5]>::type,const int(&)[5]>::value));
        Static_Assert((IsSameType<AddConst<const int(*)[5]>::type,const int(* const)[5]>::value));
    }

    inline void TestCase_addRemove()
    {        
        PrintTestcase();
        using namespace MiniMPL;

        TestCase_addCPointer();
        TestCase_removeCPointer();
        TestCase_addRef();
        TestCase_removeRef();
        TestCase_addVolatile();
        TestCase_removeVolatile();

        ConstStruct obj;
        ConstStruct const& demo=obj;
        process(obj.m_Chars[5]);
        process(demo.m_Chars[6]);        
    }

#ifdef RUN_EXAMPLE_ADDREMOVE
    InitRunFunc(TestCase_addRemove);
#else //else of RUN_EXAMPLE_ADDREMOVE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_ADDREMOVE)=(outputTxtV(TXT("[Unit test run disabled] addRemove.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"addRemove.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_ADDREMOVE
}

#else //else of COMPILE_EXAMPLE_ADDREMOVE
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_ADDREMOVE)=(outputTxtV(TXT("[Unit test compile disabled] addRemove.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"addRemove.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_ADDREMOVE

#endif // __TEST_ADDREMOVE_HPP__
