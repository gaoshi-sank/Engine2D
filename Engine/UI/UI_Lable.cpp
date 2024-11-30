#include "UI_Lable.h"


// 构造 
UI_Lable::UI_Lable() {
	// 窗口类型 
	this->window_style = WindowType_Static;

	// 静态
	_image = nullptr;
	_text = nullptr;
}

// 析构
UI_Lable::~UI_Lable() {

}

// 创建
bool UI_Lable::Create() {
	return UI_Window::Create();
}

// 构造
bool UI_Lable::Create(std::string filename, D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);
	if (!filename.empty() && !_image) {
		_image = SpriteProvider::CreateImage(filename.c_str(), _rect);
	}
	return Create();
}

// 释放
void UI_Lable::Release() {
	// 文本 
	if (_text) {
		_text->Release();
		delete _text;
		_text = nullptr;
	}

	// 图像
	if (_image) {
		_image->Release();
		delete _image;
		_image = nullptr;
	}


	UI_Window::Release();
}

// 更新事件
void UI_Lable::CheckEvent(int* param) {
	UI_Window::CheckEvent(param);
}

// 更新
void UI_Lable::Update() {

	// 图像 
	if (_image) {
		_image->Update();
	}

	// 文本 
	if (_text) {
		_text->Update();
	}
}

// 渲染
void UI_Lable::Draw() {

	// 图像 
	if (_image) {
		_image->Draw();
	}

	// 文本 
	if (_text) {
		_text->Draw();
	}

}

// 设置窗口区域
void UI_Lable::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// 图像 
	if (_image) {
		_image->rect = _rect;
	}

	// 文本 
	if (_text) {
		_text->ReSetRect(_rect);
	}
}

// 设置可见性
void UI_Lable::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// 图像
	if (_image) {
		_image->visiable = life;
	}

}

// 设置文本
void UI_Lable::SetStaticText(const char* text) {
	if (!_text) {
		_text = SpriteProvider::CreateText(text, window_rect, D2D1::ColorF(255, 255,0));
	}
}