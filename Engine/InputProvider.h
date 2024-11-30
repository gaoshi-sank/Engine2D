/*
* �򵥿����� -- ����Win32API��Ϣ
*/
#ifndef _InputProvider_H_
#define _InputProvider_H_

enum MOUSESTATUS {
	MOUSESTATUS_LEFT = 0,
	MOUSESTATUS_MID,
	MOUSESTATUS_RIGHT
};

// ����״ֵ̬
const int UP = 2;
const int DOWN = 1;
const int NONE = 0;



// ������
class InputProvider {
private:
	int key_status[256];
	int mouse_status[3];
	int mouse_pos[2];

private:
	// ����
	InputProvider();
	
	// ����
	~InputProvider();

public:
	// ��ȡʵ��
	static InputProvider* GetInstance();

	// �ͷ�
	static void Release();

	// ��ʼ��״̬
	void InitStatus();

	// ���ü���״̬
	void SetKeyStatus(int MainKey, int status);

	// �������״̬
	void SetMouseStatus(int MainKey, int status);

	// �������λ��
	void SetMousePos(int x, int y);

	// ��ȡ����״̬
	int GetKeyStatus(int MainKey);

	// ��ȡ���״̬
	int GetMouseStatus(int MainKey);

	// ��ȡ���λ��
	void GetMousePos(int& x, int& y);

};



#endif // !_InputProvider_H_