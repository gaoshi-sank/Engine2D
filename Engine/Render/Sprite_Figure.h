/*
	基础精灵类 -- 图形
*/
#ifndef _SPRITE_FIGURE_H_
#define _SPRITE_FIGURE_H_

// 包含库 
#include "Sprite.h"

// 绘制类 - 图形 
class Sprite_Figure : public Sprite {
public:
	ID2D1SolidColorBrush* figure_brash;		// 画刷 
	D2D1_COLOR_F figure_color;				// 线条颜色
	D2D1_RECT_F figure_rect;				// 绘制区
	float line_size;						// 线型大小 
	bool figure_full;						// 线型填充

public:
	// 构造
	Sprite_Figure();

	// 析构
	virtual ~Sprite_Figure();

	// 释放
	void Release();

	// 更新 
	void Update();

	// 绘制 
	void Draw();

	// 重设颜色 
	void ReSetColor(D2D1_COLOR_F _color = D2D1::ColorF(0, 0, 0));

	// 重设区域 
	void ReSetRect(D2D1_RECT_F _rect);

	// 重设线型大小 
	void ReSetLine(float line = 1.0f);

	// 重设充填
	// true = 全填充
	void ReSetFull(bool isfull = false);

};



#endif // !_SPRITE_FIGURE_H_

