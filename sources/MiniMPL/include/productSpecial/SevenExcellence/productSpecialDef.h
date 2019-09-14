#ifndef projectConfig_h__
#define projectConfig_h__
/********************************************************************
	created:	2014-2-14   9:47
				This file is only for products based on PDK platform in METTLER TOLEDO company(www.mt.com).
	author:		Shen Tony	
	purpose:	Different project has different config, for example stl vector/list etc
                and include project header file here
*********************************************************************/
#include <MiniMPL/libConfig.h>

//////////////////////////////////////VLD(memory leak check )///////////////////////////////////////
#include <core\core_plat_config.h>
#if !defined(CORE_PLATFORM_WIN32_WINCE) && defined(_DEBUG) && (_MSC_VER >= 1000 && _MSC_VER <= 1699)
    #define Enable_VLD_FIX    0
#endif
//////////////////////////////////////////////////STL replace //////////////////////////////////////////////////////
//define external stl lib name space
#define STLNS               ::core::

/*!  for customer STL library , it is the place to replace it */
//define STL string
#include <core\string\cstringex.h>
typedef STLNS cstringexA        stlStringA;
typedef STLNS cstringexW        stlStringW;
typedef STLNS cstringex         stlString;
typedef stlString::value_type   stlChar;
#define stlStringPack(x)        STLNS detail::CStringT< x, STLNS ChTraitsCRT< x > >
#define NewStlStringParam(Head,Tail)    Head

//define STL vector and smart pointer
#include <core\container\cvector.h>
#include <core\util\smartptr.h>
#include <core\container\map.h>
#define stlVector           STLNS cvector
#define stlSmartptr         STLNS smartptr
#define stlPair             STLNS pair
#define makePair            STLNS make_pair
#define stlMap              STLNS map
#define MapInsert(R,K,V)    (R).insert((K),(V),true)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//declare various parameter printf interfaces, it depends on project
#include <core\util\log.h>
#define MaxOutputBufLen 512     //see PDK logger_manager::log_var_output_dispatch

inline void __cdecl dbgOutput (const wchar_t* format,...)
{
    wchar_t		Buf[MaxOutputBufLen] = {0};
    va_list		arglist; 
    va_start(arglist, format);
    vswprintf_s(Buf,MaxOutputBufLen, format, arglist);
    va_end(arglist);
    OutputDebugStringW(Buf);
}
#define outputTxt(X)			    dbgOutput X 

//////////////////////////////////////////Assert replac/////////////////////////////////////////////////////////////////
//define macro _Assert_Trigger to implement assert : different platform might support different assert statement
#define _myProjectAssert()          CORE_ASSERT(0)

#define Float_Cmp_Threshold        0.000001
//**********************************************************************************************************************
///////////////////////////////////////Other special defintion for concreate product////////////////////////////////////
//cancel define macro MAKESTR in "\tresos-fw\mt-pdk\source\tresos-base\include\core/build_version.h:23"
//#define MAKESTR(p)    MAKESTR1(p)
#ifdef MAKESTR
    #undef MAKESTR      
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
    #define DEBUG_STATEMENT(X)          X
    #define REALEASE_STATEMENT(X)       
#else
    #define DEBUG_STATEMENT(X)          
    #define REALEASE_STATEMENT(X)       X
#endif


#endif // projectConfig_h__
