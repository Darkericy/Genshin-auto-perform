#pragma once
#include<fstream>
class Flie
{
public:
	Flie() = delete;
	~Flie() = default;
	Flie(std::string name) :read_name(name), speed(-1), name() {};
	Flie(const Flie&) = delete;
	Flie(Flie&&) = delete;
	Flie& operator=(const Flie&) = delete;
	Flie& operator=(Flie&&) = delete;

	//从文件中读取曲谱名和速度
	void get_nameAspeed();

	//查询文件是否正确打开
	bool is_open();

	//更换文件
	void change_score(std::string n);

	//返回速度
	int get_speed() {
		return speed;
	}

	//这是给演奏类提供的接口，来判断当前的文档有没有读到末尾
	bool read(std::string& score);

	//判断原神有没有打开
	bool is_openGenshin();

	//询问用户是否需要倍速播放
	void change_speed();
private:
	std::ifstream read_name;
	int speed;
	std::string name;
};