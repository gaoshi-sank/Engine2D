#include "SceneProvider.h"

static SceneProvider* g_scene = nullptr;

// ���� 
SceneProvider::SceneProvider() {
	scene_control = nullptr;

}

// ���� 
SceneProvider::~SceneProvider() {

}

// ��ʼ����������
void SceneProvider::InitSceneProvider() {
	if (!g_scene) {
		g_scene = new SceneProvider();
	}
}

// �ͷ�
void SceneProvider::Release() {
	if (g_scene) {
		if (g_scene->scene_control) {
			g_scene->scene_control->Release();
		}

		delete g_scene;
		g_scene = nullptr;
	}
}

// ������ʼ����
void SceneProvider::BuildScene(Scene_Base* initbase) {
	if (g_scene) {
		if (!g_scene->scene_control) {
			g_scene->scene_control = initbase;
		}
	}
}

// �л�����
void SceneProvider::ChangeScene(Scene_Base* newbase) {
	if (g_scene) {
		// ���֮ǰ�ĳ���
		if (g_scene->scene_control) {
			g_scene->scene_control->Release();
			delete g_scene->scene_control;
			g_scene->scene_control = nullptr;
		}

		// �����³���
		if (!g_scene->scene_control) {
			g_scene->scene_control = newbase;
		}
	}
}

// ��ȡ��ǰ����
Scene_Base* SceneProvider::GetScene() {
	if (g_scene) {
		return g_scene->scene_control;
	}
	return nullptr;
}

// ����
void SceneProvider::SceneUpdate() {
	
	if (g_scene && g_scene->scene_control) {
		g_scene->scene_control->Update();
	}

}

// ���� 
void SceneProvider::SceneDraw() {

	if (g_scene && g_scene->scene_control) {
		g_scene->scene_control->Draw();
	}
}
