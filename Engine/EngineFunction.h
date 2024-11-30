#ifndef _EngineFunction_h_
#define _EngineFunction_h_

// 基础包含库
#include <Windows.h>				// Win32 API


// 辅助函数
// 多字节转为宽字符 
bool CharToWChar(const char* szStr, WCHAR* wszClassName);

// 宽字节转多字节
char* WcharToChar(const wchar_t* wchar);

// ASCII 转 UTF_8
bool Ascii2Utf8(const char* szStr, WCHAR* wszClassName);

// 判定 A在B内
bool Point_In_Rect(POINT _pos, RECT _rect);



#endif // !_EngineFunction_h_