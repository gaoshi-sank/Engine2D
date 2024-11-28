#include "WinBox.h"



BaseWindow::BaseWindow() {
    m_hWnd = nullptr;
    m_hinstance = nullptr;
    Error = 0;

}

BaseWindow::BaseWindow(HINSTANCE hinstance) : BaseWindow() {
    m_hinstance = hinstance;
}

BaseWindow::~BaseWindow() {

}

void BaseWindow::Create() {

    wchar_t szTitle[] = { L"Engine2D" };
    wchar_t szWindowClass[] = { L"Engine2D" };

    WNDCLASS wcex = { 0 };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.lpfnWndProc = WndProc;                         // 设置 窗口回调
    wcex.hInstance = m_hinstance;                       // 设置 模块实例句柄
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);    // 设置 默认图标
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);      // 设置 默认光标
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    // 设置 背景颜色
    wcex.lpszMenuName = L"";                            // 设置 标题名
    wcex.lpszClassName = szWindowClass;                 // 设置 类名

    if (!RegisterClass(&wcex)) {
        Error = BuildError_Register;
        return;
    }

    // 创建窗口
    int x, y, width, height;
    x = 0;
    y = 0;
    width = 800;
    height = 600;
    m_hWnd = CreateWindow(
        szWindowClass,                 // 类名
        szTitle,                       // 窗口名称
        WS_OVERLAPPEDWINDOW,           // 窗口的创建样式
        x,
        y,
        width,
        height,
        nullptr,
        nullptr,
        m_hinstance,                    // 实例句柄
        (LPVOID)this);                  // 额外创建参数

    if (!m_hWnd) {
        Error = BuildError_BuildhWnd;
        return;
    }

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

}

void BaseWindow::MessageControl() {

    MSG msg = { 0 };
    while (1) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                break;
            }
            else {
                
            }
        }
    }

}

LRESULT CALLBACK BaseWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    if (message == WM_CREATE) {

    }

    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK BaseWindow::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}