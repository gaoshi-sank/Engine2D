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
	
	// 不在此处释放
	if (keeptime) {
		keeptime->exit();
	}
}

// 构造
Animation::Animation() {
	frame_index = 0;
	option_auto = true;

}


// 析构
Animation::~Animation() {

}

// 释放
void Animation::Release() {


}

// 增加一帧
void Animation::AddFrame(Sprite_Image* frame, float timeline) {

	if (frame && timeline > 0.0f) {
		Frame* one = new Frame();
		if (one) {
			one->image = frame;
			one->image->visiable = false;	// 不可见
			one->keeptime = TimerProvider::Create(timeline,
				[&](unsigned int time_id) {
					Callback(time_id);
				});
			one->keeptime->pause();			// 不计时
			frames.push_back(one);
		}
	}
}

// 开始循环
void Animation::BeginAnimation() {
	if (!frames.empty() && 
		frames[0]->image && frames[0]->keeptime) {
		frames[0]->image->visiable = true;
		frames[0]->keeptime->start();
	}
}

// 更新
void Animation::Update() {



}

// 绘制
void Animation::Draw() {

	if (frame_index >= 0 && frame_index < frames.size() &&
		frames[frame_index]->image) {
		frames[frame_index]->image->Draw();
	}

}

// 回调函数
void Animation::Callback(unsigned int timer_id) {

	if (timer_id != 0x00) {
		// 应该匹配当前计时器的
		if (frame_index >= 0 && frame_index < frames.size() &&
			frames[frame_index]->image && frames[frame_index]->keeptime) {
			// 停止当前计时器
			auto index = frame_index;
			frames[index]->image->visiable = false;
			frames[index]->keeptime->pause();

			// 开始下一个计时器
			index += 1;
			frame_index = (index >= frames.size()) ? 0 : index;
			frames[frame_index]->image->visiable = true;
			frames[frame_index]->keeptime->start();
		}
	}

}