#include "FileControl.h"

// ��̬����
static char static_filename[MAX_PATH] = { 0 };		// �ļ�·�� -- ��� 

// ����
FileControl::FileControl() {
	

}

// ����
FileControl::~FileControl() {

}

// �ͷ�
void FileControl::Release() {

}

// ��ʼ��
void FileControl::InitFileControl() {
	InitFilePath();			// ����·��

}

// ת��·��
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

// ��ʼ�� �ļ�·�� 
void FileControl::InitFilePath() {
	// ��ʼ��·�� 
	memset(static_filename, '\0', sizeof(MAX_PATH));

	// ��ȡ��ǰ·�� 
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

	// ��ȫ���·�� 
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

	// ��Դλ�� 
	std::string newpath = strcat(static_filename, "Res\\");
	strcpy(static_filename, newpath.c_str());
}

// ��ȡһ������ 
// -1 ��β
// 1 �س�
// 0 ��������
int FileControl::ReadLineString(std::string& result,FILE* fp) {
	if (fp != nullptr) {
		char ch = '\0';
		result.clear();			// ����ַ��� 
		while (1) {
			ch = ::fgetc(fp);
			if (ch == EOF) {
				return -1;		// ��β 
			}
			else if (ch == '\n') {
				return 1;		// �س���
			}
			else {
				result += ch;
			}
		}
	}

	return 0;
}

// ��ȡ��ֵ�������ļ�
// 2 - һ�����ݽ���
// -1 - ��β
// 0 - ��������
int FileControl::ReadJson(vector<json_map>& result, FILE* fp) {
	if (fp != nullptr) {
		// �ж���ͷ 
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

		// �ж���β 
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

		// ��ȡ��ֵ��  
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

		// ѭ����ȡ
		int ret = 0;
		int read_state = 0;
		std::string line_strs = "";

		while (1) {
			// ��ȡһ������ 
			ret = ReadLineString(line_strs, fp);
			if (ret == 1) {
				// �ж���ͷ 
				if (isone_begin(line_strs)) {
					read_state = 1;
				}
				// �ж���β 
				else if (isone_end(line_strs)) {
					read_state = 2;
					return 2;// һ�����ݽ��� 
				}
				// �м����� 
				else {
					if (read_state == 1) {
						std::string key, value;
						if (isone_data(line_strs, key, value)) {
							json_map newone = json_map(key, value);
							result.push_back(newone);
						}
					}
				}

				// ����ַ��� 
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