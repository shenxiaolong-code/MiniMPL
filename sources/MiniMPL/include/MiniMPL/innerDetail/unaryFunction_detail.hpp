#ifndef UNARYFUNCTION_DETAIL_H__
#define UNARYFUNCTION_DETAIL_H__

/***********************************************************************************************************************
Description         : 
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/unaryFunctionParams.hpp>

namespace MiniMPL
{
    template<typename F,int Idx>                                                            struct UnaryFunction;       //forward declaration
    template<typename F,int Idx,typename TUnaryFunctionParams=UnaryFuncParams<F,Idx>::type> struct UnaryFunctionDirect; //forward declaration

#define     UFInitParams(F,Idx) typename UnaryFuncParams<F,Idx>::type

    //member function
    template<typename F,bool bMemberFunctionPointer=IsMemberFunctionPointer<F>::value,unsigned int N=ParamPackageSize<typename FunctionParams<F>::Params_T>::value> 
    struct UnaryFunctionOperator;
    template<typename F> struct UnaryFunctionOperator<F,true,0>  //prototype : R (O::*)()
    {
        typedef FPP(F,0)    TP0;
        static UnaryFunction<F,0> create(F f,_)                 { return UnaryFunction<F,0>(f,UFInitParams(F,0)()); };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,0,TPS>& ufObj,TP0 p0)     { return (p0.*(ufObj.m_f))(); }
    };

    template<typename F> struct UnaryFunctionOperator<F,true,1>  //prototype : R (O::*)(P1)
    {
        typedef FPP(F,0)    TP0;
        typedef FPP(F,1)    TP1;
        static UnaryFunction<F,0> create(F f,     _,  TP1 p1 )  { return UnaryFunction<F,0>(f,UFInitParams(F,0)(p1)); };
        static UnaryFunction<F,1> create(F f, TP0 p0,      _ )  { return UnaryFunction<F,1>(f,UFInitParams(F,1)(p0)); };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,0,TPS>& ufObj,TP0 p0)     { return (p0.*(ufObj.m_f))(ufObj.m_Ps.m_p1);     }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1)     { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(p1);   }
    };

    template<typename F> struct UnaryFunctionOperator<F,true,2>   //prototype : R (O::*)(P1,P2)
    {
        typedef FPP(F,0)    TP0;
        typedef FPP(F,1)    TP1;
        typedef FPP(F,2)    TP2;
        static UnaryFunction<F,0> create(F f,     _,  TP1 p1,  TP2 p2) { return UnaryFunction<F,0>(f,UFInitParams(F,0)(p1,p2)); };
        static UnaryFunction<F,1> create(F f, TP0 p0,      _,  TP2 p2) { return UnaryFunction<F,1>(f,UFInitParams(F,1)(p0,p2)); };
        static UnaryFunction<F,2> create(F f, TP0 p0,  TP1 p1,      _) { return UnaryFunction<F,2>(f,UFInitParams(F,2)(p0,p1)); };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,0,TPS>& ufObj,TP0 p0) { return (p0.*(ufObj.m_f))(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2);     }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(p1,ufObj.m_Ps.m_p2);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,2,TPS>& ufObj,TP2 p2) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,p2);   }
    };

    template<typename F> struct UnaryFunctionOperator<F,true,3>    //prototype : R (O::*)(P1,P2,P3)
    {
        typedef FPP(F,0)    TP0;
        typedef FPP(F,1)    TP1;
        typedef FPP(F,2)    TP2;
        typedef FPP(F,3)    TP3;
        static UnaryFunction<F,0> create(F f,     _,  TP1 p1,  TP2 p2,  TP3 p3) { return UnaryFunction<F,0>(f,UFInitParams(F,0)(p1,p2,p3)); };
        static UnaryFunction<F,1> create(F f, TP0 p0,      _,  TP2 p2,  TP3 p3) { return UnaryFunction<F,1>(f,UFInitParams(F,1)(p0,p2,p3)); };
        static UnaryFunction<F,2> create(F f, TP0 p0,  TP1 p1,      _,  TP3 p3) { return UnaryFunction<F,2>(f,UFInitParams(F,2)(p0,p1,p3)); };
        static UnaryFunction<F,3> create(F f, TP0 p0,  TP1 p1,  TP2 p2,      _) { return UnaryFunction<F,3>(f,UFInitParams(F,3)(p0,p1,p2)); };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,0,TPS>& ufObj,TP0 p0) { return (p0.*(ufObj.m_f))(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3); }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,2,TPS>& ufObj,TP2 p2) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,p2,ufObj.m_Ps.m_p3);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,3,TPS>& ufObj,TP3 p3) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,p3);   }
    };

    template<typename F> struct UnaryFunctionOperator<F,true,4>    //prototype : R (O::*)(P1,P2,P3,P4)
    {
        typedef FPP(F,0)    TP0;
        typedef FPP(F,1)    TP1;
        typedef FPP(F,2)    TP2;
        typedef FPP(F,3)    TP3;
        typedef FPP(F,4)    TP4;
        static UnaryFunction<F,0> create(F f,     _,  TP1 p1,  TP2 p2,  TP3 p3,  TP4 p4) { return UnaryFunction<F,0>(f,UFInitParams(F,0)(p1,p2,p3,p4)); };
        static UnaryFunction<F,1> create(F f, TP0 p0,      _,  TP2 p2,  TP3 p3,  TP4 p4) { return UnaryFunction<F,1>(f,UFInitParams(F,1)(p0,p2,p3,p4)); };
        static UnaryFunction<F,2> create(F f, TP0 p0,  TP1 p1,      _,  TP3 p3,  TP4 p4) { return UnaryFunction<F,2>(f,UFInitParams(F,2)(p0,p1,p3,p4)); };
        static UnaryFunction<F,3> create(F f, TP0 p0,  TP1 p1,  TP2 p2,      _,  TP4 p4) { return UnaryFunction<F,3>(f,UFInitParams(F,3)(p0,p1,p2,p4)); };
        static UnaryFunction<F,4> create(F f, TP0 p0,  TP1 p1,  TP2 p2,  TP3 p3,      _) { return UnaryFunction<F,4>(f,UFInitParams(F,4)(p0,p1,p2,p3)); };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,0,TPS>& ufObj,TP0 p0) { return (p0.*(ufObj.m_f))(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4);     }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,2,TPS>& ufObj,TP2 p2) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,3,TPS>& ufObj,TP3 p3) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,p3,ufObj.m_Ps.m_p4);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,4,TPS>& ufObj,TP4 p4) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4,p4);   }
    };

    template<typename F> struct UnaryFunctionOperator<F,true,5>    //prototype : R (O::*)(P1,P2,P3,P4,P5)
    {
        typedef FPP(F,0)    TP0;
        typedef FPP(F,1)    TP1;
        typedef FPP(F,2)    TP2;
        typedef FPP(F,3)    TP3;
        typedef FPP(F,4)    TP4;
        typedef FPP(F,5)    TP5;
        static UnaryFunction<F,0> create(F f,     _,  TP1 p1,  TP2 p2,  TP3 p3,  TP4 p4,  TP5 p5) { return UnaryFunction<F,0>(f,UFInitParams(F,0)(p1,p2,p3,p4,p5)); };
        static UnaryFunction<F,1> create(F f, TP0 p0,      _,  TP2 p2,  TP3 p3,  TP4 p4,  TP5 p5) { return UnaryFunction<F,1>(f,UFInitParams(F,1)(p0,p2,p3,p4,p5)); };
        static UnaryFunction<F,2> create(F f, TP0 p0,  TP1 p1,      _,  TP3 p3,  TP4 p4,  TP5 p5) { return UnaryFunction<F,2>(f,UFInitParams(F,2)(p0,p1,p3,p4,p5)); };
        static UnaryFunction<F,3> create(F f, TP0 p0,  TP1 p1,  TP2 p2,      _,  TP4 p4,  TP5 p5) { return UnaryFunction<F,3>(f,UFInitParams(F,3)(p0,p1,p2,p4,p5)); };
        static UnaryFunction<F,4> create(F f, TP0 p0,  TP1 p1,  TP2 p2,  TP3 p3,      _,  TP5 p5) { return UnaryFunction<F,4>(f,UFInitParams(F,4)(p0,p1,p2,p3,p5)); };
        static UnaryFunction<F,5> create(F f, TP0 p0,  TP1 p1,  TP2 p2,  TP3 p3,  TP4 p4,      _) { return UnaryFunction<F,5>(f,UFInitParams(F,5)(p0,p1,p2,p3,p4)); };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,0,TPS>& ufObj,TP0 p0) { return (p0.*(ufObj.m_f))(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4,ufObj.m_Ps.m_p5);     }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4,ufObj.m_Ps.m_p5);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,2,TPS>& ufObj,TP2 p2) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4,ufObj.m_Ps.m_p5);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,3,TPS>& ufObj,TP3 p3) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,p3,ufObj.m_Ps.m_p4,ufObj.m_Ps.m_p5);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,4,TPS>& ufObj,TP4 p4) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4,p4,ufObj.m_Ps.m_p5);   }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,5,TPS>& ufObj,TP5 p5) { return ((ufObj.m_Ps.m_p1).*(ufObj.m_f))(ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4,ufObj.m_Ps.m_p5,p5);   }
    };

    //non-member function
    template<typename F> struct UnaryFunctionOperator<F,false,1>   //prototype : R (*)(P1)
    {
        typedef FPP(F,1)    TP1;                 

        static UnaryFunction<F,1> create(F f, _) { return UnaryFunction<F,1>(f,UFInitParams(F,1)()); };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1) { return (ufObj.m_f)(p1);      } 
    };

    template<typename F> struct UnaryFunctionOperator<F,false,2>   //prototype : R (*)(P1,P2)
    {
        typedef FPP(F,1)    TP1;
        typedef FPP(F,2)    TP2;                  

        static UnaryFunction<F,1> create(F f,      _,  TP2 p2) { return UnaryFunction<F,1>(f,UFInitParams(F,1)(p2)); };
        static UnaryFunction<F,2> create(F f,  TP1 p1,      _) { return UnaryFunction<F,2>(f,UFInitParams(F,2)(p1)); };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1) { return (ufObj.m_f)(p1,ufObj.m_Ps.m_p1);    }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,2,TPS>& ufObj,TP2 p2) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,p2);    }
    };

    template<typename F> struct UnaryFunctionOperator<F,false,3>   //prototype : R (*)(P1,P2,P3)
    {
        typedef FPP(F,1)    TP1;
        typedef FPP(F,2)    TP2;
        typedef FPP(F,3)    TP3;                   

        static UnaryFunction<F,1> create(F f,      _,  TP2 p2,  TP3 p3) { return UnaryFunction<F,1>(f,UFInitParams(F,1)(p2,p3));    };
        static UnaryFunction<F,2> create(F f,  TP1 p1,      _,  TP3 p3) { return UnaryFunction<F,2>(f,UFInitParams(F,2)(p1,p3));    };
        static UnaryFunction<F,3> create(F f,  TP1 p1,  TP2 p2,      _) { return UnaryFunction<F,3>(f,UFInitParams(F,3)(p1,p2));    };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1) { return (ufObj.m_f)(p1,ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2);    }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,2,TPS>& ufObj,TP2 p2) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,p2,ufObj.m_Ps.m_p2);    }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,3,TPS>& ufObj,TP3 p3) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,p3);    }
    };

    template<typename F> struct UnaryFunctionOperator<F,false,4>   //prototype : R (*)(P1,P2,P3,P4)
    {   
        typedef FPP(F,1)    TP1;
        typedef FPP(F,2)    TP2;
        typedef FPP(F,3)    TP3;
        typedef FPP(F,4)    TP4;                   

        static UnaryFunction<F,1> create(F f,      _,  TP2 p2,  TP3 p3,  TP4 p4) { return UnaryFunction<F,1>(f,UFInitParams(F,1)(p2,p3,p4));    };
        static UnaryFunction<F,2> create(F f,  TP1 p1,      _,  TP3 p3,  TP4 p4) { return UnaryFunction<F,2>(f,UFInitParams(F,2)(p1,p3,p4));    };
        static UnaryFunction<F,3> create(F f,  TP1 p1,  TP2 p2,      _,  TP4 p4) { return UnaryFunction<F,3>(f,UFInitParams(F,3)(p1,p2,p4));    };
        static UnaryFunction<F,4> create(F f,  TP1 p1,  TP2 p2,  TP3 p3,      _) { return UnaryFunction<F,4>(f,UFInitParams(F,4)(p1,p2,p3));    };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1) { return (ufObj.m_f)(p1,ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3);    }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,2,TPS>& ufObj,TP2 p2) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,p2,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3);    }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,3,TPS>& ufObj,TP3 p3) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,p3,ufObj.m_Ps.m_p3);    }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,4,TPS>& ufObj,TP4 p4) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,p4);    }
    };

    template<typename F> struct UnaryFunctionOperator<F,false,5>  //prototype : R (*)(P1,P2,P3,P4,P5)
    { 
        typedef FPP(F,1)    TP1;
        typedef FPP(F,2)    TP2;
        typedef FPP(F,3)    TP3;
        typedef FPP(F,4)    TP4;
        typedef FPP(F,5)    TP5;                    

        static UnaryFunction<F,1> create(F f,      _,  TP2 p2,  TP3 p3,  TP4 p4,  TP5 p5) { return UnaryFunction<F,1>(f,UFInitParams(F,1)(p2,p3,p4,p5)); };
        static UnaryFunction<F,2> create(F f,  TP1 p1,      _,  TP3 p3,  TP4 p4,  TP5 p5) { return UnaryFunction<F,2>(f,UFInitParams(F,2)(p1,p3,p4,p5)); };
        static UnaryFunction<F,3> create(F f,  TP1 p1,  TP2 p2,      _,  TP4 p4,  TP5 p5) { return UnaryFunction<F,3>(f,UFInitParams(F,3)(p1,p2,p4,p5)); };
        static UnaryFunction<F,4> create(F f,  TP1 p1,  TP2 p2,  TP3 p3,      _,  TP5 p5) { return UnaryFunction<F,4>(f,UFInitParams(F,4)(p1,p2,p3,p5)); };
        static UnaryFunction<F,5> create(F f,  TP1 p1,  TP2 p2,  TP3 p3,  TP4 p4,      _) { return UnaryFunction<F,5>(f,UFInitParams(F,5)(p1,p2,p3,p4)); };

        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,1,TPS>& ufObj,TP1 p1) { return (ufObj.m_f)(p1,ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4);      }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,2,TPS>& ufObj,TP2 p2) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,p2,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4);      }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,3,TPS>& ufObj,TP3 p3) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,p3,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4);      }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,4,TPS>& ufObj,TP4 p4) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,p4,ufObj.m_Ps.m_p4);      }
        template<typename TPS> static FR(F) ufCall(UnaryFunctionDirect<F,5,TPS>& ufObj,TP5 p5) { return (ufObj.m_f)(ufObj.m_Ps.m_p1,ufObj.m_Ps.m_p2,ufObj.m_Ps.m_p3,ufObj.m_Ps.m_p4,p5);      }
    }; 

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename F>            struct GetUFParamImpl;
    template<typename F,int Idx>    struct GetUFParamImpl<UnaryFunction<F,Idx> >: public Type2Type<typename UnaryFunction<F,Idx>::Param_T>{};
    template<typename R,typename P1>struct GetUFParamImpl<R (*)(P1)>            : public Type2Type<TPP(P1)>  {};
    template<typename R,typename O> struct GetUFParamImpl<R (O::*)()>           : public Type2Type<TPP(O)>   {};
    template<typename R,typename O> struct GetUFParamImpl<R (O::*)() const>     : public Type2Type<TPP(O)>   {};
}

#endif // UNARYFUNCTION_DETAIL_H__
