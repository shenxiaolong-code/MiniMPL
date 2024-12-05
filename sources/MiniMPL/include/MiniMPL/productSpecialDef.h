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

typedef STLNS string         stlStringA;
typedef STLNS wstring        stlStringW;
#if 1==USE_UNICODE_STRING
typedef stlStringW          stlString;
#else                                 
typedef stlStringA          stlString;
#endif
typedef stlString::value_type       stlChar;
#define stlStringPack(x)            STLNS basic_string< x >
#define NewStlStringParam(Head,Tail)    Head,Tail

//define STL vector and smart pointer
#include <vector>
#define stlVector               STLNS vector

#include <map>
#define stlPair                 STLNS pair
#define makePair                STLNS make_pair
#define stlMap                  STLNS map
#define MapInsert(R,K,V)        (R).insert(makePair((K),(V)))

//define smart pointer.
//Note:take care of std::auto_ptr, it will transfer ownership. 
//it can't meet requirement in many scenarios, e.g. loop scenario
#if USE_MINIMPL_SMARTPOINTER
    #include <MiniMPL/smartPointer.hpp>
    #define stlSmartptr     ::MiniMPL::RefCountSmartPtr
#else
    #include <memory>
    #define stlSmartptr         STLTR1NS shared_ptr 
    #define stlSmartptrBase     STLTR1NS enable_shared_from_this

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
