#ifndef __PLATFORMENV_H__
#define __PLATFORMENV_H__
/***********************************************************************************************************************
* Description         : define platform environment.
*                       for some platform/compiler/linker dependency code, it is helpful
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/

/******************************************************************************************************
below refer to :  How to detect the compiler name and version using compiler predefined macros
http://nadeausoftware.com/articles/2012/10/c_c_tip_how_detect_compiler_name_and_version_using_compiler_predefined_macros#Howtolistpredefinedmacros
for MSVC specific:
https://msdn.microsoft.com/en-us/library/b0084kay.aspx
******************************************************************************************************/
#include <MiniMPL/macro_makeTxt.h>

#if defined(__clang__)
    #define LLVM          /* Clang/LLVM */
#endif 

#if defined(__ICC) || defined(__INTEL_COMPILER)
    #define IntelCPP    /* Intel ICC/ICPC */
#endif 

#if defined(__GNUC__) || defined(__GNUG__)
    #define GNUCPP      /* GNU GCC/G++ */
#endif 

#if defined(__HP_cc) || defined(__HP_aCC)
    #define HPCPP      /* Hewlett-Packard C/aC++ */
#endif 

#if defined(__IBMC__) || defined(__IBMCPP__)
    #define IBMCPP       /* IBM XL C/C++. */
#endif 

#if defined(_MSC_VER)
    #define MSVC        /* Microsoft Visual Studio.*/

    #define VSListDef(_)                                                                 \
    _(_MSC_VER,       1914,       VC++ 14.14,   (Visual Studio 2017 version 15.7)     )  \
    _(_MSC_VER,       1913,       VC++ 14.13,   (Visual Studio 2017 version 15.6)     )  \
    _(_MSC_VER,       1912,       VC++ 14.12,   (Visual Studio 2017 version 15.5)     )  \
    _(_MSC_VER,       1911,       VC++ 14.11,   (Visual Studio 2017 version 15.3)     )  \
    _(_MSC_VER,       1910,       VC++ 14.1,    (Visual Studio 2017 version 15.0)     )  \
    _(_MSC_VER,       1900,       VC++ 14.0,    (Visual Studio 2015 version 14.0)     )  \
    _(_MSC_VER,       1800,       VC++ 12.0,    (Visual Studio 2013 version 12.0)     )  \
    _(_MSC_VER,       1700,       VC++ 11.0,    (Visual Studio 2012 version 11.0)     )  \
    _(_MSC_VER,       1600,       VC++ 10.0,    (Visual Studio 2010 version 10.0)     )  \
    _(_MSC_FULL_VER,  150030729,  VC++ 9.0,     (Visual Studio 2008, SP1)             )  \
    _(_MSC_VER,       1500,       VC++ 9.0,     (Visual Studio 2008 version 9.0)      )  \
    _(_MSC_VER,       1400,       VC++ 8.0,     (Visual Studio 2005 version 8.0)      )  \
    _(_MSC_VER,       1310,       VC++ 7.1,     (Visual Studio.NET 2003 version 7.1)  )  \
    _(_MSC_VER,       1300,       VC++ 7.0,     (Visual Studio.NET 2002 version 7.0)  )  \
    _(_MSC_VER,       1200,       VC++ 6.0,     (Visual Studio 6.0 version 6.0)       )  \
    _(_MSC_VER,       1100,       VC++ 5.0,     (Visual Studio 97 version 5.0)        )
    #define VSItem(a,b,c,d) __pragma(message (#a " = " MAKESTRA(b) " , " MAKESTRA(c) " , " MAKESTRA(d)))

    #define plat_info_vsList()    VSListDef(VSItem)
    #define plat_info_vs()                                                              \
    __pragma(message ("_MSC_VER = "         MAKESTRA(_MSC_VER)))                        \
    __pragma(message ("_MSC_FULL_VER  = "   MAKESTRA(_MSC_FULL_VER)))

#endif 

//////////////////////////////////////////////////////////////////////////
//C++11 sets the value of __cplusplus to 201103L
//but any version VS always set __cplusplus=199711L
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
	#define CPP11_ENABLED       1
#else
	#define CPP11_ENABLED       0
	#define final
	#define override
#endif

#if defined(_MSC_VER)
	#define plat_info_cpp()   \
			__pragma(message ("__cplusplus = " MAKESTRA(__cplusplus) " , CPP11_ENABLED = " MAKESTRA(CPP11_ENABLED) ))   

#else
	#define cplusplusList(_)																\
		_(CPP98_03	,	199711L)															\
		_(CPP11		,	201103L)															\
		_(CPP14		,	201402L)															\
		_(CPP17		,	201703L)
	#define cplusplusItem(a,b) __pragma(message (#a " = " MAKESTRA(b) ))

	#define plat_info_cpp()    cplusplusList(cplusplusItem)								\
			__pragma(message("current __cplusplus = " MAKESTRA(__cplusplus)))
#endif

#if defined(__PGI)
    #define PGICPP      /* Portland Group PGCC/PGCPP */
#endif 

#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
    #define SolarisCPP      /* Oracle Solaris Studio */
#endif
//////////////////////////////////////////////////////////////////////////
#if defined(MSVC)
    #if 1==_CPPRTTI
        #define RTTI_Enable     1
        #define RTTI_Disable    0
    #else
        #define RTTI_Enable     0
        #define RTTI_Disable    1
    #endif 
    #define plat_info_rtti() __pragma(message ("RTTI_Enable = " MAKESTRA(RTTI_Enable)))
#endif

#if defined(GNUCPP)
    #if 1==__GXX_RTTI
        #define RTTI_Enable     1
        #define RTTI_Disable    0
    #else
        #define RTTI_Enable     0
        #define RTTI_Disable    1
    #endif
#endif

#endif // __PLATFORMENV_H__
