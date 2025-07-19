#ifndef __MACRO_TRAITIMPL_HPP__
#define __MACRO_TRAITIMPL_HPP__
/***********************************************************************************************************************
* Description         : define which MPL type trait implement is used
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/platformEnv.h>

#if CPP_STD >= 11
    #define STDTRNS			::std             	//C++11 is supported
	#if _MSC_VER < 1900
		#define CompileValue	constexpr		//warning C4814: 'MiniMPL::StdWrapper::MaxValue::operator T': in C++14 'constexpr' will not imply 'const'; consider explicitly specifying 'const'
	#else
		#define CompileValue 
	#endif	
#else
    #define STDTRNS			::std::tr1			//C++11 is not supported
	#define CompileValue
#endif	// CPP_STD >= 11

#define  TRAIT_MPL          ::MiniMPL::InnerDetail

#if USE_STD_TRAIT
    #include <type_traits>
    #define TRAITNS         STDTRNS
#else
    #define TRAITNS         TRAIT_MPL      //Not use std trait.
#endif

#endif // __MACRO_TRAITIMPL_HPP__
