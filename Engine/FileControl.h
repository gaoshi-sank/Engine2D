/*
	文件操作 
*/
#ifndef _FileControl_H_
#define _FileControl_H_

// 包含库
#include "EngineConfig.h"			// 基础配置文件

#define DEBUG64 1

// 声明 
struct link_map;
class FileControl;
using json_map = struct link_map;

// 数据库类
class FileControl {
public:
	
	// 构造
	FileControl();

	// 析构
	~FileControl();

	// 释放
	static void Release();

	// 初始化
	static void InitFileControl();

	// 转化路径
	static std::string ResPath(const char* filename);

public:
	// 读取一行数据 
	// -1 结尾
	// 1 回车
	// 0 函数结束
	static int ReadLineString(std::string& result, FILE* fp = nullptr);

	// 读取键值对类型文件
	// 2 - 一个数据结束
	// -1 - 结尾
	// 0 - 函数结束
	static int ReadJson(vector<json_map>& result,FILE* fp = nullptr);

protected:
	// 初始化 文件路径 
	static void InitFilePath();
};

// 键值对 
struct link_map {
public:
	string key;		// 
	string value;	// 值

	// 构造
	link_map() {

	}

	// 构造
	// 参数 
	link_map(string _key, string _value) {
		key = _key;
		value = _value;
	}

	// 析构 
	~link_map() {
		key.clear();
		value.clear();
	}
};



#endif // !_DataProvider_H_

