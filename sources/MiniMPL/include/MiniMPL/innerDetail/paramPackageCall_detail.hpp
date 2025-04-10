#ifndef PARAMPACKAGECALL_DETAIL_H__
#define PARAMPACKAGECALL_DETAIL_H__

/***********************************************************************************************************************
Description         : implement detail of <MiniMPL/paramPackageCall.hpp>
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/paramPack.hpp>
#include <MiniMPL/isXXXEx.hpp>
#include <MiniMPL/functionParams.hpp>
#include <MiniMPL/pointer2value.hpp>
#include <MiniMPL/paramPackShift.hpp>

#define _tagF(X)    ENABLE_IF(MiniMPL::IsFunctionPointer< X >::value)
#define _tagMF(X)   ENABLE_IF((MiniMPL::IsMemberFunctionPointer< X >::value))

namespace MiniMPL
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename TP1=NullType,typename TP2=NullType,typename TP3=NullType,typename TP4=NullType,typename TP5=NullType,typename TP6=NullType,typename TP7=NullType> 
    struct ParamPackageCall;

    //resolve issue : const member function causes all data members of non-const struct are const.
    //support non-const data member in const struct and use data member's raw const qualifier, RC : remove const
#define RC  const_cast<ParamPackageCall&>(*this)    

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<> 
    struct ParamPackageCall<> : public ParamPackage<>
    {
        template<typename TF>    FR(TF) packCall(TF  f, _tagF(TF)   )   const {   return  f();    }
        template<typename T>     T*     newObject()                     const {   return new T(); }
    };

    template<typename TP1> struct ParamPackageCall<TP1> : public ParamPackage<TP1>
    {
        ParamPackageCall(TP1 p1) : ParamPackage(p1){};

        template<typename TF>    FR(TF) packCall(TF  f, _tagF(TF)   ) const {   return  f(RC.m_p1);                        }
        template<typename TF>    FR(TF) packCall(TF  f, _tagMF(TF)  ) const {   return  (Get::finalValue(RC.m_p1).*f)();   }

        template<typename T>     T*     newObject()                   const {   return new T(RC.m_p1);                     }
    };

    template<typename TP1,typename TP2> struct ParamPackageCall<TP1,TP2> : public ParamPackage<TP1,TP2>
    {
        ParamPackageCall(TP1 p1,TP2 p2) : ParamPackage(p1,p2){};

        template<typename TF>   FR(TF)  packCall(TF  f, _tagF(TF)   ) const {   return  f(RC.m_p1,RC.m_p2);                       }
        template<typename TF>   FR(TF)  packCall(TF  f, _tagMF(TF)  ) const {   return  (Get::finalValue(RC.m_p1).*f)(RC.m_p2);   } 

        template<typename T>     T*     newObject()                   const {   return new T(RC.m_p1,RC.m_p2);                    }
    };

    template<typename TP1,typename TP2,typename TP3> struct ParamPackageCall<TP1,TP2,TP3> : public ParamPackage<TP1,TP2,TP3>
    {
        ParamPackageCall(TP1 p1,TP2 p2,TP3 p3) : ParamPackage(p1,p2,p3){};

        template<typename TF>    FR(TF) packCall(TF  f, _tagF(TF)   ) const {   return  f(RC.m_p1,RC.m_p2,RC.m_p3);                      }
        template<typename TF>    FR(TF) packCall(TF  f, _tagMF(TF)  ) const {   return  (Get::finalValue(RC.m_p1).*f)(RC.m_p2,RC.m_p3);  }

        template<typename T>     T*     newObject()               const {   return new T(RC.m_p1,RC.m_p2,RC.m_p3);                   }
    };

    template<typename TP1,typename TP2,typename TP3,typename TP4> struct ParamPackageCall<TP1,TP2,TP3,TP4> : public ParamPackage<TP1,TP2,TP3,TP4>
    {
        ParamPackageCall(TP1 p1,TP2 p2,TP3 p3,TP4 p4) : ParamPackage(p1,p2,p3,p4){};

        template<typename TF>    FR(TF) packCall(TF  f, _tagF(TF)   ) const {   return  f(RC.m_p1,RC.m_p2,RC.m_p3,RC.m_p4);                     }
        template<typename TF>    FR(TF) packCall(TF  f, _tagMF(TF)  ) const {   return  (Get::finalValue(RC.m_p1).*f)(RC.m_p2,RC.m_p3,RC.m_p4); }

        template<typename T>     T*     newObject()               const {   return new T(RC.m_p1,RC.m_p2,RC.m_p3,RC.m_p4);                  }
    };

    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> struct ParamPackageCall<TP1,TP2,TP3,TP4,TP5> : public ParamPackage<TP1,TP2,TP3,TP4,TP5>
    {
        ParamPackageCall(TP1 p1,TP2 p2,TP3 p3,TP4 p4,TP5 p5) : ParamPackage(p1,p2,p3,p4,p5){};

        template<typename TF>    FR(TF) packCall(TF  f, _tagF(TF)   ) const {   return  f(RC.m_p1,RC.m_p2,RC.m_p3,RC.m_p4,RC.m_p5);                    }
        template<typename TF>    FR(TF) packCall(TF  f, _tagMF(TF)  ) const {   return  (Get::finalValue(RC.m_p1).*f)(RC.m_p2,RC.m_p3,RC.m_p4,RC.m_p5);}

        template<typename T>     T*     newObject()               const {   return new T(RC.m_p1,RC.m_p2,RC.m_p3,RC.m_p4,RC.m_p5);                 }
    };

    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6> struct ParamPackageCall<TP1,TP2,TP3,TP4,TP5,TP6> : public ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6>
    {
        ParamPackageCall(TP1 p1,TP2 p2,TP3 p3,TP4 p4,TP5 p5,TP5 p6) : ParamPackage(p1,p2,p3,p4,p5,p6){};

        template<typename TF>    FR(TF) packCall(TF  f, _tagF(TF)   ) const {   return  f(RC.m_p1,RC.m_p2,RC.m_p3,RC.m_p4,RC.m_p5,RC.m_p6);                       }
        template<typename TF>    FR(TF) packCall(TF  f, _tagMF(TF)  ) const {   return  (Get::finalValue(RC.m_p1).*f)(RC.m_p2,RC.m_p3,RC.m_p4,RC.m_p5,RC.m_p6);   }

        template<typename T>     T*     newObject()               const {   return new T(RC.m_p1,RC.m_p2,RC.m_p3,RC.m_p4,RC.m_p5,RC.m_p6);                    }
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    namespace InnerDetail
    {  
        template<typename T> struct FromParamPack;
        template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7>
        struct FromParamPack< ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> > 
            : public Type2Type<ParamPackageCall<TP1,TP2,TP3,TP4,TP5,TP6,TP7> > {};

        template<typename TF> 
        struct TPackCallParamsImpl : public FromParamPack<typename TAddTClassToPack<TF>::type>{};
        template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7>
        struct TPackCallParamsImpl< ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> > 
            : public FromParamPack< ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> > {};

        template<typename T> struct IsPack                              : public FalseType {};
        template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7>
        struct IsPack< ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> >      : public TrueType {};
        template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7>
        struct IsPack< ParamPackageCall<TP1,TP2,TP3,TP4,TP5,TP6,TP7> >  : public TrueType {};
    }
}

#endif // PARAMPACKAGECALL_DETAIL_H__
