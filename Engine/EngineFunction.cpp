#include "EngineFunction.h"


// ��������
// ���ֽ�תΪ���ַ� 
bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// ת�� 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}

	return result;
}

// ���ֽ�ת���ֽ�
char* WcharToChar(const wchar_t* wchar){
	char* pchar = nullptr;
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, (int)wcslen(wchar), NULL, 0, NULL, NULL);
	if (len > 0) {
		pchar = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wchar, (int)wcslen(wchar), pchar, len, NULL, NULL);
		pchar[len] = '\0';
	}
	return pchar;
}

// ASCII ת UTF_8
bool Ascii2Utf8(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// ת�� 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_UTF8, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}
	return result;
}

// �ж� ����������
bool Point_In_Rect(POINT _pos, RECT _rect) {
	if (_rect.left <= _pos.x && _pos.x <= _rect.right) {
		if (_rect.top <= _pos.y && _pos.y <= _rect.bottom) {
			return true;
		}
	}
	return false;
}