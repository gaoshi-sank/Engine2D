/*
	基础精灵类 -- 线条 
*/
#ifndef _SPRITE_LINE_H_
#define _SPRITE_LINE_H_

// 包含库 
#include "Sprite.h"

// 绘制类 - 线条 
class Sprite_Line : public Sprite {
public:
	ID2D1SolidColorBrush* line_brash;			// 画刷 
	D2D1_POINT_2F line_left, line_right;		// 点列表 

public:
	// 构造
	Sprite_Line();

	// 析构
	virtual ~Sprite_Line();

	// 释放
	void Release();

	// 更新 
	void Update();

	// 绘制 
	void Draw();

	// 移动位置
	void MovePoint(float x, float y, float width, float height);

	// 设置画刷颜色
	void ResetLineColor(D2D1_COLOR_F color = D2D1::ColorF(0, 0, 0, 1.0f));

};



#endif // !_SPRITE_LINE_H_

