#ifndef __MACRO_TRACELOG_H__
#define __MACRO_TRACELOG_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/macro_makeTxt.h>
#include <sstream>
#include <iostream>

//////////////////////////////log interface & macro begin////////////////////////////////////////////
#ifdef _MSC_VER 
    // two leading underscores - Microsoft specific extension
	#define		outputCompileMsg(x)			__pragma(message ( x ))
    #define     CDECL_CALL                 __cdecl
#elif defined(__GNUC__) 
    // C99  :	_Pragma ("message( \"the cl msg way\")")  => #pragma message("the cl msg way")
	#define     do_pragma_msg(x)            _Pragma (#x)    
	#define		outputCompileMsg( x )		do_pragma_msg (message ( x))
    #define     CDECL_CALL                  // No need for CDECL_CALL in GCC
	// #define	outputCompileMsg( x )		do_pragma_msg (message ( "[somePrefix] " x))
#else
    #error "Unsupported compiler"
#endif

namespace MiniMPL
{
    //output to console and debugger output window
    void __cdecl dbgOutput(const wchar_t* pStr);
    void __cdecl dbgOutput(const char* pStr);

    void __cdecl dbgOutputV(const wchar_t* format, ...);
    void __cdecl dbgOutputV(const char* format, ...);
}

#define outputTxt           MiniMPL::dbgOutput
#define outputTxtV          MiniMPL::dbgOutputV

#define outputTxtStreamA(X)                             \
{                                                       \
    std::stringstream ss;                               \
    ss << X;                                            \
    outputTxt(ss.str().c_str());                        \
}

#define outputTxtStreamW(X)                             \
{                                                       \
    std::wstringstream ss;                              \
    ss << X;                                            \
    outputTxt(ss.str().c_str());                        \
}

#if 1==USE_UNICODE_STRING
#define  outputTxtStream     outputTxtStreamW
#else
#define  outputTxtStream     outputTxtStreamA
#endif

//////////////////////////////log interface & macro end////////////////////////////////////////////


//////////////////////////////Trace source info macro begin /////////////////////////////////////////////////////////////////
#define HEREINFO_POSA()                 TXTA(__FILE__)  TXTA("(")   MAKESTRA(__LINE__)  TXTA(") : function [")  TXTA(__FUNCTION__)  TXTA("]")
#define HEREINFO_POSW()                 TXTW(__FILE__)  TXTW("(")   MAKESTRW(__LINE__)  TXTW(") : function [")  TXTW(__FUNCTION__)  TXTW("]")
#define HEREINFO_POS()                  TXT(__FILE__)   TXT("(")    MAKESTR(__LINE__)   TXT(") : function [")   TXT(__FUNCTION__)   TXT("]")

#define HEREINFO_TIMEA()                TXTA("Compile time :") TXTA(__DATE__) TXTA(" ") TXTA(__TIME__) TXTA("\t\tLast modify time :") TXTA(__TIMESTAMP__)
#define HEREINFO_TIMEW()                TXTW("Compile time :") TXTW(__DATE__) TXTW(" ") TXTW(__TIME__) TXTW("\t\tLast modify time :") TXTW(__TIMESTAMP__)
#define HEREINFO_TIME()                 TXT("Compile time :")  TXT(__DATE__)  TXT(" ")  TXT(__TIME__)  TXT("\t\tLast modify time :")  TXT(__TIMESTAMP__)

#define HEREINFOA()                     HEREINFO_POSA() TXTA("\n")  HEREINFO_TIMEA()
#define HEREINFOW()                     HEREINFO_POSW() TXTW("\n")  HEREINFO_TIMEW()
#define HEREINFO()                      HEREINFO_POS()  TXT("\n")   HEREINFO_TIME()

//////////////////////////////Trace source info macro end /////////////////////////////////////////////////////////////////



//////////////////////////////Trace helper macro begin /////////////////////////////////////////////////////////////////

#define ALWAYS_LOG_HEREA()			    outputTxt(TXTA("\n") HEREINFOA() TXTA("\n"))
#define ALWAYS_LOG_HEREW()			    outputTxt(TXTW("\n") HEREINFOW() TXTW("\n"))
#define ALWAYS_LOG_HERE()			    outputTxt(TXT("\n") HEREINFO() TXT("\n"))

#define ALWAYS_LOG_HERE_INFOA(X)		{ outputTxt(X); ALWAYS_LOG_HEREA();}
#define ALWAYS_LOG_HERE_INFOW(X)		{ outputTxt(X); ALWAYS_LOG_HEREW();}
#define ALWAYS_LOG_HERE_INFO(X)		    { outputTxt(X); ALWAYS_LOG_HERE(); }

#if 1==ENABLE_TRACE_COMPILE_SRC     //compiler message MUST be ASCII string  
    #define  ALWAYS_COMPILE_MSG(X)  outputCompileMsg ( X "\r\n" HEREINFO_POSA() )      
#else
    #define  ALWAYS_COMPILE_MSG(X)  outputCompileMsg("[Compiling " __FUNCTION__ "] " X)   
#endif

#if 1==ENABLE_COMPILE_WARNING
    #define  COMPILE_WARNING(X)    ALWAYS_COMPILE_MSG(X)
#else
    #define  COMPILE_WARNING(X)
#endif

#if defined(_MSC_VER) && (1==ENABLE_TRACE_COMPILE)
    //usage example : COMPILE_MSG("***111 ");
    #define COMPILE_MSG(X) ALWAYS_COMPILE_MSG(X)
#else
    #define COMPILE_MSG(X)
#endif 

#define TRACE_COMPILE()         COMPILE_MSG(__FUNCSIG__)
#define CheckMacroExpand(X)     outputCompileMsg(X)				//used to check macro extension

#if ENABLE_TRACE
    #define TRACE_INFO(X)		    outputTxt(X)

    #define PrefixTrace				TXT("\n[TraceHere]\t")
    #define TRACE_HERE()            ALWAYS_LOG_HERE_INFO((PrefixTrace))
    #define TRACE_HERE_INFO(X)      { outputTxt(PrefixTrace); ALWAYS_LOG_HERE_INFO(X);}
#else
    #define TRACE_INFO(X)

    #define TRACE_HERE() 
    #define TRACE_HERE_INFO(X)
#endif
//////////////////////////////Trace helper macro end /////////////////////////////////////////////////////////////////

#endif // __MACRO_TRACELOG_H__
