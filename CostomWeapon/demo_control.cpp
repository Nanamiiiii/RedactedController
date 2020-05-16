#include <iostream>
#include <sys/stat.h>
#include <direct.h>
#include <vector>
#include <string>
#include "fileop.h"
#include "getfiles.h"
#include "demo_control.h"


using namespace std;

void demo_tores() { //demoファイルの退避処理
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const string other_ext[3] = { "summary", "tags", "thumbnail" };
	struct stat st;
	if (stat(reserve_folder, &st) != 0) { //リザーブディレクトリがないなら作成
		_mkdir(reserve_folder);
	}
	vector<string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) { //vectorが0ならファイルなしの例外処理
		cout << "demoファイルが存在しません" << endl;
		return;
	}
	cout << "退避するdemoファイルを選択してください" << endl;
	cout << "######################################" << endl;
	for (int i = 0; i < demo_files.size(); i++) { //ファイル一覧の出力
		cout << i << " " << demo_files[i].c_str() << endl;
	}
	int N;
	cin >> N; //ファイル番号の入力処理

	if (N < 0 || N >= demo_files.size()) { //範囲外の番号の場合，例外処理
		cout << "有効な番号を入力してください。" << endl;
		return;
	}

	string thisFile = string(demo_folder) + string("/") + demo_files[N];
	string toFile = string(reserve_folder) + string("/") + demo_files[N]; //移行元，先のアドレス

	

	if (file_rename(thisFile.c_str(), toFile.c_str()) != 0) { //移行処理　兼　例外処理
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			string source = thisFile + '.' + other_ext[i];
			string dest = toFile + '.' + other_ext[i];
			if (file_rename(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				cout << "移動に失敗しました" << endl;
				continue;
			}
		}
	}
	else {
		cout << "移動に失敗しました" << endl;
	}
	cout << "処理が完了しました" << endl;

	getchar();
	return;
}

void demo_add() { //reserveからdemoを戻す処理
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const string other_ext[3] = { "summary", "tags", "thumbnail" };
	struct stat st;
	if (stat(reserve_folder, &st) != 0) {
		cout << "リザーブフォルダが存在しません" << endl;
		cout << "追加するdemoはリザーブフォルダ(/demo_reserve)直下に置かれている必要があります。" << endl;
		return;
	}
	vector<string> demo_files = getDemoFiles(reserve_folder);
	if (demo_files.size() == 0) {
		cout << "リザーブフォルダにdemoが存在しません" << endl;
		return;
	}
	else if (demo_files.size() > 2) {
		cout << "すでにdemoファイルが2つ以上存在します。" << endl;
		cout << "これ以上追加してもredacted側が読み込みませんがよろしいですか？ Y/N" << endl;
		string user_in;
		cin >> user_in;
		if (user_in == "Y" || user_in == "y") {
			cout << "処理を続行します。" << endl;
		}
		else if (user_in == "N" || user_in == "n") {
			cout << "処理を中断します。" << endl;
			return;
		}
		else {
			cout << "もう一度初めからやり直してください。" << endl;
			return;
		}

	}

	cout << "追加するdemoを選択してください" << endl;
	cout << "##############################" << endl;
	for (int i = 0; i < demo_files.size(); i++) {
		cout << i << " " << demo_files[i].c_str() << endl;
	}

	int N;
	cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		cout << "有効な番号を入力してください。" << endl;
		return;
	}

	string toFile = string(demo_folder) + '/' + demo_files[N];
	string thisFile = string(reserve_folder) + '/' + demo_files[N];

	if (file_rename(thisFile.c_str(), toFile.c_str()) != 0) { //移行処理　兼　例外処理
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			string source = thisFile + '.' + other_ext[i];
			string dest = toFile + '.' + other_ext[i];
			if (file_rename(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				cout << "移動に失敗しました" << endl;
				continue;
			}
		}
	}
	else {
		cout << "移動に失敗しました" << endl;
	}
	cout << "処理が完了しました" << endl;

	getchar();
	return;

}

