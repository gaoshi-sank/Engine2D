/*
* 游戏引擎 - 渲染部分 
*/
#ifndef _RenderProvider_H_
#define _RenderProvider_H_

#include "EngineConfig.h"
#include "EngineFunction.h"
#include "EngineRenderConfig.h"


// 2.5D旋转矩阵
const D2D1::Matrix3x2F matrix_25d(
	0.866f, 0.5f,
	-0.866f, 0.5f,
	0, 0
);


enum figuretype {
	figuretype_rect = 1,
};

// 渲染实例 
class RenderProvider {
private:
	// 工具 
	ID2D1Factory* factory;							// 渲染工厂
	ID2D1HwndRenderTarget* render_target;			// 渲染画刷
	IWICImagingFactory* WicFactory = nullptr;		// WIC工厂
	IDWriteFactory* textfactory;					// 文字工厂

private:
	// 构造
	RenderProvider();

	// 析构
	~RenderProvider();


public:
	// 新建 渲染器
	static void BuildRenderProvider(HWND hwnd = NULL, D2D1_SIZE_U rect = {});

	// 释放 渲染器
	static void Release();

public:
	// 创建图像
	static ID2D1Bitmap* CreateImage(const char* filename, int index = 0);

	// 创建文件格式
	static IDWriteTextFormat* CreateTextFormat(float font_size);

	// 创建画刷
	static ID2D1SolidColorBrush* CreateBrush(D2D1_COLOR_F color);

	// 创建布局
	static IDWriteTextLayout* CreateTextLayout(wchar_t* render_text, IDWriteTextFormat* text_format);

	// 获取当前变换矩阵
	static D2D1::Matrix3x2F GetMatrix();

	// 复制图像
	static ID2D1Bitmap* CopyImage(ID2D1Bitmap* src, D2D1_SIZE_U size, D2D1_RECT_U src_rect);

	// 旋转
	static void Rotate(D2D1_MATRIX_3X2_F matrix, bool life = true);

	// 绘制图像
	static void RenderImage(ID2D1Bitmap* image, D2D1_RECT_F rect = D2D1::RectF(), D2D1_RECT_F src_rect = D2D1::RectF(), float opacity = 1.0f, float angle = 0.0f);

	// 绘制文本
	static void RenderText(wchar_t* render_text, IDWriteTextLayout* text_layout, D2D1_RECT_F text_rect, ID2D1SolidColorBrush* text_brash);

	// 绘制图形
	static void RenderFigure(int figure_type, D2D1_RECT_F rect, ID2D1SolidColorBrush* figure_brash, float line_size, bool isfull);

	// 绘制线条
	static void RenderLine(D2D1_POINT_2F line_left, D2D1_POINT_2F line_right, ID2D1SolidColorBrush* line_brash);

	// 开始渲染
	static void Begin(D2D1_COLOR_F color = D2D1::ColorF(0, 0, 0));

	// 结束渲染 
	static void End();

public:
	// 创建WIC图像 
	IWICBitmap* GetD2Wic(LPCWSTR filename, int index = 0);

public:
	// 获取GID帧数
	int GetGIFIndex(LPCWSTR filename);

	// 获取文本像素值 
	bool GetTextSize(const WCHAR* text, IDWriteTextFormat* pTextFormat, D2D1_SIZE_F& size);

protected:
	// 获取图像格式解析对象
	HRESULT GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename);

	// 初始化渲染资源
	bool InitRender(HWND hwnd, D2D1_SIZE_U size);

};


#endif // !_RenderProvider_H_
