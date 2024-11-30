#include "WindowProvider.h"


// ----------------------------------------------------------------------------
// BaseWindow
// ----------------------------------------------------------------------------

// 构造
BaseWindow::BaseWindow() {
    m_hWnd = nullptr;
    m_fatherhWnd = nullptr;
    m_hinstance = nullptr;
    m_menu = nullptr;
    Error = BuildError_None;
    x = y = 0;
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
    style = WS_POPUP | WS_VISIBLE;
    isfull = true;

    wsprintf(szTitle, L"Engine2D");
    wsprintf(szWindowClass, L"Engine2D_%p", this);

}

// 构造
// 实例句柄
BaseWindow::BaseWindow(HINSTANCE hinstance) : BaseWindow() {
    m_hinstance = hinstance;
}

// 析构
BaseWindow::~BaseWindow() {

}

// 创建 - 基础参数
void BaseWindow::Create() {

    // 区分窗口类别
    if (m_hinstance && !m_fatherhWnd) {
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
    }
   
    // 创建窗口
    m_hWnd = CreateWindow(
        szWindowClass,  // 类名
        szTitle,        // 窗口名称
        style,          // 窗口的创建样式
        x,
        y,
        width,
        height,
        m_fatherhWnd,   // 父窗口
        m_menu,         // 菜单栏
        m_hinstance,    // 实例句柄
        (LPVOID)this);  // 额外创建参数

    if (!m_hWnd) {
        Error = BuildError_BuildhWnd;
        return;
    }

    // 区分窗口类别
    if (m_hinstance && !m_fatherhWnd) {
        // 保存
        SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

        // 显示和更新
        ShowWindow(m_hWnd, isfull ? SW_MAXIMIZE : SW_SHOW);
        UpdateWindow(m_hWnd);
    }
}

// 消息控制 - 死循环
void BaseWindow::MessageControl() {

    MSG msg = { 0 };
    while (1) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                break;
            }
        }
    }

}

// 实例处理的回调函数
LRESULT CALLBACK BaseWindow::HandleProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

// 全局用窗口回调函数
LRESULT CALLBACK BaseWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    BaseWindow* ptr = reinterpret_cast<BaseWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (ptr) {
        // 通知到实例的窗口回调函数
        return ptr->HandleProc(hwnd, message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}


// ----------------------------------------------------------------------------
// WindowProvider
// ----------------------------------------------------------------------------

// 构造
WindowProvider::WindowProvider() {


}

// 构造
// 父类句柄
WindowProvider::WindowProvider(HWND fatherhWnd) : WindowProvider() {
    m_fatherhWnd = fatherhWnd;
}

// 构造
// 实例句柄
WindowProvider::WindowProvider(HINSTANCE hinstance) : WindowProvider() {
    m_hinstance = hinstance;
}

// 析构
WindowProvider::~WindowProvider() {

}

// 创建
// 全屏
void WindowProvider::Create() {
    // 空窗口
    if (!m_hWnd) {
        style = WS_POPUP | WS_VISIBLE;
        if (m_fatherhWnd) {
            style =  WS_VISIBLE | WS_CHILD;
        }

        // 创建
        BaseWindow::Create();
    }
}

// 创建
// 位置、宽度、高度
void WindowProvider::Create(int x, int y, int width, int height) {
    // 空窗口
    if(!m_hWnd){
        // 修正
        this->x = (x <= 0) ? 0 : x;
        this->y = (y <= 0) ? 0 : y;
        this->width = (width <= 0) ? 480 : width;
        this->height = (height <= 0) ? 320 : height;
        style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
        isfull = false;
        if (m_fatherhWnd) {
            style =  WS_VISIBLE | WS_CHILD;
        }

        // 创建
        BaseWindow::Create();
    }
}

// 创建
// 标题，类型，位置、宽度、高度
void WindowProvider::Create(const wchar_t* _title, const wchar_t* _style, int x, int y, int width, int height) {
    
    if (_title) {
        wsprintf(szTitle, L"%s", _title);
    }
    
    if (_style) {
        wsprintf(szWindowClass, L"%s", _style);
    }
   
    // 创建
    Create(x, y, width, height);

}

// 循环消息处理
void WindowProvider::MessageControl() {
    BaseWindow::MessageControl();
}

// 返回句柄
HWND WindowProvider::GetHandle() {
    return m_hWnd;
}

// 返回父类窗口句柄
HWND WindowProvider::GetFatherHandle() {
    return m_fatherhWnd;
}

// 回调函数
LRESULT CALLBACK WindowProvider::HandleProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return BaseWindow::HandleProc(hwnd, message, wParam, lParam);
}