#include "RenderProvider.h"

// 全局渲染程序 
RenderProvider* g_render = nullptr;

// 构造
RenderProvider::RenderProvider(){
	this->factory = nullptr;				// 渲染工厂
	this->render_target = nullptr;			// 画刷
	this->WicFactory = nullptr;			// WIC
	this->textfactory = nullptr;			// 文字工厂

}

// 析构
RenderProvider::~RenderProvider() {

}

// 新建 渲染器
void RenderProvider::BuildRenderProvider(HWND hwnd, D2D1_SIZE_U size) {
	if (!g_render) {
		g_render = new RenderProvider();
		g_render->InitRender(hwnd, size);
	}
}

// 释放 渲染器
void RenderProvider::Release() {
	if (g_render) {
		delete g_render;
		g_render = nullptr;
	}
}


// 创建图像
ID2D1Bitmap* RenderProvider::CreateImage(const char* filename, int index) {
	// 变量列表
	IWICFormatConverter* pConverter = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	wchar_t wfilename[260] = { 0 };
	bool result = 0;

	// 转换字符
	result = CharToWChar(filename, wfilename);
	if (result && g_render && g_render->render_target) {
		// 获取格式解析器
		hr = g_render->GetFormatConvert(pConverter, wfilename);

		// 由渲染器创建一个图像
		if (SUCCEEDED(hr)) {
			hr = g_render->render_target->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap);
			if (FAILED(hr)) {
				pBitmap->Release();
				pBitmap = nullptr;
			}
		}

		// 释放临时变量
		if (pConverter) {
			pConverter->Release();
			pConverter = nullptr;
		}
		return pBitmap;
	}
	return nullptr;
}

// 创建文件格式
IDWriteTextFormat* RenderProvider::CreateTextFormat(float font_size) {
	IDWriteTextFormat* textformat = nullptr;
	if (g_render && g_render->textfactory) {
		g_render->textfactory->CreateTextFormat(
			L"宋体", nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			font_size,
			L"",
			&textformat);
	}
	return textformat;
}

// 创建画刷
ID2D1SolidColorBrush* RenderProvider::CreateBrush(D2D1_COLOR_F color) {
	ID2D1SolidColorBrush* color_brush = nullptr;
	if (g_render && g_render->render_target) {
		g_render->render_target->CreateSolidColorBrush(color, &color_brush);
	}
	return color_brush;
}

// 创建布局
IDWriteTextLayout* RenderProvider::CreateTextLayout(wchar_t* render_text, IDWriteTextFormat* text_format) {
	IDWriteTextLayout* text_layout = nullptr;
	if (g_render && g_render->textfactory) {
		g_render->textfactory->CreateTextLayout(render_text,
			UINT32(wcslen(render_text)),
			text_format,
			0, 0,
			&text_layout);
	}
	return text_layout;
}

// 获取当前变换矩阵
D2D1::Matrix3x2F RenderProvider::GetMatrix() {
	D2D1::Matrix3x2F now_matrix;
	if (g_render && g_render->render_target) {
		g_render->render_target->GetTransform(&now_matrix);
	}
	return now_matrix;
}

// 复制图像
ID2D1Bitmap* RenderProvider::CopyImage(ID2D1Bitmap* src, D2D1_SIZE_U size, D2D1_RECT_U src_rect) {
	HRESULT hr = S_OK;
	ID2D1Bitmap* dst = nullptr;
	D2D1_POINT_2U start_pos = D2D1::Point2U();
	if (src && g_render && g_render->render_target) {
		hr = g_render->render_target->CreateBitmap(size, D2D1::BitmapProperties(src->GetPixelFormat()), &dst);
		if (dst && hr == S_OK) {
			dst->CopyFromBitmap(&start_pos, src, &src_rect);
		}
	}
	return dst;
}

// 旋转
void RenderProvider::Rotate(D2D1_MATRIX_3X2_F matrix, bool life) {

	if (g_render && g_render->render_target) {
		// 复原 
		if (life) {
			matrix = D2D1::Matrix3x2F(
				1, 0,
				0, 1,
				0, 0
			);
		}

		g_render->render_target->SetTransform(matrix);
	}

}

