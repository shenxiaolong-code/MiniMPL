#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\unaryFunctionCreater.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_UNARYFUNCTIONCREATER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_UNARYFUNCTIONCREATER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_UNARYFUNCTIONCREATER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_UNARYFUNCTIONCREATER
#endif

#if defined(RUN_EXAMPLE_UNARYFUNCTIONCREATER) && !defined(COMPILE_EXAMPLE_UNARYFUNCTIONCREATER)
    #define COMPILE_EXAMPLE_UNARYFUNCTIONCREATER
#endif

//#undef RUN_EXAMPLE_UNARYFUNCTIONCREATER
//#undef COMPILE_EXAMPLE_UNARYFUNCTIONCREATER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_UNARYFUNCTIONCREATER

#include <MiniMPL/unaryFunctionCreater.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <MiniMPL/valueCompare.hpp>
#include <UT_material/tc_def_globalFunc.h>
#include <MiniMPL/productSpecialDef.h>
#include <UT_material/tc_def_typeStruct.h>
#include <MiniMPL/smartPointer.hpp>

namespace UnitTest
{
    void testUnaryFunction()
    {
        PrintTitle1(MAKESTR(testUnaryFunction));

        using namespace MiniMPL;

        //test implicit constructor/conversion between different type
        char charStr[] = "hello";
        stlStringA  stlStrOK = "hello";
        stlStringA  stlStrFail = "hellp";
        bool bOK = makeUnaryFunction(&MiniMPL::equal<stlStringA,stlStringA>,stlStrOK,_$)(charStr);
        AssertB(bOK);

        bool bFail = makeUnaryFunction(&MiniMPL::equal<stlStringA,stlStringA>,stlStrFail,_$)(charStr);
        AssertB(!bFail);

        float fVal = 9.56f;
        std::vector<int> vInts;
        vInts.push_back(10);
        std::vector<int>::iterator it = vInts.begin();
        bool bYes = makeUnaryFunction(testPointer2CPointer,_$,&fVal)(it);
        AssertB(bYes);
        bYes = makeUnaryFunction(testPointer2CPointer,_$,&fVal)(stlSmartptr<int>(new int(10)));
        AssertB(bYes);
        int a=10;
        bYes = makeUnaryFunction(testPointer2CPointer,_$,&fVal)(a);
        //bYes = makeUnaryFunction(testPointer2CPointer,_$,&fVal)(10);                      //Fails :  can't reference to hardcode value
        int rInt = 10;
        bYes = makeUnaryFunction(testPointer2CPointer,_$,&fVal)(&rInt);    //OK :  package hardcode value to reference
        AssertB(bYes);
    }

