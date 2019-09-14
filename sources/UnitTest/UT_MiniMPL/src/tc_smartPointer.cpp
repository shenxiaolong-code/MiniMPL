#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\smartPointer.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_SMARTPOINTER to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_SMARTPOINTER

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_SMARTPOINTER
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_SMARTPOINTER
#endif

#if defined(RUN_EXAMPLE_SMARTPOINTER) && !defined(COMPILE_EXAMPLE_SMARTPOINTER)
    #define COMPILE_EXAMPLE_SMARTPOINTER
#endif

//#undef RUN_EXAMPLE_SMARTPOINTER
//#undef COMPILE_EXAMPLE_SMARTPOINTER

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_SMARTPOINTER
#include <MiniMPL/smartPointer.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UT_material/tc_def_typeStruct.h>

#undef stlSmartptr
#define stlSmartptr     ::MiniMPL::RefCountSmartPtr

namespace UnitTest
{
    struct DS4 : public S4
    {           
        int m_ds4;
    };
    typedef stlSmartptr<S4>     TpS4;
    typedef stlSmartptr<DS4>    TpDS4;
    typedef stlSmartptr<S3>     TpS3;        

    void TestCase_SmartPtr_const()
    {
        TpS4        nullS4;

        S4          vs4;
        const S4    vs4c;
        S4*         pS41  = new S4();
        S4*         pS42  = new S4();
        S4*         pS43  = new S4();
        S4 const*   pS4c = new S4();
        TpS4        tps4_11(pS41);       //explicit SmartPtr_V2(T* pObj)
        TpS4        tps4_12(pS43);       //explicit SmartPtr_V2(T* pObj)
        const TpS4  tps4_2c(pS42);      //explicit SmartPtr_V2(T* pObj)
        const TpS4  tps4_2cc(tps4_2c);  //SmartPtr_V2(SmartPtr_V2 const& rOther)
        TpDS4       pDS4(new DS4());
        TpS4        pDbS4(pDS4);

        //test
        //ps4_1c = ps4_1;           //error, OK! implicit construct is not allowned.
        //TpS4 failConst(pS4c);     //error, OK! const T construct is not allowned.
        delete pS4c;

        ASSERT_AND_LOG(tps4_11==pS41);   //inline bool operator==(T const* p) const
        ASSERT_AND_LOG(tps4_11==tps4_11); //inline bool operator==(SmartPtr_V2<D> const& rOther) const
        ASSERT_AND_LOG(tps4_11!=tps4_2c);//inline bool operator!=(SmartPtr_V2<D> const& rOther) const 
        ASSERT_AND_LOG(tps4_11!=pS42);   //inline bool operator!=(T const* p) const

        ASSERT_AND_LOG(tps4_2c==pS42);    //inline bool operator==(T const* p) const
        ASSERT_AND_LOG(tps4_2c==tps4_2c); //inline bool operator==(SmartPtr_V2<D> const& rOther) const
        ASSERT_AND_LOG(tps4_2c!=pS41);    //inline bool operator!=(T const* p) const
        ASSERT_AND_LOG(tps4_2c!=tps4_11);  //inline bool operator!=(SmartPtr_V2<D> const& rOther) const

        tps4_11=tps4_2cc;  //SmartPtr_V2& operator=(SmartPtr_V2<T> const& rOther)
        tps4_11=tps4_12;   //SmartPtr_V2& operator=(SmartPtr_V2<T> const& rOther)

        tps4_11 = pDS4;    //SmartPtr_V2& operator=(SmartPtr_V2<D> const& rOther)
        ASSERT_AND_LOG(tps4_11==pDS4);  //inline bool operator==(SmartPtr_V2<D> const& rOther) const 
        ASSERT_AND_LOG(tps4_12!=pDS4);  //inline bool operator!=(SmartPtr_V2<D> const& rOther) const 

        pDS4->print();      //inline T*	operator->() const
        S4& rS4 = *pDS4;    //inline T&	operator*() const

        ASSERT_AND_LOG(!nullS4);  //operator unspecified_bool_type() const
        ASSERT_AND_LOG(tps4_11);  //operator unspecified_bool_type() const
        ASSERT_AND_LOG(tps4_12); //operator unspecified_bool_type() const
        ASSERT_AND_LOG(tps4_2c); //operator unspecified_bool_type() const
        ASSERT_AND_LOG(tps4_2cc); //operator unspecified_bool_type() const

        tps4_11.reset(new S4());   //SmartPtr_V2& reset(T* pNewObj)
        //      tps4_2c.reset(new S4());   //const Fails, OK!
        //      tps4_2cc.reset(new S4());  //const Fails, OK!
        //      pDS4.reset(new S4());      //Fails base => derive, OK!

        S4* pS4 =  tps4_11.get();   //inline T*	getPtr() const
        pS4     =  tps4_2c.get();   //inline T*	getPtr() const

    }

