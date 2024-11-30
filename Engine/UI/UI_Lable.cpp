#include "UI_Lable.h"


// ���� 
UI_Lable::UI_Lable() {
	// �������� 
	this->window_style = WindowType_Static;

	// ��̬
	_image = nullptr;
	_text = nullptr;
}

// ����
UI_Lable::~UI_Lable() {

}

// ����
bool UI_Lable::Create() {
	return UI_Window::Create();
}

// ����
bool UI_Lable::Create(std::string filename, D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);
	if (!filename.empty() && !_image) {
		_image = SpriteProvider::CreateImage(filename.c_str(), _rect);
	}
	return Create();
}

// �ͷ�
void UI_Lable::Release() {
	// �ı� 
	if (_text) {
		_text->Release();
		delete _text;
		_text = nullptr;
	}

	// ͼ��
	if (_image) {
		_image->Release();
		delete _image;
		_image = nullptr;
	}


	UI_Window::Release();
}

// �����¼�
void UI_Lable::CheckEvent(int* param) {

}

// ����
void UI_Lable::Update() {

	// ͼ�� 
	if (_image) {
		_image->Update();
	}

	// �ı� 
	if (_text) {
		_text->Update();
	}
}

// ��Ⱦ
void UI_Lable::Draw() {

	// ͼ�� 
	if (_image) {
		_image->Draw();
	}

	// �ı� 
	if (_text) {
		_text->Draw();
	}

}

// ���ô�������
void UI_Lable::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// ͼ�� 
	if (_image) {
		_image->rect = _rect;
	}

	// �ı� 
	if (_text) {
		_text->ReSetRect(_rect);
	}
}

// ���ÿɼ���
void UI_Lable::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// ͼ��
	if (_image) {
		_image->visiable = life;
	}

}

// �����ı�
void UI_Lable::SetStaticText(const char* text) {
	if (!_text) {
		_text = SpriteProvider::CreateText(text, window_rect, D2D1::ColorF(255, 255,0));
	}
}