/*
	精灵类
*/
#ifndef _SpriteProvider_H_
#define _SpriteProvider_H_

// 包含库 
#include "Sprite_Image.h"
#include "Sprite_Text.h"
#include "Sprite_Line.h"
#include "Sprite_Figure.h"
#include "Animation.h"

enum AniamtionStyle {
	AniamtionStyle_Row4 = 1,
	AniamtionStyle_Row8,
	AniamtionStyle_Row16,
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
	static Sprite_Image* CreateImage(const char* filename, D2D1_RECT_F rect = D2D1::RectF(), D2D1_RECT_F src_rect = D2D1::RectF(), float opacity = 1.0f, float angle = 0.0f);

	// 创建文本精灵
	static Sprite_Text* CreateText(const char* text, D2D1_RECT_F rect = D2D1::RectF(), D2D1_COLOR_F color = D2D1::ColorF(0, 0, 0));

	// 创建图形精灵
	static Sprite_Figure* CreateFigure(D2D1_COLOR_F color, float line_size);

	// 创建线条精灵
	static Sprite_Line* CreateLine(D2D1_COLOR_F color, float line_size);

	// 创建动画精灵 - 单图创建
	static Animation* CreateAnimation(const char* filename, int style, float timeline = 0.0f, D2D1_RECT_F rect = D2D1::RectF(), D2D1_RECT_F _src_rect = D2D1::RectF(), float opacity = 1.0f, float angle = 0.0f);
};



#endif // !_SpriteProvider_H_


