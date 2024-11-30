/*
* ��̬ͼ��
*/
#ifndef _UI_Lable_H_
#define _UI_Lable_H_


#include "UI_Window.h"


// ��̬ͼ 
class UI_Lable : public UI_Window {
private:
	Sprite_Image* _image;				// ��̬ͼ��
	Sprite_Text* _text;					// ��̬�ı�

public:
	// ����
	UI_Lable();

	// ����
	~UI_Lable();

	// ����
	virtual bool Create();

	// ����
	virtual bool Create(std::string filename, D2D1_RECT_F _rect);

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

	// �����ı�
	virtual void SetStaticText(const char* text);
};


#endif // !_UI_STATIC_H_

