/*
* ��ť
*/
#ifndef _UI_Button_H_
#define _UI_Button_H_


#include "UI_Window.h"

enum buttonstate {
	buttonstate_out = 1,
	buttonstate_in,
	buttonstate_down,
	buttonstate_lose
};

enum rollstate {
	rollstate_out = 1,
	rollstate_in,
};

enum buttonsize {
	buttonsize_roll = 2,
	buttonsize_button = 4,
};

enum buttontype {
	buttontype_row2 = 1,
	buttontype_row4
};

// ��ť 
class UI_Button : public UI_Window {
private:
	Sprite_Text* text;								// ��̬�ı� 
	std::vector<Sprite_Image*> buttons;				// ��ťͼ��
	int button_state = 0;							// ��ť״̬
	int button_click[2] = { 0 };					// ���� - ���״̬

	// �ص�����
	std::function<void(unsigned int)> callback_buttonclick;	// �����ť

public:
	// ����
	UI_Button();

	// ����
	~UI_Button();

	// ����
	virtual bool Create();

	// ����
	// �ļ���
	// style = buttontype_row4������4�а�ť��
	virtual bool Create(std::string filename, int style, D2D1_RECT_F _rect);

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

	// ���ð�ťͼ��
	virtual void SetButtonImage(int type = buttontype_row4, const char* filename = nullptr);

	// ���ð�ť�ı�
	virtual void SetButtonText(const char* _text);

	// ���ð�ť�ı�����
	virtual void SetButtonFont(int font_size, D2D1_COLOR_F color = D2D1::ColorF(0,0,0));

	// ���ûص����� - ���
	virtual void SetFunction_Click(std::function<void(unsigned int _id)> _callback_function);	

	// ��ȡ��ť��ͣ״̬
	virtual bool GetButtonHoverState();


};


#endif // !_UI_Button_H_