#include <iostream>
#include <sys/stat.h>
#include <direct.h>
#include <vector>
#include <string>
#include "fileop.h"
#include "getfiles.h"
#include "demo_control.h"




void demo_tores() { //demoファイルの退避処理
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const std::string other_ext[3] = { "summary", "tags", "thumbnail" };
	struct stat st;
	if (stat(reserve_folder, &st) != 0) { //リザーブディレクトリがないなら作成
		_mkdir(reserve_folder);
	}
	std::vector<std::string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) { //vectorが0ならファイルなしの例外処理
		std::cout << "demoファイルが存在しません" << std::endl;
		std::cout << std::endl;
		return;
	}
	std::cout << "退避するdemoファイルを選択してください" << std::endl;
	std::cout << "######################################" << std::endl;
	for (int i = 0; i < demo_files.size(); i++) { //ファイル一覧の出力
		std::cout << i << " " << demo_files[i].c_str() << std::endl;
	}
	int N;
	std::cin >> N; //ファイル番号の入力処理

	if (N < 0 || N >= demo_files.size()) { //範囲外の番号の場合，例外処理
		std::cout << "有効な番号を入力してください。" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::string thisFile = std::string(demo_folder) + std::string("/") + demo_files[N];
	std::string toFile = std::string(reserve_folder) + std::string("/") + demo_files[N]; //移行元，先のアドレス

	

	if (file_rename(thisFile.c_str(), toFile.c_str()) != 0) { //移行処理　兼　例外処理
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			std::string source = thisFile + '.' + other_ext[i];
			std::string dest = toFile + '.' + other_ext[i];
			if (file_rename(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				std::cout << "移動に失敗しました" << std::endl;
				continue;
			}
		}
	}
	else {
		std::cout << "移動に失敗しました" << std::endl;
	}
	std::cout << "処理が完了しました" << std::endl;
	std::cout << std::endl;
	getchar();
	return;
}

