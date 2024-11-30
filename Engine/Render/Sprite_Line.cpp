#include "Sprite_Line.h"

// 
Sprite_Line::Sprite_Line() {
	// 基础属性
	type = SpriteType_Line;

	// 线条属性 
	line_left = D2D1::Point2F(0, 0);
	line_right = D2D1::Point2F(0, 0);
	line_brash = RenderProvider::CreateBrush(D2D1::ColorF(0, 0, 0));

}

// 析构 
Sprite_Line::~Sprite_Line() {

}


// 释放 
void Sprite_Line::Release() {


}

// 更新 
void Sprite_Line::Update() {

}


// 绘制 
void Sprite_Line::Draw() {
	if (visiable) {
		RenderProvider::RenderLine(line_left, line_right, line_brash);
	}
}

// 移动位置
void Sprite_Line::MovePoint(float x, float y, float width, float height) {
	line_left.x = x; line_left.y = y;
	line_right.x = x; line_right.y = y + height;
}

// 设置画刷颜色
void Sprite_Line::ResetLineColor(D2D1_COLOR_F color) {
	// 删除 
	if (line_brash != nullptr) {
		line_brash->Release();
		line_brash = nullptr;
	}

	// 重设
	line_brash = RenderProvider::CreateBrush(color);
}