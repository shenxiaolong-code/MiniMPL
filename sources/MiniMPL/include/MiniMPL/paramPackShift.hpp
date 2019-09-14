#ifndef __PARAMPACKSHIFT_HPP__
#define __PARAMPACKSHIFT_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/paramPack.hpp>
#include <MiniMPL/sameQualifier.hpp>

namespace MiniMPL
{
    template<typename T>    struct TInsert;

    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6> 
    struct TInsert<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,NullType> >
    {
        template<typename T,unsigned>   struct apply;
        template<typename T> struct apply<T,1> : public Type2Type<ParamPackage<T,TP1,TP2,TP3,TP4,TP5,TP6> >{};
        template<typename T> struct apply<T,2> : public Type2Type<ParamPackage<TP1,T,TP2,TP3,TP4,TP5,TP6> >{};
        template<typename T> struct apply<T,3> : public Type2Type<ParamPackage<TP1,TP2,T,TP3,TP4,TP5,TP6> >{};
        template<typename T> struct apply<T,4> : public Type2Type<ParamPackage<TP1,TP2,TP3,T,TP4,TP5,TP6> >{};
        template<typename T> struct apply<T,5> : public Type2Type<ParamPackage<TP1,TP2,TP3,TP4,T,TP5,TP6> >{};
        template<typename T> struct apply<T,6> : public Type2Type<ParamPackage<TP1,TP2,TP3,TP4,TP5,T,TP6> >{};        
    };

    template<typename T>    struct TErase;
    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7> 
    struct TErase<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> >
    {
        template<unsigned>   struct apply;
        template<>  struct apply<1> : public Type2Type<ParamPackage<TP2,TP3,TP4,TP5,TP6,TP7>    >{};
        template<>  struct apply<2> : public Type2Type<ParamPackage<TP1,TP3,TP4,TP5,TP6,TP7>    >{};
        template<>  struct apply<3> : public Type2Type<ParamPackage<TP1,TP2,TP4,TP5,TP6,TP7>    >{};
        template<>  struct apply<4> : public Type2Type<ParamPackage<TP1,TP2,TP3,TP5,TP6,TP7>    >{};
        template<>  struct apply<5> : public Type2Type<ParamPackage<TP1,TP2,TP3,TP4,TP6,TP7>    >{};
        template<>  struct apply<6> : public Type2Type<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP7>    >{};        
    };

    template<typename T>    struct TReplace;
    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7> 
    struct TReplace<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> >
    {
        template<typename T,unsigned>   struct apply;
        template<typename T> struct apply<T,1> : public Type2Type<ParamPackage<T,TP2,TP3,TP4,TP5,TP6,TP7> >{};
        template<typename T> struct apply<T,2> : public Type2Type<ParamPackage<TP1,T,TP3,TP4,TP5,TP6,TP7> >{};
        template<typename T> struct apply<T,3> : public Type2Type<ParamPackage<TP1,TP2,T,TP4,TP5,TP6,TP7> >{};
        template<typename T> struct apply<T,4> : public Type2Type<ParamPackage<TP1,TP2,TP3,T,TP5,TP6,TP7> >{};
        template<typename T> struct apply<T,5> : public Type2Type<ParamPackage<TP1,TP2,TP3,TP4,T,TP6,TP7> >{};
        template<typename T> struct apply<T,6> : public Type2Type<ParamPackage<TP1,TP2,TP3,TP4,TP5,T,TP7> >{};        
    };

    //for non-build-in type,non-ref transfer will reduce efficiency.
    //so intermediate transfer can use ref , but final package use actual type -- consider object life cycle in multiple thread. 
    template<typename T>    struct TTransferPack;
    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7> 
    struct TTransferPack<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> >
    { 
    protected:
        template<typename TPS,unsigned idx> struct TReplaceAt   : TReplace<TPS>::template apply<typename RefAdapter<typename ParamPackageAt<TPS,idx>::type>::type,idx> {}; 
        template<typename TPS,unsigned idx> struct apply        : TReplaceAt<typename apply<TPS,idx-1>::type,idx> {}; 
        template<typename TPS>              struct apply<TPS,1> : TReplaceAt<TPS,1>{};

    public:
        typedef  ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7>                      TPack;
        typedef typename apply<TPack,ParamPackageSize<TPack>::value>::type      type;
    };

}


#endif // __PARAMPACKSHIFT_HPP__
