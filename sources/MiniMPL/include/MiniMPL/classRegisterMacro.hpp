#ifndef __CLASSREGISTERMACRO_HPP__
#define __CLASSREGISTERMACRO_HPP__
//for different platform/compiler/linker, the symbol name style is different , here is collection.refer to : 
// https://en.wikipedia.org/wiki/Name_mangling
// http://www.agner.org/optimize/calling_conventions.pdf

#include <MiniMPL/classRegisterMacro_MSVC.hpp>

//demand driven, on other platform, need according classRegisterMacro_XXX.hpp 
//#include <MiniMPL/classRegisterMacro_XXX.hpp>

/******************************************************************************************************
//short example for symbol style based on different platform:
Compiler	                    void h(int)	        void h(int, char)	        void h(void)
Intel C++ 8.0 for Linux	        _Z1hi	            _Z1hic	                    _Z1hv
HP aC++ A.05.55 IA-64           _Z1hi	            _Z1hic	                    _Z1hv
IAR EWARM C++ 5.4 ARM           _Z1hi	            _Z1hic	                    _Z1hv
GCC 3.x and 4.x                 _Z1hi	            _Z1hic	                    _Z1hv
IAR EWARM C++ 7.4 ARM	        _Z<number>hi	    _Z<number>hic	            _Z<number>hv
GCC 2.9x	                    h__Fi	            h__Fic	                    h__Fv
HP aC++ A.03.45 PA-RISC         h__Fi	            h__Fic	                    h__Fv
Microsoft Visual C++ v6-v10     ?h@@YAXH@Z	        ?h@@YAXHD@Z	                ?h@@YAXXZ
Digital Mars C++                ?h@@YAXH@Z	        ?h@@YAXHD@Z	                ?h@@YAXXZ
Borland C++ v3.1	            @h$qi	            @h$qizc	                    @h$qv
OpenVMS C++ V6.5 (ARM mode)	    H__XI	            H__XIC	                    H__XV
OpenVMS C++ V6.5 (ANSI mode)                        CXX$__7H__FIC26CDH77	    CXX$__7H__FV2CB06E8
OpenVMS C++ X7.1 IA-64	        CXX$_Z1HI2DSQ26A	CXX$_Z1HIC2NP3LI4	        CXX$_Z1HV0BCA19V
SunPro CC	                    __1cBh6Fi_v_	    __1cBh6Fic_v_	            __1cBh6F_v_
Tru64 C++ V6.5 (ARM mode)	    h__Xi	            h__Xic	                    h__Xv
Tru64 C++ V6.5 (ANSI mode)	    __7h__Fi	        __7h__Fic	                __7h__Fv
Watcom C++ 10.6	                W?h$n(i)v	        W?h$n(ia)v	                W?h$n()v

******************************************************************************************************/

#endif // __CLASSREGISTERMACRO_HPP__
