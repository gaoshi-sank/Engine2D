#ifndef _WindowProvider_h_
#define _WindowProvider_h_

// 包含库
#include "EngineConfig.h"

enum BuildError {
	BuildError_None = 0,
	BuildError_Register,
	BuildError_BuildhWnd,
};

// 
class BaseWindow {
public:
	HWND m_hWnd;				// 当前窗口句柄
	HWND m_fatherhWnd;			// 父窗口句柄
	HINSTANCE m_hinstance;		// 实例句柄
	HMENU m_menu;				// 菜单句柄（子窗口ID）
	int Error;					// 标准错误值
	int style;					// 窗口风格
	int x, y, width, height;	// 窗口区域
	bool isfull;				// 全屏状态
	wchar_t szTitle[32];		// 标题
	wchar_t szWindowClass[16];	// 类名

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

// 
class WindowProvider : private BaseWindow {
public:
	// 构造
	WindowProvider();

	// 构造
	// 父类句柄
	WindowProvider(HWND fatherhWnd);

	// 构造
	// 实例句柄
	WindowProvider(HINSTANCE hinstance);

	// 析构
	~WindowProvider();

	// 创建
	// 全屏
	void Create();

	// 创建
	// 位置、宽度、高度
	void Create(int x, int y, int width, int height);

	// 创建
	// 标题，类型，位置、宽度、高度
	void Create(const wchar_t* _title, const wchar_t* _style, int x, int y, int width, int height);

	// 循环消息处理
	virtual void MessageControl();

	// 返回句柄
	virtual HWND GetHandle();

	// 返回父类窗口句柄
	virtual HWND GetFatherHandle();

private:
	// 回调函数
	virtual LRESULT CALLBACK HandleProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

#endif //!_WindowProvider_h_