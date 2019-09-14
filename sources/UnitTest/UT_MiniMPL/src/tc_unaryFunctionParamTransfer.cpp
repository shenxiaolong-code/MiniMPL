#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\unaryFunctionParamTransfer.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER
#endif

#if defined(RUN_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER) && !defined(COMPILE_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER)
    #define COMPILE_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER
#endif

//#undef RUN_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER
//#undef COMPILE_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER

#undef ENABLE_TRACE
#define ENABLE_TRACE    1
#include <MiniMPL/unaryFunctionParamTransfer.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <ut_material/tc_def_unaryFunctionParamTransfer.h>

namespace UnitTest
{
    inline void TestCase_unaryFunctionParamTransfer()
    {
        PrintTestcase();
        using namespace MiniMPL;
        UFParamConverter obj;
        
        //test ImplicitConstructDiffObj
        ASSERT_AND_LOG(2==obj.autoConvert(2));

        //test Pointer2Value
        stlSmartptr<structFromInt> pTP2V11(new structFromInt(11));
        ASSERT_AND_LOG(11==obj.autoConvert(*pTP2V11));      //T                 ==> T
        ASSERT_AND_LOG(11==obj.autoConvert(&*pTP2V11));     //T*                ==> T
        ASSERT_AND_LOG(11==obj.autoConvert(pTP2V11));       //stlSmartptr<T>    ==> T
        ASSERT_AND_LOG(11==obj.autoConvert(&pTP2V11));      //stlSmartptr<T>*   ==> T
        stlSmartptr<stlSmartptr<structFromInt> > pTP2V12(new stlSmartptr<structFromInt>(new structFromInt(12)));
        ASSERT_AND_LOG(12==obj.autoConvert(pTP2V12));       //stlSmartptr<stlSmartptr<T> >==> T
        std::vector<structFromInt>  vP2V13;
        vP2V13.push_back(structFromInt(13));
        ASSERT_AND_LOG(13==obj.autoConvert(vP2V13.begin()));  //vector<T>::iterator ==> T
        std::vector<stlSmartptr<structFromInt> >  vP2V14;
        vP2V14.push_back(stlSmartptr<structFromInt>(new structFromInt(14)));
        ASSERT_AND_LOG(14==obj.autoConvert(vP2V14.begin()));  //vector<stlSmartptr<T> >::iterator ==> T

        //test Value2CPointer        
        stlSmartptr<structFromInt> pV2P11(new structFromInt(21));
        ASSERT_AND_LOG(21==obj.autoConvertP(pV2P11));    //stlSmartptr<T>    =>  T*
        ASSERT_AND_LOG(21==obj.autoConvertP(*pV2P11));   //T                 =>  T*
        ASSERT_AND_LOG(21==obj.autoConvertP(&pV2P11));   //stlSmartptr<T>*   =>  T*
        ASSERT_AND_LOG(21==obj.autoConvertP(&*pV2P11));  //T*                =>  T*
        stlSmartptr<stlSmartptr<structFromInt> > pV2P12(new stlSmartptr<structFromInt>(new structFromInt(22)));
        ASSERT_AND_LOG(22==obj.autoConvertP(pV2P12));     //stlSmartptr<stlSmartptr<T> >==> T*

        std::vector<structFromInt>  pV2P13;
        pV2P13.push_back(structFromInt(23));
        ASSERT_AND_LOG(23==obj.autoConvertP(pV2P13.begin()));  //vector<T>::iterator ==> T*
        std::vector<stlSmartptr<structFromInt> >  pV2P14;
        pV2P14.push_back(stlSmartptr<structFromInt>(new structFromInt(24)));
        ASSERT_AND_LOG(24==obj.autoConvertP(pV2P14.begin()));  //vector<stlSmartptr<T> >::iterator ==> T*
    }

#ifdef RUN_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER
    InitRunFunc(TestCase_unaryFunctionParamTransfer);
#else //else of RUN_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_UNARYFUNCTIONPARAMTRANSFER)=(outputTxtV(TXT("[Unit test run disabled] unaryFunctionParamTransfer.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"unaryFunctionParamTransfer.h\".")
    #endif
#endif  	// RUN_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER
}

#else //else of COMPILE_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_UNARYFUNCTIONPARAMTRANSFER)=(outputTxtV(TXT("[Unit test compile disabled] unaryFunctionParamTransfer.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"unaryFunctionParamTransfer.h\".")
    #endif
#endif // COMPILE_EXAMPLE_UNARYFUNCTIONPARAMTRANSFER

