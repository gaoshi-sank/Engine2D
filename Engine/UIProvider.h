/*
* ���ڹ���UI�ؼ�
*/
#ifndef _UIProvider_H_
#define _UIProvider_H_

#include "EngineConfig.h"
#include "EngineFunction.h"
#include "UI/UI_Window.h"

/*
#include "UI/UI_Static.h"
#include "UI/UI_Button.h"
#include "UI/UI_SingleButton.h"
#include "UI/UI_Excel.h"
#include "UI/UI_Roll.h"
#include "UI/UI_List.h"
#include "UI/UI_GIF.h"
#include "UI/UI_Lable.h"
*/

// 
class UIProvider {
private:
	// ��
	std::mutex lockList;
	std::mutex lockAddlist;
	std::mutex lockDellist;

	// UI�б�
	std::vector<UI_Window*> list;
	std::vector<UI_Window*> addList;
	std::vector<UI_Window*> delList;

	// ����
	UIProvider();

	// ����
	~UIProvider();

public:
	// ��ʼ��
	static void InitUIManager();

	// �ͷ�
	static void Release();

	// ���ӿؼ�
	static void AddWindow(UI_Window* _ui);

	// ɾ���ؼ�
	static void DelWindow(UI_Window* _ui);

	// ����
	static void Update();

	// ��Ⱦ
	static void Draw();

	// �ж϶���
	static bool GetLevelTop(UI_Window* _ui, POINT pos);
};

#endif //!_UIProvider_H_ 