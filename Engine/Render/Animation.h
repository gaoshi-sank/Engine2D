#ifndef _Animation_H_
#define _Animation_H_

#include "../TimerProvider.h"
#include "Sprite_Image.h"

// 一帧的参数
struct Frame {
	Sprite_Image* image;		// 图像
	TimerProvider* keeptime;	// 持续时间

	Frame();
	~Frame();
};

// 动画本
class Animation {
public:
	std::vector<Frame*> frames;		// 精灵列表
	unsigned int frame_index;		// 绘制索引
	bool option_auto;				// 自动开关
	

public:
	// 构造
	Animation();

	// 析构
	~Animation();

	// 释放
	void Release();

	// 增加一帧
	void AddFrame(Sprite_Image* frame, float timeline);

	// 开始循环
	void BeginAnimation();

	// 更新
	void Update();

	// 绘制
	void Draw();


protected:
	// 回调函数
	void Callback(unsigned int timer_id);

};





#endif // !_Animation_H_

