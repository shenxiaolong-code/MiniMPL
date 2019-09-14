#ifndef ISFUNCPOINTER_DETAIL_H__
#define ISFUNCPOINTER_DETAIL_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	implement 
*************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/kitType.hpp>

namespace MiniMPL
{
#if HAS_BOOST_SUPPORT==0
    //only max support 5 parameter
    template<typename T>    struct FunctionPointerTester : FalseType {};
    template<typename R>    struct FunctionPointerTester<R (*)()>      : TrueType {};
    template<typename R>    struct FunctionPointerTester<R (*)(...)>   : TrueType {};
    template<typename R,typename P1> struct FunctionPointerTester<R (*)(P1)>       : TrueType {};
    template<typename R,typename P1> struct FunctionPointerTester<R (*)(P1,...)>   : TrueType {};
    template<typename R,typename P1,typename P2>    struct FunctionPointerTester<R (*)(P1,P2)>     : TrueType {};
    template<typename R,typename P1,typename P2>    struct FunctionPointerTester<R (*)(P1,P2,...)> : TrueType {};
    template<typename R,typename P1,typename P2,typename P3>    struct FunctionPointerTester<R (*)(P1,P2,P3)>      : TrueType {};
    template<typename R,typename P1,typename P2,typename P3>    struct FunctionPointerTester<R (*)(P1,P2,P3,...)>  : TrueType {};
    template<typename R,typename P1,typename P2,typename P3,typename P4>    struct FunctionPointerTester<R (*)(P1,P2,P3,P4)>       : TrueType {};
    template<typename R,typename P1,typename P2,typename P3,typename P4>    struct FunctionPointerTester<R (*)(P1,P2,P3,P4,...)>   : TrueType {};
    template<typename R,typename P1,typename P2,typename P3,typename P4,typename P5>    struct FunctionPointerTester<R (*)(P1,P2,P3,P4,P5)>       : TrueType {};
    template<typename R,typename P1,typename P2,typename P3,typename P4,typename P5>    struct FunctionPointerTester<R (*)(P1,P2,P3,P4,P5,...)>   : TrueType {};

    template<typename T>    struct MemberFunctionPointerTester : FalseType {};
    template<typename R,typename O>    struct MemberFunctionPointerTester<R (O::*)()>      : TrueType {};
    template<typename R,typename O>    struct MemberFunctionPointerTester<R (O::*)(...)>   : TrueType {};
    template<typename R,typename O,typename P1> struct MemberFunctionPointerTester<R (O::*)(P1)>       : TrueType {};
    template<typename R,typename O,typename P1> struct MemberFunctionPointerTester<R (O::*)(P1,...)>   : TrueType {};
    template<typename R,typename O,typename P1,typename P2>    struct MemberFunctionPointerTester<R (O::*)(P1,P2)>     : TrueType {};
    template<typename R,typename O,typename P1,typename P2>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,...)> : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3)>      : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,...)>  : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3,typename P4>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,P4)>       : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3,typename P4>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,P4,...)>   : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3,typename P4,typename P5>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,P4,P5)>       : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3,typename P4,typename P5>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,P4,P5,...)>   : TrueType {};

    template<typename R,typename O>    struct MemberFunctionPointerTester<R (O::*)() const>      : TrueType {};
    template<typename R,typename O>    struct MemberFunctionPointerTester<R (O::*)(...) const>   : TrueType {};
    template<typename R,typename O,typename P1> struct MemberFunctionPointerTester<R (O::*)(P1) const>       : TrueType {};
    template<typename R,typename O,typename P1> struct MemberFunctionPointerTester<R (O::*)(P1,...) const>   : TrueType {};
    template<typename R,typename O,typename P1,typename P2>    struct MemberFunctionPointerTester<R (O::*)(P1,P2) const>     : TrueType {};
    template<typename R,typename O,typename P1,typename P2>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,...) const> : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3) const>      : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,...) const>  : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3,typename P4>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,P4) const>       : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3,typename P4>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,P4,...) const>   : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3,typename P4,typename P5>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,P4,P5) const>       : TrueType {};
    template<typename R,typename O,typename P1,typename P2,typename P3,typename P4,typename P5>    struct MemberFunctionPointerTester<R (O::*)(P1,P2,P3,P4,P5,...) const>   : TrueType {};
#endif
}

#endif // ISFUNCPOINTER_DETAIL_H__
