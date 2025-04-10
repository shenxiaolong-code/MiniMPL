#ifndef __PRODUCTSPECIALDEF_H__
#define __PRODUCTSPECIALDEF_H__
/***********************************************************************************************************************
* Description         : Different project has different config, for example stl vector/list etc
                        and include project header file here
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/platformEnv.h>
//////////////////////////////////////////////////STL replace //////////////////////////////////////////////////////
/*!  for customer STL library , it is the place to replace it */
//define STL string
#include <string>

using stlStringA=std::string;
using stlStringW=std::wstring;
#if 1==USE_UNICODE_STRING
    using stlString=stlStringW;
#else
    using stlString=stlStringA;
#endif
using stlChar=stlString::value_type;
template<typename T> using stlStringPack=std::basic_string<T>;

//define STL vector and smart pointer
#include <vector>
#define stlVector               std::vector

#include <map>
#define stlMap                  std::map
#define MapInsert(R,K,V)        (R).insert(std::make_pair((K),(V)))

//define smart pointer.
//Note:take care of std::auto_ptr, it will transfer ownership. 
//it can't meet requirement in many scenarios, e.g. loop scenario
#if USE_MINIMPL_SMARTPOINTER
    #include <MiniMPL/smartPointer.hpp>
    #define stlSmartptr     ::MiniMPL::RefCountSmartPtr
#else
    #include <memory>
    #define stlSmartptr         std::shared_ptr 
    #define stlSmartptrBase     std::enable_shared_from_this

    #define DeclarePtr(T)       typedef stlSmartptr< T >   T##Ptr
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//declare various parameter printf interfaces, it depends on project
#define Float_Cmp_Threshold         0.000001

//////////////////////////////////////////Assert replac/////////////////////////////////////////////////////////////////
//define macro _Assert_Trigger to implement assert : different platform might support different assert statement
#ifdef _MSC_VER 
    inline void _myProjectAssert() { __asm { int 3 } } 
#elif defined(__GNUC__) 
    inline void _myProjectAssert() { asm volatile("int $3"); }
#else
    #error "Unsupported compiler"
#endif

//**********************************************************************************************************************
///////////////////////////////////////Other special definition for concrete product////////////////////////////////////
//////////////////////////////////////VLD(memory leak check )//////////////////////////////////////////////////////
#if defined(_WIN32) && defined(_DEBUG) && (_MSC_VER >= 1000 && _MSC_VER <= 1699)
    #define Enable_VLD_FIX   0
#endif

#endif // __PRODUCTSPECIALDEF_H__
