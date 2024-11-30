#include "Sprite_Text.h"


// 
Sprite_Text::Sprite_Text() {
	// 基础属性
	type = SpriteType_Text;

	// 文本属性
	this->text = "";
	render_text = nullptr;
	font_size = 18.0f;
	text_brash = nullptr;
	text_color = D2D1::ColorF(0, 0, 0, 1.0f);
	text_layout = nullptr;
	text_rect = D2D1::RectF(0, 0, 0, 0);
	max_fontlength = 1024;						// 默认
	text_LevelStyle = 1;						// 水平风格 
	text_VerticalStyle = 1;						// 垂直风格
	text_swrapping = 0;							// 自动换行 

	text_format = RenderProvider::CreateTextFormat(font_size);
	text_brash = RenderProvider::CreateBrush(text_color);

}

// 析构 
Sprite_Text::~Sprite_Text() {

}


// 释放 
void Sprite_Text::Release() {
	// 文字格式
	if (text_format != nullptr) {
		text_format->Release();
		text_format = nullptr;
	}

	// 文本布局 
	if (text_layout != nullptr) {
		text_layout->Release();
		text_layout = nullptr;
	}

	// 底子画刷 
	if (text_brash != nullptr) {
		text_brash->Release();
		text_brash = nullptr;
	}

	// 文字
	if (!text.empty()) {
		text.clear();
	}

	// 渲染用
	if (render_text != nullptr) {
		delete[] render_text;
		render_text = nullptr;
	}
}

// 更新 
void Sprite_Text::Update() {

}

// 绘制 
void Sprite_Text::Draw() {
	// 可见
	if (visiable) {
		RenderProvider::RenderText(render_text, text_layout, text_rect, text_brash);
	}
}

// 绘制文本
void Sprite_Text::DrawExternText(D2D1_RECT_F _rect, std::string _text){
	// 变量
	bool ret = false;
	size_t loopnum = _text.size() / LIMIT_STRING_LENGTH;

	// 字节转换
	wchar_t* extern_text = new wchar_t[LIMIT_STRING_LENGTH * (loopnum + 1)];
	if (extern_text) {
		memset(extern_text, '\0', sizeof(wchar_t) * (LIMIT_STRING_LENGTH * (loopnum + 1)));
		ret = CharToWChar(_text.c_str(), extern_text);
		if (ret) {
			RenderProvider::RenderText(extern_text, text_layout, _rect, text_brash);
		}
		delete[] extern_text;
		extern_text = nullptr;
	}
}

// 绘制文本
void Sprite_Text::DrawExternText(D2D1_RECT_F _rect, wchar_t* _text) {
	if (visiable) {
		RenderProvider::RenderText(_text, text_layout, _rect, text_brash);
	}
}

// 重设文本 
bool Sprite_Text::ReSetText(const char* _text) {

	if (_text != nullptr) {
		// 重新设置文本
		this->text.clear();		
		this->text = _text;

		// 字节转换
		size_t loopnum = text.size() / LIMIT_STRING_LENGTH;
		this->render_text = new wchar_t[LIMIT_STRING_LENGTH * (loopnum + 1)];
		memset(this->render_text, '\0', sizeof(wchar_t) * (LIMIT_STRING_LENGTH * (loopnum + 1)));
		CharToWChar(text.c_str(), this->render_text);	

		// 文本布局
		ReSetLayout();

		return true;
	}

	return false;
}

// 重设区域 
void Sprite_Text::ReSetRect(D2D1_RECT_F _rect) {
	text_rect = _rect;
}

// 重设布局 
void Sprite_Text::ReSetLayout(int level_Style, int vertical_Style, int swrapping) {
	// 重设布局
	if (!this->text_layout) {
		this->text_layout = RenderProvider::CreateTextLayout(this->render_text, this->text_format);
	}

	// 其他属性 
	ReSetLevelStyle(level_Style);
	ReSetVerticalStyle(vertical_Style);
	ReSetSwrapping(swrapping);

}


// 重设字体大小
void Sprite_Text::ReSetFont(int _font_size) {

	// 设置字体
	font_size = (float)_font_size;
	this->text_format = RenderProvider::CreateTextFormat(font_size);

}

// 重设颜色 
void Sprite_Text::ReSetColor(D2D1_COLOR_F _color) {
	// 删除 
	if (text_brash != nullptr) {
		text_brash->Release();
		text_brash = nullptr;
	}

	// 重设
	text_color = _color;
	text_brash = RenderProvider::CreateBrush(text_color);
}

// 重设格式
// 默认1 = 居中
void Sprite_Text::ReSetLevelStyle(int state) {
	text_LevelStyle = state;
	if (text_layout != nullptr) {
		if (text_LevelStyle == 1) {
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);				// 水平居中 - 默认
		}
		else if (text_LevelStyle == 2) {
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);			// 字体铺满区域 - 可能存在拉伸
		}
		else if (text_LevelStyle == 3) {
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);			// 水平居右
		}
		else {
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);			// 水平居左
		}
	}
}

// 重设垂直格式 - 默认1 = 居中
void Sprite_Text::ReSetVerticalStyle(int state) {
	text_VerticalStyle = state;
	if (text_layout != nullptr) {
		if (text_VerticalStyle == 1) {
			text_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);	// 垂直居中 - 默认
		}
		else if (text_VerticalStyle == 2) {
			text_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);		// 下边
		}
		else {
			text_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);	// 上边
		}
	}
}

// 重设自动换行 
void Sprite_Text::ReSetSwrapping(int isSwrapping) {
	text_swrapping = isSwrapping;
	if (text_layout != nullptr) {
		if (text_swrapping == 1) {
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);				// 保持在同一行
		}
		else if (text_swrapping == 2) {
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_EMERGENCY_BREAK);		// 
		}
		else if (text_swrapping == 3) {
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_WHOLE_WORD);			// 
		}
		else if (text_swrapping == 4) {
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_CHARACTER);			// 
		}
		else {
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_WRAP);				// 文字跨行打断，以避免文字溢出布局框
		}
	}
}
