/*
	�ļ����� 
*/
#ifndef _FileControl_H_
#define _FileControl_H_

// ������
#include "EngineConfig.h"			// ���������ļ�

#define DEBUG64 1

// ���� 
struct link_map;
class FileControl;
using json_map = struct link_map;

// ���ݿ���
class FileControl {
public:
	
	// ����
	FileControl();

	// ����
	~FileControl();

	// �ͷ�
	static void Release();

	// ��ʼ��
	static void InitFileControl();

	// ת��·��
	static std::string ResPath(const char* filename);

public:
	// ��ȡһ������ 
	// -1 ��β
	// 1 �س�
	// 0 ��������
	static int ReadLineString(std::string& result, FILE* fp = nullptr);

	// ��ȡ��ֵ�������ļ�
	// 2 - һ�����ݽ���
	// -1 - ��β
	// 0 - ��������
	static int ReadJson(vector<json_map>& result,FILE* fp = nullptr);

protected:
	// ��ʼ�� �ļ�·�� 
	static void InitFilePath();
};

// ��ֵ�� 
struct link_map {
public:
	string key;		// 
	string value;	// ֵ

	// ����
	link_map() {

	}

	// ����
	// ���� 
	link_map(string _key, string _value) {
		key = _key;
		value = _value;
	}

	// ���� 
	~link_map() {
		key.clear();
		value.clear();
	}
};



#endif // !_DataProvider_H_
