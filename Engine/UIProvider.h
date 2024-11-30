/*
* 用于管理UI控件
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
	// 锁
	std::mutex lockList;
	std::mutex lockAddlist;
	std::mutex lockDellist;

	// UI列表
	std::vector<UI_Window*> list;
	std::vector<UI_Window*> addList;
	std::vector<UI_Window*> delList;

	// 构造
	UIProvider();

	// 析构
	~UIProvider();

public:
	// 初始化
	static void InitUIManager();

	// 释放
	static void Release();

	// 添加控件
	static void AddWindow(UI_Window* _ui);

	// 删除控件
	static void DelWindow(UI_Window* _ui);

	// 更新
	static void Update();

	// 渲染
	static void Draw();

	// 判断顶层
	static bool GetLevelTop(UI_Window* _ui, POINT pos);
};

#endif //!_UIProvider_H_ 