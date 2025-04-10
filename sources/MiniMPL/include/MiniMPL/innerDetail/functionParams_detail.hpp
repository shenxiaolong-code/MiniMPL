#ifndef FUNCTIONPARAMS_DETAIL_H__
#define FUNCTIONPARAMS_DETAIL_H__

/***********************************************************************************************************************
Description         : 
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/paramPack.hpp>
#include <MiniMPL/paramPackShift.hpp>

namespace MiniMPL
{
    namespace InnerDetail
    {
        template<typename R,typename Params>
        struct FunctionParamsPack
        {
            typedef Params          Params_T;
            typedef R               Return_T;       
        };

        template<typename R,typename O,typename Params>
        struct MemFunctionParamsImpl : public FunctionParamsPack<R,Params>
        {
            typedef O               Object_T;
        };

///////////////////////////////////////////GetFunctionParam Impl//////////////////////////////////////////////////////////////////////////////
        template<typename R> struct FunctionParamsImpl; //3 style : function pointer / function reference / function 

        //default __cdecl calling convention
        template<typename R> struct FunctionParamsImpl<R (*)()> : public FunctionParamsPack<R,ParamPackage<> >    { };
        template<typename R> struct FunctionParamsImpl<R (&)()> : public FunctionParamsPack<R,ParamPackage<> >    { };
        template<typename R> struct FunctionParamsImpl<R    ()> : public FunctionParamsPack<R,ParamPackage<> >    { };

        template<typename R,typename P1> struct FunctionParamsImpl<R (*)(P1)> : public FunctionParamsPack<R,ParamPackage<P1> >    { };
        template<typename R,typename P1> struct FunctionParamsImpl<R (&)(P1)> : public FunctionParamsPack<R,ParamPackage<P1> >    { };
        template<typename R,typename P1> struct FunctionParamsImpl<R    (P1)> : public FunctionParamsPack<R,ParamPackage<P1> >    { };

        template<typename R,typename P1,typename P2> struct FunctionParamsImpl<R (*)(P1,P2)> : public FunctionParamsPack<R,ParamPackage<P1,P2> >    { };
        template<typename R,typename P1,typename P2> struct FunctionParamsImpl<R (&)(P1,P2)> : public FunctionParamsPack<R,ParamPackage<P1,P2> >    { };
        template<typename R,typename P1,typename P2> struct FunctionParamsImpl<R    (P1,P2)> : public FunctionParamsPack<R,ParamPackage<P1,P2> >    { };

        template<typename R,typename P1,typename P2,typename P3> struct FunctionParamsImpl<R (*)(P1,P2,P3)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3> >    { };
        template<typename R,typename P1,typename P2,typename P3> struct FunctionParamsImpl<R (&)(P1,P2,P3)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3> >    { };
        template<typename R,typename P1,typename P2,typename P3> struct FunctionParamsImpl<R    (P1,P2,P3)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3> >    { };

        template<typename R,typename P1,typename P2,typename P3,typename P4> struct FunctionParamsImpl<R (*)(P1,P2,P3,P4)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4> >    { };
        template<typename R,typename P1,typename P2,typename P3,typename P4> struct FunctionParamsImpl<R (&)(P1,P2,P3,P4)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4> >    { };
        template<typename R,typename P1,typename P2,typename P3,typename P4> struct FunctionParamsImpl<R    (P1,P2,P3,P4)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4> >    { };

        template<typename R,typename P1,typename P2,typename P3,typename P4,typename P5> struct FunctionParamsImpl<R (*)(P1,P2,P3,P4,P5)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4,P5> >    { };
        template<typename R,typename P1,typename P2,typename P3,typename P4,typename P5> struct FunctionParamsImpl<R (&)(P1,P2,P3,P4,P5)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4,P5> >    { };
        template<typename R,typename P1,typename P2,typename P3,typename P4,typename P5> struct FunctionParamsImpl<R    (P1,P2,P3,P4,P5)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4,P5> >    { };

        //__stdcall calling convention
#if defined(_MSC_VER) && !defined(UNDER_CE)
        /* WinCE doesn't differ __stdcall and __cdecl (__stdcall is MS spec), see windef.h
        #ifdef UNDER_CE
        #define __stdcall __cdecl	// Note this doesn't match the desktop definition
        #define _stdcall __cdecl	// Note this doesn't match the desktop definition
        #endif
        */
        template<typename R> struct FunctionParamsImpl<R (__stdcall *)()> : public FunctionParamsPack<R,ParamPackage<> >    { };
        template<typename R> struct FunctionParamsImpl<R (__stdcall &)()> : public FunctionParamsPack<R,ParamPackage<> >    { };
        template<typename R> struct FunctionParamsImpl<R  __stdcall   ()> : public FunctionParamsPack<R,ParamPackage<> >    { };

        template<typename R,typename P1> struct FunctionParamsImpl<R (__stdcall *)(P1)> : public FunctionParamsPack<R,ParamPackage<P1> >    { };
        template<typename R,typename P1> struct FunctionParamsImpl<R (__stdcall &)(P1)> : public FunctionParamsPack<R,ParamPackage<P1> >    { };
        template<typename R,typename P1> struct FunctionParamsImpl<R  __stdcall   (P1)> : public FunctionParamsPack<R,ParamPackage<P1> >    { };

        template<typename R,typename P1,typename P2> struct FunctionParamsImpl<R (__stdcall *)(P1,P2)> : public FunctionParamsPack<R,ParamPackage<P1,P2> >    { };
        template<typename R,typename P1,typename P2> struct FunctionParamsImpl<R (__stdcall &)(P1,P2)> : public FunctionParamsPack<R,ParamPackage<P1,P2> >    { };
        template<typename R,typename P1,typename P2> struct FunctionParamsImpl<R  __stdcall   (P1,P2)> : public FunctionParamsPack<R,ParamPackage<P1,P2> >    { };

        template<typename R,typename P1,typename P2,typename P3> struct FunctionParamsImpl<R (__stdcall *)(P1,P2,P3)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3> >    { };
        template<typename R,typename P1,typename P2,typename P3> struct FunctionParamsImpl<R (__stdcall &)(P1,P2,P3)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3> >    { };
        template<typename R,typename P1,typename P2,typename P3> struct FunctionParamsImpl<R  __stdcall   (P1,P2,P3)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3> >    { };

        template<typename R,typename P1,typename P2,typename P3,typename P4> struct FunctionParamsImpl<R (__stdcall *)(P1,P2,P3,P4)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4> >    { };
        template<typename R,typename P1,typename P2,typename P3,typename P4> struct FunctionParamsImpl<R (__stdcall &)(P1,P2,P3,P4)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4> >    { };
        template<typename R,typename P1,typename P2,typename P3,typename P4> struct FunctionParamsImpl<R  __stdcall   (P1,P2,P3,P4)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4> >    { };

        template<typename R,typename P1,typename P2,typename P3,typename P4,typename P5> struct FunctionParamsImpl<R (__stdcall *)(P1,P2,P3,P4,P5)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4,P5> >    { };
        template<typename R,typename P1,typename P2,typename P3,typename P4,typename P5> struct FunctionParamsImpl<R (__stdcall &)(P1,P2,P3,P4,P5)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4,P5> >    { };
        template<typename R,typename P1,typename P2,typename P3,typename P4,typename P5> struct FunctionParamsImpl<R  __stdcall   (P1,P2,P3,P4,P5)> : public FunctionParamsPack<R,ParamPackage<P1,P2,P3,P4,P5> >    { };
