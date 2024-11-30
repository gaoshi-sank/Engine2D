#include "UI_Roll.h"

// ����
UI_Roll::UI_Roll() {
	// �������� 
	this->window_style = WindowType_Roll;

	// ͼ��
	rolls.resize(buttonsize_roll);

	// ��ť״̬
	roll_state = buttonstate_out;

}

// ����
UI_Roll::~UI_Roll() {

}

// ����
bool UI_Roll::Create() {
	return UI_Window::Create();
}

// ����
bool UI_Roll::Create(D2D1_RECT_F _rect, int style) {
	UI_Window::MoveWindow(_rect);
	if (style == buttontype_row2) {
		std::string res_path = "C:\\Users\\asus\\source\\repos\\san9pk\\Res\\Skin\\377-1.png";
		SetRollImage(buttontype_row2, res_path.c_str());
	}
	return Create();
}

// �ͷ�
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

// �����¼�
void UI_Roll::CheckEvent(int* param) {


}

// ���� 
void UI_Roll::Update() {
	UI_Window::Update();

	// ��ȡ���״̬
	int ret_leftdown = false;
	auto input = InputProvider::GetInstance();
	if (input) {
		ret_leftdown = input->GetMouseStatus(MOUSESTATUS_LEFT);
	}

	// �������
	if (ret_leftdown == DOWN) {
		// �ڷ�Χ��
		if (window_inrect) {
			// ����ȫ��״̬
			if (roll_click[0] == 0) {
				// �������
				roll_click[1] = 1;
			}
		}
		// ��Χ��
		else {
			roll_click[0] = 1;
			roll_click[1] = 0;
		}
	}
	// ����ſ�
	else if(ret_leftdown == UP) {
		// �ڷ�Χ�� - �ҵ����
		if (window_inrect && roll_click[1] == 1) {
			// ������ť���
			if (this->callback_rollclick) {
				this->callback_rollclick();
			}
		}

		roll_click[0] = 0;
		roll_click[1] = 0;
	}

	// ����״̬
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

// ���� 
void UI_Roll::Draw() {
	UI_Window::Draw();

	if (rolls.size() >= buttonsize_roll &&
		(roll_state >= rollstate_out && roll_state <= rollstate_in)) {
		rolls[roll_state - 1]->Draw();
	}

}

// ���ô�������
void UI_Roll::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);


}

// ���ÿɼ���
void UI_Roll::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);



}

// ���ù�����ͼ��
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

			// �ͷ�
			img->Release();
			img = nullptr;
		}
	}

}