#ifndef _WinBox_h_
#define _WinBox_h_

#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

enum BuildError {
	BuildError_None = 0,
	BuildError_Register,
	BuildError_BuildhWnd,
};

class BaseWindow {
public:
	HWND m_hWnd;				// ��ǰ���ھ��
	HWND m_fatherhWnd;			// �����ھ��
	HINSTANCE m_hinstance;		// ʵ�����
	HMENU m_menu;				// �˵�������Ӵ���ID��
	int Error;					// ��׼����ֵ
	int style;					// ���ڷ��
	int x, y, width, height;	// ��������
	bool isfull;				// ȫ��״̬
	wchar_t szTitle[32];		// ����
	wchar_t szWindowClass[16];	// ����

public:
	BaseWindow();
	BaseWindow(HINSTANCE hinstance);
	~BaseWindow();
	
	// ���� - ��������
	void Create();

	// ��Ϣ���� - ��ѭ��
	virtual void MessageControl();

	// ʵ�������Ļص�����
	virtual LRESULT CALLBACK HandleProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	// ȫ���ô��ڻص�����
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

class WinBox : private BaseWindow {
public:
	// ����
	WinBox();

	// ����
	// ������
	WinBox(HWND fatherhWnd);

	// ����
	// ʵ�����
	WinBox(HINSTANCE hinstance);

	// ����
	~WinBox();

	// ����
	// ȫ��
	void Create();

	// ����
	// λ�á����ȡ��߶�
	void Create(int x, int y, int width, int height);

	// ����
	// ���⣬���ͣ�λ�á����ȡ��߶�
	void Create(const wchar_t* _title, const wchar_t* _style, int x, int y, int width, int height);

	// ѭ����Ϣ����
	virtual void MessageControl();

	// ���ؾ��
	virtual HWND GetHandle();

	// ���ظ��ര�ھ��
	virtual HWND GetFatherHandle();

private:
	// �ص�����
	virtual LRESULT CALLBACK HandleProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

#endif //!_WinBox_h_