#ifndef winMsgWindProcHelper_h__
#define winMsgWindProcHelper_h__
#include <windows.h>

class WinMsgQueueHelper
{
public:
    static void CreateHelperWindow();
    static void DestroyHelperWindow();
    static LRESULT SendMessage(HWND hWnd, UINT Msg, WPARAM wp, LPARAM lp);
};

#endif // winMsgWindProcHelper_h__
