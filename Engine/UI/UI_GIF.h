/*
* ��̬ͼ
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

// ��̬ͼ 
class UI_GIF : public UI_Window {
private:
	TimerProvider* m_timer;					// ʱ����
	std::vector<Sprite_Image*> list_frames;	// ��ͼʱ - ȡ[0]
	int gif_style;							// ��񣬶�ͼ���� - ��ͼ���
	int gif_mulindex;						// ��ͼʱ - ����
	int gif_singleindex;					// ��ͼʱ - ����
	int gif_onesize[4];						// ��ͼʱ - ��λ��С
	std::string gif_mapping;				// ��̬ͼӳ��

public:
	// ����
	UI_GIF();

	// ����
	~UI_GIF();

	// ����
	virtual bool Create();

	// ����
	virtual bool Create(D2D1_RECT_F _rect, int style);

	// �ͷ�
	virtual void Release();

	// �����¼�
	virtual void CheckEvent(int* param);

	// ���� 
	virtual void Update();

	// ���� 
	virtual void Draw();

	// ���ô�������
	virtual void MoveWindow(D2D1_RECT_F _rect);

	// ���ÿɼ���
	virtual void SetVisiable(bool life = true);

	// ���ö�ͼ��Դ
	virtual void SetGIF(std::vector<std::string> filename_lists, float time_lines);

	// ���õ�ͼ��Դ
	virtual void SetGIF(std::string filename, int maxsize[2], float time_lines);

	// �ص�
	virtual void Callback_GifTimer(unsigned int _id);

	// ��ȡ���
	virtual int GetGIFStyle();

private:
	// �ͷ�ͼ����Դ
	virtual void ReleaseImage();

};


#endif // !_UI_GIF_H_

