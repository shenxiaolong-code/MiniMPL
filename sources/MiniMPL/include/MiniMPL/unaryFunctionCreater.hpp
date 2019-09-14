#ifndef __UNARYFUNCTIONCREATER_HPP__
#define __UNARYFUNCTIONCREATER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/unaryFunction.hpp>
#include <MiniMPL/placeHolder.hpp>

namespace MiniMPL
{
    template<typename F,int Idx> struct UnaryFunctionCreater : public UnaryFunctionOperator<F> { };
    //     template<typename F> struct UnaryFunctionCreater<F,0> : public UnaryFunctionImpl<F> { };
    //     template<typename F> struct UnaryFunctionCreater<F,1> : public UnaryFunctionImpl<F> { };
    //     template<typename F> struct UnaryFunctionCreater<F,2> : public UnaryFunctionImpl<F> { };
    //     template<typename F> struct UnaryFunctionCreater<F,3> : public UnaryFunctionImpl<F> { };
    //     template<typename F> struct UnaryFunctionCreater<F,4> : public UnaryFunctionImpl<F> { };
    //     template<typename F> struct UnaryFunctionCreater<F,5> : public UnaryFunctionImpl<F> { };

    template<int Idx,typename F,typename TUFParams>
    inline UnaryFunctionDirect<F,Idx,TUFParams> makeUnaryFunctionDirectly(F f,TUFParams& ps)
    {
        return UnaryFunctionDirect<F,Idx,TUFParams>(f,ps);
    }

