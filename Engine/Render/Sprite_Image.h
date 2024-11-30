/*
	������
*/
#ifndef _Sprite_Image_H_
#define _Sprite_Image_H_


#include "Sprite.h"


class Sprite_Image : public Sprite {
public:
	ID2D1Bitmap* image;				// ͼ��
	D2D1::Matrix3x2F begin_matrix;	// ��ת����
	D2D1_RECT_F rect, src_rect;		// ���������ü��� ���������£�
	float opacity;					// ��͸����
	float angle;					// ��ת�Ƕ� 

public:
	// ����
	Sprite_Image();

	// ����
	virtual ~Sprite_Image();

	// �ͷ�
	virtual void Release();

	// ����
	virtual void Update();

	// ����
	virtual void Draw();

	// ��ת
	virtual void Rotate(bool isrotate, float width, float height);
};

#endif //!_Sprite_Image_H_