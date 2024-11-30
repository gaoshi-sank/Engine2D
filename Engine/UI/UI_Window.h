/*
* ����
*/
#ifndef _UI_Window_H_
#define _UI_Window_H_


#include "../Render/SpriteProvider.h"

// ��������
enum WindowType {
	WindowType_None = 0,
	WindowType_Base,			// ����
	WindowType_Static,			// ��̬
	WindowType_Button,			// ��ť
	WindowType_SingleButton,	// ��ѡ
	WindowType_Checkbox,		// ��ѡ
	WindowType_Edit,			// �༭
	WindowType_Excel,			// �ĵ��б�
	WindowType_Roll,			// ��ֱ����
	WindowType_2,				// ˮƽ����
	WindowType_GIF,				// GIF
	WindowType_Lable,			// Lable
	WindowType_Plane,			// ���
};


// ������
// ��� - �Ӵ���
class UI_Window {
public:
	// ��������
	unsigned int window_id;			// ���ڱ�� 
	unsigned int window_style;		// �������� 
	unsigned int window_level;		// ���ڵȼ�
	unsigned int window_base;		// ��������Id
	unsigned int window_tip;		// �趨��־ - �����ļ���xml_id
	bool window_visible;			// �ɼ��¼�
	bool window_active;				// �����¼� 
	bool window_release;			// �ڴ��ͷ�
	bool window_key;				// �����¼� 
	bool window_mouse;				// ����¼� 
	bool window_allowacyive;		// ״̬���� - ���������¼�
	int window_renderlevel;			// ������Ⱦ�ȼ�
	RECT  window_rect;				// ��������
	POINT cursor_pos;				// ���λ��
	bool window_inrect;				// ���״̬ - ������


public:
	// ����
	UI_Window();

	// ����
	virtual ~UI_Window();


public:
	// ����
	virtual bool Create() = 0;

	// �ͷ�
	virtual void Release() = 0;

	// �����¼�
	virtual void CheckEvent(int* param) = 0;

	// ���� 
	virtual void Update() = 0;

	// ���� 
	virtual void Draw() = 0;

public:
	// ���ô�������
	virtual void MoveWindow(RECT _rect) = 0;

	// ���ÿɼ���
	virtual void SetVisiable(bool life = true) = 0;

	// ���ø������ڱ��
	virtual void SetFather(unsigned int _father);
	


};

#endif //!_UI_Window_H_