/*
* �������������� 
*/
#ifndef _SceneProvider_H_
#define _SceneProvider_H_

#include "Scene/Scene_Base.h"


// ���������� 
class SceneProvider {
private:
	Scene_Base* scene_control;


	// ���� 
	SceneProvider();

	// ���� 
	~SceneProvider();

public:
	// ��ʼ����������
	static void InitSceneProvider();

	// �ͷ�
	static void Release();

	// ������ʼ����
	static void BuildScene(Scene_Base* initbase);
	
	// �л�����
	static void ChangeScene(Scene_Base* newbase);

	// ��ȡ��ǰ����
	static Scene_Base* GetScene();

public:
	// ����
	static void SceneUpdate();

	// ���� 
	static void SceneDraw();


};

#endif // !_SceneProvider_H_