#include "Course.h"
#include <iostream>

using namespace std;

Course::Course(int course_num, string course_name, int num_hws, float weight_hws) : course_num_(course_num),
	course_name_(course_name), num_hws_(num_hws), weight_hws_(weight_hws) 
{
	grades_hws_ = new int[num_hws_];
	for (int i = 0; i < num_hws_; i++)
		grades_hws_[i] = 0;
	exam_grade_ = 0;
};


Course::~Course()
{
	delete[] grades_hws_;
}


int Course::getNum() const
{
	return course_num_;
}


string Course::getName() const
{
	return course_name_;
}


int Course::getExamGrade() const
{
	return exam_grade_;
}


int Course::getHwGrade(int hw_num) const
{
	if (hw_num < 0 || hw_num > num_hws_ - 1)
		return -1; // Illegal hw_num
	else
		return grades_hws_[hw_num];
}


int Course::getHwNum() const
{
	return (num_hws_);
}


float Course::getHwWeigh() const
{
	return (weight_hws_);
}


float Course::getHwAverage() const
{
	if (0 == num_hws_)
		return 0;

	float hws_avg = 0;
	for (int i = 0; i < num_hws_; i++)
		hws_avg += grades_hws_[i];
	hws_avg /= num_hws_;
	return (hws_avg);
}


int Course::getCourseGrade() const
{
	return ((int)((1 - weight_hws_) * exam_grade_ + weight_hws_ * getHwAverage() + 0.5));
}


bool Course::setExamGrade(int exam_grade)
{
	if (exam_grade < 0 || exam_grade > 100)
		return false;
	exam_grade_ = exam_grade;
	return true;
}


bool Course::setHwGrade(int hw_num, int grade)
{
	if (hw_num < 0 || hw_num > num_hws_ - 1 || grade < 0 || grade > 100)
		return false;
	grades_hws_[hw_num] = grade;
	return true;
}


void Course::print()
{
}
