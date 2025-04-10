#include <MiniMPL/libConfig.h>
#include <MiniMPL/placeHolder.hpp>
#include <MiniMPL/classRegister.hpp>

#if defined(_WIN32)	
    #include <windows.h>
#endif 

namespace MiniMPL
{
#if defined(_WIN32)
    inline void CDECL_CALL outputDebugger(const wchar_t* pStr)
    {
        if (IsDebuggerPresent())
        {
            OutputDebugStringW(pStr);
        }
    }

    inline void CDECL_CALL outputDebugger(const char* pStr)
    {
        if (IsDebuggerPresent())
        {
            OutputDebugStringA(pStr);
        }
    }    
#else
    //OS dependent,Not impl,issue a linker error to block procedure
    void CDECL_CALL outputDebugger(const wchar_t* pStr);
    void CDECL_CALL outputDebugger(const wchar_t* pStr);
#endif
}

namespace MiniMPL	
{
    //used by placeHolder.hpp and all placeholder user.
    _ _$;

    //////////////////////////////////////////////////////////////////////////
    //used by classRegister.hpp
    ClassRegister* ClassRegister::gs_pHeader=NULL;

    //////////////////////////////////////////////////////////////////////////
    //used by MiniMPL/InnerDetail/fromToString_detail.hpp
    //                                  0       1      2      3     4       5         6       7
    extern char const*    strFmtA[] = {"%c",   "%d",  "%u",  "%f",  "%lf",  "%s",  "%I64d",  "%I64u" };
    extern wchar_t const* strFmtW[] = {L"%c", L"%d", L"%u", L"%f", L"%lf", L"%s", L"%I64d", L"%I64u" };
#if USE_UNICODE_STRING==0
    extern char const**     strFmt = strFmtA;
#else
    extern wchar_t const**  strFmt = strFmtW;
#endif

    //////////////////////////////////////////////////////////////////////////
    inline void CDECL_CALL dbgOutput(const wchar_t* pStr)
    {
        CHECK_NULL_ELSE_RETURN_VAL(pStr,);        
        std::wcout << pStr;
        outputDebugger(pStr);
    }

    inline void CDECL_CALL dbgOutput(const char* pStr)
    {
        CHECK_NULL_ELSE_RETURN_VAL(pStr,);
        std::cout << pStr;
        outputDebugger(pStr);
    }

#define MaxOutputBufLen         2048
    void CDECL_CALL dbgOutputV (const wchar_t* format,...)
    {
        wchar_t		Buf[MaxOutputBufLen] = {0};

        va_list		arglist; 
        va_start(arglist, format);
        vswprintf_s(Buf,MaxOutputBufLen, format, arglist);
        va_end(arglist);

        dbgOutput(Buf);  //output to console and debugger output window
    }
    void CDECL_CALL dbgOutputV (const char* format,...)
    {
        char		Buf[MaxOutputBufLen] = {0};

        va_list		arglist; 
        va_start(arglist, format);
        vsprintf_s(Buf,MaxOutputBufLen, format, arglist);
        va_end(arglist);

        dbgOutput(Buf);  //output to console and debugger output window
    }
}
