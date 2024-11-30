#include "Sprite_Figure.h"


// 
Sprite_Figure::Sprite_Figure() {
	// 基础属性
	type = SpriteType_Figure;

	// 区域属性 
	figure_rect = D2D1::RectF(0, 0, 0, 0);
	figure_color = D2D1::ColorF(0, 0, 0);
	line_size = 1.0f;
	figure_full = false;				
	figure_brash = RenderProvider::CreateBrush(figure_color);

}

// 析构 
Sprite_Figure::~Sprite_Figure() {

}


// 释放 
void Sprite_Figure::Release() {


}

// 更新 
void Sprite_Figure::Update() {

}


// 绘制 
void Sprite_Figure::Draw() {
	// 显示 
	if (visiable) {
		RenderProvider::RenderFigure(figuretype_rect, figure_rect, figure_brash, line_size, figure_full);
	}

}

// 重设颜色 
void Sprite_Figure::ReSetColor(D2D1_COLOR_F _color) {
	// 删除 
	if (figure_brash != nullptr) {
		figure_brash->Release();
		figure_brash = nullptr;
	}

	// 重设
	figure_color = _color;
	figure_brash = RenderProvider::CreateBrush(figure_color);

}

// 重设区域 
void Sprite_Figure::ReSetRect(D2D1_RECT_F _rect) {
	figure_rect = _rect;
}

// 重设线型大小 
void Sprite_Figure::ReSetLine(float line) {
	this->line_size = line;
}

// 重设充填
// true = 全填充
void Sprite_Figure::ReSetFull(bool isfull) {
	this->figure_full = isfull;
}