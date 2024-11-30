/*
* �ĵ��б���չʾ��
*/
#ifndef _UI_Excel_H_
#define _UI_Excel_H_

#include "UI_Window.h"

struct ExcelText {
	std::string _text;
	D2D1_RECT_F _rect;

	ExcelText() {
		_text = "";
		_rect = D2D1::RectF();
	}
};


class UI_Excel : public UI_Window {
private:
	std::vector<ExcelText*> list_texts;	// ��Ⱦ�ַ�
	Sprite_Image* object_background;	// ���Ʊ���
	Sprite_Text* object_text;			// ���ƶ���
	int maxlength;
	bool isbuild;

public:
	// ����
	UI_Excel();

	// ����
	virtual ~UI_Excel();

public:
	// ����
	virtual bool Create();

	// �ͷ�
	virtual void Release();

	// �����ַ�
	virtual void AddText(std::string _text);

	// ����λ�������ַ�
	virtual void AddText(int x, int y, std::string _text);

	// ������󳤶�
	virtual void SetMaxValue(int maxlength);

	// �豸����
	virtual void SetBackGround(const char* filename = nullptr);

	// ����������ɫ
	virtual void SetTextColor(D2D1_COLOR_F _color);

	// ���ÿɼ���
	virtual void SetVisiable(bool life = true);

	// �����¼�
	virtual void CheckEvent(int* param);

	// ���� 
	virtual void Update();

	// ���� 
	virtual void Draw();

	// ���ô�������
	virtual void MoveWindow(D2D1_RECT_F _rect);

};


#endif // !_UI_Excel_H_