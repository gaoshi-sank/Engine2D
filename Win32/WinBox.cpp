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

    // ��������
    int x, y, width, height;
    x = 0;
    y = 0;
    width = 800;
    height = 600;
    m_hWnd = CreateWindow(
        szWindowClass,                 // ����
        szTitle,                       // ��������
        WS_OVERLAPPEDWINDOW,           // ���ڵĴ�����ʽ
        x,
        y,
        width,
        height,
        nullptr,
        nullptr,
        m_hinstance,                    // ʵ�����
        (LPVOID)this);                  // ���ⴴ������

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