#ifndef _WinBox_h_
#define _WinBox_h_

#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

enum BuildError {
	BuildError_None = 0,
	BuildError_Register,
	BuildError_BuildhWnd,
};

class BaseWindow {
public:
	HWND m_hWnd;
	HWND m_fatherhWnd;
	HINSTANCE m_hinstance;
	int Error;

	int style;
	int x, y, width, height;
	bool isfull;

public:
	BaseWindow();
	BaseWindow(HINSTANCE hinstance);
	~BaseWindow();
	
	// 创建 - 基础参数
	void Create();

	// 消息控制 - 死循环
	virtual void MessageControl();

	// 实例处理的回调函数
	virtual LRESULT CALLBACK HandleProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	// 全局用窗口回调函数
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

class WinBox : private BaseWindow {
private:
	std::thread* main_thread;
	int status_mainThread;

public:
	// 构造
	WinBox();

	// 构造
	// 实例句柄
	WinBox(HINSTANCE hinstance);

	// 析构
	~WinBox();

	// 创建
	// 全屏
	void CreateFull();

	// 创建
	// 位置和宽高度
	void Create(int x, int y, int width, int height);

	// 设置父窗口句柄
	// 需要在Create之前调用
	void setFatherhWnd(HWND hwnd);

private:
	// 循环消息处理
	virtual void MessageControl();

	// 回调函数
	virtual LRESULT CALLBACK HandleProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

#endif //!_WinBox_h_