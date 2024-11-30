/*
* 
*/
#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_

// 包含库 
#include "../EngineConfig.h"



// 场景基础类
class Scene_Base {
public:
	unsigned int scene_id;					// 编号
	unsigned int scene_style;				// 类型 

	// 回调函数 
	std::function<void(unsigned int* param)> trigger_scene;


public:
	// 构造
	Scene_Base();

	// 析构
	virtual ~Scene_Base();

	// 释放 
	virtual void Release() = 0;

public:
	// 创建 
	virtual bool Create() = 0;

	// 更新 
	virtual void Update() = 0;

	// 绘制 
	virtual void Draw() = 0;

	// 设置回调函数 
	virtual void SetTriggerFunction(std::function<void(unsigned int* param)> func);

};


#endif // !_SCENE_BASE_H_

