#include "WinBox.h"


// ----------------------------------------------------------------------------
// BaseWindow
// ----------------------------------------------------------------------------

// ����
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

// ����
// ʵ�����
BaseWindow::BaseWindow(HINSTANCE hinstance) : BaseWindow() {
    m_hinstance = hinstance;
}

// ����
BaseWindow::~BaseWindow() {

}

// ���� - ��������
void BaseWindow::Create() {

    // ���ִ������
    if (m_hinstance && !m_fatherhWnd) {
        WNDCLASS wcex = { 0 };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.lpfnWndProc = WndProc;                         // ���� ���ڻص�
        wcex.hInstance = m_hinstance;                       // ���� ģ��ʵ�����
        wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);    // ���� Ĭ��ͼ��
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);      // ���� Ĭ�Ϲ��
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    // ���� ������ɫ
        wcex.lpszMenuName = L"";                            // ���� ������
        wcex.lpszClassName = szWindowClass;                 // ���� ����

        if (!RegisterClass(&wcex)) {
            Error = BuildError_Register;
            return;
        }
    }
   
    // ��������
    m_hWnd = CreateWindow(
        szWindowClass,  // ����
        szTitle,        // ��������
        style,          // ���ڵĴ�����ʽ
        x,
        y,
        width,
        height,
        m_fatherhWnd,   // ������
        m_menu,         // �˵���
        m_hinstance,    // ʵ�����
        (LPVOID)this);  // ���ⴴ������

    if (!m_hWnd) {
        Error = BuildError_BuildhWnd;
        return;
    }

    // ���ִ������
    if (m_hinstance && !m_fatherhWnd) {
        // ����
        SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

        // ��ʾ�͸���
        ShowWindow(m_hWnd, isfull ? SW_MAXIMIZE : SW_SHOW);
        UpdateWindow(m_hWnd);
    }
}

// ��Ϣ���� - ��ѭ��
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

// ʵ�������Ļص�����
LRESULT CALLBACK BaseWindow::HandleProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

// ȫ���ô��ڻص�����
LRESULT CALLBACK BaseWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    BaseWindow* ptr = reinterpret_cast<BaseWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (ptr) {
        // ֪ͨ��ʵ���Ĵ��ڻص�����
        return ptr->HandleProc(hwnd, message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}


// ----------------------------------------------------------------------------
// WinBox
// ----------------------------------------------------------------------------

// ����
WinBox::WinBox() {


}

// ����
// ������
WinBox::WinBox(HWND fatherhWnd) : WinBox() {
    m_fatherhWnd = fatherhWnd;
}

// ����
// ʵ�����
WinBox::WinBox(HINSTANCE hinstance) : WinBox() {
    m_hinstance = hinstance;
}

// ����
WinBox::~WinBox() {

}

// ����
// ȫ��
void WinBox::Create() {
    // �մ���
    if (!m_hWnd) {
        style = WS_POPUP | WS_VISIBLE;
        if (m_fatherhWnd) {
            style =  WS_VISIBLE | WS_CHILD;
        }

        // ����
        BaseWindow::Create();
    }
}

// ����
// λ�á����ȡ��߶�
void WinBox::Create(int x, int y, int width, int height) {
    // �մ���
    if(!m_hWnd){
        // ����
        this->x = (x <= 0) ? 0 : x;
        this->y = (y <= 0) ? 0 : y;
        this->width = (width <= 0) ? 480 : width;
        this->height = (height <= 0) ? 320 : height;
        style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
        isfull = false;
        if (m_fatherhWnd) {
            style =  WS_VISIBLE | WS_CHILD;
        }

        // ����
        BaseWindow::Create();
    }
}

// ����
// ���⣬���ͣ�λ�á����ȡ��߶�
void WinBox::Create(const wchar_t* _title, const wchar_t* _style, int x, int y, int width, int height) {
    
    if (_title) {
        wsprintf(szTitle, L"%s", _title);
    }
    
    if (_style) {
        wsprintf(szWindowClass, L"%s", _style);
    }
   
    // ����
    Create(x, y, width, height);

}

// ѭ����Ϣ����
void WinBox::MessageControl() {
    BaseWindow::MessageControl();
}

// ���ؾ��
HWND WinBox::GetHandle() {
    return m_hWnd;
}

// ���ظ��ര�ھ��
HWND WinBox::GetFatherHandle() {
    return m_fatherhWnd;
}

// �ص�����
LRESULT CALLBACK WinBox::HandleProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return BaseWindow::HandleProc(hwnd, message, wParam, lParam);
}