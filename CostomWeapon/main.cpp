#include<iostream>
#include<sys/stat.h>
#include<string>
#include "demo_control.h"
#include "patch_valid.h"
using namespace std;

int main(void) {
	int N;
	cout << "###############################" << endl;
	cout << "#                             #" << endl;
	cout << "# Redacted 管理ツール by Myuu #" << endl;
	cout << "#                             #" << endl;
	cout << "###############################" << endl;
	cout << "実行する操作を選択してください" << endl;
	cout << "1. カスタム武器MODの切り替え" << endl;
	cout << "2. demoファイルの管理" << endl;
	cout << "3. 終了" << endl;
	cin >> N;
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
	getchar();
	return 0;
}