// 绘制图像
void RenderProvider::RenderImage(ID2D1Bitmap* image, D2D1_RECT_F rect, D2D1_RECT_F src_rect, float opacity, float angle) {
	if (g_render && g_render->render_target) {
		g_render->render_target->DrawBitmap(
			image, rect, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			src_rect);
	}
}

// 绘制文本
void RenderProvider::RenderText(wchar_t* render_text, IDWriteTextLayout* text_layout, D2D1_RECT_F text_rect, ID2D1SolidColorBrush* text_brash) {
	if (g_render && g_render->render_target) {
		g_render->render_target->DrawText(
			render_text, UINT32(wcslen(render_text)),
			text_layout,
			text_rect, text_brash,
			D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

// 绘制图形
void RenderProvider::RenderFigure(int figure_type,D2D1_RECT_F rect, ID2D1SolidColorBrush* figure_brash, float line_size, bool isfull) {

	if (g_render && g_render->render_target) {
		switch (figure_type) {
		case figuretype_rect:
			if (isfull) {
				g_render->render_target->FillRectangle(rect, figure_brash);
			}
			else {
				g_render->render_target->DrawRectangle(rect, figure_brash, line_size);
			}
			break;
		}

	}
}

// 绘制线条
void RenderProvider::RenderLine(D2D1_POINT_2F line_left, D2D1_POINT_2F line_right, ID2D1SolidColorBrush* line_brash) {
	if (g_render && g_render->render_target) {
		g_render->render_target->DrawLine(line_left, line_right, line_brash);
	}
}

// 创建WIC图像 
IWICBitmap* RenderProvider::GetD2Wic(LPCWSTR filename, int index) {
	// 变量列表
	IWICFormatConverter* pConverter = nullptr;
	IWICBitmap* wic_bitmap = nullptr;
	WICRect rcLock = { 0, 0, 0, 0 };
	UINT nwidth = 0, nheight = 0;
	IWICBitmapLock* pLock = nullptr;
	HRESULT hr = S_OK;

	if (this->WicFactory != nullptr) {
		// 获取格式对象 
		hr = GetFormatConvert(pConverter, filename);
		if (SUCCEEDED(hr) && pConverter != nullptr) {
			// 创建WIC图像 
			hr = WicFactory->CreateBitmapFromSource(pConverter, WICBitmapCacheOnLoad, &wic_bitmap);
			if (SUCCEEDED(hr) && wic_bitmap != nullptr){
				// 获取大小
				hr = wic_bitmap->GetSize(&nwidth, &nheight);
				if (SUCCEEDED(hr)) {
					rcLock = { 0, 0, (int)nwidth, (int)nheight };
				}
			
				if (rcLock.Width > 0 && rcLock.Height > 0) {
					// 锁定区域 
					hr = wic_bitmap->Lock(&rcLock, WICBitmapLockRead, &pLock);
					if (SUCCEEDED(hr)) {
						UINT cbBufferSize = 0;
						UINT cbStride = 0;
						BYTE* pv = nullptr;

						// Retrieve the stride.
						hr = pLock->GetStride(&cbStride);

						if (SUCCEEDED(hr)){
							hr = pLock->GetDataPointer(&cbBufferSize, &pv);
							if (SUCCEEDED(hr)){

							}
						}

						// Release the bitmap lock.
						pLock->Release();
					}
				}
			}

		}
	}
	
	return nullptr;
}

// 开始渲染
void RenderProvider::Begin(D2D1_COLOR_F color) {
	if (g_render && g_render->render_target) { 
		g_render->render_target->BeginDraw();
		g_render->render_target->Clear(color);
	}
}

// 结束渲染 
void RenderProvider::End() {
	if (g_render && g_render->render_target) {
		g_render->render_target->EndDraw();
	}
}

// 获取GID帧数
int RenderProvider::GetGIFIndex(LPCWSTR filename) {
	// 变量列表
	IWICImagingFactory* WicFactory = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	HRESULT hr = S_OK;
	int error = 0;								// 错误值

	// 没有错误 - 渲染对象
	if (error || render_target == nullptr) {
		return -1;
	}

	// 创建图像工厂
	hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(WicFactory), (LPVOID*)&WicFactory);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip2;
	}

	// 创建解码器
	hr = WicFactory->CreateDecoderFromFilename(
		filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip2;
	}

	// 获取帧数量
	UINT counter;
	if ((hr = pDecoder->GetFrameCount(&counter)) != S_OK) {
		error = GetLastError();
		goto buildip2;
	}

	// 释放资源
buildip2:
	if (WicFactory != nullptr) {
		WicFactory->Release();
		WicFactory = nullptr;
	}
	if (pDecoder != nullptr) {
		pDecoder->Release();
		pDecoder = nullptr;
	}
	if (pFrame != nullptr) {
		pFrame->Release();
		pFrame = nullptr;
	}

	if ((error != 0) || hr != S_OK) {
		return -1;
	}

	return (int)counter;
}

// 获取文本大小
bool RenderProvider::GetTextSize(const WCHAR* text, IDWriteTextFormat* pTextFormat, D2D1_SIZE_F& result) {
	HRESULT hr = S_OK;
	IDWriteTextLayout* pTextLayout = nullptr;

	// 创建文本布局 
	hr = textfactory->CreateTextLayout(text, UINT32(wcslen(text)), pTextFormat, 0.0f, 0.0f, &pTextLayout);
	if (SUCCEEDED(hr))
	{
		// 获取文本尺寸  
		DWRITE_TEXT_METRICS textMetrics;
		hr = pTextLayout->GetMetrics(&textMetrics);
		if (SUCCEEDED(hr)) {
			result = D2D1::SizeF(ceil(textMetrics.widthIncludingTrailingWhitespace), ceil(textMetrics.height));
		}
		else {
			return false;
		}
	}

	if (pTextLayout != nullptr) {
		pTextLayout->Release();
		pTextLayout = nullptr;
	}

	return true;
}



// 获取图像格式解析对象
HRESULT RenderProvider::GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename) {
	// 变量列表
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	int error = 0;								// 错误值

	// 没有错误 - 渲染对象
	if (error || render_target == nullptr || WicFactory == nullptr) {
		return -1;
	}

	// 创建图像工厂
	// 创建解码器
	hr = WicFactory->CreateDecoderFromFilename(
		filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 获取帧数量
	UINT counter;
	if ((hr = pDecoder->GetFrameCount(&counter)) != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 获取指定帧的图像
	hr = pDecoder->GetFrame(0, &pFrame);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 创建格式
	hr = WicFactory->CreateFormatConverter(&pConverter);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 初始化格式
	hr = pConverter->Initialize(
		pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.f,
		WICBitmapPaletteTypeCustom
	);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 释放资源
buildip3:
	if (pDecoder != nullptr) {
		pDecoder->Release();
		pDecoder = nullptr;
	}
	if (pFrame != nullptr) {
		pFrame->Release();
		pFrame = nullptr;
	}

	if ((error != 0) || hr != S_OK) {
		return -1;
	}

	return S_OK;
}

// 初始化渲染资源
bool RenderProvider::InitRender(HWND hwnd, D2D1_SIZE_U size) {
	// 句柄为空
	if (hwnd == nullptr) {
		return false;
	}

	// 结果
	HRESULT hr = S_OK;

	// COM组件初始化
	hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(this->WicFactory), (LPVOID*)&(this->WicFactory));
	if (FAILED(hr)) {
		return false;
	}

	// 创建工厂
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,&(factory));
	if (FAILED(hr)) {
		return false;
	}

	// 创建渲染精灵
	hr = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(hwnd, size), &(render_target));
	if (FAILED(hr)) {
		return false;
	}

	// 文字用
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(textfactory), reinterpret_cast<IUnknown**>(&textfactory));

	// 默认返回
	return true;
}
