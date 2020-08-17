#include <iostream>
#include <string>
#include "patch_valid.h"
#include "fileop.h"


void patch_valid() {
	const char* patch_en = "zone/redacted/patch_redacted.ff";
	const char* patch_un = "zone/redacted/patch_redacted_old.ff";
	std::string user_in;
	
		if (file_ex(patch_en) != 0) {
			std::cout << "�J�X�^������MOD�𖳌��ɂ��܂����H�@Y/N" << std::endl;
			std::cin >> user_in;
			if (user_in == "y" || user_in == "Y") {
				if (file_rename(patch_en, patch_un) != 0) {
					std::cout << "�������܂���" << std::endl;
					
				}
				else {
					std::cout << "���s���܂���" << std::endl;
					
				}
			}
			else if (user_in == "N" || user_in == "n") {
				std::cout << "������L�����Z�����܂���" << std::endl;
				
			}
			else {
				std::cout << "��蒼���Ă�������" << std::endl;
			}
		}
		else if (file_ex(patch_un) != 0) {
			std::cout << "�J�X�^������MOD��L���ɂ��܂����H�@Y/N" << std::endl;
			std::cin >> user_in;
			if (user_in == "y" || user_in == "Y") {
				if (file_rename(patch_un, patch_en) != 0) {
					std::cout << "�������܂���" << std::endl;
					
				}
				else {
					std::cout << "���s���܂���" << std::endl;
					
				}
			}
			else if (user_in == "N" || user_in == "n") {
				std::cout << "������L�����Z�����܂���" << std::endl;
				
			}
			else {
				std::cout << "��蒼���Ă�������" << std::endl;
			}
		}
		else {
			std::cout << "EROOR! Redacted MOD�t�@�C�������݂��܂���" << std::endl;
			
		}
	
	std::cout << std::endl;
	getchar();
}