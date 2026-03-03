#include <vector>
#include <iostream>
using namespace std;

class student_manage_system {
public:
	string student_name[10];
	int student_score[10];
	int count = 0;

	void add_student(string name, int score);

};