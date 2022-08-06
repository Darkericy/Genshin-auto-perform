#include "Key.h"
#include<fstream>
#include<iostream>
#include"File.h"
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
void Keyboard::three_connect(std::string group, int time) {
	group.pop_back();
	int now = time / 3;
	for (const auto& a : group) {
		push(a);
		Sleep(now);
	}
}
void Keyboard::arpeggio(std::string group) {
	group.pop_back();
	for (const auto& a : group) {
		push(a);
		Sleep(25);
	}
}
void Perform::play(Flie& music_score) {
	std::string temp;
	while (music_score.read(temp)) {
		int now_step = time;
		int pos = 0;
		while (pos < temp.size() && !isalpha(temp[pos])) {
			if (temp[pos] == '-') {
				now_step /= 2;
			}
			else if (temp[pos] == '+') {
				now_step *= 2;
			}
			else if (temp[pos] == '=') {
				now_step += (now_step / 2);
			}
			else if (temp[pos] == '"' || temp[pos] == '[') {
				break;
			}
			else {
				std::invalid_argument e("错误！请确认谱子正确性！");
				throw e;
			}
			++pos;
		}
		if (pos == temp.size()) {
			std::invalid_argument e("错误！请确认谱子正确性！");
			throw e;
		}
		for (int i = pos; i < temp.size(); ++i) {
			if (temp[i] == '"') {
				char tail = temp.back();
				if (tail != '"') {
					std::invalid_argument e("错误！请确认曲谱");
					throw e;
				}
				std::string other = temp.substr(i + 1);
				k.three_connect(other, now_step);
				now_step = 0;
				break;
			}
			else if (temp[i] == '[') {
				char tail = temp.back();
				if (tail != ']') {
					std::invalid_argument e("错误！请确认曲谱");
					throw e;
				}
				std::string other = temp.substr(i + 1);
				now_step -= 25 * other.size();
				now_step -= now_step > 20 ? 20 : now_step;
				k.arpeggio(other);
				break;
			}
			else {
				k.push(temp[i]);
			}
		}
		Sleep(now_step);
	}
}