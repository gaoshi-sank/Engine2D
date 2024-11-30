#include "UI_SingleButton.h"

// 构造
UI_SingleButton::UI_SingleButton() {
	// 窗口类型 
	this->window_style = WindowType_SingleButton;

	// 文本
	text = nullptr;

	// 图像
	buttons.resize(buttonstate_lose);

	// 按钮状态
	single_click = NONE;
	button_state = buttonstate_out;

}

// 析构
UI_SingleButton::~UI_SingleButton() {

}

// 创建
bool UI_SingleButton::Create() {
	return UI_Window::Create();
}

// 构造
bool UI_SingleButton::Create(std::string filename, int style, D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);
	SetButtonImage(style, filename.c_str());
	return Create();
}

// 释放
void UI_SingleButton::Release() {

	// 图像
	for (auto& image : buttons) {
		if (image) {
			image->Release();
			delete image;
			image = nullptr;
		}
	}
	buttons.clear();

	// 文本
	if (text) {
		text->Release();
		delete text;
		text = nullptr;
	}

	UI_Window::Release();
}

// 更新事件
void UI_SingleButton::CheckEvent(int* param) {
	UI_Window::CheckEvent(param);
}

// 更新 
void UI_SingleButton::Update() {
	UI_Window::Update();

	// 非释放状态
	if (!window_release && window_active) {
		// 获取左键状态
		int ret_leftdown = false;
		auto input = InputProvider::GetInstance();
		if (input) {
			ret_leftdown = input->GetMouseStatus(MOUSESTATUS_LEFT);
		}

		if (ret_leftdown == DOWN) {
			if (window_inrect) {
				if (button_click[0] == 0) {
					button_click[1] = 1;
				}
			}
			else {
				button_click[0] = 1;
			}
		}
		else if (ret_leftdown == UP) {
			if (button_click[1] == 1) {
				single_click = (single_click == DOWN) ? UP : DOWN;

				// 触发单选
				if (this->window_allowacyive && this->callback_buttonclick) {
					this->callback_buttonclick(this->window_id);
					if (this->window_release) {
						return;
					}
				}
			}
			button_click[0] = 0;
			button_click[1] = 0;
		}

		if (single_click == DOWN) {
			button_state = buttonstate_down;
		}
		else {
			if (window_inrect) {
				button_state = buttonstate_in;
			}
			else {
				button_state = buttonstate_out;
			}
		}
	}
	// 禁止状态
	else if (!window_active) {
		button_state = buttonstate_lose;
	}

	// 状态更新
	if (buttons.size() >= 4 &&
		(button_state >= buttonstate_out && button_state <= buttonstate_lose) &&
		buttons[button_state - 1]) {
		buttons[button_state - 1]->Update();
	}

	// 文本
	if (text) {
		text->Update();
	}
}

// 绘制 
void UI_SingleButton::Draw() {
	UI_Window::Draw();

	if (buttons.size() >= 4 &&
		(button_state >= buttonstate_out && button_state <= buttonstate_lose) &&
		buttons[button_state - 1]) {
		buttons[button_state - 1]->Draw();
	}

	// 文本
	if (text) {
		text->Draw();
	}
}

// 设置窗口区域
void UI_SingleButton::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// 图像
	for (auto& node : buttons) {
		if (node) {
			node->rect = _rect;
		}
	}
}

// 获取单选状态
// DOWN - UP
int UI_SingleButton::GetSingleState() {
	return single_click;
}

// 设置可见性
void UI_SingleButton::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// 文本
	if (text) {
		text->visiable = life;
	}

	// 图像
	for (auto& node : buttons) {
		if (node) {
			node->visiable = life;
		}
	}

}

// 设置按钮图像
void UI_SingleButton::SetButtonImage(int type, const char* filename) {

	if (type == buttontype_row4) {
		auto img = RenderProvider::CreateImage(filename);
		if (img) {
			float width = img->GetSize().width / 4.0f;
			float height = img->GetSize().height;
			for (auto i = 0; i < buttonstate_lose && !buttons[i]; i++) {
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
void UI_SingleButton::SetButtonText(const char* _text) {
	if (!text) {
		text = SpriteProvider::CreateText(_text, window_rect);
	}
}

// 设置按钮文本字体
void UI_SingleButton::SetButtonFont(int font_size, D2D1_COLOR_F color) {
	// 文本
	if (text) {
		if (font_size >= 5) {
			text->ReSetFont(font_size);
		}
		text->ReSetColor(color);
	}
}

// 设置回调函数
void UI_SingleButton::SetFunction_Click(std::function<void(unsigned int _id)> _callback_function) {
	this->callback_buttonclick = _callback_function;
}

// 设置单选状态
void UI_SingleButton::SetSingleState(int state) {
	single_click = state;

	// 触发单选
	if (single_click == 1 && this->callback_buttonclick) {
		this->callback_buttonclick(this->window_id);
	}
}