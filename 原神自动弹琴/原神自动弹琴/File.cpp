#include "File.h"
#include<iostream>
#include<Windows.h>
#include<string>
void Flie::get_nameAspeed() {
	std::string name;
	int speed;
	std::getline(read_name, name);
	read_name >> speed;
	if (speed <= 0) {
		std::cout << "我的乖乖，速度为" << speed << "我怎么弹？" << std::endl;
		std::cout << "我命令你速速把速度改正常一点，重头再来一次！";
		std::string e;
		throw e;
	}
	if (name.size() >= 200) {
		std::cout << "你什么毛病？曲谱名怎么会超过200个字符？你什么毛病？" << std::endl;
		std::cout << "重新来！";
		std::string e;
		throw e;
	}
	std::cout << "请确认：" << std::endl;
	std::cout << "曲谱名： " << name << std::endl;
	std::cout << "曲谱速度：" << speed << std::endl;
	std::cout << "是否正确？正确请输入Y，错误请输入N：";
	char flag;
	std::cin >> flag;
	if (flag == '#') {
		int e = 0;
		throw e;
	}
	while (flag != 'N' && flag != 'Y') {
		std::cout << "只输入Y或者N好嘛，你知道我要为了这种低级错误多写三行代码吗？" << std::endl;
		std::cout << "好好输入： ";
		std::cin >> flag;
		if (flag == '#') {
			int e = 0;
			throw e;
		}
	}
	if (flag == 'N') {
		std::runtime_error e("那就从头来喽~");
		throw e;
	}
	this->name = name;
	this->speed = speed;
}
bool Flie::is_open() {
	if (!read_name.is_open()) {
		return false;
	}
	return true;
}
void Flie::change_score(std::string n) {
	read_name.open(n);
}
bool Flie::read(std::string& score) {
	if (read_name >> score) {
		return true;
	}
	return false;
}
bool Flie::is_openGenshin() {
	if (!FindWindowA(nullptr, "原神")) {
		return false;
	}
	return true;
}
void Flie::change_speed() {
	char n;
	std::cin >> n;
	if (n == 'N' || n == 'n') {
		return;
	}
	else if (n == 'Y' || n == 'y') {
		std::cout << "那么你需要几倍速（理论上你可以输入任何数）?";
		double over;
		std::cin >> over;
		while (over < 0) {
			std::cout << "你不觉得负数也太搞了嘛？重来";
			std::cin >> over;
			speed *= over;
			std::cout << "设置完成，现在的速度为：" << speed;
		}
	}
}