#include "UIProvider.h"


// 变量列表
UIProvider* g_ui = nullptr;

// 构造
UIProvider::UIProvider() {

}

// 析构
UIProvider::~UIProvider() {

}

// 初始化
void UIProvider::InitUIManager() {
	if (!g_ui) {
		g_ui = new UIProvider();
	}
}

// 释放
void UIProvider::Release() {
	if (g_ui) {
		// 释放控件

	}
}

// 添加控件
void UIProvider::AddWindow(UI_Window* _ui) {
	if (g_ui) {
		std::lock_guard<std::mutex> lck(g_ui->lockAddlist);
		bool isdiff = true;
		for (auto& node : g_ui->addList) {
			if (node && _ui && (node == _ui || node->window_id == _ui->window_id)) {
				isdiff = false;
				break;
			}
		}
		if (isdiff) {
			g_ui->addList.push_back(_ui);
		}
	}
}

// 删除控件
void UIProvider::DelWindow(UI_Window* _ui) {
	if (g_ui) {
		std::lock_guard<std::mutex> lck(g_ui->lockDellist);
		bool issame = false;
		for (auto& node : g_ui->delList) {
			if (node && _ui && (node == _ui || node->window_id == _ui->window_id)) {
				issame = true;
				break;
			}
		}
		if (issame) {
			g_ui->delList.push_back(_ui);
		}
	}
}

// 更新
void UIProvider::Update() {
	if (g_ui) {
		std::lock_guard<std::mutex> lck(g_ui->lockList);

		// 删除
		for (auto& delui : g_ui->delList) {
			if (delui) {
				bool isdel = false;
				for (auto i = 0; i < g_ui->list.size();i++) {
					auto& node = g_ui->list[i];
					if (node && (node == delui || node->window_id == delui->window_id)) {
						delete node;
						node = nullptr;
						g_ui->list.erase(g_ui->list.begin() + i);
						isdel = true;
						break;
					}
				}
			}
		}
		g_ui->delList.clear();

		// 清空无效UI
		std::vector<UI_Window*>::iterator it;
		for (it = g_ui->list.begin(); it != g_ui->list.end(); ) {
			auto& node = (*it);
			bool iskeep = true;
			if (node && (node->window_id == 0x00 || node->window_release)) {
				delete node;
				node = nullptr;
				it = g_ui->list.erase(it);
				iskeep = false;
			}
			if (iskeep) {
				it++;
			}
		}

		// 增加
		for (auto& addui : g_ui->addList) {
			if (addui) {
				bool isdiff = true;
				for (auto i = 0; i < g_ui->list.size(); i++) {
					auto& node = g_ui->list[i];
					if (node && (node == addui || node->window_id == addui->window_id)) {
						isdiff = false;
						break;
					}
				}
				if (isdiff) {
					g_ui->list.push_back(addui);
				}
			}
		}
		g_ui->addList.clear();
		
		// 更新
		for (auto& _ui : g_ui->list) {
			if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
				_ui->Update();
			}
		}
	}
}

// 渲染
void UIProvider::Draw() {
	if (g_ui) {
		std::lock_guard<std::mutex> lck(g_ui->lockList);
		for (auto& _ui : g_ui->list) {
			if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
				_ui->Draw();
			}
		}
	}
}

// 可更新选项 
bool UIProvider::GetLevelTop(UI_Window* _ui, POINT pos) {
	if (g_ui) {
		// 获取可见-可用UI控件
		vector<UI_Window*> alltop;
		for (auto ui : g_ui->list) {
			// 可见
			if (ui && ui->window_visible) {
				// 符合当前区域 
				if (Point_In_Rect(pos, ui->window_rect)) {
					alltop.push_back(ui);
				}
			}
		}

		// 计算
		if (!alltop.empty()) {
			// 排序函数 
			auto func = [](UI_Window* left, UI_Window* right) -> bool {
				if (left != right) {
					if (left->window_renderlevel > right->window_renderlevel) {
						return true;
					}
				}
				return false;
				};
			// 重新排序渲染顺序 
			std::sort(alltop.begin(), alltop.end(), func);
			// 直接比较最大值 
			UI_Window*& maxlevel = alltop[0];
			if (maxlevel != nullptr) {
				if (_ui->window_renderlevel >= maxlevel->window_renderlevel) {
					return true;
				}
			}
		}
	}

	return false;
}
