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
for MSVC specific:
https://msdn.microsoft.com/en-us/library/b0084kay.aspx
******************************************************************************************************/
#include <MiniMPL/macro_makeTxt.h>
#include <cstdint>      //for bit32/bit64

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
       
#if INTPTR_MAX == INT32_MAX
    #define BIT32
    #define BIT_NUM     32
    #define bit_info()  __pragma(message ("bit = BIT32 , value=" MAKESTRA(BIT_NUM))) 
#elif INTPTR_MAX == INT64_MAX
    #define BIT64
    #define BIT_NUM     64
    #define bit_info()  __pragma(message ("bit = BIT64 , value=" MAKESTRA(BIT_NUM))) 
#else
    #error "Environment not 32 or 64-bit."
    #define BIT_NUM     00
    #define bit_info()  __pragma(message ("bit = unknown , value=" MAKESTRA(BIT_NUM))) 
#endif

//https://sourceforge.net/p/predef/wiki/Architectures/
//you need this definition if using assemble code (don't use header file which is dependent-based-on-platform)
//for general architecture type x86 , amd64 , intel64 , arm 
#if defined(i386) || defined(__i386) || defined(__i386) || defined(_M_I86) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__) || defined(__386)
    #define     ASM_X86
    #define     ASM_MOD   1
    #define     asm_info()  __pragma(message ("ASM_MOD = ASM_X86 , value:" MAKESTRA(ASM_MOD) )) 
#endif // _X86_
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
    #define     ASM_AMD64
    #define     ASM_MOD   2
    #define asm_info()  __pragma(message ("ASM_MOD = ASM_AMD64 , value:" MAKESTRA(ASM_MOD) )) 
#endif // AMD64
#if defined(_IA64) || defined(__ia64) || defined(_M_IA64) || defined(_M_IA64) || defined(__itanium__)
    #define     ASM_INTEL64
    #define     ASM_MOD   3
    #define asm_info()  __pragma(message ("ASM_MOD = ASM_AMD64 , value:" MAKESTRA(ASM_MOD) )) 
#endif // Intel 64
#if defined(__arm__) || defined(_ARM) || defined(_M_ARM) || defined(_M_ARMT) || defined(__arm)
    #define     ASM_ARM
    #define     ASM_MOD   4
    #define asm_info()  __pragma(message ("ASM_MOD = ASM_ARM , value:" MAKESTRA(ASM_MOD) )) 
#endif // ARM
//some other architectures for embed board are skipped. e.g.  MIPS , PowerPC , TMS470, SuperH , Motorola 68k ...
#ifndef ASM_MOD
    #error "Unknown Compiler Macros for CPU Architectures , ASM_MOD is not defined. "
#endif // !ASM_MOD

#if defined(_MSC_VER)
    #define MSVC        /* Microsoft Visual Studio.*/

    #define VSListDef(_)                                                                 \
	_(_MSC_VER,       1923,       VC++ 14.23,   (Visual Studio 2019 version 16.3)     )  \
	_(_MSC_VER,       1922,       VC++ 14.22,   (Visual Studio 2019 version 16.2)     )  \
	_(_MSC_VER,       1921,       VC++ 14.21,   (Visual Studio 2019 version 16.1)     )  \
	_(_MSC_VER,       1920,       VC++ 14.2 ,   (Visual Studio 2019 version 16.0)     )  \
	_(_MSC_VER,       1916,       VC++ 14.16,   (Visual Studio 2017 version 15.9)     )  \
	_(_MSC_VER,       1915,       VC++ 14.15,   (Visual Studio 2017 version 15.8)     )  \
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
#if __cplusplus >= 201103L
	#define CPP11_ENABLED       1
#else
	#define CPP11_ENABLED       0
#endif

//C++17 sets the value of __cplusplus to 201703L
#if __cplusplus >= 201703L
    #define CPP17_ENABLED 1
#else
    #if (defined(_MSC_VER) && _MSC_VER > 1929)
        #define CPP17_ENABLED       1
    #else
        #define CPP17_ENABLED       0
    #endif
#endif

//*/ bug fix
#if 199711L == __cplusplus && defined(_MSC_VER)
//but any version VS always set __cplusplus=199711L  and _MSC_VER=1929
//vs can't detect whether the C++11 and C++17 is enabled. we set it manual
    #pragma message("building on MS visual studio platform, set CPP11_ENABLED=1 and CPP17_ENABLED=0 manual. \r\n" __FILE__ "("  MAKESTRA(__LINE__) ")" )
    #undef  CPP11_ENABLED    
    #define CPP11_ENABLED       1

    #undef  CPP17_ENABLED
    #define CPP17_ENABLED       0
#endif
//*/

#if CPP11_ENABLED
    #define STLNS               _STD
	#define STLTR1NS			_STD
#else
	#define STLNS               _STD
	#define STLTR1NS			_STD tr1::
	#define final
	#define override
#endif

#if defined(_MSC_VER)
	#define plat_info_cpp()   \
			__pragma(message ("__cplusplus = " MAKESTRA(__cplusplus) " , CPP11_ENABLED = " MAKESTRA(CPP11_ENABLED) ))   \
            __pragma(message ("__cplusplus = " MAKESTRA(__cplusplus) " , CPP17_ENABLED = " MAKESTRA(CPP17_ENABLED) ))
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
