/*
	精灵类
*/
#ifndef _Sprite_H_
#define _Sprite_H_


#include "../RenderProvider.h"

// 精灵类型
enum SpriteType{
	SpriteType_Image = 1,
	SpriteType_Text,
	SpriteType_Figure,
	SpriteType_Line,
	SpriteType_Flip
};

class Sprite {
public:
	unsigned int id;
	unsigned int type;
	bool visiable;

	Sprite();
	virtual ~Sprite();
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

};

#endif //!_Sprite_H_