#ifndef _EngineFunction_h_
#define _EngineFunction_h_

// 基础包含库
#include <Windows.h>				// Win32 API
#include "EngineConfig.h"			// 基础配置文件
#include "EngineRenderConfig.h"		// 渲染模块配置文件



// 辅助函数
// 多字节转为宽字符 
bool CharToWChar(const char* szStr, WCHAR* wszClassName);

// 宽字节转多字节
char* WcharToChar(const wchar_t* wchar);

// ASCII 转 UTF_8
bool Ascii2Utf8(const char* szStr, WCHAR* wszClassName);

// 总和 
int Sum_Int(vector<int> check);

// 总和 
int Sum_Int(int* check, int len);

// 切割字符串 - 返回整形数值 
vector<int> Split_Int(const string strs, const string sub);

// 切割字符串 - 返回字符数值 
vector<string> Split(const string strs, const string sub);

// 返回方向键
int GetFaceValue(WPARAM wparam);

// -----------------------------
// 字节流 
// int 2 unsigned char
unsigned char* int2uchar(int key);

// unsigned char 2 int
bool uchar2int(const unsigned char* key, int& value);

// 2个bit转int
bool u2chtoint(const byte* key, int& value);

// 判定 A在B内
bool Point_In_Rect(POINT _pos, D2D1_RECT_F _rect);
bool Point_In_Rect(D2D1_POINT_2F _pos, D2D1_RECT_F _rect);

// 判定区域交互1
// rect1主区域， rect2判定区域
bool Rect_In_Rect(D2D1_RECT_F rect1, D2D1_RECT_F rect2);

// 判定区域交互2
// rect1主区域， rect2判定区域
bool Rect_In_Rect(int left, int top, int right, int bottom, D2D1_RECT_F rect2);


// 判定区域交互
// rect1主区域， rect2判定区域
// 1 = 不相交
// 2 = 重叠
// 3 = 其他
// 4 = 未知
int RectBoom(D2D1_RECT_F _rect1, D2D1_RECT_F _rect2);

// 判断两个区域的方位
// rect1主区域， rect2判定区域
// 返回 九宫格方向
int RectFace(D2D1_RECT_F _rect1, D2D1_RECT_F _rect2);

// 判断两个区域的方位
// 给定判定区域与主区域的距离关系 movex，movey
// 返回 九宫格方向
int RectFace(int movex, int movey);



#endif // !_EngineFunction_h_