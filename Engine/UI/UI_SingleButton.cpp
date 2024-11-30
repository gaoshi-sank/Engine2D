#include "UI_SingleButton.h"

// ����
UI_SingleButton::UI_SingleButton() {
	// �������� 
	this->window_style = WindowType_SingleButton;

	// �ı�
	text = nullptr;

	// ͼ��
	buttons.resize(buttonstate_lose);

	// ��ť״̬
	single_click = NONE;
	button_state = buttonstate_out;

}

// ����
UI_SingleButton::~UI_SingleButton() {

}

// ����
bool UI_SingleButton::Create() {
	return UI_Window::Create();
}

// ����
bool UI_SingleButton::Create(std::string filename, int style, D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);
	SetButtonImage(style, filename.c_str());
	return Create();
}

// �ͷ�
void UI_SingleButton::Release() {

	// ͼ��
	for (auto& image : buttons) {
		if (image) {
			image->Release();
			delete image;
			image = nullptr;
		}
	}
	buttons.clear();

	// �ı�
	if (text) {
		text->Release();
		delete text;
		text = nullptr;
	}

	UI_Window::Release();
}

// �����¼�
void UI_SingleButton::CheckEvent(int* param) {


}

// ���� 
void UI_SingleButton::Update() {
	UI_Window::Update();

	// ���ͷ�״̬
	if (!window_release && window_active) {
		// ��ȡ���״̬
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

				// ������ѡ
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
	// ��ֹ״̬
	else if (!window_active) {
		button_state = buttonstate_lose;
	}

	// ״̬����
	if (buttons.size() >= 4 &&
		(button_state >= buttonstate_out && button_state <= buttonstate_lose) &&
		buttons[button_state - 1]) {
		buttons[button_state - 1]->Update();
	}

	// �ı�
	if (text) {
		text->Update();
	}
}

// ���� 
void UI_SingleButton::Draw() {
	UI_Window::Draw();

	if (buttons.size() >= 4 &&
		(button_state >= buttonstate_out && button_state <= buttonstate_lose) &&
		buttons[button_state - 1]) {
		buttons[button_state - 1]->Draw();
	}

	// �ı�
	if (text) {
		text->Draw();
	}
}

// ���ô�������
void UI_SingleButton::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// ͼ��
	for (auto& node : buttons) {
		if (node) {
			node->rect = _rect;
		}
	}
}

// ��ȡ��ѡ״̬
// DOWN - UP
int UI_SingleButton::GetSingleState() {
	return single_click;
}

// ���ÿɼ���
void UI_SingleButton::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// �ı�
	if (text) {
		text->visiable = life;
	}

	// ͼ��
	for (auto& node : buttons) {
		if (node) {
			node->visiable = life;
		}
	}

}

// ���ð�ťͼ��
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

			// �ͷ�
			img->Release();
			img = nullptr;
		}
	}

}

// ���ð�ť�ı�
void UI_SingleButton::SetButtonText(const char* _text) {
	if (!text) {
		text = SpriteProvider::CreateText(_text, window_rect);
	}
}

// ���ð�ť�ı�����
void UI_SingleButton::SetButtonFont(int font_size, D2D1_COLOR_F color) {
	// �ı�
	if (text) {
		if (font_size >= 5) {
			text->ReSetFont(font_size);
		}
		text->ReSetColor(color);
	}
}

// ���ûص�����
void UI_SingleButton::SetFunction_Click(std::function<void(unsigned int _id)> _callback_function) {
	this->callback_buttonclick = _callback_function;
}

// ���õ�ѡ״̬
void UI_SingleButton::SetSingleState(int state) {
	single_click = state;

	// ������ѡ
	if (single_click == 1 && this->callback_buttonclick) {
		this->callback_buttonclick(this->window_id);
	}
}