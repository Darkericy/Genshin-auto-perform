#pragma once
#include<fstream>
class Flie
{
public:
	Flie() = delete;
	~Flie() = default;
	Flie(std::string name) :read_name(name),speed(-1),name() {};
	Flie(const Flie&) = delete;
	Flie(Flie&&) = delete;
	Flie& operator=(const Flie&) = delete;
	Flie& operator=(Flie&&) = delete;
	void get_nameAspeed();
	bool is_open();
	void change_score(std::string n);
	int get_speed() {
		return speed;
	}
	bool read(std::string& score);
	bool is_openGenshin();
private:
	std::ifstream read_name;
	int speed;
	std::string name;
};

