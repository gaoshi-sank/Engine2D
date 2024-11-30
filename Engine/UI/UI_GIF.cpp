#include "UI_GIF.h"


// ���� 
UI_GIF::UI_GIF() {
	// �������� 
	this->window_style = WindowType_GIF;

	// Ĭ�Ϸ��
	gif_style = GIFSTYLE_NONE;
	m_timer = nullptr;
	gif_mulindex = -1;
	gif_singleindex = -1;
	memset(gif_onesize, 1, sizeof(int) * 4);
	gif_mapping = "";

}

// ����
UI_GIF::~UI_GIF() {

}

// ����
bool UI_GIF::Create() {
	return UI_Window::Create();
}

// ����
bool UI_GIF::Create(D2D1_RECT_F _rect, int style) {
	UI_Window::MoveWindow(_rect);
	gif_style = style;
	return Create();
}

// �ͷ�
void UI_GIF::Release() {

	// �ͷ�ͼ����Դ
	ReleaseImage();

	// ��ʱ��
	if (m_timer) {
		m_timer->exit();
		m_timer = nullptr;
	}

	UI_Window::Release();
}

// �����¼�
void UI_GIF::CheckEvent(int* param) {

}

// ����
void UI_GIF::Update() {
	UI_Window::Update();
	
	if (gif_style == GIFSTYLE_MUL) {
		if (gif_mulindex >= 0 && gif_mulindex < list_frames.size()) {
			list_frames[gif_mulindex]->Update();
		}
	}
	else if (gif_style == GIFSTYLE_SINGLE) {
		if (!list_frames.empty()) {
			auto& frame = list_frames[0];

			// ���²ü�����
			if (this->gif_onesize[0] != 0) {
				int left = gif_singleindex  % this->gif_onesize[0];
				int top = gif_singleindex / this->gif_onesize[0];
				frame->src_rect.left = left * this->gif_onesize[2] * 1.0f;
				frame->src_rect.top = top * this->gif_onesize[3] * 1.0f;
				frame->src_rect.right = frame->src_rect.left + this->gif_onesize[2];
				frame->src_rect.bottom = frame->src_rect.top + this->gif_onesize[3];
			}

			// ����
			frame->Update();
		}
	}
	
}

// ��Ⱦ
void UI_GIF::Draw() {
	if (gif_style == GIFSTYLE_MUL) {
		if (gif_mulindex >= 0 && gif_mulindex < list_frames.size()) {
			list_frames[gif_mulindex]->Draw();
		}
	}
	else if (gif_style == GIFSTYLE_SINGLE) {
		if (!list_frames.empty()) {
			list_frames[0]->Draw();
		}
	}

}

// ���ô�������
void UI_GIF::MoveWindow(D2D1_RECT_F _rect) {
	UI_Window::MoveWindow(_rect);


}

// ���ÿɼ���
void UI_GIF::SetVisiable(bool life) {
	UI_Window::SetVisiable(life);

	for (auto i = 0; i < list_frames.size(); i++) {
		list_frames[i]->visiable = life;
	}

}

// ���ö�ͼ��Դ
void UI_GIF::SetGIF(std::vector<std::string> filename_lists, float time_lines) {

	for (auto i = 0; i < filename_lists.size();i++) {
		auto filename = filename_lists[i];
		if (!filename.empty()) {
			auto image = SpriteProvider::CreateImage(filename.c_str(), window_rect);
			if (image) {
				this->list_frames.push_back(image);
			}
		}
	}

	if (time_lines > 0.0f) {
		m_timer = TimerProvider::Create(time_lines, [&](unsigned int _id) {
			Callback_GifTimer(_id);
		}, true);
		if (m_timer) {
			m_timer->start();
			gif_mulindex = 0;
		}
	}
}

// ���õ�ͼ��Դ
void UI_GIF::SetGIF(std::string filename, int maxsize[2], float time_lines) {

	if (!filename.empty() && maxsize[0] != 0) {
		// ���ͼ����Դ
		ReleaseImage();

		// �������
		auto image = SpriteProvider::CreateImage(filename.c_str(), window_rect);
		if (image) {
			this->gif_onesize[0] = maxsize[0];	// ����
			this->gif_onesize[1] = maxsize[1];	// �߶�
			this->gif_onesize[2] = (int)(image->src_rect.right - image->src_rect.left) / maxsize[0];	// �����ü�ͼ���С
			this->gif_onesize[3] = (int)(image->src_rect.bottom - image->src_rect.top) / maxsize[1];	// 
			this->list_frames.push_back(image);
		}
	}

	if (time_lines > 0.0f) {
		m_timer = TimerProvider::Create(time_lines, [&](unsigned int _id) {
			Callback_GifTimer(_id);
		}, true);
		if (m_timer) {
			m_timer->start();
			gif_singleindex = 0;
		}
	}

}

// �ص�
void UI_GIF::Callback_GifTimer(unsigned int _id) {

	if (gif_style == GIFSTYLE_MUL) {
		++gif_mulindex;
		if (gif_mulindex >= list_frames.size()) {
			gif_mulindex = 0;
		}
	}
	else if (gif_style == GIFSTYLE_SINGLE) {
		++gif_singleindex;
		if (gif_singleindex >= (gif_onesize[0] * gif_onesize[1])) {
			gif_singleindex = 0;
		}
	}

}


// ��ȡ���
int UI_GIF::GetGIFStyle() {
	return this->gif_style;
}

// �ͷ�ͼ����Դ
void UI_GIF::ReleaseImage() {
	// ͼ��
	for (auto& image : list_frames) {
		if (image) {
			image->Release();
			delete image;
			image = nullptr;
		}
	}
	list_frames.clear();
}