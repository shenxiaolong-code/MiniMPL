#ifndef __MACRO_MAKETXT_H__
#define __MACRO_MAKETXT_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>

//////////////////////////String helper macro begin ////////////////////////////////////////////////////////////////////
// Difference between TXT and MAKESTR : param of TXT is string, param of MAKESTR is not string 
// TXT      : ASCII / UNICODE
// MAKESTR  : non-string => string

//[ASCII string]
#define __TXTA(X)                       X
#define TXTA(X)                         __TXTA(X)

#define __TXTW(X)                       L ## X
#define TXTW(X)                         __TXTW(X)

#define __MAKESTRA(X)				    #X
#define __MAKESTRA2(X,Y)			    #X#Y
#define __MAKESTRA3(X,Y,Z)			    #X#Y#Z
#define MAKESTRA(X)				        __MAKESTRA(X)
#define MAKESTRA2(X,Y)			        __MAKESTRA2(X,Y)
#define MAKESTRA3(X,Y,Z)			    __MAKESTRA3(X,Y,Z)

//[UNICODE string]
#define __MAKESTRW(X)                   L ## #X
#define __MAKESTRW2(X,Y)			    L ## #X L ## #Y
#define __MAKESTRW3(X,Y,Z)		        L ## #X L ## #Y L ## #Z
#define MAKESTRW(X)                     __MAKESTRW(X)
#define MAKESTRW2(X,Y)			        __MAKESTRW2(X,Y)
#define MAKESTRW3(X,Y,Z)		        __MAKESTRW3(X,Y,Z)

//make string
#if 1==USE_UNICODE_STRING
    typedef wchar_t                     VCHAR;
    #define TXT(X)                      __TXTW(X)           //caution : 3 time expand as "TXTW(X)" will cause error in some case.
    #define MAKESTR(X)                  __MAKESTRW(X)
    #define MAKESTR2(X,Y)			    __MAKESTRW2(X,Y)
    #define MAKESTR3(X,Y,Z)		        __MAKESTRW3(X,Y,Z)
#else
    typedef char                        VCHAR;
    #define TXT(X)                      __TXTA(X)
    #define MAKESTR(X)                  __MAKESTRA(X)
    #define MAKESTR2(X,Y)			    __MAKESTRA2(X,Y)
    #define MAKESTR3(X,Y,Z)		        __MAKESTRA3(X,Y,Z)
#endif

//////////////////////////String helper macro end ////////////////////////////////////////////////////////////////////

#endif // __MACRO_MAKETXT_H__
