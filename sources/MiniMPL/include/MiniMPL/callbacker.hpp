#ifndef __CALLBACKER_HPP__
#define __CALLBACKER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/paramPackageCall.hpp>
#include <MiniMPL/sameQualifier.hpp>
#ifdef WIN32
#include <Windows.h>
#endif

namespace MiniMPL
{
    struct ICallbacker
    {
        unsigned long   m_senderId;
        ICallbacker() : m_senderId(0)
        {
#ifdef WIN32
            m_senderId = GetCurrentThreadId(); //used for debug check source
#endif
        };

        virtual void execute()=0;
        virtual ~ICallbacker(){};
    };
               
    typedef stlSmartptr<ICallbacker> TpCallbacker;

    //////////////////////////////////////////////Global/Static callback function ///////////////////////////////////////////
    //Convert has-parameter function into No-Param function.
    template<typename TF,typename TPamams>
    struct TCallbacker : public ICallbacker
    {
        TCallbacker(TF pFunc,const TPamams& params)
            : m_pFunc(pFunc)
            , m_params(params){};

        virtual void execute()
        {
            MiniMPL::doPackCall(m_pFunc,m_params);
        }        

    protected:
        TF          m_pFunc;
        TPamams     m_params;
    };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename TF,typename TParams>
    inline ICallbacker* makeCallbackerDirect(TF f, const TParams& params)
    {   
        // TF shouldn't be function object,if it is, pls convert it into TR T::operator()(...) formal. e.g.
        // TR (T::*pMF)(Tp1,Tp2,Tp3) = &T::operator()
        // makeCallbackerDirect(pMF,ParamPackageCall);        
        typedef TCallbacker<TF,TParams> TCallbackerImpl;
        return new TCallbackerImpl(f,params);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //create helper. take care of life cycle of local variable
    //if sync execution, free to use helper "makeCallbacker"
    //if async execution,function parameter has LOCAL life cycle ,pls use makeCallbackerDirect.e.g
    /*
    //solution 1 : duplicate object to resolve life cycle issue
    int T::egFunc(int,S4&);
    S4  os4;    //async call, local variable has lifecycle issue.
    T   obj;    //async call, local variable has lifecycle issue.
    makeCallbackerDirect(&T::egFunc,ParamPackageCall<T,int,S4>(obj,5,os4));
    //ParamPackageCall<T,int,S4>    will cause obj/os4 be duplicated, resolved life cycle issue.   OK!
    //ParamPackageCall<T&,int,S4&>  will NOT cause obj/os4 be duplicated,life cycle issue exists.  Fails!
    
    //solution 2 : smart pointer to resolve life cycle issue of host object of member function.
    //for host object of member function, smart pointer is supported to resolve life cycle issue.e.g.
    int T::egFunc(int,S3);
    S3  os3;    //async call, but S3 in T::egFunc(,S3) is duplicatable, local variable hasn't lifecycle issue.
    stlSmartptr<T>  pObj(new T());  //async call, smart pointer resolved lifecycle issue.
    ParamPackageCall<stlSmartptr<T>,int,S3>  paramPacks;
    makeCallbackerDirect(&T::egFunc,paramPacks); //OK, host object hasn't life cycle issue
    */
    //member function,exactly parameter type match    
    template<typename TR,typename TO> 
    inline ICallbacker* makeCallbacker(TR(TO::*f)(),TPP(TO) p0)  
    {
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TO)>(p0));
    };
   
    template<typename TR,typename TO,typename TP1> 
    inline ICallbacker* makeCallbacker(TR(TO::*f)(TP1),TPP(TO) p0,TPP(TP1) p1)  
    {
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TO),TPP(TP1)>(p0,p1));
    };

    template<typename TR,typename TO,typename TP1,typename TP2> 
    inline ICallbacker* makeCallbacker(TR(TO::*f)(TP1,TP2),TPP(TO) p0,TPP(TP1) p1,TPP(TP2) p2)  
    { 
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TO),TPP(TP1),TPP(TP2)>(p0,p1,p2));
    };
    template<typename TR,typename TO,typename TP1,typename TP2,typename TP3> 
    inline ICallbacker* makeCallbacker(TR(TO::*f)(TP1,TP2,TP3),TPP(TO) p0,TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3)  
    {
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TO),TPP(TP1),TPP(TP2),TPP(TP3)>(p0,p1,p2,p3));
    };
    template<typename TR,typename TO,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline ICallbacker* makeCallbacker(TR(TO::*f)(TP1,TP2,TP3,TP4),TPP(TO) p0,TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4)  
    {                     
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TO),TPP(TP1),TPP(TP2),TPP(TP3),TPP(TP4)>(p0,p1,p2,p3,p4));
    };
    template<typename TR,typename TO,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline ICallbacker* makeCallbacker(TR(TO::*f)(TP1,TP2,TP3,TP4,TP5),TPP(TO) p0,TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4,TPP(TP5) p5)  
    {
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TO),TPP(TP1),TPP(TP2),TPP(TP3),TPP(TP4),TPP(TP5)>(p0,p1,p2,p3,p4,p5)); 
    };

    /*cancel specialization function object, because below factors:
    1.    it is replaceable by member function formal
    1.1   e.g.
          R (TO::*pOperator2P)(TP1&,TP2) = &TO::operator ();
          TpCallbackWorker pWorker = makeCallbacker(pOperator2P,TO_obj,p1,p2);

    2.    it is easy to be mis-used about ref/non-ref
    2.1   e.g. 
          TpCallbackWorker pWorker = makeCallbacker(obj,iVal,pChar,rStr); 
    2.2   ref qualifier is missing and ref might be output parameter

    3.    it is inconvenience to provide every parameter type in makeCallbacker function.
    3.1   e.g.
          TpCallbackWorker pWorker = makeCallbacker<TObj,int&,char*,string&>(obj,iVal,pChar,rStr); 
    
    4.    it can't return value because compile can't deduce return type without function signature.
    */

    //non-member function,exactly parameter type match
    template<typename TR> 
    inline ICallbacker* makeCallbacker(TR(*f)())  
    {
        return makeCallbackerDirect(f,ParamPackageCall<>());
    };

    template<typename TR,typename TP1> 
    inline ICallbacker* makeCallbacker(TR(*f)(TP1),TPP(TP1) p1)  
    {
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TP1)>(p1));      
    };

    template<typename TR,typename TP1,typename TP2> 
    inline ICallbacker* makeCallbacker(TR(*f)(TP1,TP2),TPP(TP1) p1,TPP(TP2) p2)  
    {
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TP1),TPP(TP2)>(p1,p2));
    };

    template<typename TR,typename TP1,typename TP2,typename TP3> 
    inline ICallbacker* makeCallbacker(TR(*f)(TP1,TP2,TP3),TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3)  
    { 
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TP1),TPP(TP2),TPP(TP3)>(p1,p2,p3));
    };
    template<typename TR,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline ICallbacker* makeCallbacker(TR(*f)(TP1,TP2,TP3,TP4),TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4)  
    {
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TP1),TPP(TP2),TPP(TP3),TPP(TP4)>(p1,p2,p3,p4));
    };    
    template<typename TR,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline ICallbacker* makeCallbacker(TR(*f)(TP1,TP2,TP3,TP4,TP5),TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4,TPP(TP5) p5) 
    {
        return makeCallbackerDirect(f,ParamPackageCall<TPP(TP1),TPP(TP2),TPP(TP3),TPP(TP4),TPP(TP5)>(p1,p2,p3,p4,p5));
    };
}

#endif // __CALLBACKER_HPP__
