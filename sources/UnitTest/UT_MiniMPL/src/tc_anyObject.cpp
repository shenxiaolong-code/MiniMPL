#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\anyObject.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_ANYOBJECT to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_ANYOBJECT

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_ANYOBJECT
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_ANYOBJECT
#endif

#if defined(RUN_EXAMPLE_ANYOBJECT) && !defined(COMPILE_EXAMPLE_ANYOBJECT)
    #define COMPILE_EXAMPLE_ANYOBJECT
#endif

//#undef RUN_EXAMPLE_ANYOBJECT
//#undef COMPILE_EXAMPLE_ANYOBJECT

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_ANYOBJECT
#include <MiniMPL/anyObject.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <UnitTestKit/tc_dump.h>
#include <UT_material/tc_def_typeStruct.h>
#include <MiniMPL/paramPackageCall.hpp>
#include <MiniMPL/functionParams.hpp>
#include <MiniMPL/unaryFunction.hpp>

namespace UnitTest
{
    template <typename paramType1> class CTypeTraints;
    class CObjectAdapter
    {
    public:
        template <typename objectType> 
        CObjectAdapter(objectType& object,bool bAutoDelete=true)
			:m_pObject(new MiniMPL::CAnyObjectImpl<objectType>(object,bAutoDelete)) {}

        virtual ~CObjectAdapter()
        {
            delete m_pObject;
        }

        template<typename operatorType> operator operatorType&()
        {
            return (operatorType&)(*m_pObject);
        }

        template<typename operatorType> operator operatorType*()
        {
            return (operatorType*)(*m_pObject);
        }

        /*! known actual derived handler type, and invoke it explicitly*/
        template<typename F,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7> 
        FR(F) demoFuncCall(F f,MiniMPL::ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> const& rObj)
        {
            typedef MiniMPL::ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> const TPS;
            MiniMPL::UnaryFunctionDirect<F,0,TPS> uf(f,rObj);
            return uf((FO(F)&)*m_pObject);
        }

        void dump()
        {
            m_pObject->dump();
        }

    private:
        MiniMPL::CAnyObject*   m_pObject;
    };

    /*!  example parameter type */
    typedef struct _tagParamType
    {
        int m_iData;
    }UserParam,*lpUserParam;

    /*!  example handler type */
    class  UserHandler
    {
    public:
        UserHandler():m_count(0)
        {
            TRACE_HERE();
        };
        UserHandler(UserHandler const& other)
        {
            TRACE_HERE();
        };

        virtual ~UserHandler()
        {
            TRACE_HERE();
        };

        int demoFuncTraintCall(UserParam& obj) 
        {
            m_count++;
            TRACE_HERE();
            return m_count;
        };

        void dump()
        {
            outputTxt(TXT("I am UserHandler!\n"));
        }

        char demoFuncCall()                     
        {
            m_count++;
            TRACE_HERE();
            return 'Y';
        }

    private:
        int m_count;
    };

    /*!  Bind parameter type [UserParam] and handler type [ UserHandler] */
    template<>  class CTypeTraints<UserParam>
    {
    public:
        typedef UserHandler    Handler_Type;
    };

    void otherUserFuncP(UserHandler* pObj)
    {
        AssertP(pObj);
        pObj->demoFuncCall();
    }

    void otherUserFunc(UserHandler& obj)
    {
        obj.demoFuncCall();
    }

    void demoObjectWrapperInterface(CObjectAdapter* pObj)
    {
        PrintTestcaseSub();
        TRACE_INFO((TXT("dump MyObjectWrapper:\n")));
        pObj->dump();

        TRACE_INFO((TXT("No param , known handler type : %s\n"),getTypeName<UserHandler>().c_str()));
        char cInvokeRet01   = pObj->demoFuncCall(&UserHandler::demoFuncCall,MiniMPL::makeParamPackage_Ref());

        UserParam paramT;
        TRACE_INFO((TXT("param type : %s , handler type : %s\n"),getTypeName(paramT).c_str(),TXT("decided by traits")));    
        int iInvokeRet11 = pObj->demoFuncCall(&UserHandler::demoFuncTraintCall,MiniMPL::makeParamPackage_Ref(paramT));

        /*!
        * otherUserFunc needs parameter "UserHandler", but we only has parameter "CObjectAdapter".
        * operator override will convert CObjectAdapter type to  UserHandler automatically
        */
        TRACE_INFO((TXT("required param type : %s , actual param type : %s\n"),getTypeName<UserHandler>().c_str(),getTypeName<CObjectAdapter>()));
        otherUserFunc(*pObj);
        otherUserFuncP(*pObj);        
    }

    struct VpAnyObject
    {
        VpAnyObject(){};
        VpAnyObject(int){};
        VpAnyObject(float&){};
        VpAnyObject(S3&){};
        VpAnyObject(char*p,int){};        
        VpAnyObject(S3,S4&){};

        VpAnyObject(char*p,int,float&){};
        ~VpAnyObject()
        {
            TRACE_HERE();
        }
    };


    bool TestCase_anyObject()
    {
        using namespace MiniMPL;
        PrintTestcase();

        //test operatorType* and cast2Type
        S3 obj;
        typedef MiniMPL::CAnyObjectImpl<S3>     AnyObjectImpl_T;

        MiniMPL::CAnyObject* pObj = new AnyObjectImpl_T(obj,true);
        S3* pCastObj = pObj->cast2Type<S3*>();
        Assertb(pCastObj==&obj);
        pCastObj = *pObj;
        Assertb(pCastObj==&obj);
        //test operatorType&
        S3& rS3 = *pObj;
        Assertb(&rS3 == &obj);
        //delete pObj;      //memeory leak becase of testing operatorType& , tolerate it

        //test default constructor
        pObj = new MiniMPL::CAnyObjectImpl<VpAnyObject>();
        delete pObj;

        //test constructor with 1 parameter
        //.2 variable input parameter   : int or int&
        int iParam = 4;
        pObj = new MiniMPL::CAnyObjectImpl<VpAnyObject>(makeParamPackage_Ref(iParam));
        delete pObj;
        //.3 customized reference type  : S3&
        pObj = new MiniMPL::CAnyObjectImpl<VpAnyObject>(makeParamPackage_Ref(rS3));      //for variable, both makeAnyObject<T>(p) and makeAnyObject<T>(MP(p)) are OK
        delete pObj;

        //test constructor with 2 parameter
        pObj = new MiniMPL::CAnyObjectImpl<VpAnyObject>(makeParamPackage_Ref(rS3,S4()));        //for variable, both makeAnyObject<T>(p) and makeAnyObject<T>(MP(p)) are OK
        delete pObj;

        PrintTitle1(TXT("Demo object wrapper usage"));
        CObjectAdapter* pNew=new CObjectAdapter(*new UserHandler());   //wrapper encapsulates actual type : UserHandler
        demoObjectWrapperInterface(pNew);

        return true;
    }

#ifdef RUN_EXAMPLE_ANYOBJECT
    InitRunFunc(TestCase_anyObject);
#else //else of RUN_EXAMPLE_ANYOBJECT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_ANYOBJECT)=(outputTxtV(TXT("[Unit test run disabled] anyObject.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"anyObject.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_ANYOBJECT
}

#else //else of COMPILE_EXAMPLE_ANYOBJECT
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_ANYOBJECT)=(outputTxtV(TXT("[Unit test compile disabled] anyObject.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"anyObject.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_ANYOBJECT

