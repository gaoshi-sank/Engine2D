/*
* 动态图
*/
#ifndef _UI_GIF_H_
#define _UI_GIF_H_


#include "UI_Window.h"
#include "../TimerProvider.h"

enum GIFSTYLE {
	GIFSTYLE_NONE = 0,
	GIFSTYLE_MUL,
	GIFSTYLE_SINGLE,
};

// 静态图 
class UI_GIF : public UI_Window {
private:
	TimerProvider* m_timer;					// 时间间隔
	std::vector<Sprite_Image*> list_frames;	// 单图时 - 取[0]
	int gif_style;							// 风格，多图索引 - 单图多框
	int gif_mulindex;						// 多图时 - 索引
	int gif_singleindex;					// 单图时 - 索引
	int gif_onesize[4];						// 单图时 - 单位大小
	std::string gif_mapping;				// 动态图映射

public:
	// 构造
	UI_GIF();

	// 析构
	~UI_GIF();

	// 创建
	virtual bool Create();

	// 创建
	virtual bool Create(D2D1_RECT_F _rect, int style);

	// 释放
	virtual void Release();

	// 更新事件
	virtual void CheckEvent(int* param);

	// 更新 
	virtual void Update();

	// 绘制 
	virtual void Draw();

	// 设置窗口区域
	virtual void MoveWindow(D2D1_RECT_F _rect);

	// 设置可见性
	virtual void SetVisiable(bool life = true);

	// 设置多图资源
	virtual void SetGIF(std::vector<std::string> filename_lists, float time_lines);

	// 设置单图资源
	virtual void SetGIF(std::string filename, int maxsize[2], float time_lines);

	// 回调
	virtual void Callback_GifTimer(unsigned int _id);

	// 获取风格
	virtual int GetGIFStyle();

private:
	// 释放图像资源
	virtual void ReleaseImage();

};


#endif // !_UI_GIF_H_


