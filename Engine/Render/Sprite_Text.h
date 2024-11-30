/*
	基础精灵类 -- 文本 
	默认 18号大小，字体宋体，水平和垂直居中
*/
#ifndef _SPRITE_TEXT_H_
#define _SPRITE_TEXT_H_

// 包含库 
#include "Sprite.h"

#define UTF_8 0						// 编码格式 
#define LIMIT_STRING_LENGTH 1024	// 文字限制大小 

// 绘制类 - 文字 
class Sprite_Text : public Sprite {
public:
	string text;							// 文字
	wchar_t* render_text;					// 渲染用
	D2D1_RECT_F text_rect;					// 绘制区域
	float font_size;						// 文字大小

	IDWriteTextFormat* text_format;			// 文字格式
	IDWriteTextLayout* text_layout;			// 文本布局 
	ID2D1SolidColorBrush* text_brash;		// 底子画刷 
	D2D1_COLOR_F text_color;				// 画刷颜色

	int max_fontlength;						// 可绘制文本长度
	int text_LevelStyle;					// 文本水平风格 - 1 默认居中
	int text_VerticalStyle;					// 文本垂直风格 - 1 默认居中
	int text_swrapping;						// 换行格式

public:
	// 构造
	Sprite_Text();

	// 析构
	virtual ~Sprite_Text();

	// 释放
	void Release();

	// 更新 
	void Update();

	// 绘制 
	void Draw();

	// 绘制文本
	void DrawExternText(D2D1_RECT_F _rect, std::string _text);

	// 绘制文本
	void DrawExternText(D2D1_RECT_F _rect, wchar_t* _text);

	// 重设文本
	bool ReSetText(const char* text);

	// 重设区域 
	void ReSetRect(D2D1_RECT_F _rect);

	// 重设布局 
	// 水平格式，垂直格式，自动换行 
	void ReSetLayout(int level_Style = 1, int vertical_Style = 1, int swrapping = 0);

	// 重设字体大小 
	void ReSetFont(int font_size = 18.0f);

	// 重设颜色 
	void ReSetColor(D2D1_COLOR_F color = D2D1::ColorF(0, 0, 0));

	// 重设水平格式 
	// 默认1 = 居中
	void ReSetLevelStyle(int state = 1);

	// 重设垂直格式
	// 默认1 = 居中
	void ReSetVerticalStyle(int state = 1);

	// 重设自动换行 
	void ReSetSwrapping(int isSwrapping = 0);

};



#endif // !_SPRITE_TEXT_H_

