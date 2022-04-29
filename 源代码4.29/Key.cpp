#include "Key.h"
#include<fstream>
#include<iostream>
#include"Flie.h"
class Flie;
void Keyboard::push(char key) {
	//非法数据
	if (key == 'P') {
		return;
	}
	if (name.find(key) == name.end()) {
		std::invalid_argument e("错误！请确认曲谱！");
		throw e;
	}
	//只有根据我的标准读谱才能正确弹奏
	keybd_event(static_cast<BYTE>(key), 0, 0, 0);
	keybd_event(static_cast<BYTE>(key), 0, KEYEVENTF_KEYUP, 0);
}
void Keyboard::strum(std::string group) {
	for (const auto& a : group) {
		push(a);
		Sleep(5);
	}
}
void Keyboard::arpeggio(std::string group) {
	for (const auto& a : group) {
		push(a);
		Sleep(25);
	}
}
void Perform::play(Flie& music_score) {
	std::string temp;
	while (music_score.read(temp)) {
		int now_step = time;
		while (!temp.empty()&&!isalpha(temp[0])) {
			if (temp[0] == '-') {
				now_step /= 2;
			}
			else if (temp[0] == '+') {
				now_step *= 2;
			}
			else if (temp[0] == '=') {
				now_step += (now_step / 2);
			}
			else if (temp[0] == '('||temp[0]=='[') {
				break;
			}
			else {
				std::invalid_argument e("错误！请确认谱子正确性！");
				throw e;
			}
			temp = temp.substr(1);
		}
		if (temp.empty()) {
			std::invalid_argument e("错误！请确认谱子正确性！");
			throw e;
		}
		for (auto i = temp.begin(); i != temp.end(); ++i) {
			if (*i == '(') {
				auto j = i + 1;
				while (j != temp.end() && *j != ')') {
					++j;
				}
				if (j == temp.end()||j==i+1) {
					std::invalid_argument e("错误！请确认曲谱");
					throw e;
				}
				std::string other(i+1, j);
				now_step -= 5 * other.size();
				now_step -= now_step > 20 ? 20 : now_step;
				k.strum(other);
				i = j;
			}
			else if (*i == '[') {
				auto j = i + 1;
				while (j != temp.end() && *j != ']') {
					++j;
				}
				if (j == temp.end() || j == i + 1) {
					std::invalid_argument e("错误！请确认曲谱");
					throw e;
				}
				std::string other(i + 1, j);
				now_step -= 25 * other.size();
				now_step -= now_step > 20 ? 20 : now_step;
				k.arpeggio(other);
				i = j;
			}
			else {
				k.push(*i);
			}
		}
		Sleep(now_step);
	}
}