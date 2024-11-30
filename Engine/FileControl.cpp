#include "FileControl.h"

// 静态变量
static char static_filename[MAX_PATH] = { 0 };		// 文件路径 -- 相对 

// 构造
FileControl::FileControl() {
	

}

// 析构
FileControl::~FileControl() {

}

// 释放
void FileControl::Release() {

}

// 初始化
void FileControl::InitFileControl() {
	InitFilePath();			// 基础路径

}

// 转化路径
std::string FileControl::ResPath(const char* _path) {
	std::string resultpath;
	if (_path) {
		size_t len = strlen(_path);
		if (len > 0) {
			resultpath = static_filename;
			resultpath += _path;
		}
	}
	return resultpath;
}

// 初始化 文件路径 
void FileControl::InitFilePath() {
	// 初始化路径 
	memset(static_filename, '\0', sizeof(MAX_PATH));

	// 获取当前路径 
	GetModuleFileNameA(NULL, static_filename, MAX_PATH);

	//  
	size_t len = strlen(static_filename);
	size_t i = len - 1;
	int count = 0;
	int checkcount = 2;

	// 
#if _DEBUG
	checkcount = 3;
#else
	checkcount = 1;
#endif

	// 补全相对路径 
	while (i >= 0) {
		if (static_filename[i] == '\\') {
			count += 1;
			if (count >= checkcount) {
				static_filename[i + 1] = '\0';
				break;
			}
		}

		i--;
	}

	// 资源位置 
	std::string newpath = strcat(static_filename, "Res\\");
	strcpy(static_filename, newpath.c_str());
}

// 读取一行数据 
// -1 结尾
// 1 回车
// 0 函数结束
int FileControl::ReadLineString(std::string& result,FILE* fp) {
	if (fp != nullptr) {
		char ch = '\0';
		result.clear();			// 清空字符串 
		while (1) {
			ch = ::fgetc(fp);
			if (ch == EOF) {
				return -1;		// 结尾 
			}
			else if (ch == '\n') {
				return 1;		// 回车符
			}
			else {
				result += ch;
			}
		}
	}

	return 0;
}

// 读取键值对类型文件
// 2 - 一个数据结束
// -1 - 结尾
// 0 - 函数结束
int FileControl::ReadJson(vector<json_map>& result, FILE* fp) {
	if (fp != nullptr) {
		// 判定开头 
		auto isone_begin = [=](std::string strs) {
			for (auto ch : strs) {
				if (ch == '\n' || ch == '\r') {
					return false;
				}
				else if (ch == '{') {
					return true;
				}
			}
			return false;
		};

		// 判定结尾 
		auto isone_end = [=](std::string strs) {
			for (auto ch : strs) {
				if (ch == '\n' || ch == '\r') {
					return false;
				}
				else if (ch == '}') {
					return true;
				}
			}
			return false;
		};

		// 获取键值对  
		auto isone_data = [&](std::string strs, std::string& key, std::string& value) {
			int tip = 0;
			for (auto ch : strs) {
				if (ch == '\n' || ch == '\r') {
					break;
				}
				else if (ch == '"') {
					tip++;
				}
				else {
					if (tip >= 1 && tip < 2) {
						if (ch != '\t' && ch != ':') {
							key += ch;
						}
					}
					if (tip >= 3 && tip < 4) {
						value += ch;
					}
				}
			}
			return true;
		};

		// 循环读取
		int ret = 0;
		int read_state = 0;
		std::string line_strs = "";

		while (1) {
			// 读取一行数据 
			ret = ReadLineString(line_strs, fp);
			if (ret == 1) {
				// 判定开头 
				if (isone_begin(line_strs)) {
					read_state = 1;
				}
				// 判定结尾 
				else if (isone_end(line_strs)) {
					read_state = 2;
					return 2;// 一个数据结束 
				}
				// 中间数据 
				else {
					if (read_state == 1) {
						std::string key, value;
						if (isone_data(line_strs, key, value)) {
							json_map newone = json_map(key, value);
							result.push_back(newone);
						}
					}
				}

				// 清空字符串 
				line_strs.clear();
			}
			else {
				break;
			}
		}
		return ret;
	}

	return 0;
}
