#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macroDef.h>
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\callbacker.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_CALLBACKER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_CALLBACKER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_CALLBACKER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_CALLBACKER
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_CALLBACKER
#endif

//#undef RUN_EXAMPLE_CALLBACKER
//#undef COMPILE_EXAMPLE_CALLBACKER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_CALLBACKER
#include <MiniMPL/callbacker.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>
#include <UT_material/tc_def_globalFunc.h>
#include <UT_material/tc_def_NoCopy.h>

namespace UnitTest
{

    template<typename T>
    void  diff_callFuncObj(T& vObj)
    {
        using namespace MiniMPL;
        TpCallbacker pWorker;

        //test object function : operator
        typedef bool (NoCopyObj::*TObjOperator0P)();
        TObjOperator0P pMF0P=&NoCopyObj::operator ();
        pWorker = TpCallbacker(makeCallbackerDirect(pMF0P,makeParamPackage_Ref(vObj)));
        pWorker->execute();

        //smart pointer
        stlSmartptr<NoCopyObj> pTmp(new NoCopyObj());
        pWorker = TpCallbacker(makeCallbackerDirect(pMF0P,makeParamPackage_Ref(vObj)));
        pWorker->execute();
        //C pointer
        NoCopyObj* pObj = new NoCopyObj();
        pWorker = TpCallbacker(makeCallbackerDirect(pMF0P,makeParamPackage_Ref(vObj)));
        pWorker->execute();
        delete pObj;
        //mixed pointer
        stlSmartptr<NoCopyObj>* ppTmp=new stlSmartptr<NoCopyObj>(new NoCopyObj());
        pWorker = TpCallbacker(makeCallbackerDirect(pMF0P,makeParamPackage_Ref(vObj)));
        pWorker->execute();
        delete ppTmp;

        int a=5;
        S4 obj;
        typedef bool (NoCopyObj::*TObjOperator2P)(S4&,int&);
        TObjOperator2P pMF2P=&NoCopyObj::operator ();
        pWorker = TpCallbacker(makeCallbackerDirect(pMF2P,makeParamPackage_Ref(vObj,obj,a)));
        pWorker->execute();
    }

    inline void TestCase_callbacker()
    {
        PrintTestcase();
        using namespace MiniMPL;

        S4 obj;
        int     a=5;
        char    c = 10;
        char*   pC=&c;

        //test global function without any parameter
        TpCallbacker pWorker(makeCallbacker(CallBackRoutineF));
        pWorker->execute();

        //test global function with parameter(s)
        pWorker = TpCallbacker(makeCallbacker(CallBackRoutineF1,obj));
        pWorker->execute();

        //test member function without parameter
        pWorker = TpCallbacker(makeCallbacker(CallBackRoutineF2,obj,a));
        pWorker->execute();

        pWorker = TpCallbacker(makeCallbacker(CallBackRoutineF3,obj,a,pC));
        pWorker->execute();

        //test member function with parameter(s)
        pWorker = TpCallbacker(makeCallbacker(&S4::print1Param,obj,a));
        pWorker->execute();

        pWorker = TpCallbacker(makeCallbacker(&S4::print2Params,obj,a,pC));
        pWorker->execute();

        //test member function with parameter
        //test raw object
        NoCopyObj funcObj;
        //NoCopyObj tmp(funcObj);   //error, OK:confirm no copy constructor!
        //tmp=funcObj;              //error, OK:confirm no assign operator!

        //smart pointer
        stlSmartptr<NoCopyObj> tpObj(new NoCopyObj());
        diff_callFuncObj(tpObj);

        //C pointer
        NoCopyObj* pObj = new NoCopyObj();
        diff_callFuncObj(pObj);
        delete pObj;

        //mixed pointer
        stlSmartptr<NoCopyObj>* ppTmp=new stlSmartptr<NoCopyObj>(new NoCopyObj());
        diff_callFuncObj(ppTmp);
        delete ppTmp;

        //cout<<endl;
    }

#ifdef RUN_EXAMPLE_CALLBACKER
    InitRunFunc(TestCase_callbacker);
#else //else of RUN_EXAMPLE_CALLBACKER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] callbacker.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"callbacker.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_CALLBACKER
}

#else //else of COMPILE_EXAMPLE_CALLBACKER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] callbacker.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"callbacker.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_CALLBACKER

