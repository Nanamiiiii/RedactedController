#include<iostream>
#include<sys/stat.h>
#include<string>
#include "demo_control.h"
#include "patch_valid.h"


int main(void) {
	while (true){
	int N;
	std::cout << "###############################" << std::endl;
	std::cout << "#                             #" << std::endl;
	std::cout << "# Redacted 管理ツール by Myuu #" << std::endl;
	std::cout << "#                             #" << std::endl;
	std::cout << "###############################" << std::endl;
	std::cout << "実行する操作を選択してください" << std::endl;
	std::cout << "1. カスタム武器MODの切り替え" << std::endl;
	std::cout << "2. demoファイルの管理" << std::endl;
	std::cout << "3. 終了" << std::endl;
	std::cout << std::endl;
	std::cin >> N;
	
		switch (N) {
		case 1:
			patch_valid();
			break;
		case 2:
			demo_control();
			break;
		case 3:
			return 0;
		default:
			break;
		}
	}
	getchar();
	return 0;
}
