/*
* 窗体
*/
#ifndef _UI_Window_H_
#define _UI_Window_H_


#include "../Render/SpriteProvider.h"
#include "../InputProvider.h"

enum WindowType {
	WindowType_None = 0,
	WindowType_Base,			// 基础
	WindowType_Static,			// 静态
	WindowType_Button,			// 按钮
	WindowType_SingleButton,	// 单选
	WindowType_Checkbox,		// 多选
	WindowType_Edit,			// 编辑
	WindowType_Excel,			// 文档列表
	WindowType_Roll,			// 垂直滚动
	WindowType_2,				// 水平滚动
	WindowType_GIF,				// GIF
	WindowType_Lable,			// Lable
	WindowType_Plane,			// 面板
};



// 窗口类
// 面板 - 子窗口
class UI_Window {
public:
	// 基础属性
	unsigned int window_id;			// 窗口编号 
	unsigned int window_style;		// 窗口类型 
	unsigned int window_level;		// 窗口等级
	unsigned int window_base;		// 归属窗口Id
	unsigned int window_tip;		// 设定标志 - 布局文件的xml_id
	bool window_visible;			// 可见事件
	bool window_active;				// 激活事件 
	bool window_release;			// 内存释放
	bool window_key;				// 键盘事件 
	bool window_mouse;				// 鼠标事件 
	bool window_allowacyive;		// 状态更新 - 允许激活事件
	int window_renderlevel;			// 窗口渲染等级
	D2D1_RECT_F  window_rect;		// 窗口区域
	D2D1_POINT_2F cursor_pos;		// 鼠标位置
	bool window_inrect;				// 光标状态 - 窗口内


public:
	// 构造
	UI_Window();

	// 析构
	virtual ~UI_Window();


public:
	// 创建
	virtual bool Create() = 0;

	// 释放
	virtual void Release() = 0;

	// 更新 
	virtual void Update() = 0;

	// 绘制 
	virtual void Draw() = 0;

public:
	// 设置窗口区域
	virtual void MoveWindow(D2D1_RECT_F _rect) = 0;

	// 设置可见性
	virtual void SetVisiable(bool life = true) = 0;

	// 设置父级窗口编号
	virtual void SetBaseWindow(unsigned int _father);
	
	// 判断是否为父级窗口
	virtual bool IsBaseWindow();

};

#endif //!_UI_Window_H_