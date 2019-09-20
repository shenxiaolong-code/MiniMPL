#ifndef MACRO_MAKEVAR_H__
#define MACRO_MAKEVAR_H__
/************************************************************************************
author  :	Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
purpose :	macro to make variable name by function style
*************************************************************************************/
#include <MiniMPL/innerDetail/macro_traitimpl.hpp>
#include <memory>

#if defined(_MSC_VER)
    #define UNIQUEID			__COUNTER__
#else
    #define UNIQUEID			__LINE__
#endif

//make variable name
#define __MAKEVAR(X,Y)          X##Y
#define MAKEVAR(X,Y)            __MAKEVAR(X,Y)
#define MAKEVAR2(X,Y)           MAKEVAR(X,Y)
#define MAKEVAR3(X,Y,Z)         MAKEVAR(X,MAKEVAR(Y,Z))

//////////////////////////////////////////////////////////////////////////
//simply & unified std type declare
#define DECLARE_PTR(x)				typedef STDTRNS::shared_ptr<x>			x##Ptr
#define DECLARE_WPTR(x)				typedef STDTRNS::weak_ptr<x>			x##Wptr
#define DECLARE_PTRS(x)				DECLARE_PTR(x);									\
									DECLARE_WPTR(x)
#define DECLARE_PTRS_STRUCT(x)		struct x;										\
									DECLARE_PTRS(x)
#define DECLARE_PTRS_CLASS(x)		class x;										\
									DECLARE_PTRS(x)

//type defined in namespace field
#define DECLARE_PTR_NS(N,x)			typedef STDTRNS::shared_ptr<N::##x>		x##Ptr
#define DECLARE_WPTR_NS(N,x)		typedef STDTRNS::weak_ptr<N::##x>		x##Wptr
#define DECLARE_PTRS_NS(N,x)		DECLARE_PTR_NS(N,x);							\
									DECLARE_WPTR_NS(N,x)
#define DECLARE_PTRS_STRUCT_NS(N,x)	namespace N {		struct x;		}			\
									DECLARE_PTRS_NS(N,x)
#define DECLARE_PTRS_CLASS_NS(N,x)	namespace N {		class x;		}			\
									DECLARE_PTRS_NS(N,x)
//////////////////////////////////////////////////////////////////////////

#endif // MACRO_MAKEVAR_H__
