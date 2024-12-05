#ifndef __PLACEHOLDER_HPP__
#define __PLACEHOLDER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/kitType.hpp>

#if HAS_BOOST_SUPPORT==0
//Args is borrowed from Boost.MPL
//http://www.boost.org/doc/libs/1_55_0/libs/mpl/doc/index.html

namespace MiniMPL
{
    template<int N> struct Args;

    template<> struct Args<-1> {};
    typedef Args<-1>    _;
    extern  _           _$;

    template<> struct Args<1>
    {
        template<typename A1,typename A2=NullType,typename A3=NullType,typename A4=NullType,typename A5=NullType,typename A6=NullType>
        struct apply : Type2Type<A1> {};
    };
    typedef Args<1>  _1;

    template<> struct Args<2>
    {
        template<typename A1,typename A2,typename A3=NullType,typename A4=NullType,typename A5=NullType,typename A6=NullType>
        struct apply : Type2Type<A2> {};
    };
    typedef Args<2>     _2;  

    template<> struct Args<3>
    {
        template<typename A1,typename A2,typename A3,typename A4=NullType,typename A5=NullType,typename A6=NullType>
        struct apply : Type2Type<A3> {};
    };
    typedef Args<3>     _3; 

    template<> struct Args<4>
    {
        template<typename A1,typename A2,typename A3,typename A4,typename A5=NullType,typename A6=NullType>
        struct apply : Type2Type<A4> {};
    };
    typedef Args<4>     _4; 

    template<> struct Args<5>
    {
        template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6=NullType>
        struct apply : Type2Type<A5> {};
    };
    typedef Args<5>     _5; 

    template<> struct Args<6>
    {
        template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
        struct apply : Type2Type<A6> {};
    };
    typedef Args<6>     _6; 
}

#endif   //end of HAS_BOOST_SUPPORT

#endif // __PLACEHOLDER_HPP__