    inline void TestCase_smartPointer()
    {
        PrintTestcase();

        using namespace MiniMPL;

        S3*     pS3     = new S3();
        S4*     pS4     = new S4();        
        DS4*    pDS4    = new DS4();
        //test constructor  : SmartPtr_V2(ObjectType*	pObj=NULL) 
        TpS3    pS3_1(new S3);
        TpS3    pS3_2(pS3);
        TpS4    pS4_1(pS4);	
        TpS4    pS4_2(new S4());
        TpDS4   pDs4_1(new DS4());
        TpDS4   pDs4_2(pDS4);

        //test constructor  : template<typename D> SmartPtr_V2(SmartPtr_V2<D>& rOther)
        TpS4    pS4_3(pS4_1);       //same class    //std::auto_ptr will take ownership when assign, it needs shared-ptr
        TpS4    pS4_4(pDs4_1);      //derived => base, OK.
        //TpDS4   pDs4_2(pS4_2);    //base => derived : fails is expected. OK.
        //TpS4 pS4_5(pS3_1);        //unrelatived class can't be casted : fails is expected. OK

        //test T* operator->()
        pS4_1->m_s4 = 123;
        Assertb(pS4_1->m_s4 == pS4->m_s4);
        pS3_2->m_s3 = 11;
        Assertb(pS3_2->m_s3 == pS3->m_s3);        

        //test template<typename D> SmartPtr_V2(SmartPtr_V2<D>& rOther) 
        pS4_1  = TpS4(new S4());
        pS4_2  = pDs4_1;

        typedef int S4::*memPtr_T;
        RefCountSmartPtr<memPtr_T> ptt(new memPtr_T(&S4::m_s4));
        S4	obj;

        //test T& operator *()
        int		memOfS = obj.*(*ptt);
        Assertb(memOfS == obj.m_s4);

        //test operator bool(), implemented implicitly by operator T*()
        TpS4  pBool;

        //stlSmartptr<TpS4>      pTTObj(pS4_1);     //TODO : Fails case 

        //std::auto_ptr has not below operator
        Assertb(!pBool);
        if (pBool)  {   Assertb(false); }
        pBool = pS4_1;
        Assertb(pBool);
        if (!pBool) {   Assertb(false); }

        //test implicit conversion
        S4* pCvt = pS4_1.get();
        //bool      boolVal     = pS4_1;    //warning C4800 , OK
        //float     floatVal    = pS4_1;    //fail : pointer can't be converted to float
        //float*    pfloat      = pS4_1;    //fail: type is different, can't convert

        //test bool operator==()
        Assertb(pS4_1==pCvt);
        Assertb(pBool==pS4_1);
        Assertb(pS4_1 != pDs4_2);

        pS4_1.reset(NULL);
    }

#ifdef RUN_EXAMPLE_SMARTPOINTER
    InitRunFunc(TestCase_smartPointer);
    InitRunFunc(TestCase_SmartPtr_const);
#else //else of RUN_EXAMPLE_SMARTPOINTER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_SMARTPOINTER)=(outputTxtV(TXT("[Unit test run disabled] smartPointer.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"smartPointer.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_SMARTPOINTER
}

#else //else of COMPILE_EXAMPLE_SMARTPOINTER
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_SMARTPOINTER)=(outputTxtV(TXT("[Unit test compile disabled] smartPointer.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"smartPointer.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_SMARTPOINTER

