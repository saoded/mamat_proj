#ifndef STUDENT_H_
#define STUDENT_H_

#include "Person.h"
#include "EE_Course.h"
#include "CS_Course.h"
#include "Proj.h"

class Student : public Person{
protected:
	EE_Course* ee_courses_[MAX_COURSE_NUM];
	int num_ee_courses_;
	CS_Course* cs_courses_[MAX_COURSE_NUM];
	int num_cs_courses_;

	// helper functions
	int getCourseCnt_EE() const;
	int getCourseCnt_CS() const;

public:
	Student(string name, int id);
	~Student();
	int getCourseCnt() const;
	bool addEE_Course(EE_Course* p_ee_course);
	bool addCS_Course(CS_Course* p_cs_course);
	bool remCourse(const int course_num);
	EE_Course* getEE_Course(const int course_num);
	CS_Course* getCS_Course(const int course_num);
	int getAvg();
	void print();

	bool remEE_Course(const int course_num);
	bool remCS_Course(const int course_num);
	int getEE_CourseInd(const int course_num); // returns course index in array, or (-1) if not found
	int getCS_CourseInd(const int course_num); // returns course index in array, or (-1) if not found
};

#endif