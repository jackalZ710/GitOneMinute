// tintest_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <vector>
#include <iostream>
using namespace std;
#include "MyStudentManage.h"

int main() {
	int choice;
	string name;
	int score;
	int sum = 0;
	double average;
	student_manage_system sms;
	do {
		cout << "==学生管理系统==" << endl;
		cout << "1.添加学生" << endl;
		cout << "2.显示所有学生" << endl;
		cout << "3.显示平均分" << endl;
		cout << "0.退出" << endl;
		cout << "请输入你想进行的操作：" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "请输入学生的姓名:" << endl;
			cin >> name;
			cout << "请输入学生的分数:" << endl;
			cin >> score;
			sms.add_student(name, score);
			sms.count += 1;
			break;

		case 2:
			for (int i = 0; i < sms.count; i++) {
				cout << "学生姓名:" << sms.student_name[i] << " 学生成绩:" << sms.student_score[i] << endl;
			}
			break;

		case 3:
			for (int i = 0; i < sms.count; i++) {
				sum += sms.student_score[i];
			};
			 average = static_cast<double> (sum )/ sms.count;
			cout << "平均分：" << average << endl;
			break;

		default:
			cout << "无效的选择，请重新输入！" << endl;
		}
		
	} while (choice != 0);
}