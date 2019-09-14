#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\convert_enale_if.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_CONVERT_ENABLE_IF to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_CONVERT_ENABLE_IF

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_CONVERT_ENABLE_IF
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_CONVERT_ENABLE_IF
#endif

#if defined(RUN_EXAMPLE_CONVERT_ENABLE_IF) && !defined(COMPILE_EXAMPLE_CONVERT_ENABLE_IF)
    #define COMPILE_EXAMPLE_CONVERT_ENABLE_IF
#endif

//#undef RUN_EXAMPLE_CONVERT_ENABLE_IF
//#undef COMPILE_EXAMPLE_CONVERT_ENABLE_IF

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_CONVERT_ENABLE_IF
#include <MiniMPL/convert_enable_if.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{

    inline void TestCase_convert_enale_if()
    {
        PrintTestcase();
        
        //test Pointer => Value
        typedef MiniMPL::ConvertEnableIf<S4*,S4>    TPointer2Value;
        Static_Assert(!(TPointer2Value::Value2CPointer::value));
        Static_Assert((TPointer2Value::Pointer2Value::value));
        Static_Assert(!(TPointer2Value::DiffPointer2CPointer::value));
        Static_Assert(!(TPointer2Value::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlSmartptr<S4*>,S4>    TSmartPointer2Value;
        Static_Assert(!(TSmartPointer2Value::Value2CPointer::value));
        Static_Assert((TSmartPointer2Value::Pointer2Value::value));
        Static_Assert(!(TSmartPointer2Value::DiffPointer2CPointer::value));
        Static_Assert(!(TSmartPointer2Value::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlVector<S4*>::iterator,S4>    TIteratorP2Value;
        Static_Assert(!(TIteratorP2Value::Value2CPointer::value));
        Static_Assert((TIteratorP2Value::Pointer2Value::value));
        Static_Assert(!(TIteratorP2Value::DiffPointer2CPointer::value));
        Static_Assert(!(TIteratorP2Value::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlVector<S4>::iterator,S4>    TIterator2Value;
        Static_Assert(!(TIterator2Value::Value2CPointer::value));
        Static_Assert((TIterator2Value::Pointer2Value::value));
        Static_Assert(!(TIterator2Value::DiffPointer2CPointer::value));
        Static_Assert(!(TIterator2Value::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlSmartptr<stlVector<S4>::iterator>,S4>    TSmartPtrIterator2Value;
        Static_Assert(!(TSmartPtrIterator2Value::Value2CPointer::value));
        Static_Assert((TSmartPtrIterator2Value::Pointer2Value::value));
        Static_Assert(!(TSmartPtrIterator2Value::DiffPointer2CPointer::value));
        Static_Assert(!(TSmartPtrIterator2Value::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlVector<stlSmartptr<S4> >::iterator,S4>    TIteratorSmartPtr2Value;
        Static_Assert(!(TIteratorSmartPtr2Value::Value2CPointer::value));
        Static_Assert((TIteratorSmartPtr2Value::Pointer2Value::value));
        Static_Assert(!(TIteratorSmartPtr2Value::DiffPointer2CPointer::value));
        Static_Assert(!(TIteratorSmartPtr2Value::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlVector<S4>::iterator*,S4>    TIteratorCPtr2Value;
        Static_Assert(!(TIteratorCPtr2Value::Value2CPointer::value));
        Static_Assert((TIteratorCPtr2Value::Pointer2Value::value));
        Static_Assert(!(TIteratorCPtr2Value::DiffPointer2CPointer::value));
        Static_Assert(!(TIteratorCPtr2Value::ImplicitConstructDiffObj::value));

        //test value => C Pointer
        typedef MiniMPL::ConvertEnableIf<S4,S4*>    TValue2Pointer;
        Static_Assert((TValue2Pointer::Value2CPointer::value));
        Static_Assert(!(TValue2Pointer::Pointer2Value::value));
        Static_Assert(!(TValue2Pointer::DiffPointer2CPointer::value));
        Static_Assert(!(TValue2Pointer::ImplicitConstructDiffObj::value));

        //test different pointer = > C Pointer
        typedef MiniMPL::ConvertEnableIf<stlSmartptr<S4*>,S4*>    TSmartPointer2CPtr;
        Static_Assert(!(TSmartPointer2CPtr::Value2CPointer::value));
        Static_Assert(!(TSmartPointer2CPtr::Pointer2Value::value));
        Static_Assert((TSmartPointer2CPtr::DiffPointer2CPointer::value));
        Static_Assert(!(TSmartPointer2CPtr::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlVector<S4*>::iterator,S4*>    TIteratorP2CPtr;
        Static_Assert(!(TIteratorP2CPtr::Value2CPointer::value));
        Static_Assert(!(TIteratorP2CPtr::Pointer2Value::value));
        Static_Assert((TIteratorP2CPtr::DiffPointer2CPointer::value));
        Static_Assert(!(TIteratorP2CPtr::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlVector<S4>::iterator,S4*>    TIterator2CPtr;
        Static_Assert(!(TIterator2CPtr::Value2CPointer::value));
        Static_Assert(!(TIterator2CPtr::Pointer2Value::value));
        Static_Assert((TIterator2CPtr::DiffPointer2CPointer::value));
        Static_Assert(!(TIterator2CPtr::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlSmartptr<stlVector<S4>::iterator>,S4*>    TSmartPtrIterator2CPtr;
        Static_Assert(!(TSmartPtrIterator2CPtr::Value2CPointer::value));
        Static_Assert(!(TSmartPtrIterator2CPtr::Pointer2Value::value));
        Static_Assert((TSmartPtrIterator2CPtr::DiffPointer2CPointer::value));
        Static_Assert(!(TSmartPtrIterator2CPtr::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlVector<stlSmartptr<S4> >::iterator,S4*>    TIteratorSmartPtr2CPtr;
        Static_Assert(!(TIteratorSmartPtr2CPtr::Value2CPointer::value));
        Static_Assert(!(TIteratorSmartPtr2CPtr::Pointer2Value::value));
        Static_Assert((TIteratorSmartPtr2CPtr::DiffPointer2CPointer::value));
        Static_Assert(!(TIteratorSmartPtr2CPtr::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlVector<S4>::iterator*,S4*>    TIteratorCPtr2CPtr;
        Static_Assert(!(TIteratorCPtr2CPtr::Value2CPointer::value));
        Static_Assert(!(TIteratorCPtr2CPtr::Pointer2Value::value));
        Static_Assert((TIteratorCPtr2CPtr::DiffPointer2CPointer::value));
        Static_Assert(!(TIteratorCPtr2CPtr::ImplicitConstructDiffObj::value));

        //test implicit construct different object
        typedef MiniMPL::ConvertEnableIf<char*,stlStringA>    TImplicitConstructChar2Stl;
        Static_Assert(!(TImplicitConstructChar2Stl::Value2CPointer::value));
        Static_Assert(!(TImplicitConstructChar2Stl::Pointer2Value::value));
        Static_Assert(!(TImplicitConstructChar2Stl::DiffPointer2CPointer::value));
        Static_Assert((TImplicitConstructChar2Stl::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<char[8],stlStringA>    TImplicitConstructCharArr2Stl;
        Static_Assert(!(TImplicitConstructCharArr2Stl::Value2CPointer::value));
        Static_Assert(!(TImplicitConstructCharArr2Stl::Pointer2Value::value));
        Static_Assert(!(TImplicitConstructCharArr2Stl::DiffPointer2CPointer::value));
        Static_Assert((TImplicitConstructCharArr2Stl::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlChar*,stlString>    TImplicitConstructStlChar2Stl;
        Static_Assert(!(TImplicitConstructStlChar2Stl::Value2CPointer::value));
        Static_Assert(!(TImplicitConstructStlChar2Stl::Pointer2Value::value));
        Static_Assert(!(TImplicitConstructStlChar2Stl::DiffPointer2CPointer::value));
        Static_Assert((TImplicitConstructStlChar2Stl::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<stlChar[8],stlString>    TImplicitConstructStlCharArr2Stl;
        Static_Assert(!(TImplicitConstructStlCharArr2Stl::Value2CPointer::value));
        Static_Assert(!(TImplicitConstructStlCharArr2Stl::Pointer2Value::value));
        Static_Assert(!(TImplicitConstructStlCharArr2Stl::DiffPointer2CPointer::value));
        Static_Assert((TImplicitConstructStlCharArr2Stl::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<int,double>    TImplicitConstructInt2Double;
        Static_Assert(!(TImplicitConstructInt2Double::Value2CPointer::value));
        Static_Assert(!(TImplicitConstructInt2Double::Pointer2Value::value));
        Static_Assert(!(TImplicitConstructInt2Double::DiffPointer2CPointer::value));
        Static_Assert((TImplicitConstructInt2Double::ImplicitConstructDiffObj::value));

        typedef MiniMPL::ConvertEnableIf<S4,CParameters1>    TImplicitConstructS42CParameters1;
        Static_Assert(!(TImplicitConstructS42CParameters1::Value2CPointer::value));
        Static_Assert(!(TImplicitConstructS42CParameters1::Pointer2Value::value));
        Static_Assert(!(TImplicitConstructS42CParameters1::DiffPointer2CPointer::value));
        Static_Assert((TImplicitConstructS42CParameters1::ImplicitConstructDiffObj::value));
    }

#ifdef RUN_EXAMPLE_CONVERT_ENABLE_IF
    InitRunFunc(TestCase_convert_enale_if);
#else //else of RUN_EXAMPLE_CONVERT_ENABLE_IF

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_CONVERT_ENABLE_IF)=(outputTxtV(TXT("[Unit test run disabled] convert_enale_if.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"convert_enale_if.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_CONVERT_ENABLE_IF
}

#else //else of COMPILE_EXAMPLE_CONVERT_ENABLE_IF
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_CONVERT_ENABLE_IF)=(outputTxtV(TXT("[Unit test compile disabled] convert_enale_if.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"convert_enale_if.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_CONVERT_ENABLE_IF

