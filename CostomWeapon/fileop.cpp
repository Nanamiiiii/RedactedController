#include <iostream>
#include <sys/stat.h>
#include "fileop.h"
#include <vector>
#include <direct.h>

int file_ex(const char* path) { /*�t�@�C�����ݔ���*/
	struct stat st;
	if (stat(path, &st) != 0) return 0;
	return (st.st_mode & S_IFMT) == S_IFREG;
}

int file_rename(const char* bef, const char* aft) { /*�t�@�C�����ύX*/
	if (file_ex(aft)) return 0;
	return !(rename(bef, aft));
}

int file_trans(const char* bef, const char* aft) { //�t�@�C���ړ��i���݊m�F����j
	if (file_ex(aft)) return 0;
	return (rename(bef, aft) == 0);
}

