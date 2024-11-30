/*
* ��ѡ
*/
#ifndef _UI_SingleButton_H_
#define _UI_SingleButton_H_


#include "UI_Button.h"


// ��ѡ 
class UI_SingleButton : public UI_Window {
private:
	Sprite_Text* text;								// ��̬�ı� 
	std::vector<Sprite_Image*> buttons;				// ��ťͼ��
	int button_state = 0;							// ��ť״̬
	int button_click[2] = { 0 };					// ���� - ���״̬
	int single_click = 0;							// ��ѡ״̬

	// �ص�����
	std::function<void(unsigned int)> callback_buttonclick;	// �����ť


public:
	// ����
	UI_SingleButton();

	// ����
	~UI_SingleButton();

	// ����
	virtual bool Create();

	// ����
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

	// ��ȡ��ѡ״̬
	// DOWN - UP
	virtual int GetSingleState();

	// ���ÿɼ���
	virtual void SetVisiable(bool life = true);

	// ���ð�ťͼ��
	virtual void SetButtonImage(int type = buttontype_row4, const char* filename = nullptr);

	// ���ð�ť�ı�
	virtual void SetButtonText(const char* _text);

	// ���ð�ť�ı�����
	virtual void SetButtonFont(int font_size, D2D1_COLOR_F color = D2D1::ColorF(0, 0, 0));

	// ���ûص�����
	virtual void SetFunction_Click(std::function<void(unsigned int _id)> _callback_function);

	 // ���õ�ѡ״̬
	virtual void SetSingleState(int state);

};


#endif // !_UI_SingleButton_H_