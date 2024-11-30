#include "TimerProvider.h"

// 变量
static unsigned int timers_id = 0;
static std::thread* mainthread = nullptr;
static bool mainthreadstate = true;
static std::vector<TimerProvider*> list_timer;

// 独立线程计时
void MainThreadLoop() {

	// 线程下遍历
	LARGE_INTEGER now_timer;
	while (mainthreadstate) {
		// 获取当前时间
		QueryPerformanceCounter(&now_timer);	// 计时开始

		// 计算回调
		for (auto& timer : list_timer) {
			if (timer && timer->timer_id != 0) {
				timer->update(now_timer);
			}
		}

		// 删除计时器
		bool isdel = false;
		std::vector<TimerProvider*>::iterator it;
		for (it = list_timer.begin(); it != list_timer.end();) {
			isdel = false;
			if (*it && (*it)->timer_id == 0x00 && (*it)->isrelease()) {
				delete (*it);
				(*it) = nullptr;
				isdel = true;
				it = list_timer.erase(it);
			}

			if (!isdel) {
				it++;
			}
		}

		// 停止计时
		Sleep(1);
	}

	// 清空计时器 - 无视运行状态
	std::vector<TimerProvider*>::iterator it;
	for (it = list_timer.begin(); it != list_timer.end();it++) {
		if (*it) {
			(*it)->exit();
			delete (*it);
			(*it) = nullptr;
		}
	}
	list_timer.clear();

}

// 构造
TimerProvider::TimerProvider() {
	timer_id = ++timers_id;					// 编号
	option_timer = 0.0f;					// 回调间隔
	option_loop = true;						// 默认循环
	timer_state = timestate_init;			// 初始化

	QueryPerformanceFrequency(&frequency);	// cpu频率
	QueryPerformanceCounter(&timer_start);	// 计时开始
	QueryPerformanceCounter(&timer_end);	// 计时结束

}

// 析构
TimerProvider::~TimerProvider() {

}

// 计时器引擎初始化
void TimerProvider::InitTimer() {

	if (!mainthread) {
		mainthread = new std::thread(MainThreadLoop);
		if (mainthread) {
			mainthread->detach();
		}
	}

}

// 计时器引擎停止
void TimerProvider::Release() {

	mainthreadstate = false;
	while (!list_timer.empty()) {
		Sleep(1);
	}

	// 进程置空
	mainthread = nullptr;

}

// 计时器创建
TimerProvider* TimerProvider::Create(float timer, std::function<void(unsigned int)> call_function, bool loop) {
	TimerProvider* newnode = new TimerProvider();
	if (newnode) {
		// 回调函数
		newnode->option_timer = timer;					// 回调间隔
		newnode->trigger_function = call_function;		// 回调函数

		// 应该加个线程锁
		list_timer.push_back(newnode);
	}
	return newnode;
}


// 开始计时
void TimerProvider::start() {
	timer_state = timestate_start;
	QueryPerformanceCounter(&timer_start);
	QueryPerformanceCounter(&timer_end);
}

// 暂停计时
void TimerProvider::pause() {
	timer_state = timestate_pause;
	QueryPerformanceCounter(&timer_start);
	QueryPerformanceCounter(&timer_end);
}

// 结束计时
void TimerProvider::exit() {
	timer_state = timestate_stop;
	timer_id = 0x00;
}

// 判定释放
bool TimerProvider::isrelease() {
	return (timer_state == timestate_stop);
}

// 更新
void TimerProvider::update(LARGE_INTEGER now_timer) {
	timer_start = now_timer;
	
	// 开始
	if (timer_state == timestate_start) {
		double elapsedTime = static_cast<double>(timer_start.QuadPart - timer_end.QuadPart) / (frequency.QuadPart / 1000);
		if (abs(elapsedTime) >= 0.001f && abs(elapsedTime) >= option_timer) {
			timer_end = timer_start;
			// 计时器到期
			if (trigger_function) {
				trigger_function(timer_id);
			}

			// 循环触发
			if (!option_loop) {
				this->exit();
			}
		}
	}
	// 暂停
	else if (timer_state == timestate_pause) {
		timer_end = timer_start;
	}

}
