#include "SceneProvider.h"

static SceneProvider* g_scene = nullptr;

// 构造 
SceneProvider::SceneProvider() {
	scene_control = nullptr;

}

// 析构 
SceneProvider::~SceneProvider() {

}

// 初始化场景管理
void SceneProvider::InitSceneProvider() {
	if (!g_scene) {
		g_scene = new SceneProvider();
	}
}

// 释放
void SceneProvider::Release() {
	if (g_scene) {
		if (g_scene->scene_control) {
			g_scene->scene_control->Release();
		}

		delete g_scene;
		g_scene = nullptr;
	}
}

// 创建初始场景
void SceneProvider::BuildScene(Scene_Base* initbase) {
	if (g_scene) {
		if (!g_scene->scene_control) {
			g_scene->scene_control = initbase;
		}
	}
}

// 切换场景
void SceneProvider::ChangeScene(Scene_Base* newbase) {
	if (g_scene) {
		// 清空之前的场景
		if (g_scene->scene_control) {
			g_scene->scene_control->Release();
			delete g_scene->scene_control;
			g_scene->scene_control = nullptr;
		}

		// 添加新场景
		if (!g_scene->scene_control) {
			g_scene->scene_control = newbase;
		}
	}
}

// 获取当前场景
Scene_Base* SceneProvider::GetScene() {
	if (g_scene) {
		return g_scene->scene_control;
	}
	return nullptr;
}

// 更新
void SceneProvider::SceneUpdate() {
	
	if (g_scene && g_scene->scene_control) {
		g_scene->scene_control->Update();
	}

}

// 绘制 
void SceneProvider::SceneDraw() {

	if (g_scene && g_scene->scene_control) {
		g_scene->scene_control->Draw();
	}
}

