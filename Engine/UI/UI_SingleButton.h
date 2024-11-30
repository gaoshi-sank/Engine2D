/*
* 单选
*/
#ifndef _UI_SingleButton_H_
#define _UI_SingleButton_H_


#include "UI_Button.h"


// 单选 
class UI_SingleButton : public UI_Window {
private:
	Sprite_Text* text;								// 静态文本 
	std::vector<Sprite_Image*> buttons;				// 按钮图像
	int button_state = 0;							// 按钮状态
	int button_click[2] = { 0 };					// 触发 - 点击状态
	int single_click = 0;							// 单选状态

	// 回调函数
	std::function<void(unsigned int)> callback_buttonclick;	// 点击按钮


public:
	// 构造
	UI_SingleButton();

	// 析构
	~UI_SingleButton();

	// 创建
	virtual bool Create();

	// 创建
	virtual bool Create(std::string filename, int style, D2D1_RECT_F _rect);

	// 释放
	virtual void Release();

	// 更新事件
	virtual void CheckEvent(int* param);

	// 更新 
	virtual void Update();

	// 绘制 
	virtual void Draw();

	// 设置窗口区域
	virtual void MoveWindow(D2D1_RECT_F _rect);

	// 获取单选状态
	// DOWN - UP
	virtual int GetSingleState();

	// 设置可见性
	virtual void SetVisiable(bool life = true);

	// 设置按钮图像
	virtual void SetButtonImage(int type = buttontype_row4, const char* filename = nullptr);

	// 设置按钮文本
	virtual void SetButtonText(const char* _text);

	// 设置按钮文本字体
	virtual void SetButtonFont(int font_size, D2D1_COLOR_F color = D2D1::ColorF(0, 0, 0));

	// 设置回调函数
	virtual void SetFunction_Click(std::function<void(unsigned int _id)> _callback_function);

	 // 设置单选状态
	virtual void SetSingleState(int state);

};


#endif // !_UI_SingleButton_H_
