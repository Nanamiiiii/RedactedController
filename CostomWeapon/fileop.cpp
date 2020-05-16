#include <iostream>
#include <sys/stat.h>
#include "fileop.h"
#include <vector>
#include <direct.h>

int file_ex(const char* path) { /*ファイル存在判定*/
	struct stat st;
	if (stat(path, &st) != 0) return 0;
	return (st.st_mode & S_IFMT) == S_IFREG;
}

int file_rename(const char* bef, const char* aft) { /*ファイル名変更*/
	if (file_ex(aft)) return 0;
	return !(rename(bef, aft));
}

int file_trans(const char* bef, const char* aft) { //ファイル移動（存在確認あり）
	if (file_ex(aft)) return 0;
	return (rename(bef, aft) == 0);
}

