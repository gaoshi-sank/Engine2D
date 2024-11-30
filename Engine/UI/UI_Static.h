/*
* ��̬��
*/
#ifndef _UI_STATIC_H_
#define _UI_STATIC_H_


#include "UI_Window.h"


// ��̬ͼ 
class UI_Static : public UI_Window {
private:
	Sprite_Text* text;				// ��̬�ı� 

public:
	// ����
	UI_Static();

	// ����
	~UI_Static();

	// ����
	virtual bool Create();

	// ����
	virtual bool Create(std::string _name, D2D1_RECT_F _rect);

	// �ͷ�
	virtual void Release();

	// �����¼�
	virtual void CheckEvent(int* param);

	// ���� 
	virtual void Update();

	// ���� 
	virtual void Draw();

	// ���ô�������
	virtual void MoveWindow(D2D1_RECT_F _rect);

	// ���ÿɼ���
	virtual void SetVisiable(bool life = true);
};


#endif // !_UI_STATIC_H_

