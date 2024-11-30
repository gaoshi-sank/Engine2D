/*
* 场景管理控制类 
*/
#ifndef _SceneProvider_H_
#define _SceneProvider_H_

#include "Scene/Scene_Base.h"


// 场景管理类 
class SceneProvider {
private:
	Scene_Base* scene_control;


	// 构造 
	SceneProvider();

	// 析构 
	~SceneProvider();

public:
	// 初始化场景管理
	static void InitSceneProvider();

	// 释放
	static void Release();

	// 创建初始场景
	static void BuildScene(Scene_Base* initbase);
	
	// 切换场景
	static void ChangeScene(Scene_Base* newbase);

	// 获取当前场景
	static Scene_Base* GetScene();

public:
	// 更新
	static void SceneUpdate();

	// 绘制 
	static void SceneDraw();


};

#endif // !_SceneProvider_H_
