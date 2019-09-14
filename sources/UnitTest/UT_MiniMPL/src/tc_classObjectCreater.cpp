#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\classObjectCreater.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_CLASSOBJECTCREATER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_CLASSOBJECTCREATER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_CLASSOBJECTCREATER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_CLASSOBJECTCREATER
#endif

#if defined(RUN_EXAMPLE_CLASSOBJECTCREATER) && !defined(COMPILE_EXAMPLE_CLASSOBJECTCREATER)
    #define COMPILE_EXAMPLE_CLASSOBJECTCREATER
#endif

//#undef RUN_EXAMPLE_CLASSOBJECTCREATER
//#undef COMPILE_EXAMPLE_CLASSOBJECTCREATER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_CLASSOBJECTCREATER
#include <MiniMPL/classObjectCreater.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_classregister.h>
#include <MiniMPL/classRegisterMacro.hpp>

#define Link_ClassRegister_Symbol_UnitTest(X)   Link_ClassRegister_Symbol_N1(UnitTest,X)
Link_ClassRegister_Symbol_UnitTest(CDri_Type1);
Link_ClassRegister_Symbol_UnitTest(CDri_Type2);
Link_ClassRegister_Symbol_UnitTest(CDri_Value1);
Link_ClassRegister_Symbol_UnitTest(CDri_Value2);
Link_ClassRegister_Symbol_UnitTest(CDri_Value3);

namespace UnitTest
{
    inline void TestCase_classObjectCreater()
    {
        PrintTestcase();
        using namespace MiniMPL;

        CGenBase*   pNew1 = createObjectByName<CGenBase>(L"CDri_Value2");    //create CDri_Value2
        //         Assertb(typeid(CDri_Value2)==pNew1->getTypeInfo());
        Assertb(pNew1);
        
        CGenBase*   pNew2 = createObject<CGenBase>(int(1));
        Assertb(pNew2);
        //Assertb(typeid(CDri_Value1)==pNew2->getTypeInfo());

        //create CDri_Value1
        CGenBase*   pNew3 = createObject<CGenBase>(2);  //Create NULL , No type whose trait type is int and value is 2
        Assertb(NULL == pNew3);

        CGenBase*   pNew4 = createObject<CGenBase>(2,&IsThisDevice);					//create CDri_Value2
        //Assertb(typeid(CDri_Value2)==pNew4->getTypeInfo());
        Assertb(pNew4);
        
        CGenBase*   pNew5 = createObject<CGenBase>(3,&Device::m_id);				//create CDri_Value3
        //Assertb(typeid(CDri_Value3)==pNew5->getTypeInfo());
        Assertb(pNew5);
        
        MiniMPL::ClassRegister*  pCls = getClassRegisterByName<CGenBase>(L"CDri_Value1");
        Assertb((NULL == pCls->getTypedRegister<CDemoCast>()));
        Assertb((NULL != pCls->getObjectCreater<CGenBase>()));
        
        CGenBase*   pClsObj = pCls->tryCreateObject<CGenBase>();
        AssertP(pClsObj);

        ClassRegisterEx<CGenBase>* pExRegister = pCls->getTypedRegister<CGenBase>();                
        CGenBase*   pNew6 = pExRegister->createObject();															//create CDri_Value1
        //Assertb(typeid(CDri_Value1)==pNew6->getTypeInfo());
        Assertb(pNew6);
        
        CGenBase*   pNew7 = createObjectByTraitType<CGenBase,DemoTraintType>();    //Create CDri_Type2
        //Assertb(typeid(CDri_Type2)==pNew7->getTypeInfo());
        Assertb(pNew7);

        CDemoCast*  pNew8 = createObjectByTraitType<CDemoCast,DemoTraintType>();   //Create CDri_Type1
        //Assertb(typeid(CDri_Type1)==pNew8->getTypeInfo());
        Assertb(pNew8);
        
        //display how many classes use Device as its trait type
        unsigned int iSize = getClassRegisterNumberByTraitType<CGenBase,Device>();
        outputTxtV(TXT("\nThere are %d type whose trait type is Device.\n"),iSize);
        
        for(unsigned int i=0;i<iSize;i++)
        {
            MiniMPL::ClassRegisterEx<CGenBase>* pCur = getClassRegisterByTraitType<CGenBase,Device>(i);
            outputTxtV(TXT("No. %d class register with Device trait : \nName:%s\tDevice trait value : %s\n"),i,pCur->getName().c_str(),pCur->getTraitValue<Device>()->dumpStr().c_str());
        }
        
        //display how many classes use int as its trait type
        iSize = getClassRegisterNumberByTraitType<CGenBase,int>();
        outputTxtV(TXT("\nThere are %d type whose trait type is int.\n"),iSize);
        
        for(unsigned int i=0;i<iSize;i++)
        {
            MiniMPL::ClassRegisterEx<CGenBase>* pCur = getClassRegisterByTraitType<CGenBase,int>(i);
            outputTxtV(TXTA("No. %d class register with int trait : \nName:%s\tint trait value : %d\n"),i,pCur->getName().c_str(),*pCur->getTraitValue<int>());
        }
        outputTxt(TXT("\ndump ClassRegisterBase:\n"));
        MiniMPL::dump<void>();
        
        outputTxt(TXT("dump ClassRegisterEx<CGenBase>:\n"));
        MiniMPL::dump<CGenBase>();

        outputTxt(TXT("dump ClassRegisterEx<CDemoCast>:\n"));
        MiniMPL::dump<CDemoCast>();

        delete pNew1;
        delete pNew2;
        delete pNew3;
        delete pNew4;
        delete pNew5;
        delete pNew6;
        delete pNew7;
        delete pNew8;
        delete pClsObj;

    }
    
#ifdef RUN_EXAMPLE_CLASSOBJECTCREATER
    InitRunFunc(TestCase_classObjectCreater);
#else //else of RUN_EXAMPLE_CLASSOBJECTCREATER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_CLASSOBJECTCREATER)=(outputTxtV(TXT("[Unit test run disabled] classObjectCreater.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"classObjectCreater.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_CLASSOBJECTCREATER
}

#else //else of COMPILE_EXAMPLE_CLASSOBJECTCREATER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_CLASSOBJECTCREATER)=(outputTxtV(TXT("[Unit test compile disabled] classObjectCreater.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"classObjectCreater.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_CLASSOBJECTCREATER