void demo_exchange() {
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	const string other_ext[3] = { "summary", "tags", "thumbnail" };

	struct stat st;
	if (stat(reserve_folder, &st) != 0) {
		cout << "リザーブフォルダが存在しません" << endl;
		cout << "入れ替えるするdemoはリザーブフォルダ(/demo_reserve)直下に置かれている必要があります。" << endl;
		return;
	}
	
	vector <string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) {
		cout << "demoフォルダにファイルが存在しません。" << endl;
		return;
	}

	cout << "交換するファイルを選択してください。(demoフォルダ側)" << endl;
	cout << "####################################" << endl;
	for (int i = 0; i < demo_files.size(); i++) {
		cout << i << " " << demo_files[i].c_str() << endl;
	}

	int N;
	cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		cout << "有効な数字を入力して下さい。" << endl;
		return;
	}

	vector <string> demo_files_res = getDemoFiles(reserve_folder);
	if (demo_files_res.size() == 0) {
		cout << "reserveフォルダにファイルが存在しません。" << endl;
		return;
	}

	cout << "交換するファイルを選択してください。(reserve側)" << endl;
	cout << "####################################" << endl;
	for (int i = 0; i < demo_files_res.size(); i++) {
		cout << i << " " << demo_files_res[i].c_str() << endl;
	}

	int M;
	cin >> M;

	if (M < 0 || M >= demo_files_res.size()) {
		cout << "有効な数字を入力してください。" << endl;
		return;
	}


	string thisFile = string(demo_folder) + '/' + demo_files[N];
	string toFile = string(reserve_folder) + '/' + demo_files[N]; //移行元，先のアドレス

	string thisFile_res = string(reserve_folder) + '/' + demo_files_res[M];
	string toFile_res = string(demo_folder) + '/' + demo_files_res[M];

	cout << "以下の入れ替えを実行します Y/N" << endl;
	cout << thisFile.c_str() << "⇔" << thisFile_res.c_str() << endl;

	string user_in;
	if (user_in == "N" || user_in == "n"){
		cout << "中断しました" << endl;
		return;
	}
	else if(user_in != "Y" || user_in != "y"){
		cout << "やり直してください" << endl;
		return;
	}

	if (file_trans(thisFile.c_str(), toFile.c_str()) != 0) { //移行処理　兼　例外処理 (demo >> reserve)
		remove(thisFile.c_str());
		for (int i = 0; i < 3; i++) {
			string source = thisFile + '.' + other_ext[i];
			string dest = toFile + '.' + other_ext[i];
			if (file_trans(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				cout << "移動に失敗しました" << endl;
				continue;
			}
		}
	}
	else {
		cout << "移動に失敗しました" << endl;
	}

	if (file_trans(thisFile_res.c_str(), toFile_res.c_str()) != 0) { //移行処理　兼　例外処理 (reserve >> demo)
		remove(thisFile_res.c_str());
		for (int i = 0; i < 3; i++) {
			string source = thisFile_res + '.' + other_ext[i];
			string dest = toFile_res + '.' + other_ext[i];
			if (file_trans(source.c_str(), dest.c_str()) != 0) {
				remove(source.c_str());
			}
			else {
				cout << "移動に失敗しました" << endl;
				continue;
			}
		}
	}
	else {
		cout << "移動に失敗しました" << endl;
	}

	cout << "処理が完了しました" << endl;
	getchar();

}

void demo_delete() { //demo削除
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const string other_ext[3] = { "summary", "tags", "thumbnail" };
	vector <string> demo_files = getDemoFiles(demo_folder);
	if (demo_files.size() == 0) { //vectorが0ならファイルなしの例外処理
		cout << "demoファイルが存在しません" << endl;
		return;
	}
	cout << "削除するdemoファイルを選択してください" << endl;
	cout << "######################################" << endl;
	for (int i = 0; i < demo_files.size(); i++) {
		cout << i << " " << demo_files[i].c_str() << endl;
	}

	int N;
	cin >> N;

	if (N < 0 || N >= demo_files.size()) {
		cout << "有効な数字を入力してください" << endl;
		return;
	}

	string target = string(demo_folder) + '/' + demo_files[N];
	if (remove(target.c_str()) != 0) {
		cout << "削除できませんでした" << endl;
		return;
	}
	cout << "処理が完了しました" << endl;
	return;
}

void demo_control() { //demo操作のメイン処理
	const char* demo_folder = "Plugins/OpenNetStorage/Cloud/FILM_MP";
	const char* reserve_folder = "demo_reserve";
	struct stat st;
	if (stat(demo_folder, &st) != 0) {
		cout << "demoフォルダが存在しません" << endl;
		return;
	}
	while (true) {
		cout << "操作を選択してください。" << endl;
		cout << "1. demoファイルの退避" << endl;
		cout << "2. demoファイルの追加" << endl;
		cout << "3. demoファイルの入れ替え" << endl;
		cout << "4. demoファイルの削除" << endl;
		cout << "5. demo操作の終了" << endl;
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