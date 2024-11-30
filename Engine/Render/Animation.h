#ifndef _Animation_H_
#define _Animation_H_

#include "../TimerProvider.h"
#include "Sprite_Image.h"

// һ֡�Ĳ���
struct Frame {
	Sprite_Image* image;		// ͼ��
	TimerProvider* keeptime;	// ����ʱ��

	Frame();
	~Frame();
};

// ������
class Animation {
public:
	std::vector<Frame*> frames;		// �����б�
	unsigned int frame_index;		// ��������
	bool option_auto;				// �Զ�����
	

public:
	// ����
	Animation();

	// ����
	~Animation();

	// �ͷ�
	void Release();

	// ����һ֡
	void AddFrame(Sprite_Image* frame, float timeline);

	// ��ʼѭ��
	void BeginAnimation();

	// ����
	void Update();

	// ����
	void Draw();


protected:
	// �ص�����
	void Callback(unsigned int timer_id);

};





#endif // !_Animation_H_
