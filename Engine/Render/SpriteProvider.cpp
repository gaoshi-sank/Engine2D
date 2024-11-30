#include "SpriteProvider.h"

// 构造
SpriteProvider::SpriteProvider() {


}

// 析构 
SpriteProvider::~SpriteProvider() {

}

// 创建精灵
// 参数 - 图像路径
// 其他 绘制区域，裁剪区域，不透明度，旋转角度
Sprite_Image* SpriteProvider::CreateImage(const char* filename, D2D1_RECT_F _rect, D2D1_RECT_F _src_rect, float opacity, float angle) {
	Sprite_Image* resultsprite = new Sprite_Image();
	if (resultsprite) {
		// 获取图像
		resultsprite->image = RenderProvider::CreateImage(filename);
		if (resultsprite->image) {
			// 绘制整个图片
			if (_rect.right != 0) {
				resultsprite->rect = _rect;
			}
			else {
				resultsprite->rect.right = resultsprite->image->GetSize().width;
				resultsprite->rect.bottom = resultsprite->image->GetSize().height;
			}

			// 裁剪区 
			if (_src_rect.right == 0) {
				// 重设裁剪区
				resultsprite->src_rect.right = resultsprite->src_rect.left + resultsprite->image->GetSize().width;
				resultsprite->src_rect.bottom = resultsprite->src_rect.top + resultsprite->image->GetSize().height;
			}
			else {
				resultsprite->src_rect = _src_rect;
			}

			// 其他属性 
			resultsprite->opacity = opacity;
			resultsprite->angle = angle;
		}

	}
	return resultsprite;
}

// 创建文本精灵
// 参数 - 文本
// 其他 绘制区域，文本颜色
Sprite_Text* SpriteProvider::CreateText(const char* text, D2D1_RECT_F rect, D2D1_COLOR_F color) {
	Sprite_Text* resultsprite = new Sprite_Text();
	if (resultsprite) {
		resultsprite->ReSetText(text);
		resultsprite->ReSetRect(rect);
		resultsprite->ReSetColor(color);
	}
	return resultsprite;
}

// 创建图形精灵
Sprite_Figure* SpriteProvider::CreateFigure(D2D1_COLOR_F color, float line_size) {
	Sprite_Figure* resultsprite = new Sprite_Figure();
	if (resultsprite) {
		resultsprite->ReSetColor(color);
		resultsprite->ReSetLine(line_size);
	}
	return resultsprite;
}

// 创建线条精灵
Sprite_Line* SpriteProvider::CreateLine(D2D1_COLOR_F color, float line_size) {
	Sprite_Line* resultsprite = new Sprite_Line();
	if (resultsprite) {
		resultsprite->ResetLineColor(color);
	}
	return resultsprite;
}

// 创建动画精灵 - 单图创建
Animation* SpriteProvider::CreateAnimation(const char* filename, int style, float timeline, D2D1_RECT_F rect, D2D1_RECT_F _src_rect, float opacity, float angle) {
	Animation* result = new Animation();
	if (result) {
		ID2D1Bitmap* main_image = RenderProvider::CreateImage(filename);
		if (main_image) {
			// 素材拆解
			int cols = 1, rows = 1;
			switch (style) {
			case AniamtionStyle_Row4:
				cols = 4;
				break;
			case AniamtionStyle_Row8:
				cols = 8;
				break;
			case AniamtionStyle_Row16:
				cols = 16;
				break;
			}

			// 生成实例
			auto width = main_image->GetSize().width / cols;
			auto height = main_image->GetSize().height / rows;
			for (auto i = 0; i < cols;i++) {
				Sprite_Image* frame = new Sprite_Image();
				D2D1_RECT_U src_rect = D2D1::RectU((UINT32)(i * width), 0, (UINT32)((i + 1) * width), (UINT32)height);
				ID2D1Bitmap* newimage = RenderProvider::CopyImage(main_image, D2D1::SizeU((UINT32)width, (UINT32)height), src_rect);
				if (newimage && frame) {
					frame->image = newimage;
					frame->rect = rect;
					frame->src_rect = D2D1::RectF(0, 0, newimage->GetSize().width, newimage->GetSize().height);
					frame->opacity = opacity;
					frame->angle = angle;
					result->AddFrame(frame, timeline);
				}
			}
		}
	}
	return result;
}