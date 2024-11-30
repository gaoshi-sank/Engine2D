#include "Scene_Base.h"
#include "../SceneProvider.h"

unsigned int baseid = 0x00;

// ����
Scene_Base::Scene_Base() {
	scene_id = ++baseid;
	scene_style = 0;
}

// ����
Scene_Base::~Scene_Base() {

}

// �ͷ� 
void Scene_Base::Release() {
	
}

// ���� 
bool Scene_Base::Create() {
	if (scene_id != 0x00) {
		return true;
	}
	return false;
}

// ���ûص����� 
void Scene_Base::SetTriggerFunction(std::function<void(unsigned int* param)> func) {
	this->trigger_scene = func;
}