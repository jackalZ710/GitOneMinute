#pragma execution_character_set("utf-8")
#pragma once

#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class to_do_manage
{
public:
    to_do_manage();  // 构造函数声明
    void run();

private:
    vector<string> missions;  // 将missions作为成员变量

    void print();
    void add_mission();
    void check_mission() const;  // const表示不会修改成员变量
    void delet_mission();
    void file_operation();  // 添加文件操作功能
};