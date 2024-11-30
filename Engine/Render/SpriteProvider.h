/*
	精灵提供类
*/
#ifndef _SpriteProvider_H_
#define _SpriteProvider_H_

// 包含库 
#include "Sprite_Image.h"
#include "Sprite_Text.h"
#include "Sprite_Line.h"
#include "Sprite_Figure.h"
#include "Animation.h"

// 动画风格 - 枚举
enum AniamtionStyle {
	AniamtionStyle_Row4 = 1,
	AniamtionStyle_Row8,
	AniamtionStyle_Row16,
};

// 自定义颜色结构体
struct COLOR {
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	COLOR(){
		red = 0;
		green = 0;
		blue = 0;
	}
	COLOR(unsigned char r, unsigned char g, unsigned char b) {
		red = r;
		green = g;
		blue = b;
	}
	COLOR(const COLOR& _color) {
		if (this != &_color) {
			this->red = _color.red;
			this->green = _color.green;
			this->blue = _color.blue;
		}
	}
	~COLOR(){}
};

// 绘制类 - 基础
class SpriteProvider {
private:
	// 构造
	SpriteProvider();

	// 析构
	virtual ~SpriteProvider();

public:
	// 创建图像精灵
	static Sprite_Image* CreateImage(const char* filename, RECT draw_rect = { 0 }, RECT src_rect = { 0 }, float opacity = 1.0f, float angle = 0.0f);

	// 创建文本精灵
	static Sprite_Text* CreateText(const char* text, RECT draw_rect = { 0 }, COLOR color = { 0,0,0 });

	// 创建图形精灵
	static Sprite_Figure* CreateFigure(COLOR color, float line_size);

	// 创建线条精灵
	static Sprite_Line* CreateLine(COLOR color, float line_size);

	// 创建动画精灵 - 单图创建
	static Animation* CreateAnimation(const char* filename, int style, float timeline = 0.0f, RECT draw_rect = { 0 }, float opacity = 1.0f, float angle = 0.0f);
};



#endif // !_SpriteProvider_H_


