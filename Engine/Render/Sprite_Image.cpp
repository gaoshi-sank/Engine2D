#include "Sprite_Image.h"

// 构造
Sprite_Image::Sprite_Image() {
	// 基础属性
	type = SpriteType_Image;

	// 图像属性
	image = nullptr;					// 图像
	begin_matrix = D2D1::Matrix3x2F();	// 旋转矩阵
	rect = src_rect = D2D1::RectF();	// 绘制区、裁剪区 （左上右下）
	opacity = 1.0f;						// 不透明度
	angle = 0.0f;						// 旋转角度 
}

// 析构
Sprite_Image::~Sprite_Image() {

}

// 释放 
void Sprite_Image::Release() {
	// 释放内存
	if (image) {
		image->Release();
		// delete image;	- Dreict2D会自动释放
		image = nullptr;
	}

}

// 更新 
void Sprite_Image::Update() {

}

// 绘制 
void Sprite_Image::Draw() {
	if (visiable && this->image) {
		RenderProvider::RenderImage(this->image, this->rect, this->src_rect, this->opacity, this->angle);
	}
}

// 旋转
void Sprite_Image::Rotate(bool isrotate, float width, float height) {
	if (isrotate) {
		begin_matrix = RenderProvider::GetMatrix();								// 获取开头设置
		auto move = D2D1::Matrix3x2F::Translation(D2D1::SizeF(width, height));	// 旋转中心
		auto result = matrix_25d * move;										// 2.5D
		RenderProvider::Rotate(result);
	}
	else {
		RenderProvider::Rotate(begin_matrix);
	}
}
