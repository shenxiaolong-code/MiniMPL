#ifndef __CLASSREGISTERMACRO_MSVC_HPP__
#define __CLASSREGISTERMACRO_MSVC_HPP__
/***********************************************************************************************************************
* Description         : helper macro to use ClassRegisterEx to dynamic generate object implicitly.
*                       Note : below macro is MSVC specific
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/platformEnv.h>
#ifdef MSVC
#ifndef __CLASSREGISTERMACRO_HPP__
    #error  "don't include MiniMPL/classRegisterMacro_MSVC.hpp directly,should include MiniMPL/classRegisterMacro.hpp"
#endif

#include <MiniMPL/macroDef.h>
#include <MiniMPL/classRegister.hpp>

//below code is compiler/linker dependency. it is MSVC specific , refer to : 
// http://www.kegel.com/mangle.html
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// same with below project configuration:
// Project Properties -> Configuration Properties -> Librarian -> Genaral : Force Symbol References
// or
// Project Properties -> Configuration Properties -> Linker -> Input : Force Symbol References
//below macro help to generate deconstruction raw C++ name of derived class.
//N1,N2,N3 is namespace name, Nx is different level namespace name
#define Symbol_N0(X)                MAKESTRA(X)
#define Symbol_N1(N1,X)             MAKESTRA(X) MAKESTRA2(@,N1)
#define Symbol_N2(N1,N2,X)          MAKESTRA(X) MAKESTRA2(@,N2) MAKESTRA2(@,N1) 
#define Symbol_N3(N1,N2,N3,X)       MAKESTRA(X) MAKESTRA2(@,N3) MAKESTRA2(@,N2) MAKESTRA2(@,N1)

//Note: for constructor symbol , struct and class is same, but for deconstructor symbol, they are different.
//ClassRegisterEx dynamic creator requests constructor without parameter, so do not use unique and reliable deconstructor.
#define Constructor_Symbol(X)                      "/include:??0"  X   "@@QAE@XZ"
#define Force_Symbol_Reference(X)                   __pragma(comment(linker,Constructor_Symbol(X))) \
													CheckMacroExpand(HEREINFO_POSA() " forcely inject symbol : #pragma comment(linker, \"" Constructor_Symbol(X) "\")" )

#define Link_ClassRegister_Symbol_N0(X)             Force_Symbol_Reference(Symbol_N0(X))
#define Link_ClassRegister_Symbol_N1(N1,X)          Force_Symbol_Reference(Symbol_N1(N1,X))
#define Link_ClassRegister_Symbol_N2(N1,N2,X)       Force_Symbol_Reference(Symbol_N2(N1,N2,X))
#define Link_ClassRegister_Symbol_N3(N1,N2,N3,X)    Force_Symbol_Reference(Symbol_N3(N1,N2,N3,X))

///////////////////////////////////////////////////////////////////////////////////////////////////
//MUST XCD, after system CRT global symbol initialization and before user global symbol initialization
#define ClassRegisterSECNAME ".CRT$XCD"
#pragma section(ClassRegisterSECNAME,long, read)
typedef void (__cdecl *_PVFV)();

//parameter order : derived class name, base class name
#define IMPLEMENT_CLASS(driT,baseT)																									                                    \
    void __cdecl  __##driT (){ static MiniMPL::ClassRegisterEx<baseT> _##driT(MAKESTR(driT),new MiniMPL::CTypeObjectCreaterImpl<driT,baseT>(),MiniMPL::NullType()); };  \
    __declspec(allocate(ClassRegisterSECNAME)) _PVFV _##driT[] = { __##driT }  

//parameter order : derived class name, base class name,trait value
#define IMPLEMENT_CLASS_BIND_DAT(driT,baseT,pExtra)                                                                                                                                             \
    void __cdecl  __##driT (){ static MiniMPL::ClassRegisterEx<baseT> _##driT(MAKESTR(driT),new MiniMPL::CTypeObjectCreaterImpl<driT,baseT>(),MiniMPL::InnerDetail::makeTraitData(pExtra)); };  \
    __declspec(allocate(ClassRegisterSECNAME)) _PVFV _##driT[] = { __##driT }  

//parameter order : derived class name, base class name,trait type
#define IMPLEMENT_CLASS_BIND_TYPE(driT,baseT,AddT)                                                                                                                                          \
    void __cdecl  __##driT (){ static MiniMPL::ClassRegisterEx<baseT> _##driT(MAKESTR(driT),new MiniMPL::CTypeObjectCreaterImpl<driT,baseT>(),MiniMPL::InnerDetail::TraitType<AddT>()); }   \
    __declspec(allocate(ClassRegisterSECNAME)) _PVFV _##driT[] = { __##driT }  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************
//////////////////////////////////////   usage read me   /////////////////////////////////////////
CAUTION: MUST take care of symbol accessibility/visibility when using ClassRegister to dynamic create object implicitly.
In general , if creating object and object class definition lies in same project of solution, there is no any problems.
[ELSE] if creating object and object class definition lies in different project,if symbols of derived object class definition
is not used EXPLICITLY, these symbols might be removed when linking and they are not visible and not accessible.

In this case,the project of creating object needs to force linker to link derived class symbols which needed to be created dynamic.
#pragma comment(linker, "/include:yourDerivedClassSymbolRawName")
for example: we need to dynamic create CDri_Type1
namespace UnitTest
{
    class  CDri_Type1 :public CDemoCast{};
    IMPLEMENT_CLASS_BIND_TYPE(CDri_Type1,CDemoCast,DemoTraintType);
}

In different project which will IMPLICIT dynamic create CDri_Type1. 
if symbol CDri_Type1 is not visible, you need to link symbol "CDri_Type1" forcedly by below way:
#define Link_ClassRegister_Symbol_UnitTest(X)   Link_ClassRegister_Symbol_N1(UnitTest,X)
Link_ClassRegister_Symbol_UnitTest(CDri_Type1)

where is #pragma comment(linker, "/include:...") ??
any .cpp is OK if this .cpp symbol is not removed by linker. (it can't be derived class definition .cpp file.)
below two position might be better:
1. .cpp file of base class "CDemoCast" because base class symbol "CDemoCast" is certain to be linked into creating object project. 
2. .cpp of creating objects.
if derived class definition scatter on many different projects, it is better that every project has one symbol link list(.h) like below:
//CDemoCast_Symbol_List_1.h
Link_ClassRegister_Symbol_UnitTest(CDri_Type1)
//CDemoCast_Symbol_List_2.h
Link_ClassRegister_Symbol_UnitTest(CDri_Type2)
Link_ClassRegister_Symbol_UnitTest(CDri_Type3)
and include the header file "CDemoCast_Symbol_List.h" in .cpp of creating objects
#include <CDemoCast_Symbol_List_1.h>
#include <CDemoCast_Symbol_List_2.h>

certainly if in same project, you can use ClassRegister/ClassRegisterEx freely without taking care of link symbol issue.
Frankly speaking it is MSVC linker issues.(MS might do it like so to optimize performance)
In this case(extern global variable in different project), MSVC compiler/linker is not compatible with C++ specification completely.
In other compiler/linker, it might be good.(not tested).
******************************************************************************************************/

#endif // end of MSVC
#endif // __CLASSREGISTERMACRO_MSVC_HPP__
