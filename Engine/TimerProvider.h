/*
* 简单计时器
*/
#ifndef _TimerProvider_H_
#define _TimerProvider_H_

// 包含库
#include "EngineConfig.h"

// 常量
const int FRAME_NUM = 1000 / 60;		// 60帧

enum timestate {
	timestate_init = 1,
	timestate_start,
	timestate_pause,
	timestate_stop,
};

// 简单计时器类
// 使用方式：生成，创建，等回调
class TimerProvider {
public:
	unsigned int timer_id;	// 计时器编号

private: 
	LARGE_INTEGER frequency;	// 计时频率
	LARGE_INTEGER timer_start;
	LARGE_INTEGER timer_end;	// 计时器
	bool option_loop;			// 循环开关
	float option_timer;			// 计时时间
	int timer_state;			// 计时状态

	// 回调函数
	std::function<void(unsigned int)> trigger_function;	


public:
	// 构造
	TimerProvider();

	// 析构
	~TimerProvider();

	// 计时器引擎初始化
	static void InitTimer();

	// 计时器引擎停止
	static void Release();

	// 计时器创建
	static TimerProvider* Create(float timer,std::function<void(unsigned int)> call_function = nullptr, bool loop = false);

	// 开始计时 
	void start();

	// 暂停计时
	void pause();

	// 结束计时
	void exit();

	// 判定释放
	bool isrelease();

	// 更新 
	void update(LARGE_INTEGER now_timer);


};



#endif // !_TimerProvider_H_
