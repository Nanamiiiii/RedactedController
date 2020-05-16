#include <iostream>
#include <sys/stat.h>
#include <direct.h>
#include <vector>
#include <string>
#include "fileop.h"
#include "getfiles.h"
#include "demo_control.h"


using namespace std;

void demo_tores() { //demo�t�@�C���̑ޔ�����
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const string other_ext[3] = { "summary", "tags", "thumbnail" };
	struct stat st;
	if (stat(reserve_folder, &st) != 0) { //���U�[�u�f�B���N�g�����Ȃ��Ȃ�쐬
		_mkdir(reserve_folder);
	}
	vector<string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) { //vector��0�Ȃ�t�@�C���Ȃ��̗�O����
		cout << "demo�t�@�C�������݂��܂���" << endl;
		return;
	}
	cout << "�ޔ�����demo�t�@�C����I�����Ă�������" << endl;
	cout << "######################################" << endl;
	for (int i = 0; i < demo_files.size(); i++) { //�t�@�C���ꗗ�̏o��
		cout << i << " " << demo_files[i].c_str() << endl;
	}
	int N;
	cin >> N; //�t�@�C���ԍ��̓��͏���

	if (N < 0 || N >= demo_files.size()) { //�͈͊O�̔ԍ��̏ꍇ�C��O����
		cout << "�L���Ȕԍ�����͂��Ă��������B" << endl;
		return;
	}

	string thisFile = string(demo_folder) + string("/") + demo_files[N];
	string toFile = string(reserve_folder) + string("/") + demo_files[N]; //�ڍs���C��̃A�h���X

	

	if (file_rename(thisFile.c_str(), toFile.c_str()) != 0) { //�ڍs�����@���@��O����
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			string source = thisFile + '.' + other_ext[i];
			string dest = toFile + '.' + other_ext[i];
			if (file_rename(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				cout << "�ړ��Ɏ��s���܂���" << endl;
				continue;
			}
		}
	}
	else {
		cout << "�ړ��Ɏ��s���܂���" << endl;
	}
	cout << "�������������܂���" << endl;

	getchar();
	return;
}

void demo_add() { //reserve����demo��߂�����
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const string other_ext[3] = { "summary", "tags", "thumbnail" };
	struct stat st;
	if (stat(reserve_folder, &st) != 0) {
		cout << "���U�[�u�t�H���_�����݂��܂���" << endl;
		cout << "�ǉ�����demo�̓��U�[�u�t�H���_(/demo_reserve)�����ɒu����Ă���K�v������܂��B" << endl;
		return;
	}
	vector<string> demo_files = getDemoFiles(reserve_folder);
	if (demo_files.size() == 0) {
		cout << "���U�[�u�t�H���_��demo�����݂��܂���" << endl;
		return;
	}
	else if (demo_files.size() > 2) {
		cout << "���ł�demo�t�@�C����2�ȏ㑶�݂��܂��B" << endl;
		cout << "����ȏ�ǉ����Ă�redacted�����ǂݍ��݂܂��񂪂�낵���ł����H Y/N" << endl;
		string user_in;
		cin >> user_in;
		if (user_in == "Y" || user_in == "y") {
			cout << "�����𑱍s���܂��B" << endl;
		}
		else if (user_in == "N" || user_in == "n") {
			cout << "�����𒆒f���܂��B" << endl;
			return;
		}
		else {
			cout << "������x���߂����蒼���Ă��������B" << endl;
			return;
		}

	}

	cout << "�ǉ�����demo��I�����Ă�������" << endl;
	cout << "##############################" << endl;
	for (int i = 0; i < demo_files.size(); i++) {
		cout << i << " " << demo_files[i].c_str() << endl;
	}

	int N;
	cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		cout << "�L���Ȕԍ�����͂��Ă��������B" << endl;
		return;
	}

	string toFile = string(demo_folder) + '/' + demo_files[N];
	string thisFile = string(reserve_folder) + '/' + demo_files[N];

	if (file_rename(thisFile.c_str(), toFile.c_str()) != 0) { //�ڍs�����@���@��O����
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			string source = thisFile + '.' + other_ext[i];
			string dest = toFile + '.' + other_ext[i];
			if (file_rename(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				cout << "�ړ��Ɏ��s���܂���" << endl;
				continue;
			}
		}
	}
	else {
		cout << "�ړ��Ɏ��s���܂���" << endl;
	}
	cout << "�������������܂���" << endl;

	getchar();
	return;

}