#endif // defined(_MSC_VER) && !defined(UNDER_CE)

        //this calling convention ,NO reference-to-member-function in C++
        template<typename R,typename O> struct FunctionParamsImpl<R (O::*)()> : public MemFunctionParamsImpl<R,O,ParamPackage<> >    { };
        template<typename R,typename O,typename P1> struct FunctionParamsImpl<R (O::*)(P1)> : public MemFunctionParamsImpl<R,O,ParamPackage<P1> >    { };
        template<typename R,typename O,typename P1,typename P2> struct FunctionParamsImpl<R (O::*)(P1,P2)> : public MemFunctionParamsImpl<R,O,ParamPackage<P1,P2> >    { };
        template<typename R,typename O,typename P1,typename P2,typename P3> struct FunctionParamsImpl<R (O::*)(P1,P2,P3)> : public MemFunctionParamsImpl<R,O,ParamPackage<P1,P2,P3> >    { };
        template<typename R,typename O,typename P1,typename P2,typename P3,typename P4> struct FunctionParamsImpl<R (O::*)(P1,P2,P3,P4)> : public MemFunctionParamsImpl<R,O,ParamPackage<P1,P2,P3,P4> >    { };
        template<typename R,typename O,typename P1,typename P2,typename P3,typename P4,typename P5> struct FunctionParamsImpl<R (O::*)(P1,P2,P3,P4,P5)> : public MemFunctionParamsImpl<R,O,ParamPackage<P1,P2,P3,P4,P5> >    { };

        template<typename R,typename O> struct FunctionParamsImpl<R (O::*)() const> : public MemFunctionParamsImpl<R,O const,ParamPackage<> >    { };
        template<typename R,typename O,typename P1> struct FunctionParamsImpl<R (O::*)(P1) const> : public MemFunctionParamsImpl<R,O const,ParamPackage<P1> >    { };
        template<typename R,typename O,typename P1,typename P2> struct FunctionParamsImpl<R (O::*)(P1,P2) const> : public MemFunctionParamsImpl<R,O const,ParamPackage<P1,P2> >    { };
        template<typename R,typename O,typename P1,typename P2,typename P3> struct FunctionParamsImpl<R (O::*)(P1,P2,P3) const> : public MemFunctionParamsImpl<R,O const,ParamPackage<P1,P2,P3> >    { };
        template<typename R,typename O,typename P1,typename P2,typename P3,typename P4> struct FunctionParamsImpl<R (O::*)(P1,P2,P3,P4) const> : public MemFunctionParamsImpl<R,O const,ParamPackage<P1,P2,P3,P4> >    { };
        template<typename R,typename O,typename P1,typename P2,typename P3,typename P4,typename P5> struct FunctionParamsImpl<R (O::*)(P1,P2,P3,P4,P5) const> : public MemFunctionParamsImpl<R,O const,ParamPackage<P1,P2,P3,P4,P5> >    { };
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    namespace InnerDetail
    {  
        template<typename TPack,typename TF,bool bMF=IsMemberFunctionPointer<TF>::value> 
        struct TAddTClassToPackImpl: TInsert<TPack>::template apply<typename AddRef<typename FunctionParamsImpl<TF>::Object_T>::type,1> {};
        template<typename TPack,typename TF> 
        struct TAddTClassToPackImpl<TPack,TF,false> : Type2Type<TPack> {Static_Assert(IsFunctionPointer<TF>::value)}; 
    }
}

#endif // FUNCTIONPARAMS_DETAIL_H__