void demo_add() { //reserveからdemoを戻す処理
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const std::string other_ext[3] = { "summary", "tags", "thumbnail" };
	struct stat st;
	if (stat(reserve_folder, &st) != 0) {
		std::cout << "リザーブフォルダが存在しません" << std::endl;
		std::cout << "追加するdemoはリザーブフォルダ(/demo_reserve)直下に置かれている必要があります。" << std::endl;
		std::cout << std::endl;
		return;
	}
	std::vector<std::string> res_demo_files = getDemoFiles(reserve_folder);
	if (res_demo_files.size() == 0) {
		std::cout << "リザーブフォルダにdemoが存在しません" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::vector<std::string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() >= 2) {
		std::cout << "すでにdemoファイルが2つ以上存在します。" << std::endl;
		std::cout << "これ以上追加してもredacted側が読み込みませんがよろしいですか？ Y/N" << std::endl;
		std::string user_in;
		std::cin >> user_in;
		if (user_in == "Y" || user_in == "y") {
			std::cout << "処理を続行します。" << std::endl;
		}
		else if (user_in == "N" || user_in == "n") {
			std::cout << "処理を中断します。" << std::endl;
			std::cout << std::endl;
			return;
		}
		else {
			std::cout << "もう一度初めからやり直してください。" << std::endl;
			std::cout << std::endl;
			return;
		}

	}

	std::cout << "追加するdemoを選択してください" << std::endl;
	std::cout << "##############################" << std::endl;
	for (int i = 0; i < res_demo_files.size(); i++) {
		std::cout << i << " " << res_demo_files[i].c_str() << std::endl;
	}

	int N;
	std::cin >> N;

	if (N < 0 || N >= res_demo_files.size()) {
		std::cout << "有効な番号を入力してください。" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::string toFile = std::string(demo_folder) + '/' + res_demo_files[N];
	std::string thisFile = std::string(reserve_folder) + '/' + res_demo_files[N];

	if (file_rename(thisFile.c_str(), toFile.c_str()) != 0) { //移行処理　兼　例外処理
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			std::string source = thisFile + '.' + other_ext[i];
			std::string dest = toFile + '.' + other_ext[i];
			if (file_rename(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				std::cout << "移動に失敗しました" << std::endl;
				continue;
			}
		}
	}
	else {
		std::cout << "移動に失敗しました" << std::endl;
	}
	std::cout << "処理が完了しました" << std::endl;
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
		std::cout << "リザーブフォルダが存在しません" << std::endl;
		std::cout << "入れ替えるするdemoはリザーブフォルダ(/demo_reserve)直下に置かれている必要があります。" << std::endl;
		std::cout << std::endl;
		return;
	}
	
	std::vector <std::string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) {
		std::cout << "demoフォルダにファイルが存在しません。" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::cout << "交換するファイルを選択してください。(demoフォルダ側)" << std::endl;
	std::cout << "####################################" << std::endl;
	for (int i = 0; i < demo_files.size(); i++) {
		std::cout << i << " " << demo_files[i].c_str() << std::endl;
	}

	int N;
	std::cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		std::cout << "有効な数字を入力して下さい。" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::vector <std::string> demo_files_res = getDemoFiles(reserve_folder);
	if (demo_files_res.size() == 0) {
		std::cout << "reserveフォルダにファイルが存在しません。" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::cout << "交換するファイルを選択してください。(reserve側)" << std::endl;
	std::cout << "####################################" << std::endl;
	for (int i = 0; i < demo_files_res.size(); i++) {
		std::cout << i << " " << demo_files_res[i].c_str() << std::endl;
	}

	int M;
	std::cin >> M;

	if (M < 0 || M >= demo_files_res.size()) {
		std::cout << "有効な数字を入力してください。" << std::endl;
		std::cout << std::endl;
		return;
	}


	std::string thisFile = std::string(demo_folder) + '/' + demo_files[N];
	std::string toFile = std::string(reserve_folder) + '/' + demo_files[N]; //移行元，先のアドレス

	std::string thisFile_res = std::string(reserve_folder) + '/' + demo_files_res[M];
	std::string toFile_res = std::string(demo_folder) + '/' + demo_files_res[M];

	std::cout << "以下の入れ替えを実行します Y/N" << std::endl;
	std::cout << thisFile.c_str() << "⇔" << thisFile_res.c_str() << std::endl;

	std::string user_in;
	std::cin >> user_in;
	if (user_in == "N" || user_in == "n"){
		std::cout << "中断しました" << std::endl;
		std::cout << std::endl;
		return;
	}
	else if(user_in == "Y" || user_in == "y"){

		if (file_trans(thisFile.c_str(), toFile.c_str()) != 0) { //移行処理　兼　例外処理 (demo >> reserve)
			remove(thisFile.c_str());
			for (int i = 0; i < 3; i++) {
				std::string source = thisFile + '.' + other_ext[i];
				std::string dest = toFile + '.' + other_ext[i];
				if (file_trans(source.c_str(), dest.c_str()) != 0) {
					remove(source.c_str());
				}
				else {
					std::cout << "移動に失敗しました" << std::endl;
					continue;
				}
			}
		}
		else {
			std::cout << "移動に失敗しました" << std::endl;
		}

		if (file_trans(thisFile_res.c_str(), toFile_res.c_str()) != 0) { //移行処理　兼　例外処理 (reserve >> demo)
			remove(thisFile_res.c_str());
			for (int i = 0; i < 3; i++) {
				std::string source = thisFile_res + '.' + other_ext[i];
				std::string dest = toFile_res + '.' + other_ext[i];
				if (file_trans(source.c_str(), dest.c_str()) != 0) {
					remove(source.c_str());
				}
				else {
					std::cout << "移動に失敗しました" << std::endl;
					continue;
				}
			}
		}
		else {
			std::cout << "移動に失敗しました" << std::endl;
		}
	}
	else {
		std::cout << "やり直してください" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::cout << "処理が完了しました" << std::endl;
	getchar();

}

void demo_delete() { //demo削除
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const std::string other_ext[3] = { "summary", "tags", "thumbnail" };
	std::vector <std::string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) { //vectorが0ならファイルなしの例外処理
		std::cout << "demoファイルが存在しません" << std::endl;
		std::cout << std::endl;
		return;
	}
	std::cout << "削除するdemoファイルを選択してください" << std::endl;
	std::cout << "######################################" << std::endl;
	for (int i = 0; i < demo_files.size(); i++) {
		std::cout << i << " " << demo_files[i].c_str() << std::endl;
	}

	int N;
	std::cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		std::cout << "有効な数字を入力してください" << std::endl;
		std::cout << std::endl;
		return;
	}

	std::string target = std::string(demo_folder) + '/' + demo_files[N];
	remove(target.c_str());
	for (int i = 0; i < 3; i++) {
		std::string target2 = target + '.' + other_ext[i];
		remove(target2.c_str());
	}
	
	std::cout << "処理が完了しました" << std::endl;
	std::cout << std::endl;
	return;
}

void demo_control() { //demo操作のメイン処理
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	struct stat st;
	if (stat(demo_folder, &st) != 0) {
		std::cout << "demoフォルダが存在しません" << std::endl;
		std::cout << std::endl;
		return;
	}
	while (true) {
		std::cout << "操作を選択してください。" << std::endl;
		std::cout << "1. demoファイルの退避" << std::endl;
		std::cout << "2. demoファイルの追加" << std::endl;
		std::cout << "3. demoファイルの入れ替え" << std::endl;
		std::cout << "4. demoファイルの削除" << std::endl;
		std::cout << "5. demo操作の終了" << std::endl;
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