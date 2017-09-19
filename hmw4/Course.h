#ifndef COURSE_H_
#define COURSE_H_

#include <string>

using namespace std;

class Course{
protected:
	int course_num_;
	string course_name_;
	int num_hws_;
	float weight_hws_;
	int exam_grade_;
	int* grades_hws_;

public:
	Course(int course_num, string course_name, int num_hws, float weight_hws);
	virtual ~Course();
	int getNum() const;
	string getName() const;
	int getExamGrade() const;
	int getHwGrade(int hw_num) const;
	int getHwNum() const;
	float getHwWeigh() const;
	float getHwAverage() const;
	virtual int getCourseGrade() const;
	bool setExamGrade(int exam_grade);
	bool setHwGrade(int hw_num, int grade);
	virtual void print();
};


#endif


