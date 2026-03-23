#include "to_do_manage.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// 构造函数实现
to_do_manage::to_do_manage() {
    // 可以在这里初始化一些东西
}

void to_do_manage::run() {
    cout << "===简易事务待办列表===" << endl;
    int choice;

    do {
        print();
        cin >> choice;

        // 处理输入错误
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请输入数字。" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            add_mission();
            break;
        case 2:
            check_mission();
            break;
        case 3:
            delet_mission();
            break;
        case 4:
            file_operation();
            break;
        case 5:
            cout << "退出程序，感谢使用！" << endl;
            break;
        default:
            cout << "无效选择，请重新输入。" << endl;
        }
    } while (choice != 5);
}

void to_do_manage::print() {
    cout << "\n--- 主菜单 ---" << endl;
    cout << "1. 添加任务" << endl;
    cout << "2. 查看所有任务" << endl;
    cout << "3. 删除任务" << endl;
    cout << "4. 文件操作" << endl;
    cout << "5. 退出程序" << endl;
    cout << "请选择操作 (1-5):" << endl;
}

void to_do_manage::add_mission() {
    string mission;
    cout << "请输入要添加的任务内容:" << endl;

    // 清空输入缓冲区
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, mission);  // 使用getline以支持空格

    if (mission.empty()) {
        cout << "任务内容不能为空，请重新输入。" << endl;
    }
    else {
        missions.push_back(mission);
        cout << "任务已添加成功！" << endl;
    }
}

void to_do_manage::check_mission() const {
    if (missions.empty()) {
        cout << "暂无任务" << endl;
    }
    else {
        cout << "任务列表如下：" << endl;
        for (size_t i = 0; i < missions.size(); i++) {
            cout << i + 1 << ". " << missions[i] << endl;
        }
    }
}

void to_do_manage::delet_mission() {
    check_mission();

    if (missions.empty()) {
        return;
    }

    int a;
    cout << "请输入要删除的任务编号：" << endl;
    cin >> a;

    // 验证输入的有效性
    if (cin.fail() || a < 1 || a > missions.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "无效的任务编号！" << endl;
        return;
    }

    missions.erase(missions.begin() + a - 1);
    cout << "任务已删除成功！" << endl;
}

void to_do_manage::file_operation() {
    cout << "\n--- 文件操作子菜单 ---" << endl;
    cout << "1. 保存任务到文件" << endl;
    cout << "2. 从文件加载任务" << endl;
    cout << "3. 返回主菜单" << endl;
    cout << "请选择操作: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        ofstream outFile("tasks.txt");
        if (outFile.is_open()) {
            for (const auto& task : missions) {
                outFile << task << endl;
            }
            outFile.close();
            cout << "任务已保存到 tasks.txt" << endl;
        }
        else {
            cout << "无法创建文件！" << endl;
        }
        break;
    }
    case 2: {
        ifstream inFile("tasks.txt");
        if (inFile.is_open()) {
            missions.clear();
            string task;
            while (getline(inFile, task)) {
                missions.push_back(task);
            }
            inFile.close();
            cout << "已从 tasks.txt 加载任务" << endl;
        }
        else {
            cout << "无法打开文件！" << endl;
        }
        break;
    }
    case 3:
        return;
    default:
        cout << "无效选择！" << endl;
    }
}