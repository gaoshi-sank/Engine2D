#include "InputProvider.h"
#include "string.h"

static InputProvider* g_input = nullptr;

// 构造
InputProvider::InputProvider() {
	// 基础属性
	memset(key_status, 0, sizeof(int) * 256);
	memset(mouse_status, 0, sizeof(int) * 3);
	memset(mouse_pos, 0, sizeof(int) * 2);
}

// 析构
InputProvider::~InputProvider() {

}

// 获取实例
InputProvider* InputProvider::GetInstance() {
	if (!g_input) {
		g_input = new InputProvider();
	}
	return g_input;
}

// 释放
void InputProvider::Release() {
	if (g_input) {
		delete g_input;
		g_input = nullptr;
	}
}

// 初始化状态
void InputProvider::InitStatus() {

}

// 设置键盘状态
void InputProvider::SetKeyStatus(int MainKey, int status) {
	if (MainKey >= 0 && MainKey < 256) {
		key_status[MainKey] = status;
	}
}

// 设置鼠标状态
void InputProvider::SetMouseStatus(int MainKey, int status) {
	if (MainKey >= 0 && MainKey < 3) {
		mouse_status[MainKey] = status;
	}
}

// 设置鼠标位置
void InputProvider::SetMousePos(int x, int y) {
	mouse_pos[0] = x;
	mouse_pos[1] = y;
}

// 获取键盘状态
int InputProvider::GetKeyStatus(int MainKey) {
	if (MainKey >= 0 && MainKey < 256) {
		return key_status[MainKey];
	}
	return -1;
}

// 获取鼠标状态
int InputProvider::GetMouseStatus(int MainKey) {
	if (MainKey >= 0 && MainKey < 3) {
		return mouse_status[MainKey];
	}
	return -1;
}

// 获取鼠标位置
void InputProvider::GetMousePos(int& x, int& y) {
	x = mouse_pos[0];
	y = mouse_pos[1];
}