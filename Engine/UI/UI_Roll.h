/*
* 滚动条
*/
#ifndef _UI_Roll_H_
#define _UI_Roll_H_

#include "UI_Window.h"
#include "UI_Button.h"


class UI_Roll : public UI_Window {
private:
	std::vector<Sprite_Image*> rolls;				// 按钮图像
	int roll_state = 0;								// 按钮状态
	int roll_click[2] = { 0 };						// 触发 - 点击状态

	// 回调函数
	std::function<void(void)> callback_rollclick;	// 点击按钮

public:
	// 构造
	UI_Roll();

	// 析构
	virtual ~UI_Roll();

public:
	// 创建
	virtual bool Create();

	// 创建
	virtual bool Create(D2D1_RECT_F _rect, int style = buttontype_row2);

	// 释放
	virtual void Release();

	// 更新事件
	virtual void CheckEvent(int* param);

	// 更新 
	virtual void Update();

	// 绘制 
	virtual void Draw();

public:
	// 设置窗口区域
	virtual void MoveWindow(D2D1_RECT_F _rect);

	// 设置可见性
	virtual void SetVisiable(bool life = true);

	// 设置滚动条图像
	virtual void SetRollImage(int type = buttontype_row4, const char* filename = nullptr);
};


#endif // !_UI_Roll_H_

