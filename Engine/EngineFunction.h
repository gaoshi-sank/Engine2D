#ifndef _EngineFunction_h_
#define _EngineFunction_h_

// ����������
#include <Windows.h>				// Win32 API


// ��������
// ���ֽ�תΪ���ַ� 
bool CharToWChar(const char* szStr, WCHAR* wszClassName);

// ���ֽ�ת���ֽ�
char* WcharToChar(const wchar_t* wchar);

// ASCII ת UTF_8
bool Ascii2Utf8(const char* szStr, WCHAR* wszClassName);

// �ж� A��B��
bool Point_In_Rect(POINT _pos, RECT _rect);



#endif // !_EngineFunction_h_