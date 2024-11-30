#include "UI_Window.h"
#include "../UIProvider.h"

// 部分设置
static unsigned int baseid = 0x00;										// 窗口编号
const float config_windowtitle_height = 16.0f;							// 基础标题高度
const float window_title_height = 0.125f;								// 标题高度
const D2D1_COLOR_F window_title_color = D2D1::ColorF(0, 0, 255);		// 标题颜色

// 构造
UI_Window::UI_Window() {
	// 基础属性
	this->window_id = ++baseid;				// 窗口编号 
	this->window_style = WindowType_Base;	// 窗口类型 
	this->window_level = 0;					// 最小 - 最下面
	this->window_base = 0;					// 默认为父级窗口，不归属任意窗口
	this->window_tip = 0;					// 无标志
	this->window_visible = true;			// 触发可见事件 
	this->window_active = true;				// 触发激活事件 
	this->window_key = false;				// 触发键盘事件 
	this->window_mouse = true;				// 触发鼠标事件 
	this->window_allowacyive = true;		// 不允许触发激活事件
	this->window_rect = D2D1::RectF();		// 窗口区域
	this->cursor_pos = D2D1::Point2F();		// 鼠标位置
	this->window_inrect = false;			// 不在窗口内
	this->window_renderlevel = 0x00;		// 窗口渲染等级
	this->window_release = false;			// 未释放

}

// 析构
UI_Window::~UI_Window() {

}

// 创建
bool UI_Window::Create() {
	UIProvider::AddWindow(this);
	return true;
}

// 释放
void UI_Window::Release() {
	// 剔除控制列表
	UIProvider::DelWindow(this);

	// 重置状态
	this->window_id = 0x00;
	this->window_release = true;
}

// 更新事件
void UI_Window::CheckEvent(int* param){
	if (!param) {
		return;
	}

	int paramlen = param[0];
	if (paramlen < 2) {
		return;
	}

	int message = param[1];
	switch (message) {
	case WM_MOUSEMOVE:
	{
		if (paramlen >= 4) {
			cursor_pos.x = param[2];
			cursor_pos.y = param[3];
		}
	}
		break;
	default:
		break;
	}
}

// 更新 
void UI_Window::Update() {
	// 判定顶层
	window_inrect = false;
	auto ret_top = UIProvider::GetLevelTop(cursor_pos, this);

	// 顶层 -- 可见状态
	if (ret_top && window_visible) {
		if (Point_In_Rect(cursor_pos, window_rect)) {
			window_inrect = true;
		}
	}
}

// 绘制 
void UI_Window::Draw() {

}

// 设置窗口区域
void UI_Window::MoveWindow(D2D1_RECT_F _rect) {
	// 窗口区域
	window_rect = _rect;
}

// 设置可见性
void UI_Window::SetVisiable(bool life) {
	window_visible = life;
}

// 设置父级窗口编号
void UI_Window::SetBaseWindow(unsigned int _father) {
	this->window_base = _father;
}

// 判断是否为父级窗口
bool UI_Window::IsBaseWindow() {
	return this->window_base == 0;
}