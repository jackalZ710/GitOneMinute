// dolist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "to_do_manage.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#pragma execution_character_set("utf-8")
#include <fstream>
using namespace std;

void show_file(vector<string>& missions);
void add_mission(vector<string>& missions);
void check_mission(const vector<string>& missions);
void delet_mission(vector<string>& missions);
void save_file(const vector<string>& missions, const string file_name);
void print();
void load_file(vector<string>& missions, const string file_name);
to_do_manage manage;
int main()
{
	manage.run();
	return 0;
}

void print() {
	cout << "\n--- 主菜单 ---" << endl;
	cout << "1. 添加任务" << endl;
	cout << "2. 查看所有任务" << endl;
	cout << "3. 删除任务" << endl;
	cout << "4. 文件操作" << endl;
	cout << "5. 退出程序" << endl;
	cout << "请选择操作 (1-5):" << endl;
}
void show_file(vector<string>& missions) {
	const string file_name = "missions.txt";
	int fileChoice;
	do {
		cout << "\n--- 文件操作 ---" << endl;
		cout << "1. 保存任务到文件" << endl;
		cout << "2. 从文件加载任务" << endl;
		cout << "3. 查看文件内容" << endl;
		cout << "4. 返回主菜单" << endl;
		cout << "请选择操作 (1-4): ";
		cin >> fileChoice;
		switch (fileChoice)
		{
		case 1:
			//保存任务到文件
			save_file(missions, file_name);
			break;
		case 2:
			load_file(missions, file_name);
			break;
		case 3: {
			string missionss;
			ifstream file(file_name);
			while (getline(file, missionss)) {
				if (!missionss.empty()) {
					cout << missionss << endl;
				}
			}
		}

			  break;
		default:
			break;
		}
	} while (fileChoice != 4);

}
void add_mission(vector<string>& missions) {
	string mission;
	cout << "请输入要添加的任务内容:" << endl;
	cin >> mission;
	if (mission.empty()) {
		cout << "任务内容不能为空，请重新输入。" << endl;

	}
	else {
		missions.push_back(mission);
		cout << "任务已添加成功！" << endl;
	}
}
void check_mission(const vector<string>& missions) {
	if (missions.empty()) {
		cout << "无任务" << endl;

	}
	else {
		cout << "如下：" << endl;
		for (int i = 0; i < missions.size(); i++) {
			cout << i + 1 << ". " << missions[i] << endl;
		}
	}

}
void delet_mission(vector<string>& missions) {
	int a;
	check_mission(missions);
	if (missions.empty()) {
		cout << "无任务" << endl;

	}
	else {
		cout << "请输入要删除的任务编号：" << endl;
		cin >> a;
		missions.erase(missions.begin() + a - 1);


	}
}
void save_file(const vector<string>& missions, const string file_name) {
	ofstream utputFile(file_name);
	if (!utputFile.is_open()) {
		cout << "无法打开文件进行写入！" << endl;
		return;
	}
	for (int i = 0; i < missions.size(); i++) {
		utputFile << missions[i] << endl;
	}
	utputFile.close();
	cout << "成功保存 " << missions.size() << " 个任务到文件: " << file_name << std::endl;
}
void load_file(vector<string>& missions, const string file_name) {
	ifstream inputFile(file_name);

	if (!inputFile.is_open()) {
		std::cout << "文件 " << file_name << " 不存在或无法打开，将创建新文件。" << std::endl;
		return;
	}
	missions.clear();
	string line;
	int count = 0;
	while (getline(inputFile, line)) {
		if (!line.empty()) {
			missions.push_back(line);
			count++;
		}


	}
	inputFile.close(); // 关闭文件
	cout << "加载了 " << count << " 个任务从文件: " << file_name << std::endl;
}