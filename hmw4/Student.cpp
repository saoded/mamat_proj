#include "Student.h"
#include <iostream>

Student::Student(string name, int id) : Person(name, id)
{
	for (int i = 0; i < MAX_COURSE_NUM;  i++)
	{
		ee_courses_[i] = NULL;
		cs_courses_[i] = NULL;
	}
	num_ee_courses_ = 0;
	num_cs_courses_ = 0;
}


Student::~Student()
{
	for (int i = 0; i < MAX_COURSE_NUM; i++)
	{
		if (NULL != ee_courses_[i])
			delete ee_courses_[i];
		if (NULL != cs_courses_[i])
			delete cs_courses_[i];
	}
}


int Student::getCourseCnt_EE() const
{
	int course_cnt = 0;
	for (int i = 0; i < MAX_COURSE_NUM; i++)
		if (NULL != ee_courses_[i])
			course_cnt++;
	return (course_cnt);
}


int Student::getCourseCnt_CS() const
{
	int course_cnt = 0;
	for (int i = 0; i < MAX_COURSE_NUM; i++)
		if (NULL != cs_courses_[i])
			course_cnt++;
	return (course_cnt);
}


int Student::getCourseCnt() const
{
	return (getCourseCnt_EE() + getCourseCnt_CS());
}


bool Student::addEE_Course(EE_Course* p_ee_course)
{
	ee_courses_[num_ee_courses_++] = p_ee_course;
	return true;
}


bool Student::addCS_Course(CS_Course* p_cs_course)
{
	cs_courses_[num_cs_courses_++] = p_cs_course;
	return true;
}


bool Student::remCourse(const int course_num)
{
	if (remEE_Course(course_num))
		return true;
	if (remCS_Course(course_num))
		return true;
	return false;
}


EE_Course* Student::getEE_Course(const int course_num)
{
	int i = getEE_CourseInd(course_num);
	if (-1 == i) 
		return NULL;
	return ee_courses_[i];
}


CS_Course* Student::getCS_Course(const int course_num)
{
	int i = getCS_CourseInd(course_num);
	if (-1 == i)
		return NULL;
	return cs_courses_[i];
}


int Student::getAvg()
{
	double sum_grades = 0;
	double num_courses = 0;
	for (int i = 0; i < MAX_COURSE_NUM; i++)
	{
		if (NULL != ee_courses_[i])
		{
			sum_grades += ee_courses_[i]->getCourseGrade();
			num_courses++;
		}
		if (NULL != cs_courses_[i])
		{
			sum_grades += cs_courses_[i]->getCourseGrade();
			num_courses++;
		}
	}
	if (0 == num_courses)
		return 0;
	return ((int)(sum_grades / num_courses + 0.5));
}


void Student::print()
{
	cout << "Student Name: " << name_ << endl;
	cout << "Student ID: " << id_ << endl;
	cout << "Average Grade: " << getAvg() << endl << endl;
	
	cout << "EE Courses:" << endl;
	for (int i = 0; i < MAX_COURSE_NUM; i++)
		if (NULL != ee_courses_[i])
			ee_courses_[i]->print();
	cout << endl;

	cout << "CS Courses:" << endl;
	for (int i = 0; i < MAX_COURSE_NUM; i++)
		if (NULL != cs_courses_[i])
			cs_courses_[i]->print();
	cout << endl;
}


bool Student::remEE_Course(const int course_num)
{
	int i = getEE_CourseInd(course_num);
	if (-1 == i)
		return false;
	ee_courses_[i]->~EE_Course();
	ee_courses_[i] = NULL;
	num_ee_courses_--;
	return true;
}


bool Student::remCS_Course(const int course_num)
{
	int i = getCS_CourseInd(course_num);
	if (-1 == i)
		return false;
	cs_courses_[i]->~CS_Course();
	cs_courses_[i] = NULL;
	num_cs_courses_--;
	return true;
}


int Student::getEE_CourseInd(const int course_num)
{
	for (int i = 0; i < MAX_COURSE_NUM; i++)
	{
		if (NULL == ee_courses_[i])
			continue;
		if (ee_courses_[i]->getNum() == course_num)
			return i;
	}
	return -1;
}


int Student::getCS_CourseInd(const int course_num)
{
	for (int i = 0; i < MAX_COURSE_NUM; i++)
	{
		if (NULL == cs_courses_[i])
			continue;
		if (cs_courses_[i]->getNum() == course_num)
			return i;
	}
	return -1;
}
