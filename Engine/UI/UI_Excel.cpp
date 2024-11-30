#include "UI_Excel.h"

// 构造
UI_Excel::UI_Excel() {
	// 窗口类型 
	window_style = WindowType_Excel;

	// 基础属性
	object_text = new Sprite_Text();
	object_background = nullptr;
	maxlength = 1;
	isbuild = true;

}

// 析构
UI_Excel::~UI_Excel() {

}

// 创建
bool UI_Excel::Create() {
	return UI_Window::Create();
}

// 释放
void UI_Excel::Release() {

	// 文本
	for (auto& text : list_texts) {
		if (text) {
			delete text;
			text = nullptr;
		}
	}
	list_texts.clear();

	if (object_text) {
		object_text->Release();
		delete object_text;
		object_text = nullptr;
	}

	UI_Window::Release();
}

// 增加字符
void UI_Excel::AddText(std::string _text) {
	ExcelText* onetext = new ExcelText();
	if (list_texts.size() < maxlength && onetext) {
		int index = (int)(list_texts.size());
		float width = (window_rect.right - window_rect.left) / maxlength;
		float height = (window_rect.bottom - window_rect.top);

		onetext->_text = _text;
		onetext->_rect = window_rect;
		onetext->_rect.left = window_rect.left + index * width;
		onetext->_rect.right = onetext->_rect.left + width;
		list_texts.push_back(onetext);
	}
	
	if (object_text && list_texts.size() >= 1) {
		object_text->ReSetText(list_texts[0]->_text.c_str());
		object_text->ReSetLayout();
	}
}

// 根据位置增加字符
void UI_Excel::AddText(int x, int y, std::string _text) {
	ExcelText* onetext = new ExcelText();
	if (onetext) {
		float width = (window_rect.right - window_rect.left) / maxlength;
		float height = (window_rect.bottom - window_rect.top) / 10;
		height = (height > 24.0f) ? 24.0f : height;

		onetext->_text = _text;
		onetext->_rect = window_rect;
		onetext->_rect.left = window_rect.left + x * width;
		onetext->_rect.right = onetext->_rect.left + width;
		onetext->_rect.top = window_rect.top + (y - 1) * height;
		onetext->_rect.bottom = onetext->_rect.top + height;
		list_texts.push_back(onetext);
	}

	if (object_text && list_texts.size() >= 1 && isbuild) {
		object_text->ReSetText(list_texts[0]->_text.c_str());
		isbuild = false;
	}
}

// 设置最大长度
void UI_Excel::SetMaxValue(int _maxlength) {
	maxlength = _maxlength;
}

// 设备背景
void UI_Excel::SetBackGround(const char* filename) {
	if (filename) {
		object_background = SpriteProvider::CreateImage(filename, window_rect);
		if (object_background) {

		}
	}
}

// 绘制文字颜色
void UI_Excel::SetTextColor(D2D1_COLOR_F _color) {
	if (object_text) {
		object_text->ReSetColor(_color);
		object_text->ReSetLayout();
	}
}

// 设置可见性
void UI_Excel::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// 背景
	if (object_background) {
		object_background->visiable = life;
	}

	// 绘制对象
	if (object_text) {
		object_text->visiable = life;
	}
}

// 更新事件
void UI_Excel::CheckEvent(int* param) {

}


// 更新 
void UI_Excel::Update() {
	UI_Window::Update();

}

// 绘制 
void UI_Excel::Draw() {
	UI_Window::Draw();

	if (object_text && this->window_visible) {
		for (auto node : list_texts) {
			object_text->DrawExternText(node->_rect, node->_text);
		}
	}
}

// 设置窗口区域
void UI_Excel::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	if (object_text) {
		object_text->text_rect = window_rect;
	}
}

