/*
* ������
*/
#ifndef _UI_Roll_H_
#define _UI_Roll_H_

#include "UI_Window.h"
#include "UI_Button.h"


class UI_Roll : public UI_Window {
private:
	std::vector<Sprite_Image*> rolls;				// ��ťͼ��
	int roll_state = 0;								// ��ť״̬
	int roll_click[2] = { 0 };						// ���� - ���״̬

	// �ص�����
	std::function<void(void)> callback_rollclick;	// �����ť

public:
	// ����
	UI_Roll();

	// ����
	virtual ~UI_Roll();

public:
	// ����
	virtual bool Create();

	// ����
	virtual bool Create(D2D1_RECT_F _rect, int style = buttontype_row2);

	// �ͷ�
	virtual void Release();

	// �����¼�
	virtual void CheckEvent(int* param);

	// ���� 
	virtual void Update();

	// ���� 
	virtual void Draw();

public:
	// ���ô�������
	virtual void MoveWindow(D2D1_RECT_F _rect);

	// ���ÿɼ���
	virtual void SetVisiable(bool life = true);

	// ���ù�����ͼ��
	virtual void SetRollImage(int type = buttontype_row4, const char* filename = nullptr);
};


#endif // !_UI_Roll_H_
