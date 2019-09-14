#ifndef __TEST_ISXXXEX_HPP__
#define __TEST_ISXXXEX_HPP__
#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\isXXXEx.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_ISXXXEX to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_ISXXXEX

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_ISXXXEX
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_ISXXXEX
#endif

#if defined(RUN_EXAMPLE_ISXXXEX) && !defined(COMPILE_EXAMPLE_ISXXXEX)
    #define COMPILE_EXAMPLE_ISXXXEX
#endif

//#undef RUN_EXAMPLE_ISXXXEX
//#undef COMPILE_EXAMPLE_ISXXXEX

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_ISXXXEX
#include <MiniMPL/isXXXEx.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_MiniMPL/ut_material.h>

namespace UnitTest
{

    inline void TestCase_isXXXEx()
    {
        PrintTestcase();        
        //test IsSameType && IsSameRawType
        Static_Assert((MiniMPL::IsSameType<int,int>::value));
        Static_Assert((MiniMPL::IsSameRawType<int,int>::value));
        Static_Assert((!MiniMPL::IsSameType<int,char>::value));
        Static_Assert((!MiniMPL::IsSameRawType<int,char>::value));
        Static_Assert((!MiniMPL::IsSameType<float,double>::value));
        Static_Assert((!MiniMPL::IsSameRawType<float,double>::value));
        Static_Assert((!MiniMPL::IsSameType<int,const int>::value));
        Static_Assert((MiniMPL::IsSameRawType<int,const int>::value));
        Static_Assert((!MiniMPL::IsSameType<int,int*>::value));
        Static_Assert((!MiniMPL::IsSameRawType<int,int*>::value));
        Static_Assert((!MiniMPL::IsSameType<int,volatile int>::value));
        Static_Assert((!MiniMPL::IsSameRawType<volatile int,int*>::value));
        Static_Assert((!MiniMPL::IsSameType<int&,int>::value));
        Static_Assert((MiniMPL::IsSameRawType<int,int&>::value));

        //demo IsPointer
        Static_Assert((MiniMPL::IsPointer<const int*>::value));
        Static_Assert((MiniMPL::IsPointer<int*&>::value)); 
        Static_Assert((MiniMPL::IsPointer<int* const>::value)); 
        Static_Assert(!(MiniMPL::IsPointer<int&>::value)); 
        Static_Assert((!MiniMPL::IsPointer<const volatile int&>::value));
        Static_Assert((MiniMPL::IsPointer<int (*)[2]>::value));
        Static_Assert((MiniMPL::IsPointer<const int (*)[2]>::value));
        Static_Assert((MiniMPL::IsPointer<const int[5]>::value==false));
        Static_Assert((MiniMPL::IsPointer<const int(&)[5]>::value==false));
        // Note : it seems that function pointer belongs to pointer category also.
        Static_Assert((!MiniMPL::IsPointer<void()>::value));
        Static_Assert((MiniMPL::IsPointer<void*>::value));
        Static_Assert((MiniMPL::IsPointer<void(*)>::value));        //same as void*
        Static_Assert((!MiniMPL::IsPointer<void(*)()>::value));     //function pointer
        Static_Assert((!MiniMPL::IsPointer<void(int)>::value));     //function
        Static_Assert((!MiniMPL::IsPointer<void(*)(int)>::value));        //function pointer
        Static_Assert((!MiniMPL::IsPointer<void(int,stlString)>::value));   //function
        Static_Assert((!MiniMPL::IsPointer<void(*)(int,stlString)>::value));  //function pointer
        Static_Assert((MiniMPL::IsPointer<stlSmartptr<int*> >::value));
        Static_Assert((MiniMPL::IsPointer<stlSmartptr<int> >::value));
        Static_Assert((MiniMPL::IsPointer<stlSmartptr<int> >::value));

        Static_Assert((!MiniMPL::IsSmartPointer<const int*>::value));
        Static_Assert((!MiniMPL::IsSmartPointer<int*>::value));
        Static_Assert((!MiniMPL::IsSmartPointer<int>::value));
        Static_Assert((!MiniMPL::IsSmartPointer<int&>::value));
        Static_Assert((MiniMPL::IsSmartPointer<stlSmartptr<int*> >::value));
        Static_Assert((MiniMPL::IsSmartPointer<stlSmartptr<int> >::value));
        Static_Assert((MiniMPL::IsSmartPointer<stlSmartptr<int>& >::value));
        Static_Assert((MiniMPL::IsSmartPointer<stlSmartptr<int> const >::value));
        Static_Assert((MiniMPL::IsSmartPointer<stlSmartptr<int> const& >::value));
        Static_Assert((MiniMPL::IsSmartPointer<volatile stlSmartptr<int>>::value));

        //demo IsAtomType 
        Static_Assert(MiniMPL::IsAtomType<int>::value);
        Static_Assert(MiniMPL::IsAtomType<unsigned int>::value);
        Static_Assert(MiniMPL::IsAtomType<unsigned int&>::value);
        Static_Assert(MiniMPL::IsAtomType<int*>::value);
        Static_Assert(MiniMPL::IsAtomType<char>::value);        
        Static_Assert(MiniMPL::IsAtomType<char*>::value);
        Static_Assert(!MiniMPL::IsAtomType<CDemoDrived>::value);    //CDemoDrived is not atom type    
        Static_Assert(MiniMPL::IsAtomType<CDemoDrived*>::value);    //but CDemoDrived* is atom type --- pointer is atom type
        Static_Assert(MiniMPL::IsAtomType<EnumType>::value);
        Static_Assert(!MiniMPL::IsAtomType<EnumType[3]>::value);
        Static_Assert(!MiniMPL::IsAtomType<int[2]>::value);
        Static_Assert(MiniMPL::IsAtomType<int(&)[2]>::value);
        Static_Assert(MiniMPL::IsAtomType<float>::value);
        Static_Assert(MiniMPL::IsAtomType<void (*)(int)>::value);
        Static_Assert(MiniMPL::IsAtomType<void (&)(int)>::value);
        Static_Assert(MiniMPL::IsAtomType<S3 (*)(S4,int)>::value);
        Static_Assert(MiniMPL::IsAtomType<int (*)(char*)>::value);
        Static_Assert(MiniMPL::IsAtomType<void (CDemoBase::*)(int)>::value);
        Static_Assert(MiniMPL::IsAtomType<int S4::*>::value);
        Static_Assert((MiniMPL::IsAtomType<bool (__cdecl *)(const UnitTest::S4 &)>::value));

        //demo IsBuildInType
        Static_Assert(!MiniMPL::IsBuildInType<void>::value);
        Static_Assert(MiniMPL::IsBuildInType<void*>::value);
        Static_Assert(MiniMPL::IsBuildInType<int>::value);
        Static_Assert(MiniMPL::IsBuildInType<unsigned int>::value);
        Static_Assert(!MiniMPL::IsBuildInType<int[20]>::value);
        Static_Assert(MiniMPL::IsBuildInType<double>::value);
        Static_Assert(MiniMPL::IsBuildInType<const int>::value);
        Static_Assert(MiniMPL::IsBuildInType<const char>::value);
        Static_Assert(MiniMPL::IsBuildInType<unsigned char>::value);
        Static_Assert(MiniMPL::IsBuildInType<bool>::value);
        Static_Assert(MiniMPL::IsBuildInType<char*>::value);         //pointer is inner type
        Static_Assert(!MiniMPL::IsBuildInType<char*[20]>::value);
        Static_Assert(!MiniMPL::IsBuildInType<CDemoIndenpent>::value); 
        Static_Assert(!MiniMPL::IsBuildInType<CDemoIndenpent[20]>::value);
        Static_Assert(!MiniMPL::IsBuildInType<int(&)[20]>::value);
        Static_Assert(!MiniMPL::IsBuildInType<CDemoIndenpent(&)[20]>::value);
        Static_Assert(!MiniMPL::IsBuildInType<EnumType>::value);
        Static_Assert(MiniMPL::IsBuildInType<bool*>::value);
        Static_Assert(MiniMPL::IsBuildInType<char*>::value);
        Static_Assert(MiniMPL::IsBuildInType<signed char*>::value);
        Static_Assert(MiniMPL::IsBuildInType<wchar_t*>::value);
        Static_Assert(MiniMPL::IsBuildInType<short*>::value);
        Static_Assert(MiniMPL::IsBuildInType<unsigned short*>::value);
        Static_Assert(MiniMPL::IsBuildInType<float*>::value);
        Static_Assert(MiniMPL::IsBuildInType<double*>::value);
        Static_Assert(!MiniMPL::IsBuildInType<stlSmartptr<int> >::value);
        Static_Assert(!MiniMPL::IsBuildInType<stlSmartptr<int*> >::value);
        Static_Assert(!MiniMPL::IsBuildInType<stlSmartptr<bool> >::value);
        Static_Assert(!MiniMPL::IsBuildInType<stlSmartptr<char> >::value);
        Static_Assert(!MiniMPL::IsBuildInType<typename stlVector<int>::iterator >::value);
        Static_Assert(!MiniMPL::IsBuildInType<typename stlVector<int*>::iterator >::value);
        Static_Assert(!MiniMPL::IsBuildInType<typename stlVector<bool>::iterator>::value);
        Static_Assert(!MiniMPL::IsBuildInType<typename stlVector<char>::iterator>::value);
        Static_Assert(!(MiniMPL::IsBuildInType<typename stlMap<int,char>::iterator >::value));
        Static_Assert(!(MiniMPL::IsBuildInType<typename stlMap<int*,bool>::iterator >::value));
        Static_Assert(!(MiniMPL::IsBuildInType<typename stlMap<bool,stlStringA>::iterator>::value));
        Static_Assert(!(MiniMPL::IsBuildInType<typename stlMap<char,stlStringW>::iterator>::value));
        Static_Assert(!MiniMPL::IsBuildInType<typename stlVector<int>::const_iterator >::value);
        Static_Assert(!MiniMPL::IsBuildInType<typename stlVector<int*>::const_iterator >::value);
        Static_Assert(!MiniMPL::IsBuildInType<typename stlVector<bool>::const_iterator>::value);
        Static_Assert(!MiniMPL::IsBuildInType<typename stlVector<char>::const_iterator>::value);
        Static_Assert(MiniMPL::IsBuildInType<typename stlVector<int>::pointer >::value);
        Static_Assert(MiniMPL::IsBuildInType<typename stlVector<int*>::pointer >::value);
        Static_Assert(!MiniMPL::IsBuildInType<typename stlVector<bool>::pointer>::value); //class vector<_Bool> is override for alloc reason
        Static_Assert(MiniMPL::IsBuildInType<typename stlVector<char>::pointer>::value);

        //demo IsBuildInInteger
        Static_Assert((MiniMPL::IsBuildInInteger<bool>::value));
        Static_Assert((MiniMPL::IsBuildInInteger<char>::value));
        Static_Assert((MiniMPL::IsBuildInInteger<unsigned char>::value));
        Static_Assert((MiniMPL::IsBuildInInteger<unsigned>::value));
        Static_Assert((MiniMPL::IsBuildInInteger<signed>::value));
        Static_Assert((MiniMPL::IsBuildInInteger<wchar_t>::value));
        Static_Assert((MiniMPL::IsBuildInInteger<long long>::value));
        Static_Assert((MiniMPL::IsBuildInInteger<unsigned long>::value));
        Static_Assert((!MiniMPL::IsBuildInInteger<void>::value));
        Static_Assert((!MiniMPL::IsBuildInInteger<void*>::value));
        Static_Assert((!MiniMPL::IsBuildInInteger<bool*>::value));
        Static_Assert((!MiniMPL::IsBuildInInteger<char*>::value));
        Static_Assert((!MiniMPL::IsBuildInInteger<int*>::value));
        Static_Assert((!MiniMPL::IsBuildInInteger<float>::value));
        Static_Assert((!MiniMPL::IsBuildInInteger<double>::value));
        Static_Assert((!MiniMPL::IsBuildInInteger<long double>::value));

        //demo isBuildinFloat
        Static_Assert((!MiniMPL::isBuildinFloat<void>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<void*>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<bool>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<char>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<unsigned char>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<unsigned>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<signed>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<wchar_t>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<long long>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<unsigned long>::value));        
        Static_Assert((!MiniMPL::isBuildinFloat<bool*>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<char*>::value));
        Static_Assert((!MiniMPL::isBuildinFloat<int*>::value));
        Static_Assert((MiniMPL::isBuildinFloat<float>::value));
        Static_Assert((MiniMPL::isBuildinFloat<double>::value));
        Static_Assert((MiniMPL::isBuildinFloat<long double>::value));

        //demo IsEnumType
        Static_Assert(!MiniMPL::IsEnumType<int>::value);
        Static_Assert(!MiniMPL::IsEnumType<unsigned int>::value);
        Static_Assert(!MiniMPL::IsEnumType<int[20]>::value);
        Static_Assert(!MiniMPL::IsEnumType<double>::value);
        Static_Assert(!MiniMPL::IsEnumType<char>::value);
        Static_Assert(!MiniMPL::IsEnumType<char[4]>::value);
        Static_Assert(!MiniMPL::IsEnumType<char(&)[4]>::value);
        Static_Assert(!MiniMPL::IsEnumType<unsigned char>::value);
        Static_Assert(MiniMPL::IsEnumType<enum newEnumType>::value);
        Static_Assert(MiniMPL::IsEnumType<EnumType>::value);
        Static_Assert(!MiniMPL::IsEnumType<EnumType[2]>::value);
        Static_Assert(!MiniMPL::IsEnumType<EnumType(*)[2]>::value);
        Static_Assert(!MiniMPL::IsEnumType<EnumType(&)[2]>::value);

        //demo IsStringStl/IsStringC/IsCharArray/IsString
        Static_Assert(!MiniMPL::IsStringStl<unsigned char*>::value);
        Static_Assert(!MiniMPL::IsStringStl<char(&)[2]>::value);
        Static_Assert(MiniMPL::IsStringStl<stlStringW>::value);
        Static_Assert(MiniMPL::IsStringStl<stlStringA>::value);
        //----------------------------------------------------------
        Static_Assert(!MiniMPL::IsStringC<unsigned char*>::value);
        Static_Assert(!MiniMPL::IsStringC<stlStringW>::value);
        Static_Assert(!MiniMPL::IsStringC<stlStringA>::value);
        Static_Assert(!MiniMPL::IsStringC<char[3]>::value);
        Static_Assert(!MiniMPL::IsStringC<wchar_t[3]>::value);
        Static_Assert(!MiniMPL::IsStringC<char(&)[3]>::value);
        Static_Assert(!MiniMPL::IsStringC<wchar_t(&)[3]>::value);
        Static_Assert(MiniMPL::IsStringC<char*>::value);
        Static_Assert(MiniMPL::IsStringC<wchar_t*>::value);
        //----------------------------------------------------------
        Static_Assert(!MiniMPL::IsCharArray<EnumType[2]>::value);
        Static_Assert(!MiniMPL::IsCharArray<char*>::value);  
        Static_Assert(!MiniMPL::IsCharArray<stlStringW>::value);
        Static_Assert(MiniMPL::IsCharArray<char[2]>::value);
        Static_Assert(MiniMPL::IsCharArray<char(&)[2]>::value);
        Static_Assert(MiniMPL::IsCharArray<wchar_t[2]>::value);
        Static_Assert(MiniMPL::IsCharArray<wchar_t(&)[2]>::value);
        //----------------------------------------------------------
        Static_Assert((MiniMPL::IsArray<int[3]>::value));
        Static_Assert((MiniMPL::IsArray<int(&)[3]>::value));
        Static_Assert(!(MiniMPL::IsArray<int(*)[3]>::value));
        Static_Assert(!(sizeof(int(*)[3])==sizeof(int[3])));
        Static_Assert((MiniMPL::IsArray<const int[3]>::value));
        Static_Assert((MiniMPL::IsArray<volatile int[3]>::value));
        Static_Assert((MiniMPL::IsArray<int*[3]>::value));
        //----------------------------------------------------------
        Static_Assert(!MiniMPL::IsString<unsigned char*>::value);
        Static_Assert(!MiniMPL::IsString<EnumType(&)[2]>::value);
        Static_Assert(MiniMPL::IsString<char[2]>::value);
        Static_Assert(MiniMPL::IsString<char(&)[2]>::value);
        Static_Assert(MiniMPL::IsString<wchar_t[2]>::value);
        Static_Assert(MiniMPL::IsString<wchar_t(&)[2]>::value);
        Static_Assert(MiniMPL::IsString<char*>::value);        
        Static_Assert(MiniMPL::IsString<wchar_t*>::value);
        Static_Assert(MiniMPL::IsString<const char*>::value);
        Static_Assert(MiniMPL::IsString<const wchar_t*>::value);
        Static_Assert(MiniMPL::IsString<stlStringW>::value);
        Static_Assert(MiniMPL::IsString<stlStringA>::value);
        Static_Assert(MiniMPL::IsString<const stlStringW>::value);
        Static_Assert(MiniMPL::IsString<const stlStringA>::value);
        Static_Assert(!MiniMPL::IsString<stlStringW[2]>::value);

        //test IsFunctionPointer and IsMemberFunctionPointer
        Static_Assert(!(MiniMPL::IsFunctionPointer<int (S4::*)(char,bool)>::value));
        Static_Assert((MiniMPL::IsMemberFunctionPointer<int (S4::*)(char,bool)>::value));

        Static_Assert((MiniMPL::IsFunctionPointer<int (*)(char,bool)>::value));
        Static_Assert(!(MiniMPL::IsMemberFunctionPointer<int (*)(char,bool)>::value));

        Static_Assert((MiniMPL::IsMemberFunctionPointer<int (S4::*)(char,bool) const>::value));
        Static_Assert((MiniMPL::IsMemberFunctionPointer<int (S4::*)(char,bool) const>::value));

        Static_Assert(!(MiniMPL::IsFunctionPointer<int& (S4::*)(char,bool)>::value));
        Static_Assert((MiniMPL::IsMemberFunctionPointer<int* (S4::*)(char,bool)>::value));

        Static_Assert((MiniMPL::IsFunctionPointer<int (*)(char const,bool)>::value));
        Static_Assert(!(MiniMPL::IsMemberFunctionPointer<int (*)(char,bool&)>::value));

        Static_Assert((MiniMPL::IsMemberFunctionPointer<int* (S4::*)(char const&,bool) const>::value));
        Static_Assert((MiniMPL::IsMemberFunctionPointer<int& (S4::*)(char&,bool) const>::value));
    }

#ifdef RUN_EXAMPLE_ISXXXEX
    InitRunFunc(TestCase_isXXXEx);
#else //else of RUN_EXAMPLE_ISXXXEX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_ISXXXEX)=(outputTxtV(TXT("[Unit test run disabled] isXXXEx.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"isXXXEx.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_ISXXXEX
}

#else //else of COMPILE_EXAMPLE_ISXXXEX
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_ISXXXEX)=(outputTxtV(TXT("[Unit test compile disabled] isXXXEx.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"isXXXEx.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_ISXXXEX

#endif // __TEST_ISXXXEX_HPP__
