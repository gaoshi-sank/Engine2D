#include "Animation.h"

Frame::Frame() {
	image = nullptr;
	keeptime = nullptr;

}

Frame::~Frame() {

	if (image) {
		image->Release();
		delete image;
		image = nullptr;
	}
	
	// ���ڴ˴��ͷ�
	if (keeptime) {
		keeptime->exit();
	}
}

// ����
Animation::Animation() {
	frame_index = 0;
	option_auto = true;

}


// ����
Animation::~Animation() {

}

// �ͷ�
void Animation::Release() {


}

// ����һ֡
void Animation::AddFrame(Sprite_Image* frame, float timeline) {

	if (frame && timeline > 0.0f) {
		Frame* one = new Frame();
		if (one) {
			one->image = frame;
			one->image->visiable = false;	// ���ɼ�
			one->keeptime = TimerProvider::Create(timeline,
				[&](unsigned int time_id) {
					Callback(time_id);
				});
			one->keeptime->pause();			// ����ʱ
			frames.push_back(one);
		}
	}
}

// ��ʼѭ��
void Animation::BeginAnimation() {
	if (!frames.empty() && 
		frames[0]->image && frames[0]->keeptime) {
		frames[0]->image->visiable = true;
		frames[0]->keeptime->start();
	}
}

// ����
void Animation::Update() {



}

// ����
void Animation::Draw() {

	if (frame_index >= 0 && frame_index < frames.size() &&
		frames[frame_index]->image) {
		frames[frame_index]->image->Draw();
	}

}

// �ص�����
void Animation::Callback(unsigned int timer_id) {

	if (timer_id != 0x00) {
		// Ӧ��ƥ�䵱ǰ��ʱ����
		if (frame_index >= 0 && frame_index < frames.size() &&
			frames[frame_index]->image && frames[frame_index]->keeptime) {
			// ֹͣ��ǰ��ʱ��
			auto index = frame_index;
			frames[index]->image->visiable = false;
			frames[index]->keeptime->pause();

			// ��ʼ��һ����ʱ��
			index += 1;
			frame_index = (index >= frames.size()) ? 0 : index;
			frames[frame_index]->image->visiable = true;
			frames[frame_index]->keeptime->start();
		}
	}

}