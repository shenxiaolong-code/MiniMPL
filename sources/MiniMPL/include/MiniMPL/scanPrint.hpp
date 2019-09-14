#ifndef __SCANPRINT_HPP__
#define __SCANPRINT_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/addRemove.hpp>
#include <MiniMPL/innerDetail/scanPrint_detail.hpp>
#include <iosfwd>

#define     printA                  printf_s
#define     printW                  wprintf_s
#define     printBufA               sprintf_s
#define     printBufW               swprintf_s
#define     scanfBufA               sscanf_s
#define     scanfBufW               swscanf_s

#if 1==USE_UNICODE_STRING
    #define     printConsole        printW
    #define     printBuf            printBufW
    #define     scanfBuf            scanfBufW
#else
    #define     printConsole        printA
    #define     printBuf            printBufA
    #define     scanfBuf            scanfBufA
#endif // 1==USE_UNICODE_STRING

namespace MiniMPL
{
        /*
                                           0       1      2      3     4       5         6       7
        extern char const*    strFmtA[] = {"%c",   "%d",  "%u",  "%f",  "%lf",  "%s",  "%I64d",  "%I64u" };
        extern wchar_t const* strFmtW[] = {L"%c", L"%d", L"%u", L"%f", L"%lf", L"%s", L"%I64d", L"%I64u" };
        //defined in ..\src\MiniMPL\libGlobal.cpp
        */
        extern char const*      strFmtA[8];  //size error will cause compile error. OK!
        extern wchar_t const*   strFmtW[8];  //size error will cause compile error. OK!
#if USE_UNICODE_STRING==0
        extern char const**     strFmt;
#else
        extern wchar_t const**  strFmt;
#endif

        template<typename T> struct CFormatIdx : public InnerDetail::CFormatIdxImpl<RAWTYPE(T)>  {};

        template<typename char_T> struct GetFmtArr;
        template<>                struct GetFmtArr<char>        : Value2Type<const char *const *,strFmtA>                               {};
        template<>                struct GetFmtArr<wchar_t>     : Value2Type<const wchar_t *const *,strFmtW>                            {};

        template<typename char_T,typename T>
        inline char_T const* getFmt(){ return  GetFmtArr<char_T>::value[CFormatIdx<T>::value] ;}

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if ENABLE_UNSAFE_SCANPRINT
        template<typename char_T> struct StrScanfType           : Type2Type<int (__cdecl *)(const char_T *,const char_T *,...)>         {};
        template<typename char_T> struct GetScanfFunc;
        template<>                struct GetScanfFunc<char>     : Value2Type<typename StrScanfType<char>::type, sscanf>                 {}; 
        template<>                struct GetScanfFunc<wchar_t>  : Value2Type<typename StrScanfType<wchar_t>::type, swscanf>             {}; 
#endif // ENABLE_UNSAFE_SCANPRINT
        
        template<typename char_T> struct StrScanfTypeS           : Type2Type<int (__cdecl *)(const char_T *,const char_T *,...)>        {};
        template<typename char_T> struct GetScanfFuncS;
        template<>                struct GetScanfFuncS<char>     : Value2Type<typename StrScanfTypeS<char>::type, sscanf_s>              {}; 
        template<>                struct GetScanfFuncS<wchar_t>  : Value2Type<typename StrScanfTypeS<wchar_t>::type, swscanf_s>          {}; 

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if ENABLE_UNSAFE_SCANPRINT
        template<typename char_T> struct StrPrintType           : Type2Type<int (__cdecl *)(char_T *,const char_T *,...)>               {};
        template<typename char_T> struct GetPrintfFunc;
        template<>                struct GetPrintfFunc<char>    : Value2Type<typename StrPrintType<char>::type, sprintf>                {}; 
        template<>                struct GetPrintfFunc<wchar_t> : Value2Type<typename StrPrintType<wchar_t>::type, swprintf>            {}; 
#endif // ENABLE_UNSAFE_SCANPRINT

        template<typename char_T> struct StrPrintTypeS          : Type2Type<int (__cdecl *)(char_T *,unsigned int,const char_T *,...)>  {};
        template<typename char_T> struct GetPrintfFuncS;
        template<>                struct GetPrintfFuncS<char>   : Value2Type<typename StrPrintTypeS<char>::type, sprintf_s>             {}; 
        template<>                struct GetPrintfFuncS<wchar_t>: Value2Type<typename StrPrintTypeS<wchar_t>::type, swprintf_s>         {}; 
}

#endif // __SCANPRINT_HPP__
