#include <Windows.h>
#include "Win32/WinBox.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) 
{
    WinBox* apptest = new WinBox(hInstance);
    if (apptest) {
        apptest->Create(0, 0, 640, 480);
    }

    return 0;
}