#include "UI_Static.h"


// ���� 
UI_Static::UI_Static() {
	// �������� 
	this->window_style = WindowType_Static;

	// ��̬�ı�
	text = nullptr;
}

// ����
UI_Static::~UI_Static() {

}

// ����
bool UI_Static::Create() {
	return UI_Window::Create();
}

// ����
bool UI_Static::Create(std::string _name, D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);
	if (!_name.empty() && !text) {
		text = SpriteProvider::CreateText(_name.c_str(), _rect);
	}
	return Create();
}

// �ͷ�
void UI_Static::Release() {
	// �ı� 
	if (text) {
		text->Release();
		delete text;
		text = nullptr;
	}

	UI_Window::Release();
}

// �����¼�
void UI_Static::CheckEvent(int* param) {

}

// ����
void UI_Static::Update() {
	UI_Window::Update();
	
	// �ı� 
	if (text) {
		text->Update();
	}

}

// ��Ⱦ
void UI_Static::Draw() {
	UI_Window::Draw();

	// �ı� 
	if (text) {
		text->Draw();
	}
}

// ���ô�������
void UI_Static::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// �ı�
	if (text) {
		text->text_rect = _rect;
	}
}

// ���ÿɼ���
void UI_Static::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// �ı�
	if (text) {
		text->visiable = life;
	}

}