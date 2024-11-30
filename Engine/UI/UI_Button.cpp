#include "UI_Button.h"

// ����
UI_Button::UI_Button() {
	// �������� 
	this->window_style = WindowType_Button;

	// �ı�
	text = nullptr;

	// ͼ��
	buttons.resize(buttonsize_button);

	// ��ť״̬
	button_state = buttonstate_out;

}

// ����
UI_Button::~UI_Button() {

}

// ����
bool UI_Button::Create() {
	return UI_Window::Create();
}


// ����
// �ļ���
// style = buttontype_row4������4�а�ť��
bool UI_Button::Create(std::string filename, int style, D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);
	SetButtonImage(style, filename.c_str());
	return Create();
}

// �ͷ�
void UI_Button::Release() {

	// �ı�
	if (text) {
		text->Release();
		delete text;
		text = nullptr;
	}

	// ͼ��
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

// �����¼�
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
		// �ڷ�Χ��
		if (window_inrect) {
			// ����ȫ��״̬
			if (button_click[0] == 0) {
				// �������
				button_click[1] = 1;
			}
		}
		// ��Χ��
		else {
			button_click[0] = 1;
			button_click[1] = 0;
		}
	}
		break;
	case WM_LBUTTONUP:
	{
		// �ڷ�Χ�� - �ҵ����
		if (window_inrect && button_click[1] == 1) {
			// ������ť���
			if (this->callback_buttonclick) {
				this->callback_buttonclick(this->window_id);
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

// ���� 
void UI_Button::Update() {
	UI_Window::Update();

	// ���ͷ�״̬
	if (!window_release && window_active) {
		// ����״̬
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
	// ��ֹ״̬
	else if (!window_active) {
		button_state = buttonstate_lose;
	}

	// ״̬����
	if (buttons.size() >= buttonsize_button &&
		(button_state >= buttonstate_out && button_state <= buttonstate_lose) &&
		buttons[button_state - 1]) {
		buttons[button_state - 1]->Update();
	}

	if (text) {
		text->Update();
	}

}

// ���� 
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

// ���ô�������
void UI_Button::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// ͼ��
	for (auto node : buttons) {
		if (node) {
			node->rect = _rect;
		}
	}
}

// ���ÿɼ���
void UI_Button::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// �ı�
	if (text) {
		text->visiable = life;
	}

	// ͼ��
	if (!buttons.empty()) {
		for (auto& image : buttons) {
			if (image) {
				image->visiable = life;
			}
		}
	}
}

// ���ð�ťͼ��
void UI_Button::SetButtonImage(int type, const char* filename) {
	
	if (type == buttontype_row4) {
		auto img = RenderProvider::CreateImage(filename);
		if (img) {
			float width = img->GetSize().width / buttonsize_button;
			float height = img->GetSize().height;

			// ����
			for (auto i = 0; i < buttonsize_button && !buttons[i]; i++) {
				RECT src_rect = RECT{ width * i, 0, width * (i + 1), height };
				buttons[i] = SpriteProvider::CreateImage(filename, window_rect, src_rect);
			}

			// �ͷ�
			img->Release();
			img = nullptr;
		}
	}

}

// ���ð�ť�ı�
void UI_Button::SetButtonText(const char* _text) {
	if (!text) {
		text = SpriteProvider::CreateText(_text, window_rect);
	}
}

// ���ð�ť�ı�����
void UI_Button::SetButtonFont(int font_size, D2D1_COLOR_F color) {
	// �ı�
	if (text) {
		if (font_size >= 5) {
			text->ReSetFont(font_size);
		}
		text->ReSetColor(color);
	}
}

// ���ûص�����
void UI_Button::SetFunction_Click(std::function<void(unsigned int _id)> _callback_function) {
	this->callback_buttonclick = _callback_function;
}

// ��ȡ��ť��ͣ״̬
bool UI_Button::GetButtonHoverState() {
	return (button_state != buttonstate_lose && button_state != buttonstate_out);
}