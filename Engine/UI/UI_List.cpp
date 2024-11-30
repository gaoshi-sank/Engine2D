#include "UI_List.h"

// ����
UI_List::UI_List() {
	isshowList = false;
	show_index = -1;
	TopShow = nullptr;

}

// ����
UI_List::~UI_List() {

}

// ����
bool UI_List::Create() {
	return UI_Window::Create();
}

// ����
bool UI_List::Create(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	// �б�
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

// �����¼�
void UI_List::CheckEvent(int* param) {

}

// �ͷ�
void UI_List::Release() {

	// �б�
	for (auto& text : list_text) {
		if (text) {
			text->Release();
			delete text;
			text = nullptr;
		}
	}
	list_text.clear();

	// Top��ʾ
	if (TopShow) {
		TopShow->Release();
		delete TopShow;
		TopShow = nullptr;
	}


	UI_Window::Release();
}

// ���� 
void UI_List::Update() {
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
			if (list_click[0] == 0) {
				// �������
				list_click[1] = 1;
			}
		}
		// ��Χ��
		else {
			list_click[0] = 1;
			list_click[1] = 0;
		}
	}
	// ����ſ�
	else if(ret_leftdown == UP){
		// �ڷ�Χ�� - �ҵ����
		if (window_inrect && list_click[1] == 1 && TopShow) {
			
			bool isinTop = Point_In_Rect(cursor_pos, TopShow->text_rect);

			// ���� չ�����߹ر�����
			if (isinTop) {
				isshowList = !isshowList;
			}
			else {
				// ѡ��������һ��value
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

				// ѡ��һ����ʾ
				if (isbreak) {
					isshowList = false;	// �ر�����
					TopShow->ReSetText(list_text[show_index]->text.c_str());
				}
			}

			// ��չ����
			if (!list_text.empty()) {
				auto rect = window_rect;
				if (isshowList) {
					rect.bottom = list_text.back()->text_rect.bottom;
				}
				// �ر�����
				else {
					rect = TopShow->text_rect;
				}
				ExtendWindow(rect);

				// �ɼ���
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

// ���� 
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


// ���ô�������
void UI_List::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);

	if (TopShow) {
		TopShow->ReSetRect(_rect);
	}

	// �����ı�����
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

// ���ÿɼ���
void UI_List::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	// �ı�
	if (TopShow) {
		TopShow->visiable = life;
	}

	for (auto& node : list_text) {
		if (node) {
			node->visiable = life;
		}
	}
}

// ��չ��������
void UI_List::ExtendWindow(D2D1_RECT_F _rect, bool isextend) {
	UI_Window::MoveWindow(_rect);
}

// ����һ��
void UI_List::AddValue(std::string _text) {
	auto rect = window_rect;
	if (TopShow) {
		rect = TopShow->text_rect;
	}

	// ����
	auto newtext = SpriteProvider::CreateText(_text.c_str(), rect, D2D1::ColorF(255, 255, 255));
	if (newtext) {
		newtext->visiable = false;	// ���ɼ�
		list_text.push_back(newtext);
	}

	// ��������
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

// ��ȡ��ǰѡ��
int UI_List::GetValue() {
	return show_index + 1;
}