#ifndef _WinBox_h_
#define _WinBox_h_

#include <Windows.h>

enum BuildError {
	BuildError_None = 0,
	BuildError_Register,
	BuildError_BuildhWnd,
};

class BaseWindow {
private:
	HWND m_hWnd;
	HINSTANCE m_hinstance;
	int Error;

public:
	BaseWindow();
	BaseWindow(HINSTANCE hinstance);
	~BaseWindow();

	void Create();
	void MessageControl();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

class WinBox {


};

#endif //!_WinBox_h_