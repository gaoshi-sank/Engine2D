/*
* 文档列表，展示条
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
	std::vector<ExcelText*> list_texts;	// 渲染字符
	Sprite_Image* object_background;	// 绘制背景
	Sprite_Text* object_text;			// 绘制对象
	int maxlength;
	bool isbuild;

public:
	// 构造
	UI_Excel();

	// 析构
	virtual ~UI_Excel();

public:
	// 创建
	virtual bool Create();

	// 释放
	virtual void Release();

	// 增加字符
	virtual void AddText(std::string _text);

	// 根据位置增加字符
	virtual void AddText(int x, int y, std::string _text);

	// 设置最大长度
	virtual void SetMaxValue(int maxlength);

	// 设备背景
	virtual void SetBackGround(const char* filename = nullptr);

	// 绘制文字颜色
	virtual void SetTextColor(D2D1_COLOR_F _color);

	// 设置可见性
	virtual void SetVisiable(bool life = true);

	// 更新 
	virtual void Update();

	// 绘制 
	virtual void Draw();

	// 设置窗口区域
	virtual void MoveWindow(D2D1_RECT_F _rect);

};


#endif // !_UI_Excel_H_
