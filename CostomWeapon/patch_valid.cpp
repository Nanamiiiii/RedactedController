#include <iostream>
#include <string>
#include "patch_valid.h"
#include "fileop.h"


void patch_valid() {
	const char* patch_en = "zone/redacted/patch_redacted.ff";
	const char* patch_un = "zone/redacted/patch_redacted_old.ff";
	std::string user_in;
	
		if (file_ex(patch_en) != 0) {
			std::cout << "カスタム武器MODを無効にしますか？　Y/N" << std::endl;
			std::cin >> user_in;
			if (user_in == "y" || user_in == "Y") {
				if (file_rename(patch_en, patch_un) != 0) {
					std::cout << "成功しました" << std::endl;
					
				}
				else {
					std::cout << "失敗しました" << std::endl;
					
				}
			}
			else if (user_in == "N" || user_in == "n") {
				std::cout << "操作をキャンセルしました" << std::endl;
				
			}
			else {
				std::cout << "やり直してください" << std::endl;
			}
		}
		else if (file_ex(patch_un) != 0) {
			std::cout << "カスタム武器MODを有効にしますか？　Y/N" << std::endl;
			std::cin >> user_in;
			if (user_in == "y" || user_in == "Y") {
				if (file_rename(patch_un, patch_en) != 0) {
					std::cout << "成功しました" << std::endl;
					
				}
				else {
					std::cout << "失敗しました" << std::endl;
					
				}
			}
			else if (user_in == "N" || user_in == "n") {
				std::cout << "操作をキャンセルしました" << std::endl;
				
			}
			else {
				std::cout << "やり直してください" << std::endl;
			}
		}
		else {
			std::cout << "EROOR! Redacted MODファイルが存在しません" << std::endl;
			
		}
	
	std::cout << std::endl;
	getchar();
}