#include "UI_Button.h"

// 构造
UI_Button::UI_Button() {
	// 窗口类型 
	this->window_style = WindowType_Button;

	// 文本
	text = nullptr;

	// 图像
	buttons.resize(buttonsize_button);

	// 按钮状态
	button_state = buttonstate_out;

}

// 析构
UI_Button::~UI_Button() {

}

// 创建
bool UI_Button::Create() {
	return UI_Window::Create();
}


// 创建
// 文件名
// style = buttontype_row4（常见4列按钮）
bool UI_Button::Create(std::string filename, int style, D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);
	SetButtonImage(style, filename.c_str());
	return Create();
}

// 释放
void UI_Button::Release() {

	// 文本
	if (text) {
		text->Release();
		delete text;
		text = nullptr;
	}

	// 图像
	for (auto& image : buttons) {
		if (image) {
			image->Release();
			delete image;
			image = nullptr;
		}
	}
	buttons.clear();

	UI_Window::Release();
}

// 更新事件
void UI_Button::CheckEvent(int* param) {
	UI_Window::CheckEvent(param);

	if (!param) {
		return;
	}

	int paramlen = param[0];
	if (paramlen < 2) {
		return;
	}

	int message = param[1];
	switch (message) {
	case WM_LBUTTONDOWN:
	{
		// 在范围内
		if (window_inrect) {
			// 不是全局状态
			if (button_click[0] == 0) {
				// 触发点击
				button_click[1] = 1;
			}
		}
		// 范围外
		else {
			button_click[0] = 1;
			button_click[1] = 0;
		}
	}
		break;
	case WM_LBUTTONUP:
	{
		// 在范围内 - 且点击过
		if (window_inrect && button_click[1] == 1) {
			// 触发按钮点击
			if (this->callback_buttonclick) {
				this->callback_buttonclick(this->window_id);
				if (this->window_release) {
					return;
				}
			}
		}

		button_click[0] = 0;
		button_click[1] = 0;
	}
		break;
	default:
		break;
	}
}

// 更新 
void UI_Button::Update() {
	UI_Window::Update();

	// 非释放状态
	if (!window_release && window_active) {
		// 更新状态
		if (window_inrect) {
			if (button_click[1] == 1) {
				button_state = buttonstate_down;
			}
			else {
				button_state = buttonstate_in;
			
			}
		}
		else {
			button_state = buttonstate_out;
		}
	}
	// 禁止状态
	else if (!window_active) {
		button_state = buttonstate_lose;
	}

	// 状态更新
	if (buttons.size() >= buttonsize_button &&
		(button_state >= buttonstate_out && button_state <= buttonstate_lose) &&
		buttons[button_state - 1]) {
		buttons[button_state - 1]->Update();
	}

	if (text) {
		text->Update();
	}

}

// 绘制 
void UI_Button::Draw() {
	UI_Window::Draw();

	if (buttons.size() >= buttonsize_button &&
		(button_state >= buttonstate_out && button_state <= buttonstate_lose) &&
		buttons[button_state - 1]) {
		buttons[button_state - 1]->Draw();
	}

	if (text) {
		text->Draw();
	}
}

// 设置窗口区域
void UI_Button::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// 图像
	for (auto node : buttons) {
		if (node) {
			node->rect = _rect;
		}
	}
}

// 设置可见性
void UI_Button::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// 文本
	if (text) {
		text->visiable = life;
	}

	// 图像
	if (!buttons.empty()) {
		for (auto& image : buttons) {
			if (image) {
				image->visiable = life;
			}
		}
	}
}

// 设置按钮图像
void UI_Button::SetButtonImage(int type, const char* filename) {
	
	if (type == buttontype_row4) {
		auto img = RenderProvider::CreateImage(filename);
		if (img) {
			float width = img->GetSize().width / buttonsize_button;
			float height = img->GetSize().height;

			// 重设
			for (auto i = 0; i < buttonsize_button && !buttons[i]; i++) {
				D2D1_RECT_F src_rect = D2D1::RectF(width * i, 0, width * (i + 1), height);
				buttons[i] = SpriteProvider::CreateImage(filename, window_rect, src_rect);
			}

			// 释放
			img->Release();
			img = nullptr;
		}
	}

}

// 设置按钮文本
void UI_Button::SetButtonText(const char* _text) {
	if (!text) {
		text = SpriteProvider::CreateText(_text, window_rect);
	}
}

// 设置按钮文本字体
void UI_Button::SetButtonFont(int font_size, D2D1_COLOR_F color) {
	// 文本
	if (text) {
		if (font_size >= 5) {
			text->ReSetFont(font_size);
		}
		text->ReSetColor(color);
	}
}

// 设置回调函数
void UI_Button::SetFunction_Click(std::function<void(unsigned int _id)> _callback_function) {
	this->callback_buttonclick = _callback_function;
}

// 获取按钮悬停状态
bool UI_Button::GetButtonHoverState() {
	return (button_state != buttonstate_lose && button_state != buttonstate_out);
}