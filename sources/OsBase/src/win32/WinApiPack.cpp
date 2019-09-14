#include <win32/WinApiPack.h>
#include <Windows.h>
#include <MiniMPL/macro_makeTxt.h>

namespace OS_Win32
{
    stlString GetErrorText( unsigned eCode )
    {
        LPVOID lpMsgBuf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, eCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0,NULL);

        stlString errText;
        if (lpMsgBuf)
        {
            errText = (LPCTSTR)lpMsgBuf;
        }
        else
        {
            errText = TXT("[Message not Found]");
        }
        
        LocalFree( lpMsgBuf );
        return errText;
    }
}

