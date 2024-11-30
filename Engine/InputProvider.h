/*
* 简单控制器 -- 传递Win32API消息
*/
#ifndef _InputProvider_H_
#define _InputProvider_H_

enum MOUSESTATUS {
	MOUSESTATUS_LEFT = 0,
	MOUSESTATUS_MID,
	MOUSESTATUS_RIGHT
};

// 部分状态值
const int UP = 2;
const int DOWN = 1;
const int NONE = 0;



// 控制类
class InputProvider {
private:
	int key_status[256];
	int mouse_status[3];
	int mouse_pos[2];

private:
	// 构造
	InputProvider();
	
	// 析构
	~InputProvider();

public:
	// 获取实例
	static InputProvider* GetInstance();

	// 释放
	static void Release();

	// 初始化状态
	void InitStatus();

	// 设置键盘状态
	void SetKeyStatus(int MainKey, int status);

	// 设置鼠标状态
	void SetMouseStatus(int MainKey, int status);

	// 设置鼠标位置
	void SetMousePos(int x, int y);

	// 获取键盘状态
	int GetKeyStatus(int MainKey);

	// 获取鼠标状态
	int GetMouseStatus(int MainKey);

	// 获取鼠标位置
	void GetMousePos(int& x, int& y);

};



#endif // !_InputProvider_H_
