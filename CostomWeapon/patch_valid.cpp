#include <iostream>
#include <string>
#include "patch_valid.h"
#include "fileop.h"
using namespace std;

void patch_valid() {
	const char* patch_en = "zone/redacted/patch_redacted.ff";
	const char* patch_un = "zone/redacted/patch_redacted_unabled.ff";
	string user_in;
	while (true) {
		if (file_ex(patch_en) != 0) {
			cout << "カスタム武器MODを無効にしますか？　Y/N" << endl;
			cin >> user_in;
			if (user_in == "y" || user_in == "Y") {
				if (file_rename(patch_en, patch_un) != 0) {
					cout << "成功しました" << endl;
					break;
				}
				else {
					cout << "失敗しました" << endl;
					break;
				}
			}
			else if (user_in == "N" || user_in == "n") {
				cout << "操作をキャンセルしました" << endl;
				break;
			}
			else {
				cout << "やり直してください" << endl;
			}
		}
		else if (file_ex(patch_un) != 0) {
			cout << "カスタム武器MODを有効にしますか？　Y/N" << endl;
			cin >> user_in;
			if (user_in == "y" || user_in == "Y") {
				if (file_rename(patch_un, patch_en) != 0) {
					cout << "成功しました" << endl;
					break;
				}
				else {
					cout << "失敗しました" << endl;
					break;
				}
			}
			else if (user_in == "N" || user_in == "n") {
				cout << "操作をキャンセルしました" << endl;
				break;
			}
			else {
				cout << "やり直してください" << endl;
			}
		}
		else {
			cout << "EROOR! Redacted MODファイルが存在しません" << endl;
			break;
		}
	}

	getchar();
}