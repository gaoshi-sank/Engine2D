/*
* 
*/
#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_

// ������ 
#include "../EngineConfig.h"



// ����������
class Scene_Base {
public:
	unsigned int scene_id;					// ���
	unsigned int scene_style;				// ���� 

	// �ص����� 
	std::function<void(unsigned int* param)> trigger_scene;


public:
	// ����
	Scene_Base();

	// ����
	virtual ~Scene_Base();

	// �ͷ� 
	virtual void Release() = 0;

public:
	// ���� 
	virtual bool Create() = 0;

	// ���� 
	virtual void Update() = 0;

	// ���� 
	virtual void Draw() = 0;

	// ���ûص����� 
	virtual void SetTriggerFunction(std::function<void(unsigned int* param)> func);

};


#endif // !_SCENE_BASE_H_