    void TestCase_memberFunction()
    {  
        PrintTitle1(MAKESTR(TestCase_memberFunction));

        using namespace MiniMPL;

        DemoFunction3 a;
        int         b   = 4;
        char        c   = 5;
        DemoFunction3 d;
        char*       e   = NULL;
        int         f   = 7;

        DemoFunction3    objs[5];        
        int             ints[5];
        char            chars[5];
        char*           pchars[5]={NULL};

        stlSmartptr<DemoFunction3>      pTObj(new DemoFunction3());
        DemoFunction3* pObj = new DemoFunction3();
        //stlSmartptr<DemoFunction3>      guardLifeCycle(pObj);

        typedef    void (DemoFunction3::*MemF_T0)();
        typedef    void (DemoFunction3::*MemF_T1)(int a);
        typedef    void (DemoFunction3::*MemF_T2)(int,char&);
        typedef    void (DemoFunction3::*MemF_T3)(int,char&,DemoFunction3);
        typedef    void (DemoFunction3::*MemF_T3P)(int,char&,DemoFunction3*);
        typedef    void (DemoFunction3::*MemF_T4)(int a,char& b,DemoFunction3 c,char* d);
        typedef    void (DemoFunction3::*MemF_T5)(int a,char& b,DemoFunction3 c,char* d,int e);

        UnaryFunction<MemF_T0,0> rever00=UnaryFunctionCreater<MemF_T0,0>::create(&DemoFunction3::memFuncP0,_$);
        UnaryFunction<MemF_T1,0> rever10=UnaryFunctionCreater<MemF_T1,0>::create(&DemoFunction3::memFuncP1,_$,b);
        UnaryFunction<MemF_T2,0> rever20=UnaryFunctionCreater<MemF_T2,0>::create(&DemoFunction3::memFuncP2,_$,b,c);
        UnaryFunction<MemF_T3,0> rever30=UnaryFunctionCreater<MemF_T3,0>::create(&DemoFunction3::memFuncP3,_$,b,c,d);
        UnaryFunction<MemF_T4,0> rever40=UnaryFunctionCreater<MemF_T4,0>::create(&DemoFunction3::memFuncP4,_$,b,c,d,e);
        UnaryFunction<MemF_T5,0> rever50=UnaryFunctionCreater<MemF_T5,0>::create(&DemoFunction3::memFuncP5,_$,b,c,d,e,b);

        UnaryFunction<MemF_T1,1> rever11=UnaryFunctionCreater<MemF_T1,1>::create(&DemoFunction3::memFuncP1,a,_$);
        UnaryFunction<MemF_T2,1> rever21=UnaryFunctionCreater<MemF_T2,1>::create(&DemoFunction3::memFuncP2,a,_$,c);
        UnaryFunction<MemF_T3,1> rever31=UnaryFunctionCreater<MemF_T3,1>::create(&DemoFunction3::memFuncP3,a,_$,c,d);
        UnaryFunction<MemF_T4,1> rever41=UnaryFunctionCreater<MemF_T4,1>::create(&DemoFunction3::memFuncP4,a,_$,c,d,e);
        UnaryFunction<MemF_T5,1> rever51=UnaryFunctionCreater<MemF_T5,1>::create(&DemoFunction3::memFuncP5,a,_$,c,d,e,b);

        UnaryFunction<MemF_T2,2> rever22=UnaryFunctionCreater<MemF_T2,2>::create(&DemoFunction3::memFuncP2,a,b,_$);
        UnaryFunction<MemF_T3,2> rever32=UnaryFunctionCreater<MemF_T3,2>::create(&DemoFunction3::memFuncP3,a,b,_$,d);
        UnaryFunction<MemF_T4,2> rever42=UnaryFunctionCreater<MemF_T4,2>::create(&DemoFunction3::memFuncP4,a,b,_$,d,e);
        UnaryFunction<MemF_T5,2> rever52=UnaryFunctionCreater<MemF_T5,2>::create(&DemoFunction3::memFuncP5,a,b,_$,d,e,b);

        UnaryFunction<MemF_T3,3> rever33=UnaryFunctionCreater<MemF_T3,3>::create(&DemoFunction3::memFuncP3,a,b,c,_$);
        UnaryFunction<MemF_T4,3> rever43=UnaryFunctionCreater<MemF_T4,3>::create(&DemoFunction3::memFuncP4,a,b,c,_$,e);
        UnaryFunction<MemF_T5,3> rever53=UnaryFunctionCreater<MemF_T5,3>::create(&DemoFunction3::memFuncP5,a,b,c,_$,e,b);

        UnaryFunction<MemF_T4,4> rever44=UnaryFunctionCreater<MemF_T4,4>::create(&DemoFunction3::memFuncP4,a,b,c,d,_$);
        UnaryFunction<MemF_T5,4> rever54=UnaryFunctionCreater<MemF_T5,4>::create(&DemoFunction3::memFuncP5,a,b,c,d,_$,f);

        UnaryFunction<MemF_T5,5> rever55=UnaryFunctionCreater<MemF_T5,5>::create(&DemoFunction3::memFuncP5,a,b,c,d,e,_$);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        UnaryFunction<MemF_T3P,3> reverP33=UnaryFunctionCreater<MemF_T3P,3>::create(&DemoFunction3::memFuncP3P,a,b,c,_$);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //*/
        UnaryFunction<MemF_T0,0> g_rever00=makeUnaryFunction(&DemoFunction3::memFuncP0,_$);
        UnaryFunction<MemF_T1,0> g_rever10=makeUnaryFunction(&DemoFunction3::memFuncP1,_$,b);
        UnaryFunction<MemF_T2,0> g_rever20=makeUnaryFunction(&DemoFunction3::memFuncP2,_$,b,c);
        UnaryFunction<MemF_T3,0> g_rever30=makeUnaryFunction(&DemoFunction3::memFuncP3,_$,b,c,d);
        UnaryFunction<MemF_T4,0> g_rever40=makeUnaryFunction(&DemoFunction3::memFuncP4,_$,b,c,d,e);
        UnaryFunction<MemF_T5,0> g_rever50=makeUnaryFunction(&DemoFunction3::memFuncP5,_$,b,c,d,e,b);

        UnaryFunction<MemF_T1,1> g_rever11=makeUnaryFunction(&DemoFunction3::memFuncP1,a,_$);
        UnaryFunction<MemF_T2,1> g_rever21=makeUnaryFunction(&DemoFunction3::memFuncP2,a,_$,c);
        UnaryFunction<MemF_T3,1> g_rever31=makeUnaryFunction(&DemoFunction3::memFuncP3,a,_$,c,d);
        UnaryFunction<MemF_T4,1> g_rever41=makeUnaryFunction(&DemoFunction3::memFuncP4,a,_$,c,d,e);
        UnaryFunction<MemF_T5,1> g_rever51=makeUnaryFunction(&DemoFunction3::memFuncP5,a,_$,c,d,e,b);

        UnaryFunction<MemF_T2,2> g_rever22=makeUnaryFunction(&DemoFunction3::memFuncP2,a,b,_$);
        UnaryFunction<MemF_T3,2> g_rever32=makeUnaryFunction(&DemoFunction3::memFuncP3,a,b,_$,d);
        UnaryFunction<MemF_T4,2> g_rever42=makeUnaryFunction(&DemoFunction3::memFuncP4,a,b,_$,d,e);
        UnaryFunction<MemF_T5,2> g_rever52=makeUnaryFunction(&DemoFunction3::memFuncP5,a,b,_$,d,e,b);

        UnaryFunction<MemF_T3,3> g_rever33=makeUnaryFunction(&DemoFunction3::memFuncP3,a,b,c,_$);
        UnaryFunction<MemF_T4,3> g_rever43=makeUnaryFunction(&DemoFunction3::memFuncP4,a,b,c,_$,e);
        UnaryFunction<MemF_T5,3> g_rever53=makeUnaryFunction(&DemoFunction3::memFuncP5,a,b,c,_$,e,b);

        UnaryFunction<MemF_T4,4> g_rever44=makeUnaryFunction(&DemoFunction3::memFuncP4,a,b,c,d,_$);
        UnaryFunction<MemF_T5,4> g_rever54=makeUnaryFunction(&DemoFunction3::memFuncP5,a,b,c,d,_$,f);

        UnaryFunction<MemF_T5,5> g_rever55=makeUnaryFunction(&DemoFunction3::memFuncP5,a,b,c,d,e,_$);

        for(int i=0;i<5;i++)
        {
            rever00(objs[i]); //test (host) same type
            rever10(objs[i]);
            rever20(objs[i]);
            rever30(objs[i]);
            rever40(objs[i]);
            rever50(objs[i]);

            rever00(pTObj);  //test (host) smart Pointer ==> Object
            rever10(pTObj);
            rever20(pTObj);
            rever30(pTObj);
            rever40(pTObj);
            rever50(pTObj);

            rever00(pObj);   //test (host) Pointer ==> Object
            rever10(pObj);
            rever20(pObj);
            rever30(pObj);
            rever40(pObj);
            rever50(pObj);

            reverP33(pTObj);  //test Pointer ==> Object
            reverP33(pTObj);
            reverP33(pTObj);

            reverP33(pObj);   //test Pointer ==> Object
            reverP33(pObj);
            reverP33(pObj);

            rever11(ints[i]);
            rever21(ints[i]);
            rever31(ints[i]);
            rever41(ints[i]);
            rever51(ints[i]);

            rever22(chars[i]);
            rever32(chars[i]);
            rever42(chars[i]);
            rever52(chars[i]);

            rever33(objs[i]);
            rever43(objs[i]);
            rever53(objs[i]);

            rever44(pchars[i]);
            rever54(pchars[i]);

            rever55(ints[i]); 
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            g_rever00(objs[i]);
            g_rever10(objs[i]);
            g_rever20(objs[i]);
            g_rever30(objs[i]);
            g_rever40(objs[i]);
            g_rever50(objs[i]);

            g_rever11(ints[i]);
            g_rever21(ints[i]);
            g_rever31(ints[i]);
            g_rever41(ints[i]);
            g_rever51(ints[i]);

            g_rever22(chars[i]);
            g_rever32(chars[i]);
            g_rever42(chars[i]);
            g_rever52(chars[i]);

            g_rever33(objs[i]);
            g_rever43(objs[i]);
            g_rever53(objs[i]);

            g_rever44(pchars[i]);
            g_rever54(pchars[i]);

            g_rever55(ints[i]); 
        }
    }

