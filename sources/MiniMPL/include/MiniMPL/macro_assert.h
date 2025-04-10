#ifndef __MACRO_ASSERT_H__
#define __MACRO_ASSERT_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/macro_traceLog.h>
#include <MiniMPL/platformEnv.h>

//////////////////////////////assert helper macro begin /////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
    #define Assert_Trigger()		_myProjectAssert()     //define _myProjectAssert in youre productSpecialDef.h
#else
    #if ENABLE_RELEASE_ASSERT
        #define Assert_Trigger()	outputTxt(TXT("Assert event!"))
    #else
        #define Assert_Trigger()    0
    #endif
#endif

#define UtilCondition(X)			!!(X)
#define PrefixAssert				TXT("\n[Assert]\t")

#define AssertXI(X,Info)			(void)(UtilCondition(X) || ( outputTxt(PrefixAssert),outputTxtV Info , ALWAYS_LOG_HERE(),Assert_Trigger() , 0 ) )
#define AssertX(X)					AssertXI(X,(MAKESTR(X)))
#define AssertP(P)					AssertXI(P,(TXT("NULL Pointer: ") MAKESTR(P)))
#define AssertB(B)					AssertXI(B,(TXT("Value 0: ") MAKESTR(B)))
#define Assertb(b)					AssertXI(b,(TXT("false: ") MAKESTR(b)))

#define PrefixException				TXT("\n[Exception]\t")
#define ChkExceptionThrow()			throw 1

#define ChkExceptionInfo(X,Info)	(void)( UtilCondition(X) || ( outputTxt(PrefixException),outputTxtV Info , ALWAYS_LOG_HERE(),ChkExceptionThrow(), 0) )
#define ChkExceptionX(X)			ChkExceptionInfo(X,(MAKESTR(X)))
#define ChkExceptionP(P)			ChkExceptionInfo(P,(TXT("NULL Pointer: ") MAKESTR(P)))
#define ChkExceptionB(B)			ChkExceptionInfo(B,(TXT("Value 0: ") MAKESTR(B)))
#define ChkExceptionb(b)			ChkExceptionInfo(b,(TXT("false: ") MAKESTR(b)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ASSERT_AND_LOG_INFO(X,Y)    AssertXI(X,Y)
#define ASSERT_AND_LOG(X)			ASSERT_AND_LOG_INFO(X,(MAKESTR(X)))

//////////////////////////////////////////////static assert begin///////////////////////////////////////////////////////
// show the real number or type when static_assert fails
#if CPP17_ENABLED
    template<auto v>                        struct debug_number ;               // auto need C++ 17 . g++ -std=c++17 ...
    #define show_number( v )                { using vHelper = typename debug_number< v >::type ; }
    #define static_assert_number( b , v )   if constexpr (!( b )) {  using vHelper = typename debug_number< v >::type ; }
#endif
template<typename T>                        struct debug_type;
#define show_type(   v )                    { using tHelper = typename debug_type< v >::type ;   }
#define static_assert_type(   b , v )       if constexpr (!( b )) {  using tHelper = typename debug_type< v >::type   ; }    

#define ENABLEFUNC_IF(X)    char(*)[(X)]=0      //sfinae rule :"Substitution Failure Is Not An Error". std::enable_if_t needs C++14
#define ENABLE_IF           ENABLEFUNC_IF
#define ENABLEFUNC_NOT(X)   ENABLEFUNC_IF(0==(X))
#define ENABLE_NOT          ENABLEFUNC_NOT

//CPP11 static_assert doesn't support property<T>::value assert.
#if ENABLE_STATIC_ASSERT_NEED_COMPLETE_TYPE
        template<bool> struct static_assert_failure;
        template<>     struct static_assert_failure<true>{};
        #define Static_Assert(b) typedef static_assert_failure<sizeof(static_assert_failure<(bool)(b)>)> static_assert_type_dummy;
#else
        #define Static_Assert(b) typedef char(*MAKEVAR2(static_assert_failure,UNIQUEID))[(bool)(b)==true] ;   //fix multiple Static_Assert re-definition issue in same scope
#endif


//////////////////////////////////////////////static assert end///////////////////////////////////////////////////////
//////////////////////////////assert helper macro end /////////////////////////////////////////////////////////////////

//////////////////////////////check-return helper macro begin //////////////////////////////////////////////////////////
#define CHECK_EQUAL_ELSE_ASSERT_RETURN_VAL(Val,Ref,Ret,Txt)     \
{                                                               \
    if(!((Val)!=(Ref)))                                         \
    {                                                           \
        AssertXI(false,(Txt));			                        \
        return Ret;                                             \
    }                                                           \
}

#define CHECK_TRUE_ELSE_RETURN_VAL(Exp,Ret)     CHECK_EQUAL_ELSE_ASSERT_RETURN_VAL(Exp,false,Ret,MAKESTR(Exp))
#define CHECK_NULL_ELSE_RETURN_VAL(Exp,Ret)     CHECK_EQUAL_ELSE_ASSERT_RETURN_VAL(Exp,NULL ,Ret,MAKESTR(Exp))

//////////////////////////////check-return helper macro end ////////////////////////////////////////////////////////////

#endif // __MACRO_ASSERT_H__
