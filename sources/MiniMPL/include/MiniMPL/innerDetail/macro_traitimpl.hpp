#ifndef __MACRO_TRAITIMPL_HPP__
#define __MACRO_TRAITIMPL_HPP__
/***********************************************************************************************************************
* Description         : define which MPL type trait implement is used
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/platformEnv.h>

#if CPP11_ENABLED
    #define STDTRNS       ::std             //C++11 is supported
#else
    #define STDTRNS       ::std::tr1        //C++11 is not supported
#endif

#define  TRAIT_MPL          ::MiniMPL::InnerDetail

#if USE_STD_TRAIT
    #include <type_traits>
    #define TRAITNS         STDTRNS
#else
    #define TRAITNS         TRAIT_MPL      //Not use std trait.
#endif

#endif // __MACRO_TRAITIMPL_HPP__