    void TestCase_globalFunction()
    {
        PrintTitle1(MAKESTR(TestCase_globalFunction));

        using namespace MiniMPL;
        DemoFunction3 a;
        int         b   = 4;
        char        c   = 5;
        DemoFunction3 d;
        char*       e   = NULL;
        int         f   = 7;

        DemoFunction3    objs[5];        
        int             ints[5];
        char            chars[5];
        char*           pchars[5]={NULL};

        stlSmartptr<DemoFunction3>      pTObj(new DemoFunction3());
        //DemoFunction3* pObj = new DemoFunction3();

		typedef void (*F_T1)(int a);
		typedef void (*F_T2)(int a,char& b);
		typedef void (*F_T3)(int a,char& b,DemoFunction3 c);
        typedef void (*F_T3SP)(int a,char& b,stlSmartptr<DemoFunction3> pC);
		typedef void (*F_T4)(int a,char& b,DemoFunction3 c,char*);
		typedef void (*F_T5)(int a,char& b,DemoFunction3 c,char*,int);

		UnaryFunction<F_T1,1> reverg11=UnaryFunctionCreater<F_T1,1>::create(&funcP1,_$);
		UnaryFunction<F_T2,1> reverg21=UnaryFunctionCreater<F_T2,1>::create(&funcP2,_$,c);
		UnaryFunction<F_T3,1> reverg31=UnaryFunctionCreater<F_T3,1>::create(&funcP3,_$,c,d);        
		UnaryFunction<F_T4,1> reverg41=UnaryFunctionCreater<F_T4,1>::create(&funcP4,_$,c,d,e);        
		UnaryFunction<F_T5,1> reverg51=UnaryFunctionCreater<F_T5,1>::create(&funcP5,_$,c,d,e,f);

		UnaryFunction<F_T2,2> reverg22=UnaryFunctionCreater<F_T2,2>::create(&funcP2,b,_$);
		UnaryFunction<F_T3,2> reverg32=UnaryFunctionCreater<F_T3,2>::create(&funcP3,b,_$,d);        
		UnaryFunction<F_T4,2> reverg42=UnaryFunctionCreater<F_T4,2>::create(&funcP4,b,_$,d,e);        
		UnaryFunction<F_T5,2> reverg52=UnaryFunctionCreater<F_T5,2>::create(&funcP5,b,_$,d,e,f);

		UnaryFunction<F_T3,3> reverg33=UnaryFunctionCreater<F_T3,3>::create(&funcP3,b,c,_$);        
		UnaryFunction<F_T4,3> reverg43=UnaryFunctionCreater<F_T4,3>::create(&funcP4,b,c,_$,e);        
		UnaryFunction<F_T5,3> reverg53=UnaryFunctionCreater<F_T5,3>::create(&funcP5,b,c,_$,e,f);

		UnaryFunction<F_T4,4> reverg44=UnaryFunctionCreater<F_T4,4>::create(&funcP4,b,c,d,_$);        
		UnaryFunction<F_T5,4> reverg54=UnaryFunctionCreater<F_T5,4>::create(&funcP5,b,c,d,_$,f);

		UnaryFunction<F_T5,5> reverg55=UnaryFunctionCreater<F_T5,5>::create(&funcP5,b,c,d,e,_$); 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        UnaryFunction<F_T3SP,3> revergSp31=UnaryFunctionCreater<F_T3SP,3>::create(&funcP3P,b,c,_$);        

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        UnaryFunction<F_T1,1> g_reverg11=makeUnaryFunction(&funcP1,_$);
        UnaryFunction<F_T2,1> g_reverg21=makeUnaryFunction(&funcP2,_$,c);
        UnaryFunction<F_T3,1> g_reverg31=makeUnaryFunction(&funcP3,_$,c,d);        
        UnaryFunction<F_T4,1> g_reverg41=makeUnaryFunction(&funcP4,_$,c,d,e);        
        UnaryFunction<F_T5,1> g_reverg51=makeUnaryFunction(&funcP5,_$,c,d,e,f);

        UnaryFunction<F_T2,2> g_reverg22=makeUnaryFunction(&funcP2,b,_$);
        UnaryFunction<F_T3,2> g_reverg32=makeUnaryFunction(&funcP3,b,_$,d);        
        UnaryFunction<F_T4,2> g_reverg42=makeUnaryFunction(&funcP4,b,_$,d,e);        
        UnaryFunction<F_T5,2> g_reverg52=makeUnaryFunction(&funcP5,b,_$,d,e,f);

        UnaryFunction<F_T3,3> g_reverg33=makeUnaryFunction(&funcP3,b,c,_$);        
        UnaryFunction<F_T4,3> g_reverg43=makeUnaryFunction(&funcP4,b,c,_$,e);        
        UnaryFunction<F_T5,3> g_reverg53=makeUnaryFunction(&funcP5,b,c,_$,e,f);

        UnaryFunction<F_T4,4> g_reverg44=makeUnaryFunction(&funcP4,b,c,d,_$);        
        UnaryFunction<F_T5,4> g_reverg54=makeUnaryFunction(&funcP5,b,c,d,_$,f);

        UnaryFunction<F_T5,5> g_reverg55=makeUnaryFunction(&funcP5,b,c,d,e,_$); 

        for(int i=0;i<5;i++)
		{
			reverg11(ints[i]);
			reverg21(ints[i]);
			reverg31(ints[i]);
			reverg41(ints[i]);
			reverg51(ints[i]);

			reverg22(chars[i]);
			reverg32(chars[i]);
			reverg42(chars[i]);
			reverg52(chars[i]);

			reverg33(objs[i]);
			reverg43(objs[i]);
			reverg53(objs[i]);

			reverg44(pchars[i]);
			reverg54(pchars[i]);

			reverg55(ints[i]);

            revergSp31(pTObj);
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            g_reverg11(ints[i]);
            g_reverg21(ints[i]);
            g_reverg31(ints[i]);
            g_reverg41(ints[i]);
            g_reverg51(ints[i]);

            g_reverg22(chars[i]);
            g_reverg32(chars[i]);
            g_reverg42(chars[i]);
            g_reverg52(chars[i]);

            g_reverg33(objs[i]);
            g_reverg43(objs[i]);
            g_reverg53(objs[i]);

            g_reverg44(pchars[i]);
            g_reverg54(pchars[i]);

            g_reverg55(ints[i]);
        }
    }

    inline void TestCase_unaryFunctionCreater()
    {
        PrintTestcase();
        testUnaryFunction();
        TestCase_memberFunction();
        TestCase_globalFunction();
    }

#ifdef RUN_EXAMPLE_UNARYFUNCTIONCREATER
    InitRunFunc(TestCase_unaryFunctionCreater);
#else //else of RUN_EXAMPLE_UNARYFUNCTIONCREATER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_UNARYFUNCTIONCREATER)=(outputTxtV(TXT("[Unit test run disabled] unaryFunctionCreater.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"unaryFunctionCreater.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_UNARYFUNCTIONCREATER
}

#else //else of COMPILE_EXAMPLE_UNARYFUNCTIONCREATER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_UNARYFUNCTIONCREATER)=(outputTxtV(TXT("[Unit test compile disabled] unaryFunctionCreater.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"unaryFunctionCreater.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_UNARYFUNCTIONCREATER

