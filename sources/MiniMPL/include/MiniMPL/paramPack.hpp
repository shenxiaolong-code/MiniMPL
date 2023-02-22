#ifndef __PARAMPACK_HPP__
#define __PARAMPACK_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/placeHolder.hpp>

namespace MiniMPL
{
	//refer to std::tuple in cpp11, here is cpp03 implement
    //Max support 6 parameters.
    template<typename TP1=NullType,typename TP2=NullType,typename TP3=NullType,typename TP4=NullType,typename TP5=NullType,typename TP6=NullType,typename TP7=NullType> 
    struct ParamPackage;

	//for std::tuple in cpp11, std::tuple_size  is available
    template<typename T>    struct ParamPackageSize;
    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7> 
    struct ParamPackageSize<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> > : public Int2Type<1+ParamPackageSize<ParamPackage<TP2,TP3,TP4,TP5,TP6,TP7> >::value>{};
    template<> struct ParamPackageSize<ParamPackage<NullType,NullType,NullType,NullType,NullType,NullType,NullType> > : public Int2Type<0> {};

	//for std::tuple in cpp11, std.tuple_element  is available
    template<typename T,unsigned Idx>    struct ParamPackageAt;
    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7,unsigned Idx> 
    struct ParamPackageAt<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7>,Idx > : public Args<Idx>::template apply<TP1,TP2,TP3,TP4,TP5,TP6> {};

    template<typename T> struct IsParamPackage : public FalseType{};
    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7> 
    struct IsParamPackage<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> > : public TrueType{};

#if CPP11_ENABLED
    // Get Nth formal parameters type, Nth begin from 0 , need Cpp11 support
    template<typename T>                                            struct getFormalParamterType ;
    template <class... TArgs , template< class ... > class T >      struct getFormalParamterType< T <TArgs ...> > 
    {
        template<unsigned Nth>                                      struct apply : public std::tuple_element<Nth, std::tuple<TArgs ...> > {} ;
    };
    template<typename T , unsigned Nth> 
    using getFormalParamterType_t=typename getFormalParamterType<T>::template apply<Nth> ;
#endif

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<> 
    struct ParamPackage<>
    {
    };

#pragma warning(push)
#pragma warning(disable:4505)
    static ParamPackage<> makeParamPackage_Ref()
    {
        return ParamPackage<>();
    }
#pragma warning(pop)

    template<typename TP1> struct ParamPackage<TP1> : public ParamPackage<>
    {
        ParamPackage(TP1 p1) : m_p1(p1){};
        TP1     m_p1;
    };

    template<typename TP1,typename TP2> struct ParamPackage<TP1,TP2> : public ParamPackage<TP1>
    {
        ParamPackage(TP1 p1,TP2 p2) : ParamPackage<TP1>(p1) , m_p2(p2){};
        TP2     m_p2;
    };

    template<typename TP1,typename TP2,typename TP3> struct ParamPackage<TP1,TP2,TP3> : public ParamPackage<TP1,TP2>
    {
        ParamPackage(TP1 p1,TP2 p2,TP3 p3) : ParamPackage<TP1,TP2>(p1,p2) , m_p3(p3){};
        TP3     m_p3;
    };

    template<typename TP1,typename TP2,typename TP3,typename TP4> struct ParamPackage<TP1,TP2,TP3,TP4> : public ParamPackage<TP1,TP2,TP3>
    {
        ParamPackage(TP1 p1,TP2 p2,TP3 p3,TP4 p4) : ParamPackage<TP1,TP2,TP3>(p1,p2,p3) , m_p4(p4){};
        TP4     m_p4;
    };

    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5> struct ParamPackage<TP1,TP2,TP3,TP4,TP5> : public ParamPackage<TP1,TP2,TP3,TP4>
    {
        ParamPackage(TP1 p1,TP2 p2,TP3 p3,TP4 p4,TP5 p5) : ParamPackage<TP1,TP2,TP3,TP4>(p1,p2,p3,p4) , m_p5(p5){};
        TP5     m_p5;
    };

    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6> struct ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6> : public ParamPackage<TP1,TP2,TP3,TP4,TP5>
    {
        ParamPackage(TP1 p1,TP2 p2,TP3 p3,TP4 p4,TP5 p5,TP6 p6) : ParamPackage<TP1,TP2,TP3,TP4,TP5>(p1,p2,p3,p4,p5) , m_p6(p6){};
        TP6     m_p6;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    note : makeParamPackage_Ref
    make parameter package whose parameters are reference, need to take care of parameter's life cycle
    if parameter needn't reference, use ParamPackage<TP1,TP2,...>(p1,p2,...) directly to create parameter package
    or use ParamPackage<TP1,TP2&,TP3,...>(p1,p2,p3...) to specify ref/non-ref for every parameter.
    */
    template<typename TP1>
    inline ParamPackage<TP1&> makeParamPackage_Ref(TP1& p1)
    {
        return ParamPackage<TP1&>(p1);
    }

    template<typename TP1,typename TP2>
    inline ParamPackage<TP1&,TP2&> makeParamPackage_Ref(TP1& p1,TP2& p2)
    {
        return ParamPackage<TP1&,TP2&>(p1,p2);
    }

    template<typename TP1,typename TP2,typename TP3>
    inline ParamPackage<TP1&,TP2&,TP3&> makeParamPackage_Ref(TP1& p1,TP2& p2,TP3& p3)
    {
        return ParamPackage<TP1&,TP2&,TP3&>(p1,p2,p3);
    }

    template<typename TP1,typename TP2,typename TP3,typename TP4>
    inline ParamPackage<TP1&,TP2&,TP3&,TP4&> makeParamPackage_Ref(TP1& p1,TP2& p2,TP3& p3,TP4& p4)
    {
        return ParamPackage<TP1&,TP2&,TP3&,TP4&>(p1,p2,p3,p4);
    }

    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5>
    inline ParamPackage<TP1&,TP2&,TP3&,TP4&,TP5&> makeParamPackage_Ref(TP1& p1,TP2& p2,TP3& p3,TP4& p4,TP5& p5)
    {
        return ParamPackage<TP1&,TP2&,TP3&,TP4&,TP5&>(p1,p2,p3,p4,p5);
    }

    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6>
    inline ParamPackage<TP1&,TP2&,TP3&,TP4&,TP5&,TP6&> makeParamPackage_Ref(TP1& p1,TP2& p2,TP3& p3,TP4& p4,TP5& p5,TP6& p6)
    {
        return ParamPackage<TP1&,TP2&,TP3&,TP4&,TP5&,TP6&>(p1,p2,p3,p4,p5,p6);
    }

#if CPP11_ENABLED
	template<typename... TArgs>
	struct ParamPackage11 : std::tuple<TArgs...> 
	{
		ParamPackage11(TArgs... args) : std::tuple<TArgs...>(args...) {};
	};

#endif

}


#endif // __PARAMPACK_HPP__