void demo_exchange() {
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const string other_ext[3] = { "summary", "tags", "thumbnail" };

	struct stat st;
	if (stat(reserve_folder, &st) != 0) {
		cout << "���U�[�u�t�H���_�����݂��܂���" << endl;
		cout << "����ւ��邷��demo�̓��U�[�u�t�H���_(/demo_reserve)�����ɒu����Ă���K�v������܂��B" << endl;
		return;
	}
	
	vector <string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) {
		cout << "demo�t�H���_�Ƀt�@�C�������݂��܂���B" << endl;
		return;
	}

	cout << "��������t�@�C����I�����Ă��������B(demo�t�H���_��)" << endl;
	cout << "####################################" << endl;
	for (int i = 0; i < demo_files.size(); i++) {
		cout << i << " " << demo_files[i].c_str() << endl;
	}

	int N;
	cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		cout << "�L���Ȑ�������͂��ĉ������B" << endl;
		return;
	}

	vector <string> demo_files_res = getDemoFiles(reserve_folder);
	if (demo_files_res.size() == 0) {
		cout << "reserve�t�H���_�Ƀt�@�C�������݂��܂���B" << endl;
		return;
	}

	cout << "��������t�@�C����I�����Ă��������B(reserve��)" << endl;
	cout << "####################################" << endl;
	for (int i = 0; i < demo_files_res.size(); i++) {
		cout << i << " " << demo_files_res[i].c_str() << endl;
	}

	int M;
	cin >> M;

	if (M < 0 || M >= demo_files_res.size()) {
		cout << "�L���Ȑ�������͂��Ă��������B" << endl;
		return;
	}


	string thisFile = string(demo_folder) + '/' + demo_files[N];
	string toFile = string(reserve_folder) + '/' + demo_files[N]; //�ڍs���C��̃A�h���X

	string thisFile_res = string(reserve_folder) + '/' + demo_files_res[M];
	string toFile_res = string(demo_folder) + '/' + demo_files_res[M];

	cout << "�ȉ��̓���ւ������s���܂� Y/N" << endl;
	cout << thisFile.c_str() << "��" << thisFile_res.c_str() << endl;

	string user_in;
	if (user_in == "N" || user_in == "n"){
		cout << "���f���܂���" << endl;
		return;
	}
	else if(user_in != "Y" || user_in != "y"){
		cout << "��蒼���Ă�������" << endl;
		return;
	}

	if (file_trans(thisFile.c_str(), toFile.c_str()) != 0) { //�ڍs�����@���@��O���� (demo >> reserve)
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			string source = thisFile + '.' + other_ext[i];
			string dest = toFile + '.' + other_ext[i];
			if (file_trans(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				cout << "�ړ��Ɏ��s���܂���" << endl;
				continue;
			}
		}
	}
	else {
		cout << "�ړ��Ɏ��s���܂���" << endl;
	}

	if (file_trans(thisFile_res.c_str(), toFile_res.c_str()) != 0) { //�ڍs�����@���@��O���� (reserve >> demo)
		remove(thisFile_res.c_str());
		for (int i = 0; i < 3; i++) {
			string source = thisFile_res + '.' + other_ext[i];
			string dest = toFile_res + '.' + other_ext[i];
			if (file_trans(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				cout << "�ړ��Ɏ��s���܂���" << endl;
				continue;
			}
		}
	}
	else {
		cout << "�ړ��Ɏ��s���܂���" << endl;
	}

	cout << "�������������܂���" << endl;
	getchar();

}

void demo_delete() { //demo�폜
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const string other_ext[3] = { "summary", "tags", "thumbnail" };
	vector <string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) { //vector��0�Ȃ�t�@�C���Ȃ��̗�O����
		cout << "demo�t�@�C�������݂��܂���" << endl;
		return;
	}
	cout << "�폜����demo�t�@�C����I�����Ă�������" << endl;
	cout << "######################################" << endl;
	for (int i = 0; i < demo_files.size(); i++) {
		cout << i << " " << demo_files[i].c_str() << endl;
	}

	int N;
	cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		cout << "�L���Ȑ�������͂��Ă�������" << endl;
		return;
	}

	string target = string(demo_folder) + '/' + demo_files[N];
	if (remove(target.c_str()) != 0) {
		cout << "�폜�ł��܂���ł���" << endl;
		return;
	}
	cout << "�������������܂���" << endl;
	return;
}

void demo_control() { //demo����̃��C������
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	struct stat st;
	if (stat(demo_folder, &st) != 0) {
		cout << "demo�t�H���_�����݂��܂���" << endl;
		return;
	}
	while (true) {
		cout << "�����I�����Ă��������B" << endl;
		cout << "1. demo�t�@�C���̑ޔ�" << endl;
		cout << "2. demo�t�@�C���̒ǉ�" << endl;
		cout << "3. demo�t�@�C���̓���ւ�" << endl;
		cout << "4. demo�t�@�C���̍폜" << endl;
		cout << "5. demo����̏I��" << endl;
		int N;
		cin >> N;

		switch (N) {
		case 1:
			demo_tores();
			break;
		case 2:
			demo_add();
			break;
		case 3:
			demo_exchange();
			break;
		case 4:
			demo_delete();
			break;
		case 5:
			return;
		default:
			break;
		}
	}

	return;
}