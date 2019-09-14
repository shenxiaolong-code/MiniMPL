#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\traverseTypeList.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_TRAVERSETYPELIST to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_TRAVERSETYPELIST

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_TRAVERSETYPELIST
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_TRAVERSETYPELIST
#endif

#if defined(RUN_EXAMPLE_TRAVERSETYPELIST) && !defined(COMPILE_EXAMPLE_TRAVERSETYPELIST)
    #define COMPILE_EXAMPLE_TRAVERSETYPELIST
#endif

//#undef RUN_EXAMPLE_TRAVERSETYPELIST
//#undef COMPILE_EXAMPLE_TRAVERSETYPELIST

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_TRAVERSETYPELIST
#include <MiniMPL/traverseTypeContainer.hpp>
#include <MiniMPL/typeListMacro.hpp>
#include <ut_material/td_def_callbackTemplate.h>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeList.h>

namespace UnitTest
{
    inline void TestCase_traverseTypeList_dump()
    {
        PrintTitle1(TXT("TestCase_traverseTypeList_dump"));

        using namespace MiniMPL; 
        outputTxtV(TXT("TList6 %s\n"), CTraverseTypeContainer<TList6,true>::dump().c_str() );
        outputTxtV(TXT("TypeList4 %s\n"), CTraverseTypeContainer<TypeList4,false>::dump().c_str() );
        outputTxtV(TXT("Typelist5 %s\n"), CTraverseTypeContainer<Typelist5,true>::dump().c_str() );
        outputTxtV(TXT("Typelist71 %s\n"), CTraverseTypeContainer<Typelist71,false>::dump().c_str() );

        outputTxtV(TXT("Typelist72 %s\n"), CTraverseTypeContainer<Typelist72,true>::dump().c_str() );
        outputTxtV(TXT("Typelist73 %s\n"), CTraverseTypeContainer<Typelist73,false>::dump().c_str() );

        outputTxtV(TXT("Typelist74 %s\n"), CTraverseTypeContainer<Typelist74,true>::dump().c_str() );
        outputTxtV(TXT("Typelist75 %s\n"), CTraverseTypeContainer<Typelist75,false>::dump().c_str() );

        outputTxtV(TXT("\nTypelist74 before erase EnumType\n"));
        outputTxtV(CTraverseTypeContainer<Typelist74,true>::dump().c_str() );
        outputTxtV(TXT("Typelist74 after erase EnumType\n"));
        typedef TL::Erase<Typelist74,EnumType>::type        EraseEnumType_T;;
        outputTxt(CTraverseTypeContainer<EraseEnumType_T>::dump().c_str());

        outputTxt(TXT("\nTypelist74 before erase ETypeInt\n"));
        outputTxt(CTraverseTypeContainer<Typelist74,true>::dump().c_str() );
        outputTxt(TXT("Typelist74 after erase ETypeInt\n"));
        typedef TL::Erase<Typelist74,ETypeInt >::type       EraseList_T;
        outputTxt(CTraverseTypeContainer<EraseList_T>::dump().c_str());

        outputTxt(TXT("\nTypelist75 before erase char*\n"));
        outputTxt(CTraverseTypeContainer<Typelist75,true>::dump().c_str() );
        outputTxt(TXT("Typelist75 after erase char*\n"));
        typedef TL::Erase<Typelist75,char*>::type           EraseCharP_T;  
        outputTxtV(TXT("EInt_3_5:%s\n"),CTraverseTypeContainer<EraseCharP_T>::dump().c_str());
    }

