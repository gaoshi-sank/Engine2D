#include "Sprite.h"

// ¹¹Ôì
Sprite::Sprite() {
	static unsigned int _id = 0;
	this->id = ++_id;
	this->type = 0;
	this->visiable = true;
}

// Îö¹¹
Sprite::~Sprite() {

}