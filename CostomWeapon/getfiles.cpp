#include <Windows.h>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "getfiles.h"


std::vector<std::string> getDemoFiles(std::string dir_name) {

	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::vector<std::string> file_names;

	
	std::string extension[1] = { "demo" };
	


	for (int i = 0; i < 1; i++) {

		std::string search_name = dir_name + '/' + "*." + extension[i];
		hFind = FindFirstFile(search_name.c_str() , &win32fd);

		if (hFind == INVALID_HANDLE_VALUE) {
			continue;
		}
		do {
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			}
			else {
				file_names.push_back(win32fd.cFileName);
			}
		} while (FindNextFile(hFind, &win32fd));

		FindClose(hFind);
	}
	return file_names;
}
