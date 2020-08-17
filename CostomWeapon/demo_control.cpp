#include <iostream>
#include <sys/stat.h>
#include <direct.h>
#include <vector>
#include <string>
#include "fileop.h"
#include "getfiles.h"
#include "demo_control.h"




void demo_tores() { //demo�t�@�C���̑ޔ�����
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const std::string other_ext[3] = { "summary", "tags", "thumbnail" };
	struct stat st;
	if (stat(reserve_folder, &st) != 0) { //���U�[�u�f�B���N�g�����Ȃ��Ȃ�쐬
		_mkdir(reserve_folder);
	}
	std::vector<std::string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) { //vector��0�Ȃ�t�@�C���Ȃ��̗�O����
		std::cout << "demo�t�@�C�������݂��܂���" << std::endl;
		std::cout << std::endl;
		return;
	}
	std::cout << "�ޔ�����demo�t�@�C����I�����Ă�������" << std::endl;
	std::cout << "######################################" << std::endl;
	for (int i = 0; i < demo_files.size(); i++) { //�t�@�C���ꗗ�̏o��
		std::cout << i << " " << demo_files[i].c_str() << std::endl;
	}
	int N;
	std::cin >> N; //�t�@�C���ԍ��̓��͏���

	if (N < 0 || N >= demo_files.size()) { //�͈͊O�̔ԍ��̏ꍇ�C��O����
		std::cout << "�L���Ȕԍ�����͂��Ă��������B" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::string thisFile = std::string(demo_folder) + std::string("/") + demo_files[N];
	std::string toFile = std::string(reserve_folder) + std::string("/") + demo_files[N]; //�ڍs���C��̃A�h���X

	

	if (file_rename(thisFile.c_str(), toFile.c_str()) != 0) { //�ڍs�����@���@��O����
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			std::string source = thisFile + '.' + other_ext[i];
			std::string dest = toFile + '.' + other_ext[i];
			if (file_rename(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				std::cout << "�ړ��Ɏ��s���܂���" << std::endl;
				continue;
			}
		}
	}
	else {
		std::cout << "�ړ��Ɏ��s���܂���" << std::endl;
	}
	std::cout << "�������������܂���" << std::endl;
	std::cout << std::endl;
	getchar();
	return;
}

