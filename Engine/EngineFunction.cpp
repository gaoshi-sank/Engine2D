#include "EngineFunction.h"


// 辅助函数
// 多字节转为宽字符 
bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// 转换 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}

	return result;
}

// 宽字节转多字节
char* WcharToChar(const wchar_t* wchar) {
	char* pchar = nullptr;
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, (int)wcslen(wchar), NULL, 0, NULL, NULL);
	if (len > 0) {
		pchar = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wchar, (int)wcslen(wchar), pchar, len, NULL, NULL);
		pchar[len] = '\0';
	}
	return pchar;
}

// ASCII 转 UTF_8
bool Ascii2Utf8(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// 转换 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_UTF8, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}
	return result;
}

// 总和 
int Sum_Int(vector<int> check) {
	int result;
	vector<int>::iterator it;

	// 
	result = 0;
	for (it = check.begin(); it != check.end(); it++) {
		result += (*it);
	}

	return result;
}

// 总和 
int Sum_Int(int* check, int len) {
	int result = 0;
	int i = 0;

	// 计算加合 
	if (check != nullptr && len > 0) {
		for (i = 0; i < len; i++) {
			result += check[i];
		}
	}

	return result;
}


// 切割字符串 - 返回字符数值 
vector<string> Split(const string strs, const string sub) {
	// 结果 
	vector<string> result;
	size_t start = 0, index = 0;

	//
	if (sub.empty()) {
		return result;
	}

	// 循环查找 
	index = strs.find_first_of(sub, 0);
	while (index != strs.npos) {
		// 位置和索引不一致 
		if (start != index) {
			result.push_back(strs.substr(start, index - start));
		}

		// 查找下一个位置 
		start = index + 1;
		index = strs.find_first_of(sub, start);
	}

	if (!strs.substr(start).empty()) {
		result.push_back(strs.substr(start));
	}

	return result;
}


// 返回方向键
int GetFaceValue(WPARAM wparam) {
	if (wparam == VK_LEFT) {
		return 4;
	}
	else if (wparam == VK_RIGHT) {
		return 6;
	}
	else if (wparam == VK_UP) {
		return 2;
	}
	else if (wparam == VK_DOWN) {
		return 8;
	}
	return 0;
}

// 切割字符串 - 返回整形数值 
vector<int> Split_Int(const string strs, const string sub) {
	// 结果
	vector<int> result;
	vector<string> sub_result;

	// 获取切割结果 
	sub_result = Split(strs, sub);
	if (!sub_result.empty()) {
		// 循环转换 
		for (unsigned int i = 0; i < sub_result.size(); i++) {
			result.push_back(atoi(sub_result[i].c_str()));
		}
	}

	return result;
}

// int 2 unsigned char
unsigned char* int2uchar(int key) {
	unsigned char* value = new unsigned char[4];
	memset(value, 0, sizeof(unsigned char) * 4);

	if (value != nullptr) {
		int temp = key;
		int index = sizeof(int) - 1;
		while (temp > 0) {
			value[index--] = temp % 256;
			temp /= 256;
			if (index < 0) {
				break;
			}
		}
	}

	return value;
}

// unsigned char 2 int
bool uchar2int(const unsigned char* key, int& value) {
	bool result = false;
	if (key != nullptr) {
		value = key[0] * 16777216 + key[1] * 65535 + key[2] * 256 + key[3] * 1;
		result = true;
	}

	return result;
}

// 2个bit转int
bool u2chtoint(const byte* key, int& value) {
	bool result = false;
	if (key != nullptr) {
		value = key[0] * 255 + key[1];
		result = true;
	}

	return result;
}

// 判定 点在区域内
bool Point_In_Rect(POINT _pos, D2D1_RECT_F _rect) {

	if (_rect.left <= _pos.x && _pos.x <= _rect.right) {
		if (_rect.top <= _pos.y && _pos.y <= _rect.bottom) {
			return true;
		}
	}

	return false;
}

// 判定 点在区域内
bool Point_In_Rect(D2D1_POINT_2F _pos, D2D1_RECT_F _rect) {
	if (_rect.left < _pos.x && _pos.x < _rect.right) {
		if (_rect.top < _pos.y && _pos.y < _rect.bottom) {
			return true;
		}
	}

	return false;
}

// 判定 区域在区域内
// rect1主区域， rect2判定区域
bool Rect_In_Rect(D2D1_RECT_F rect1, D2D1_RECT_F rect2) {
	// 完全处于 [ [] ]
	if ((rect1.left < rect2.left && rect1.left < rect2.right) && (rect2.left < rect1.right && rect2.right < rect1.right)) {
		if ((rect1.top < rect2.top && rect1.top < rect2.bottom) && (rect2.top < rect1.bottom && rect2.bottom < rect1.bottom)) {
			return true;
		}
	}

	return false;
}


// 判定区域交互2
// rect1主区域， rect2判定区域
bool Rect_In_Rect(int left, int top, int right, int bottom, D2D1_RECT_F rect2) {
	// 完全处于 [ [] ]
	if ((left < rect2.left && left < rect2.right) && (rect2.left < right && rect2.right < right)) {
		if ((top < rect2.top && top < rect2.bottom) && (rect2.top < bottom && rect2.bottom < bottom)) {
			return true;
		}
	}

	return false;
}


// 判定区域交互
// rect1主区域， rect2判定区域
// 1 = 不相交
// 2 = 重叠
// 3 = 其他
// 4 = 未知
int RectBoom(D2D1_RECT_F rect1, D2D1_RECT_F rect2) {
	// 不交集
	if ((rect2.left < rect1.left && rect2.right < rect1.left) ||		// 判定在主区域左边
		(rect2.left > rect1.right && rect2.right > rect1.left) ||		// 判定在主区域右边
		(rect2.top < rect1.top && rect2.bottom < rect1.top) ||			// 判定在主区域上边
		(rect2.top > rect1.bottom && rect2.bottom > rect1.bottom) 		// 判定在主区域下边
		) {
		return 1;
	}
	else {
		// 重叠或者区域内
		if (Rect_In_Rect(rect1, rect2)) {
			return 2;
		}
		// 其他
		else {
			return 3;
		}
	}
	return 0;
}

// 判断两个区域的方位
// rect1主区域， rect2判定区域
// 返回 九宫格方向
int RectFace(D2D1_RECT_F _rect1, D2D1_RECT_F _rect2) {
	int movex = (int)(_rect2.right + _rect2.left) / 2 - (int)(_rect1.right + _rect1.left) / 2;
	int movey = (int)(_rect2.bottom + _rect2.top) / 2 - (int)(_rect1.bottom + _rect1.top) / 2;
	return RectFace(movex, movey);
}

// 判断两个区域的方位
// rect1主区域， rect2判定区域
// 返回 九宫格方向
int RectFace(int movex, int movey) {
	int face = 0;
	if (movex > 0) {
		if (movey > 0) {
			face = 3;
		}
		else if (movey < 0) {
			face = 9;
		}
		else {
			face = 6;
		}
	}
	else if (movex < 0) {
		if (movey > 0) {
			face = 1;
		}
		else if (movey < 0) {
			face = 7;
		}
		else {
			face = 4;
		}
	}
	else {
		if (movey > 0) {
			face = 2;
		}
		else if (movey < 0) {
			face = 7;
		}
	}

	return face;
}
