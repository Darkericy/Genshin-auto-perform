#include"Key.h"
#include"File.h"
#include<fstream>
#include<iostream>
//F:\绿洲\曲谱\小星星.txt
int main() {
	using std::cout;
	using std::cin;
	cout << "程序启动，你可以在任何非演奏阶段输入#字符来终止程序" << std::endl;
	while (1) {
		std::string name;
		cout << "请输入文件路径：";
		std::getline(cin, name);
		if (name == "#") {
			break;
		}
		Flie music_score(name);
		//循环判断输入的文件是否有效。
		while (!music_score.is_open()) {
			cout << "文件无法打开，请重新输入：";
			std::getline(cin, name);
			if (name == "#") {
				break;
			}
			music_score.change_score(name);
		}
		if (!music_score.is_open()) {
			break;
		}
		try {
			music_score.get_nameAspeed();
		}
		catch (int& e) {
			break;
		}
		catch (std::string& e) {
			continue;
		}
		catch (std::exception& e) {
			cout << e.what();
			continue;
		}
		//查询窗口句柄
		while (!music_score.is_openGenshin()) {
			cout << "检测到原神未打开，请打开后输入任意字符继续";
			std::string flag;
			cin >> flag;
			if (flag[0] == '#') {
				break;
			}
		}
		if (!music_score.is_openGenshin()) {
			break;
		}
		cout << "前期准备完成，需要倍速吗？" << std::endl;
		music_score.change_speed();
		Perform p(music_score.get_speed());
		cout << "几秒后开始？ :";
		int n;
		cin >> n;
		cin.get();
		while (n < 0) {
			cout << "还请您不要输入比0要小的等待时间好吗？" << std::endl;
			cout << "重新输入：";
			cin >> n;
		}
		while (n) {
			if (n > 60) {
				cout << "你敢输我就敢数，等着吧" << std::endl;
			}
			cout << n-- << std::endl;
			Sleep(1000);
		}
		try {
			p.play(music_score);
		}
		catch (std::exception& e) {
			cout << e.what();
			continue;
		}
	}
	return 0;
}