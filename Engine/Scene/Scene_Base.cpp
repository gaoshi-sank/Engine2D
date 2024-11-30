#include "Scene_Base.h"
#include "../SceneProvider.h"

unsigned int baseid = 0x00;

// 构造
Scene_Base::Scene_Base() {
	scene_id = ++baseid;
	scene_style = 0;
}

// 析构
Scene_Base::~Scene_Base() {

}

// 释放 
void Scene_Base::Release() {
	
}

// 创建 
bool Scene_Base::Create() {
	if (scene_id != 0x00) {
		return true;
	}
	return false;
}

// 设置回调函数 
void Scene_Base::SetTriggerFunction(std::function<void(unsigned int* param)> func) {
	this->trigger_scene = func;
}