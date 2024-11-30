#include "Sprite_Image.h"

// ����
Sprite_Image::Sprite_Image() {
	// ��������
	type = SpriteType_Image;

	// ͼ������
	image = nullptr;					// ͼ��
	begin_matrix = D2D1::Matrix3x2F();	// ��ת����
	rect = src_rect = D2D1::RectF();	// ���������ü��� ���������£�
	opacity = 1.0f;						// ��͸����
	angle = 0.0f;						// ��ת�Ƕ� 
}

// ����
Sprite_Image::~Sprite_Image() {

}

// �ͷ� 
void Sprite_Image::Release() {
	// �ͷ��ڴ�
	if (image) {
		image->Release();
		// delete image;	- Dreict2D���Զ��ͷ�
		image = nullptr;
	}

}

// ���� 
void Sprite_Image::Update() {

}

// ���� 
void Sprite_Image::Draw() {
	if (visiable && this->image) {
		RenderProvider::RenderImage(this->image, this->rect, this->src_rect, this->opacity, this->angle);
	}
}

// ��ת
void Sprite_Image::Rotate(bool isrotate, float width, float height) {
	if (isrotate) {
		begin_matrix = RenderProvider::GetMatrix();								// ��ȡ��ͷ����
		auto move = D2D1::Matrix3x2F::Translation(D2D1::SizeF(width, height));	// ��ת����
		auto result = matrix_25d * move;										// 2.5D
		RenderProvider::Rotate(result);
	}
	else {
		RenderProvider::Rotate(begin_matrix);
	}
}