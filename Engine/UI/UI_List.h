/*
* 下拉框
*/
#ifndef _UI_List_H_
#define _UI_List_H_

#include "UI_Window.h"


class UI_List : public UI_Window {
private:				
	std::vector<Sprite_Text*> list_text;	// 列表
	Sprite_Text* TopShow;					// Top显示
	bool isshowList;						// 是否显示列表值
	int show_index;							// Top显示索引
	int list_click[2] = { 0 };				// 触发点击状态

public:
	// 构造
	UI_List();

	// 析构
	virtual ~UI_List();

public:
	// 创建
	virtual bool Create();

	// 创建
	virtual bool Create(D2D1_RECT_F _rect);

	// 更新事件
	virtual void CheckEvent(int* param);

	// 释放
	virtual void Release();

	// 更新 
	virtual void Update();

	// 绘制 
	virtual void Draw();

public:
	// 设置窗口区域
	virtual void MoveWindow(D2D1_RECT_F _rect);

	// 设置可见性
	virtual void SetVisiable(bool life = true);

	// 扩展窗口区域
	virtual void ExtendWindow(D2D1_RECT_F _rect, bool isextend = true);

	// 增加一条
	virtual void AddValue(std::string _text);

	// 获取当前选择
	virtual int GetValue();

};


#endif // !_UI_Roll_H_

