#include "EE_Course.h"
#include <iostream>

EE_Course::EE_Course(int course_num, string course_name, int num_hws, float weight_hws) :
	Course(course_num, course_name, num_hws, weight_hws), factor_(0) {};


EE_Course::~EE_Course()
{
}

int EE_Course::getFactor() const
{
	return (factor_);
}


bool EE_Course::setFactor(int factor)
{
	factor_ = factor;
	return true;
}


int EE_Course::getCourseGrade() const
{
	int grade = Course::getCourseGrade() + factor_;
	return ((grade < 100) ? grade : 100);
}


/*
EE_Course* EE_Course::cloneEE_Course()
{
	EE_Course* p_ee_course_c = new EE_Course(course_num_, course_name_, num_hws_, weight_hws_);
	return (p_ee_course_c);
}
*/


void EE_Course::print()
{
	cout << course_num_ << " " << course_name_ << ": " << getCourseGrade() << endl;
}
