#include "InputProvider.h"
#include "string.h"

static InputProvider* g_input = nullptr;

// ����
InputProvider::InputProvider() {
	// ��������
	memset(key_status, 0, sizeof(int) * 256);
	memset(mouse_status, 0, sizeof(int) * 3);
	memset(mouse_pos, 0, sizeof(int) * 2);
}

// ����
InputProvider::~InputProvider() {

}

// ��ȡʵ��
InputProvider* InputProvider::GetInstance() {
	if (!g_input) {
		g_input = new InputProvider();
	}
	return g_input;
}

// �ͷ�
void InputProvider::Release() {
	if (g_input) {
		delete g_input;
		g_input = nullptr;
	}
}

// ��ʼ��״̬
void InputProvider::InitStatus() {

}

// ���ü���״̬
void InputProvider::SetKeyStatus(int MainKey, int status) {
	if (MainKey >= 0 && MainKey < 256) {
		key_status[MainKey] = status;
	}
}

// �������״̬
void InputProvider::SetMouseStatus(int MainKey, int status) {
	if (MainKey >= 0 && MainKey < 3) {
		mouse_status[MainKey] = status;
	}
}

// �������λ��
void InputProvider::SetMousePos(int x, int y) {
	mouse_pos[0] = x;
	mouse_pos[1] = y;
}

// ��ȡ����״̬
int InputProvider::GetKeyStatus(int MainKey) {
	if (MainKey >= 0 && MainKey < 256) {
		return key_status[MainKey];
	}
	return -1;
}

// ��ȡ���״̬
int InputProvider::GetMouseStatus(int MainKey) {
	if (MainKey >= 0 && MainKey < 3) {
		return mouse_status[MainKey];
	}
	return -1;
}

// ��ȡ���λ��
void InputProvider::GetMousePos(int& x, int& y) {
	x = mouse_pos[0];
	y = mouse_pos[1];
}