    inline void TestCase_traverseTypeList_global()
    {
        PrintTitle1(TXT("TestCase_traverseTypeList_global"));
        
        using namespace MiniMPL;

        outputTxtV(TXT("dump TypeList4:%s\n"),CTraverseTypeContainer<TypeList4,true>::dump().c_str());
        outputTxtV(TXT("dump TypeList4:%s\n"),CTraverseTypeContainer<TypeList4,false>::dump().c_str());

        int sum=0;
        CTraverseTypeContainer<Typelist5>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(S4).name(),MiniMPL::makeParamPackage_Ref(sum));
        CTraverseTypeContainer<Typelist5>::applyTester<TesterT(isMe2p)>::execute<CallBackT(userFuc)>(ParamPackageCall<int,char>(5,100),MiniMPL::makeParamPackage_Ref(sum));
        //test type outside of TL
        outputTxtV(TXT("dump Typelist71:%s\n"),CTraverseTypeContainer<Typelist71,true>::dump().c_str());
        outputTxtV(TXT("dump Typelist72:%s\n"),CTraverseTypeContainer<Typelist72,true>::dump().c_str());
        outputTxtV(TXT("dump Typelist73:%s\n"),CTraverseTypeContainer<Typelist73,true>::dump().c_str());
        CTraverseTypeContainer<Typelist71>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(S4).name(),MiniMPL::makeParamPackage_Ref(sum));
        CTraverseTypeContainer<Typelist72>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(S4).name(),MiniMPL::makeParamPackage_Ref(sum));
        CTraverseTypeContainer<Typelist73>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(S4).name(),MiniMPL::makeParamPackage_Ref(sum));

        CTraverseTypeContainer<Typelist71>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(int).name(),MiniMPL::makeParamPackage_Ref(sum));
        CTraverseTypeContainer<Typelist72>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(int).name(),MiniMPL::makeParamPackage_Ref(sum));
        CTraverseTypeContainer<Typelist73>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(int).name(),MiniMPL::makeParamPackage_Ref(sum));

        CTraverseTypeContainer<Typelist71>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(S2).name(),MiniMPL::makeParamPackage_Ref(sum));
        CTraverseTypeContainer<Typelist72>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(S2).name(),MiniMPL::makeParamPackage_Ref(sum));
        CTraverseTypeContainer<Typelist73>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(S2).name(),MiniMPL::makeParamPackage_Ref(sum));

        CTraverseTypeContainer<Typelist71>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(float).name(),MiniMPL::makeParamPackage_Ref(sum));
        CTraverseTypeContainer<Typelist72>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(float).name(),MiniMPL::makeParamPackage_Ref(sum));
        CTraverseTypeContainer<Typelist73>::applyTester<TesterT(TestME)>::execute<CallBackT(userFuc)>(typeid(float).name(),MiniMPL::makeParamPackage_Ref(sum));

        CTraverseTypeContainer<Typelist5>::applyTester<TesterT(isSumGreater5)>::execute<CallBackT(userFuc) >(ParamPackageCall<int,char>(6,17),MiniMPL::makeParamPackage_Ref(sum));

        typedef bool (*pFunc_T)(int&);
        stlMap<stlStringA,pFunc_T> funcAddrs;
        CTraverseTypeContainer<Typelist5>::applyFuncIdGenerator<FuncID_getMyId>::getAllFuncAddr<CallBackT(userFuc)>(funcAddrs);
        ASSERT_AND_LOG(funcAddrs.size()==MiniMPL::TL::Length<Typelist5>::value);
        funcAddrs[stlStringA(typeid(int).name())](sum);
    }

    inline void TestCase_traverseTypeList()
    {
        PrintTestcase();
        TestCase_traverseTypeList_dump();
        TestCase_traverseTypeList_global();
    }


#ifdef RUN_EXAMPLE_TRAVERSETYPELIST
    InitRunFunc(TestCase_traverseTypeList);
#else //else of RUN_EXAMPLE_TRAVERSETYPELIST

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_TRAVERSETYPELIST)=(outputTxtV(TXT("[Unit test run disabled] traverseTypeList.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"traverseTypeList.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_TRAVERSETYPELIST
}

#else //else of COMPILE_EXAMPLE_TRAVERSETYPELIST
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_TRAVERSETYPELIST)=(outputTxtV(TXT("[Unit test compile disabled] traverseTypeList.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"traverseTypeList.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_TRAVERSETYPELIST

