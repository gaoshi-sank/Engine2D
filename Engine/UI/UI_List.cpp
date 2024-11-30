#include "UI_List.h"

// 构造
UI_List::UI_List() {
	isshowList = false;
	show_index = -1;
	TopShow = nullptr;

}

// 析构
UI_List::~UI_List() {

}

// 创建
bool UI_List::Create() {
	return UI_Window::Create();
}

// 创建
bool UI_List::Create(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// 列表
	for (auto& text : list_text) {
		if (text) {
			text->Release();
			delete text;
			text = nullptr;
		}
	}
	list_text.clear();

	if (!TopShow) {
		TopShow = SpriteProvider::CreateText("", window_rect);
	}
	return Create();
}

// 更新事件
void UI_List::CheckEvent(int* param) {

}

// 释放
void UI_List::Release() {

	// 列表
	for (auto& text : list_text) {
		if (text) {
			text->Release();
			delete text;
			text = nullptr;
		}
	}
	list_text.clear();

	// Top显示
	if (TopShow) {
		TopShow->Release();
		delete TopShow;
		TopShow = nullptr;
	}


	UI_Window::Release();
}

// 更新 
void UI_List::Update() {
	UI_Window::Update();

	// 获取左键状态
	int ret_leftdown = false;
	auto input = InputProvider::GetInstance();
	if (input) {
		ret_leftdown = input->GetMouseStatus(MOUSESTATUS_LEFT);
	}

	// 左键按下
	if (ret_leftdown == DOWN) {
		// 在范围内
		if (window_inrect) {
			// 不是全局状态
			if (list_click[0] == 0) {
				// 触发点击
				list_click[1] = 1;
			}
		}
		// 范围外
		else {
			list_click[0] = 1;
			list_click[1] = 0;
		}
	}
	// 左键放开
	else if(ret_leftdown == UP){
		// 在范围内 - 且点击过
		if (window_inrect && list_click[1] == 1 && TopShow) {
			
			bool isinTop = Point_In_Rect(cursor_pos, TopShow->text_rect);

			// 触发 展开或者关闭区域
			if (isinTop) {
				isshowList = !isshowList;
			}
			else {
				// 选择了任意一个value
				bool isbreak = false;
				for (auto i = 0; i < list_text.size();i++) {
					auto& node = list_text[i];
					if (node && node->visiable) {
						if (Point_In_Rect(cursor_pos, node->text_rect)) {
							show_index = i;
							isbreak = true;
							break;
						}
					}
				}

				// 选择一个显示
				if (isbreak) {
					isshowList = false;	// 关闭区域
					TopShow->ReSetText(list_text[show_index]->text.c_str());
				}
			}

			// 扩展区域
			if (!list_text.empty()) {
				auto rect = window_rect;
				if (isshowList) {
					rect.bottom = list_text.back()->text_rect.bottom;
				}
				// 关闭区域
				else {
					rect = TopShow->text_rect;
				}
				ExtendWindow(rect);

				// 可见性
				for (auto& node : list_text) {
					if (node) {
						node->visiable = isshowList;
					}
				}
			}
		}

		list_click[0] = 0;
		list_click[1] = 0;
	}

	if (TopShow) {
		TopShow->Update();

		if (isshowList) {
			for (auto& node : list_text) {
				if (node) {
					node->Update();
				}
			}
		}
	}

}

// 绘制 
void UI_List::Draw() {
	UI_Window::Draw();

	if (TopShow) {
		TopShow->Draw();

		if (isshowList) {
			for (auto& node : list_text) {
				if (node) {
					node->Draw();
				}
			}
		}
	}

}


// 设置窗口区域
void UI_List::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	if (TopShow) {
		TopShow->ReSetRect(_rect);
	}

	// 重设文本区域
	int index = 0x00;
	auto rect = window_rect;
	float height = rect.bottom - rect.top;
	for (auto& node : list_text) {
		if (node) {
			D2D1_RECT_F new_rect = rect;
			new_rect.top = rect.top + ++index * height;
			new_rect.bottom = new_rect.top + height;
			node->ReSetRect(new_rect);
		}
	}

}

// 设置可见性
void UI_List::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// 文本
	if (TopShow) {
		TopShow->visiable = life;
	}

	for (auto& node : list_text) {
		if (node) {
			node->visiable = life;
		}
	}
}

// 扩展窗口区域
void UI_List::ExtendWindow(D2D1_RECT_F _rect, bool isextend) {
	UI_Window::MoveWindow(_rect);
}

// 增加一条
void UI_List::AddValue(std::string _text) {
	auto rect = window_rect;
	if (TopShow) {
		rect = TopShow->text_rect;
	}

	// 新增
	auto newtext = SpriteProvider::CreateText(_text.c_str(), rect, D2D1::ColorF(255, 255, 255));
	if (newtext) {
		newtext->visiable = false;	// 不可见
		list_text.push_back(newtext);
	}

	// 重设区域
	int index = 0x00;
	float height = rect.bottom - rect.top;
	for (auto& node : list_text) {
		if (node) {
			D2D1_RECT_F new_rect = rect;
			new_rect.top = rect.top + ++index * height;
			new_rect.bottom = new_rect.top + height;
			node->ReSetRect(new_rect);
		}
	}

}

// 获取当前选择
int UI_List::GetValue() {
	return show_index + 1;
}