void demo_add() { //reserve����demo��߂�����
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const std::string other_ext[3] = { "summary", "tags", "thumbnail" };
	struct stat st;
	if (stat(reserve_folder, &st) != 0) {
		std::cout << "���U�[�u�t�H���_�����݂��܂���" << std::endl;
		std::cout << "�ǉ�����demo�̓��U�[�u�t�H���_(/demo_reserve)�����ɒu����Ă���K�v������܂��B" << std::endl;
		std::cout << std::endl;
		return;
	}
	std::vector<std::string> res_demo_files = getDemoFiles(reserve_folder);
	if (res_demo_files.size() == 0) {
		std::cout << "���U�[�u�t�H���_��demo�����݂��܂���" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::vector<std::string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() >= 2) {
		std::cout << "���ł�demo�t�@�C����2�ȏ㑶�݂��܂��B" << std::endl;
		std::cout << "����ȏ�ǉ����Ă�redacted�����ǂݍ��݂܂��񂪂�낵���ł����H Y/N" << std::endl;
		std::string user_in;
		std::cin >> user_in;
		if (user_in == "Y" || user_in == "y") {
			std::cout << "�����𑱍s���܂��B" << std::endl;
		}
		else if (user_in == "N" || user_in == "n") {
			std::cout << "�����𒆒f���܂��B" << std::endl;
			std::cout << std::endl;
			return;
		}
		else {
			std::cout << "������x���߂����蒼���Ă��������B" << std::endl;
			std::cout << std::endl;
			return;
		}

	}

	std::cout << "�ǉ�����demo��I�����Ă�������" << std::endl;
	std::cout << "##############################" << std::endl;
	for (int i = 0; i < res_demo_files.size(); i++) {
		std::cout << i << " " << res_demo_files[i].c_str() << std::endl;
	}

	int N;
	std::cin >> N;

	if (N < 0 || N >= res_demo_files.size()) {
		std::cout << "�L���Ȕԍ�����͂��Ă��������B" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::string toFile = std::string(demo_folder) + '/' + res_demo_files[N];
	std::string thisFile = std::string(reserve_folder) + '/' + res_demo_files[N];

	if (file_rename(thisFile.c_str(), toFile.c_str()) != 0) { //�ڍs�����@���@��O����
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			std::string source = thisFile + '.' + other_ext[i];
			std::string dest = toFile + '.' + other_ext[i];
			if (file_rename(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				std::cout << "�ړ��Ɏ��s���܂���" << std::endl;
				continue;
			}
		}
	}
	else {
		std::cout << "�ړ��Ɏ��s���܂���" << std::endl;
	}
	std::cout << "�������������܂���" << std::endl;
	std::cout << std::endl;
	getchar();
	return;

}

void demo_exchange() {
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const std::string other_ext[3] = { "summary", "tags", "thumbnail" };

	struct stat st;
	if (stat(reserve_folder, &st) != 0) {
		std::cout << "���U�[�u�t�H���_�����݂��܂���" << std::endl;
		std::cout << "����ւ��邷��demo�̓��U�[�u�t�H���_(/demo_reserve)�����ɒu����Ă���K�v������܂��B" << std::endl;
		std::cout << std::endl;
		return;
	}
	
	std::vector <std::string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) {
		std::cout << "demo�t�H���_�Ƀt�@�C�������݂��܂���B" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::cout << "��������t�@�C����I�����Ă��������B(demo�t�H���_��)" << std::endl;
	std::cout << "####################################" << std::endl;
	for (int i = 0; i < demo_files.size(); i++) {
		std::cout << i << " " << demo_files[i].c_str() << std::endl;
	}

	int N;
	std::cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		std::cout << "�L���Ȑ�������͂��ĉ������B" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::vector <std::string> demo_files_res = getDemoFiles(reserve_folder);
	if (demo_files_res.size() == 0) {
		std::cout << "reserve�t�H���_�Ƀt�@�C�������݂��܂���B" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::cout << "��������t�@�C����I�����Ă��������B(reserve��)" << std::endl;
	std::cout << "####################################" << std::endl;
	for (int i = 0; i < demo_files_res.size(); i++) {
		std::cout << i << " " << demo_files_res[i].c_str() << std::endl;
	}

	int M;
	std::cin >> M;

	if (M < 0 || M >= demo_files_res.size()) {
		std::cout << "�L���Ȑ�������͂��Ă��������B" << std::endl;
		std::cout << std::endl;
		return;
	}


	std::string thisFile = std::string(demo_folder) + '/' + demo_files[N];
	std::string toFile = std::string(reserve_folder) + '/' + demo_files[N]; //�ڍs���C��̃A�h���X

	std::string thisFile_res = std::string(reserve_folder) + '/' + demo_files_res[M];
	std::string toFile_res = std::string(demo_folder) + '/' + demo_files_res[M];

	std::cout << "�ȉ��̓���ւ������s���܂� Y/N" << std::endl;
	std::cout << thisFile.c_str() << "��" << thisFile_res.c_str() << std::endl;

	std::string user_in;
	std::cin >> user_in;
	if (user_in == "N" || user_in == "n"){
		std::cout << "���f���܂���" << std::endl;
		std::cout << std::endl;
		return;
	}
	else if(user_in == "Y" || user_in == "y"){

		if (file_trans(thisFile.c_str(), toFile.c_str()) != 0) { //�ڍs�����@���@��O���� (demo >> reserve)
			remove(thisFile.c_str());
			for (int i = 0; i < 3; i++) {
				std::string source = thisFile + '.' + other_ext[i];
				std::string dest = toFile + '.' + other_ext[i];
				if (file_trans(source.c_str(), dest.c_str()) != 0) {
					remove(source.c_str());
				}
				else {
					std::cout << "�ړ��Ɏ��s���܂���" << std::endl;
					continue;
				}
			}
		}
		else {
			std::cout << "�ړ��Ɏ��s���܂���" << std::endl;
		}

		if (file_trans(thisFile_res.c_str(), toFile_res.c_str()) != 0) { //�ڍs�����@���@��O���� (reserve >> demo)
			remove(thisFile_res.c_str());
			for (int i = 0; i < 3; i++) {
				std::string source = thisFile_res + '.' + other_ext[i];
				std::string dest = toFile_res + '.' + other_ext[i];
				if (file_trans(source.c_str(), dest.c_str()) != 0) {
					remove(source.c_str());
				}
				else {
					std::cout << "�ړ��Ɏ��s���܂���" << std::endl;
					continue;
				}
			}
		}
		else {
			std::cout << "�ړ��Ɏ��s���܂���" << std::endl;
		}
	}
	else {
		std::cout << "��蒼���Ă�������" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::cout << "�������������܂���" << std::endl;
	getchar();

}

void demo_delete() { //demo�폜
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const std::string other_ext[3] = { "summary", "tags", "thumbnail" };
	std::vector <std::string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) { //vector��0�Ȃ�t�@�C���Ȃ��̗�O����
		std::cout << "demo�t�@�C�������݂��܂���" << std::endl;
		std::cout << std::endl;
		return;
	}
	std::cout << "�폜����demo�t�@�C����I�����Ă�������" << std::endl;
	std::cout << "######################################" << std::endl;
	for (int i = 0; i < demo_files.size(); i++) {
		std::cout << i << " " << demo_files[i].c_str() << std::endl;
	}

	int N;
	std::cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		std::cout << "�L���Ȑ�������͂��Ă�������" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::string target = std::string(demo_folder) + '/' + demo_files[N];
	remove(target.c_str());
	for (int i = 0; i < 3; i++) {
		std::string target2 = target + '.' + other_ext[i];
		remove(target2.c_str());
	}
	
	std::cout << "�������������܂���" << std::endl;
	std::cout << std::endl;
	return;
}

void demo_control() { //demo����̃��C������
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	struct stat st;
	if (stat(demo_folder, &st) != 0) {
		std::cout << "demo�t�H���_�����݂��܂���" << std::endl;
		std::cout << std::endl;
		return;
	}
	while (true) {
		std::cout << "�����I�����Ă��������B" << std::endl;
		std::cout << "1. demo�t�@�C���̑ޔ�" << std::endl;
		std::cout << "2. demo�t�@�C���̒ǉ�" << std::endl;
		std::cout << "3. demo�t�@�C���̓���ւ�" << std::endl;
		std::cout << "4. demo�t�@�C���̍폜" << std::endl;
		std::cout << "5. demo����̏I��" << std::endl;
		std::cout << std::endl;
		int N;
		std::cin >> N;

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