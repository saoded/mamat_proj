#include "CS_Course.h"
#include <iostream>

CS_Course::CS_Course(int course_num, string course_name, int num_hws, float weight_hws, bool isTakef,
	string courseBook) : Course(course_num, course_name, num_hws, weight_hws), isTakef_(isTakef), 
	courseBook_(courseBook) {};


CS_Course::~CS_Course()
{
}


bool CS_Course::isTakef() const
{
	return (isTakef_);
}


string CS_Course::getBook() const
{
	return (courseBook_);
}


bool CS_Course::setTakef(bool isTakef)
{
	isTakef_ = isTakef;
	return true;
}


bool CS_Course::setBook(const string& courseBook)
{
	if (courseBook.empty())
		return false;
	courseBook_ = courseBook;
	return true;
}


int CS_Course::getCourseGrade() const
{
	int courseGrade = Course::getCourseGrade();
	if (isTakef())
		return courseGrade;

	return (courseGrade > exam_grade_ ? courseGrade : exam_grade_);
}


/*
CS_Course* CS_Course::cloneCS_Course()
{
	CS_Course* p_cs_course_c = new CS_Course(course_num_, course_name_, num_hws_, weight_hws_, isTakef_, courseBook_);
	return (p_cs_course_c);
}
*/


void CS_Course::print()
{
	cout << course_num_ << " " << course_name_ << ": " << getCourseGrade() << endl;
}
