/*
	精灵类
*/
#ifndef _Sprite_Image_H_
#define _Sprite_Image_H_


#include "Sprite.h"


class Sprite_Image : public Sprite {
public:
	ID2D1Bitmap* image;				// 图像
	D2D1::Matrix3x2F begin_matrix;	// 旋转矩阵
	D2D1_RECT_F rect, src_rect;		// 绘制区、裁剪区 （左上右下）
	float opacity;					// 不透明度
	float angle;					// 旋转角度 

public:
	// 构造
	Sprite_Image();

	// 析构
	virtual ~Sprite_Image();

	// 释放
	virtual void Release();

	// 更新
	virtual void Update();

	// 绘制
	virtual void Draw();

	// 旋转
	virtual void Rotate(bool isrotate, float width, float height);
};

#endif //!_Sprite_Image_H_
