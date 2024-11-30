#include "UI_Roll.h"

// 构造
UI_Roll::UI_Roll() {
	// 窗口类型 
	this->window_style = WindowType_Roll;

	// 图像
	rolls.resize(buttonsize_roll);

	// 按钮状态
	roll_state = buttonstate_out;

}

// 析构
UI_Roll::~UI_Roll() {

}

// 创建
bool UI_Roll::Create() {
	return UI_Window::Create();
}

// 创建
bool UI_Roll::Create(D2D1_RECT_F _rect, int style) {
	UI_Window::MoveWindow(_rect);
	if (style == buttontype_row2) {
		std::string res_path = "C:\\Users\\asus\\source\\repos\\san9pk\\Res\\Skin\\377-1.png";
		SetRollImage(buttontype_row2, res_path.c_str());
	}
	return Create();
}

// 释放
void UI_Roll::Release() {

	for (auto& image : rolls) {
		if (image) {
			image->Release();
			delete image;
			image = nullptr;
		}
	}
	rolls.clear();

	UI_Window::Release();
}


// 更新 
void UI_Roll::Update() {
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
			if (roll_click[0] == 0) {
				// 触发点击
				roll_click[1] = 1;
			}
		}
		// 范围外
		else {
			roll_click[0] = 1;
			roll_click[1] = 0;
		}
	}
	// 左键放开
	else if(ret_leftdown == UP) {
		// 在范围内 - 且点击过
		if (window_inrect && roll_click[1] == 1) {
			// 触发按钮点击
			if (this->callback_rollclick) {
				this->callback_rollclick();
			}
		}

		roll_click[0] = 0;
		roll_click[1] = 0;
	}

	// 更新状态
	if (window_inrect) {
		if (roll_click[1] == 1) {
			roll_state = buttonstate_down;
		}
		else {
			roll_state = buttonstate_in;
		}
	}
	else {
		roll_state = buttonstate_out;
	}


}

// 绘制 
void UI_Roll::Draw() {
	UI_Window::Draw();

	if (rolls.size() >= buttonsize_roll &&
		(roll_state >= rollstate_out && roll_state <= rollstate_in)) {
		rolls[roll_state - 1]->Draw();
	}

}

// 设置窗口区域
void UI_Roll::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);


}

// 设置可见性
void UI_Roll::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);



}

// 设置滚动条图像
void UI_Roll::SetRollImage(int type, const char* filename) {

	if (type == buttontype_row2) {
		auto img = RenderProvider::CreateImage(filename);
		if (img) {
			float width = img->GetSize().width / buttonsize_roll;
			float height = img->GetSize().height;
			for (auto i = 0; i < buttonsize_roll && !rolls[i]; i++) {
				D2D1_RECT_F src_rect = D2D1::RectF(width * i, 0, width * (i + 1), height);
				rolls[i] = SpriteProvider::CreateImage(filename, window_rect, src_rect);
			}

			// 释放
			img->Release();
			img = nullptr;
		}
	}

}