    //member function
    template<typename R,typename O> 
    inline UnaryFunction<R(O::*)(),0> makeUnaryFunction(R(O::*f)(),_)  { return UnaryFunctionCreater<R(O::*)(),0>::create(f,_$); };
    template<typename R,typename O,typename TP1> 
    inline UnaryFunction<R(O::*)(TP1),0> makeUnaryFunction(R(O::*f)(TP1),_,TPP(TP1) p1)  { return UnaryFunctionCreater<R(O::*)(TP1),0>::create(f,_$,p1); };
    template<typename R,typename O,typename TP1,typename TP2> 
    inline UnaryFunction<R(O::*)(TP1,TP2),0> makeUnaryFunction(R(O::*f)(TP1,TP2),_,TPP(TP1) p1,TPP(TP2) p2)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2),0>::create(f,_$,p1,p2); };
    template<typename R,typename O,typename TP1,typename TP2,typename TP3> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3),0> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3),_,TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3),0>::create(f,_$,p1,p2,p3); };
    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4),0> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4),_,TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4),0>::create(f,_$,p1,p2,p3,p4); };
    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4,TP5),0> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4,TP5),_,TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4,TPP(TP5) p5)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4,TP5),0>::create(f,_$,p1,p2,p3,p4,p5); };

    template<typename R,typename O,typename TP1> 
    inline UnaryFunction<R(O::*)(TP1),1> makeUnaryFunction(R(O::*f)(TP1),TPP(O) p0,_)  { return UnaryFunctionCreater<R (O::*)(TP1),1>::create(f,p0,_$); };
    template<typename R,typename O,typename TP1,typename TP2> 
    inline UnaryFunction<R(O::*)(TP1,TP2),1> makeUnaryFunction(R(O::*f)(TP1,TP2),TPP(O) p0,_,TPP(TP2) p2)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2),1>::create(f,p0,_$,p2); };
    template<typename R,typename O,typename TP1,typename TP2,typename TP3> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3),1> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3),TPP(O) p0,_,TPP(TP2) p2,TPP(TP3) p3)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3),1>::create(f,p0,_$,p2,p3); };
    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4),1> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4),TPP(O) p0,_,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4),1>::create(f,p0,_$,p2,p3,p4); };    
    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4,TP5),1> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4,TP5),TPP(O) p0,_,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4,TPP(TP5) p5)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4,TP5),1>::create(f,p0,_$,p2,p3,p4,p5); };

    template<typename R,typename O,typename TP1,typename TP2> 
    inline UnaryFunction<R(O::*)(TP1,TP2),2> makeUnaryFunction(R(O::*f)(TP1,TP2),TPP(O) p0,TPP(TP1) p1,_)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2),2>::create(f,p0,p1,_$); };
    template<typename R,typename O,typename TP1,typename TP2,typename TP3> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3),2> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3),TPP(O) p0,TPP(TP1) p1,_,TPP(TP3) p3)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3),2>::create(f,p0,p1,_$,p3); };
    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4),2> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4),TPP(O) p0,TPP(TP1) p1,_,TPP(TP3) p3,TPP(TP4) p4)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4),2>::create(f,p0,p1,_$,p3,p4); };    
    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4,TP5),2> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4,TP5),TPP(O) p0,TPP(TP1) p1,_,TPP(TP3) p3,TPP(TP4) p4,TPP(TP5) p5)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4,TP5),2>::create(f,p0,p1,_$,p3,p4,p5); };

    template<typename R,typename O,typename TP1,typename TP2,typename TP3> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3),3> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3),TPP(O) p0,TPP(TP1) p1,TPP(TP2) p2,_)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3),3>::create(f,p0,p1,p2,_$); };
    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4),3> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4),TPP(O) p0,TPP(TP1) p1,TPP(TP2) p2,_,TPP(TP4) p4)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4),3>::create(f,p0,p1,p2,_$,p4); };    
    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4,TP5),3> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4,TP5),TPP(O) p0,TPP(TP1) p1,TPP(TP2) p2,_,TPP(TP4) p4,TPP(TP5) p5)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4,TP5),3>::create(f,p0,p1,p2,_$,p4,p5); };

    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4),4> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4),TPP(O) p0,TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,_)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4),4>::create(f,p0,p1,p2,p3,_$); };    
    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4,TP5),4> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4,TP5),TPP(O) p0,TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,_,TPP(TP5) p5)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4,TP5),4>::create(f,p0,p1,p2,p3,_$,p5); };

    template<typename R,typename O,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(O::*)(TP1,TP2,TP3,TP4,TP5),5> makeUnaryFunction(R(O::*f)(TP1,TP2,TP3,TP4,TP5),TPP(O) p0,TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4,_)  { return UnaryFunctionCreater<R(O::*)(TP1,TP2,TP3,TP4,TP5),5>::create(f,p0,p1,p2,p3,p4,_$); };

    //non-member function
    template<typename R,typename TP1> 
    inline UnaryFunction<R(*)(TP1),1> makeUnaryFunction(R(*f)(TP1),_)  { return UnaryFunctionCreater<R(*)(TP1),1>::create(f,_$); };
    template<typename R,typename TP1,typename TP2> 
    inline UnaryFunction<R(*)(TP1,TP2),1> makeUnaryFunction(R(*f)(TP1,TP2),_,TPP(TP2) p2)  { return UnaryFunctionCreater<R(*)(TP1,TP2),1>::create(f,_$,p2); };
    template<typename R,typename TP1,typename TP2,typename TP3> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3),1> makeUnaryFunction(R(*f)(TP1,TP2,TP3),_,TPP(TP2) p2,TPP(TP3) p3)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3),1>::create(f,_$,p2,p3); };
    template<typename R,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3,TP4),1> makeUnaryFunction(R(*f)(TP1,TP2,TP3,TP4),_,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3,TP4),1>::create(f,_$,p2,p3,p4); };    
    template<typename R,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3,TP4,TP5),1> makeUnaryFunction(R(*f)(TP1,TP2,TP3,TP4,TP5),_,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4,TPP(TP5) p5)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3,TP4,TP5),1>::create(f,_$,p2,p3,p4,p5); };

    template<typename R,typename TP1,typename TP2> 
    inline UnaryFunction<R(*)(TP1,TP2),2> makeUnaryFunction(R(*f)(TP1,TP2),TPP(TP1) p1,_)  { return UnaryFunctionCreater<R(*)(TP1,TP2),2>::create(f,p1,_$); };
    template<typename R,typename TP1,typename TP2,typename TP3> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3),2> makeUnaryFunction(R(*f)(TP1,TP2,TP3),TPP(TP1) p1,_,TPP(TP3) p3)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3),2>::create(f,p1,_$,p3); };
    template<typename R,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3,TP4),2> makeUnaryFunction(R(*f)(TP1,TP2,TP3,TP4),TPP(TP1) p1,_,TPP(TP3) p3,TPP(TP4) p4)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3,TP4),2>::create(f,p1,_$,p3,p4); };    
    template<typename R,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3,TP4,TP5),2> makeUnaryFunction(R(*f)(TP1,TP2,TP3,TP4,TP5),TPP(TP1) p1,_,TPP(TP3) p3,TPP(TP4) p4,TPP(TP5) p5)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3,TP4,TP5),2>::create(f,p1,_$,p3,p4,p5); };

    template<typename R,typename TP1,typename TP2,typename TP3> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3),3> makeUnaryFunction(R(*f)(TP1,TP2,TP3),TPP(TP1) p1,TPP(TP2) p2,_)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3),3>::create(f,p1,p2,_$); };
    template<typename R,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3,TP4),3> makeUnaryFunction(R(*f)(TP1,TP2,TP3,TP4),TPP(TP1) p1,TPP(TP2) p2,_,TPP(TP4) p4)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3,TP4),3>::create(f,p1,p2,_$,p4); };    
    template<typename R,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3,TP4,TP5),3> makeUnaryFunction(R(*f)(TP1,TP2,TP3,TP4,TP5),TPP(TP1) p1,TPP(TP2) p2,_,TPP(TP4) p4,TPP(TP5) p5)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3,TP4,TP5),3>::create(f,p1,p2,_$,p4,p5); };

    template<typename R,typename TP1,typename TP2,typename TP3,typename TP4> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3,TP4),4> makeUnaryFunction(R(*f)(TP1,TP2,TP3,TP4),TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,_)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3,TP4),4>::create(f,p1,p2,p3,_$); };    
    template<typename R,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3,TP4,TP5),4> makeUnaryFunction(R(*f)(TP1,TP2,TP3,TP4,TP5),TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,_,TPP(TP5) p5)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3,TP4,TP5),4>::create(f,p1,p2,p3,_$,p5); };

    template<typename R,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> 
    inline UnaryFunction<R(*)(TP1,TP2,TP3,TP4,TP5),5> makeUnaryFunction(R(*f)(TP1,TP2,TP3,TP4,TP5),TPP(TP1) p1,TPP(TP2) p2,TPP(TP3) p3,TPP(TP4) p4,_)  { return UnaryFunctionCreater<R(*)(TP1,TP2,TP3,TP4,TP5),5>::create(f,p1,p2,p3,p4,_$); };

}

#endif // __UNARYFUNCTIONCREATER_HPP__
