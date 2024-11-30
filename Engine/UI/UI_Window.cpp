#include "UI_Window.h"
#include "../UIProvider.h"

// ��������
static unsigned int baseid = 0x00;										// ���ڱ��
const float config_windowtitle_height = 16.0f;							// ��������߶�
const float window_title_height = 0.125f;								// ����߶�

// ����
UI_Window::UI_Window() {
	// ��������
	this->window_id = ++baseid;				// ���ڱ�� 
	this->window_style = WindowType_Base;	// �������� 
	this->window_level = 0;					// ��С - ������
	this->window_base = 0;					// Ĭ��Ϊ�������ڣ����������ⴰ��
	this->window_tip = 0;					// �ޱ�־
	this->window_visible = true;			// �����ɼ��¼� 
	this->window_active = true;				// ���������¼� 
	this->window_key = false;				// ���������¼� 
	this->window_mouse = true;				// ��������¼� 
	this->window_allowacyive = true;		// ���������������¼�
	this->window_rect = RECT();				// ��������
	this->cursor_pos = POINT();				// ���λ��
	this->window_inrect = false;			// ���ڴ�����
	this->window_renderlevel = 0x00;		// ������Ⱦ�ȼ�
	this->window_release = false;			// δ�ͷ�

}

// ����
UI_Window::~UI_Window() {

}

// ����
bool UI_Window::Create() {
	UIProvider::AddWindow(this);
	return true;
}

// �����¼�
void UI_Window::CheckEvent(int* param) {
	if (!param) {
		return;
	}

	int paramlen = param[0];
	if (paramlen < 2) {
		return;
	}

	int message = param[1];
	switch (message) {
	case WM_MOUSEMOVE:
	{
		if (paramlen >= 4) {
			cursor_pos.x = param[2];
			cursor_pos.y = param[3];
		}
	}
		break;
	default:
		break;
	}
}

// �ͷ�
void UI_Window::Release() {
	// �޳������б�
	UIProvider::DelWindow(this);

	// ����״̬
	this->window_id = 0x00;
	this->window_release = true;
}

// ���� 
void UI_Window::Update() {
	// �ж�����
	window_inrect = false;
	auto ret_top = UIProvider::GetLevelTop(this, cursor_pos);

	// ���� -- �ɼ�״̬
	if (ret_top && window_visible) {
		if (Point_In_Rect(cursor_pos, window_rect)) {
			window_inrect = true;
		}
	}
}

// ���� 
void UI_Window::Draw() {

}

// ���ô�������
void UI_Window::MoveWindow(RECT _rect) {
	// ��������
	window_rect = _rect;
}

// ���ÿɼ���
void UI_Window::SetVisiable(bool life) {
	window_visible = life;
}

// ���ø������ڱ��
void UI_Window::SetFather(unsigned int _father) {
	this->window_base = _father;
}