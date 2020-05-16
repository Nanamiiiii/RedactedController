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
			cout << "�J�X�^������MOD�𖳌��ɂ��܂����H�@Y/N" << endl;
			cin >> user_in;
			if (user_in == "y" || user_in == "Y") {
				if (file_rename(patch_en, patch_un) != 0) {
					cout << "�������܂���" << endl;
					break;
				}
				else {
					cout << "���s���܂���" << endl;
					break;
				}
			}
			else if (user_in == "N" || user_in == "n") {
				cout << "������L�����Z�����܂���" << endl;
				break;
			}
			else {
				cout << "��蒼���Ă�������" << endl;
			}
		}
		else if (file_ex(patch_un) != 0) {
			cout << "�J�X�^������MOD��L���ɂ��܂����H�@Y/N" << endl;
			cin >> user_in;
			if (user_in == "y" || user_in == "Y") {
				if (file_rename(patch_un, patch_en) != 0) {
					cout << "�������܂���" << endl;
					break;
				}
				else {
					cout << "���s���܂���" << endl;
					break;
				}
			}
			else if (user_in == "N" || user_in == "n") {
				cout << "������L�����Z�����܂���" << endl;
				break;
			}
			else {
				cout << "��蒼���Ă�������" << endl;
			}
		}
		else {
			cout << "EROOR! Redacted MOD�t�@�C�������݂��܂���" << endl;
			break;
		}
	}

	getchar();
}