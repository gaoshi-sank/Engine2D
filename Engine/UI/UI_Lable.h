/*
* 静态图像
*/
#ifndef _UI_Lable_H_
#define _UI_Lable_H_


#include "UI_Window.h"


// 静态图 
class UI_Lable : public UI_Window {
private:
	Sprite_Image* _image;				// 静态图像
	Sprite_Text* _text;					// 静态文本

public:
	// 构造
	UI_Lable();

	// 析构
	~UI_Lable();

	// 创建
	virtual bool Create();

	// 创建
	virtual bool Create(std::string filename, D2D1_RECT_F _rect);

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

	// 设置文本
	virtual void SetStaticText(const char* text);
};


#endif // !_UI_STATIC_H_


