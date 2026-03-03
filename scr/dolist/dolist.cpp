// dolist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void add_mission(vector<string>& missions);
void check_mission(const vector<string>& missions);
void delet_mission(vector<string>& missions);
void print();
int main()
{
	cout << "===简易事务待办列表===" << endl;
	int choice;
	vector<string> missions; // 存储任务列表
	do {
		print();
		cin >> choice;
		switch (choice) {
		case 1:
			 add_mission(missions);
			break;
		case 2:
			 check_mission(missions);
			break;
			// 查看任务
			break;
		case 3:
			 delet_mission(missions);
			// 删除任务
			break;
		case 4:
			cout << "退出程序，感谢使用！" << endl;
			break;
		default:
			cout << "无效选择，请重新输入。" << endl;
		}
	} while (choice != 4);
}
void print() {
	cout << "\n--- 主菜单 ---" << endl;
	cout << "1. 添加任务" << endl;
	cout << "2. 查看所有任务" << endl;
	cout << "3. 删除任务" << endl;
	cout << "4. 退出程序" << endl;
	cout << "请选择操作 (1-4):" << endl;
	
}
void add_mission(vector<string>& missions) {
	string mission;
	cout << "请输入要添加的任务内容:" << endl;
	cin >> mission;
	if(mission.empty()){
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
		cin >>a;
		missions.erase(missions.begin() + a - 1);
		
		
	}
}