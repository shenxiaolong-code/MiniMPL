#include <UT_material/WinMsgWindProcHelper.h>

HWND msgControlWindow = NULL;
const wchar_t *windowClassName = L"windowsMessageQueueHelper";

LRESULT CALLBACK MessageWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    /*/
    //for example based on your business
    if (message == WM_COPYDATA)
    {
    }
    //*/
    return ::DefWindowProc(hWnd, message, wParam, lParam);
}

void WinMsgQueueHelper::CreateHelperWindow()
{
    if (msgControlWindow == nullptr)
    {
        WNDCLASSEX wcex;
        ZeroMemory(&wcex, sizeof(WNDCLASSEX));

        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.lpfnWndProc = MessageWindowProc;
        wcex.hInstance = nullptr;
        wcex.lpszClassName = windowClassName;

        RegisterClassEx(&wcex);
        msgControlWindow = ::CreateWindow(windowClassName, windowClassName, NULL, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
    }
}

void WinMsgQueueHelper::DestroyHelperWindow()
{   
    if (msgControlWindow)
    {
        ::DestroyWindow(msgControlWindow);
        msgControlWindow = nullptr;
    }
}

LRESULT WinMsgQueueHelper::SendMessage(HWND hWnd, UINT Msg, WPARAM wp, LPARAM lp)
{
    HWND hwDispatch = FindWindowEx(NULL, NULL, windowClassName, windowClassName);
    if (hwDispatch != nullptr)
    {
        return ::SendMessage(hwDispatch, Msg, wp, lp);
    }
    return S_FALSE;
}

