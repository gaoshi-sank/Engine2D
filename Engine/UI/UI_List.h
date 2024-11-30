/*
* ������
*/
#ifndef _UI_List_H_
#define _UI_List_H_

#include "UI_Window.h"


class UI_List : public UI_Window {
private:				
	std::vector<Sprite_Text*> list_text;	// �б�
	Sprite_Text* TopShow;					// Top��ʾ
	bool isshowList;						// �Ƿ���ʾ�б�ֵ
	int show_index;							// Top��ʾ����
	int list_click[2] = { 0 };				// �������״̬

public:
	// ����
	UI_List();

	// ����
	virtual ~UI_List();

public:
	// ����
	virtual bool Create();

	// ����
	virtual bool Create(D2D1_RECT_F _rect);

	// �����¼�
	virtual void CheckEvent(int* param);

	// �ͷ�
	virtual void Release();

	// ���� 
	virtual void Update();

	// ���� 
	virtual void Draw();

public:
	// ���ô�������
	virtual void MoveWindow(D2D1_RECT_F _rect);

	// ���ÿɼ���
	virtual void SetVisiable(bool life = true);

	// ��չ��������
	virtual void ExtendWindow(D2D1_RECT_F _rect, bool isextend = true);

	// ����һ��
	virtual void AddValue(std::string _text);

	// ��ȡ��ǰѡ��
	virtual int GetValue();

};


#endif // !_UI_Roll_H_
