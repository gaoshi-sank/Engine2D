#include <Windows.h>
#include "Win32/WinBox.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) 
{
    BaseWindow* apptest = new BaseWindow(hInstance);
    if (apptest) {
        apptest->Create();
        apptest->MessageControl();
    }

    return 0;
}