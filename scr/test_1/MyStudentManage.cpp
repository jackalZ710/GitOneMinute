#include <vector>
#include <iostream>
using namespace std;
#include "MyStudentManage.h"


void student_manage_system::add_student(string name, int score) {
	if (count < 10) {
		student_name[count] = name;
		student_score[count] = score;

	}
	}