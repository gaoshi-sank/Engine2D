/*
* 静态框
*/
#ifndef _UI_STATIC_H_
#define _UI_STATIC_H_


#include "UI_Window.h"


// 静态图 
class UI_Static : public UI_Window {
private:
	Sprite_Text* text;				// 静态文本 

public:
	// 构造
	UI_Static();

	// 析构
	~UI_Static();

	// 创建
	virtual bool Create();

	// 创建
	virtual bool Create(std::string _name, D2D1_RECT_F _rect);

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

	// 设置可见性
	virtual void SetVisiable(bool life = true);
};


#endif // !_UI_STATIC_H_


