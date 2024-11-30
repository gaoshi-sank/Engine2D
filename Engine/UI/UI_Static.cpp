#include "UI_Static.h"


// 构造 
UI_Static::UI_Static() {
	// 窗口类型 
	this->window_style = WindowType_Static;

	// 静态文本
	text = nullptr;
}

// 析构
UI_Static::~UI_Static() {

}

// 创建
bool UI_Static::Create() {
	return UI_Window::Create();
}

// 创建
bool UI_Static::Create(std::string _name, D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);
	if (!_name.empty() && !text) {
		text = SpriteProvider::CreateText(_name.c_str(), _rect);
	}
	return Create();
}

// 更新事件
void UI_Static::CheckEvent(int* param) {
	UI_Window::CheckEvent(param);
}

// 释放
void UI_Static::Release() {
	// 文本 
	if (text) {
		text->Release();
		delete text;
		text = nullptr;
	}

	UI_Window::Release();
}

// 更新
void UI_Static::Update() {
	UI_Window::Update();
	
	// 文本 
	if (text) {
		text->Update();
	}

}

// 渲染
void UI_Static::Draw() {
	UI_Window::Draw();

	// 文本 
	if (text) {
		text->Draw();
	}
}

// 设置窗口区域
void UI_Static::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// 文本
	if (text) {
		text->text_rect = _rect;
	}
}

// 设置可见性
void UI_Static::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// 文本
	if (text) {
		text->visiable = life;
	}

}
