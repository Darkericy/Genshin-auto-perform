#include"Key.h"
#include"Flie.h"
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
		cin >> name;
		if (name == "#") {
			break;
		}
		Flie music_score(name);
		while (!music_score.is_open()) {
			cout << "文件无法打开，请重新输入：";
			cin >> name;
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
		Perform p(music_score.get_speed());
		cout << "前期准备完成，三秒后演奏开始" << std::endl;
		int n = 3;
		while (n) {
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