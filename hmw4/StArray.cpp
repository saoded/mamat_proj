#include "StArray.h"

StArray::StArray()
{
	numStudetns_ = 0;
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
		pStArr_[i] = NULL;
}


StArray::~StArray()
{
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
		if (NULL != pStArr_[i])
			delete pStArr_[i];
}


bool StArray::addStudent(const int st_id, const string st_name)
{
	Student* p_st = new Student(st_name, st_id);
	if (NULL == p_st)
		return false;

	// Add new student to first free slot
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
	{
		if (NULL == pStArr_[i])
		{
			pStArr_[i] = p_st;
			return true;
		}
	}
	delete p_st; // Student not assigned (all slots taken)
	return false;
}


bool StArray::addEE_Course(const int st_id, const int course_num, const string course_name, const int num_hws, const float weight_hws)
{
	EE_Course* p_ee_course = new EE_Course(course_num, course_name, num_hws, weight_hws);
	if (NULL == p_ee_course)
		return false;

	// Add new EE course to the right student
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
	{
		if (NULL == pStArr_[i])
			continue;
		if (pStArr_[i]->getID() == st_id)
		{
			pStArr_[i]->addEE_Course(p_ee_course);
			return true;
		}
	}
	delete p_ee_course;
	return false;
}


bool StArray::addCS_Course(const int st_id, const int course_num, const string course_name, const int num_hws, const float weight_hws, const bool isTakef, const string courseBook)
{
	CS_Course* p_cs_course = new CS_Course(course_num, course_name, num_hws, weight_hws, isTakef, courseBook);
	if (NULL == p_cs_course)
		return false;

	// Add new CS course to the right student
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
	{
		if (NULL == pStArr_[i])
			continue;
		if (pStArr_[i]->getID() == st_id)
		{
			pStArr_[i]->addCS_Course(p_cs_course);
			return true;
		}
	}
	delete p_cs_course;
	return false;
}


bool StArray::setHwGrade(const int st_id, const int course_num, const int hw_num, const int hw_grade)
{
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
	{
		if (NULL == pStArr_[i])
			continue;
		if (pStArr_[i]->getID() == st_id)
		{
			// EE course
			if (-1 != pStArr_[i]->getEE_CourseInd(course_num))
			{
				if (pStArr_[i]->getEE_Course(course_num)->setHwGrade(hw_num, hw_grade))
					return true;
				return false; // Student ID and course found, but HW not valid
			}

			// CS course
			if (-1 != pStArr_[i]->getCS_CourseInd(course_num))
			{
				if (pStArr_[i]->getCS_Course(course_num)->setHwGrade(hw_num, hw_grade))
					return true;
				return false; // Student ID and course found, but HW not valid
			}
			return false; // Student ID is found, but course does not exist
		}
	}
	return false; // Student ID not found
}


bool StArray::setExamGrade(const int st_id, const int course_num, const int exam_grade)
{
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
	{
		if (NULL == pStArr_[i])
			continue;
		if (pStArr_[i]->getID() == st_id)
		{
			// EE course
			if (-1 != pStArr_[i]->getEE_CourseInd(course_num))
			{
				if (pStArr_[i]->getEE_Course(course_num)->setExamGrade(exam_grade))
					return true;
				return false; // Student ID and course found, but exam grade not valid 
			}

			// CS course
			if (-1 != pStArr_[i]->getCS_CourseInd(course_num))
			{
				if (pStArr_[i]->getCS_Course(course_num)->setExamGrade(exam_grade))
					return true;
				return false; // Student ID and course found, but exam grade not valid 
			}
			return false; // Student ID is found, but course does not exist
		}
	}
	return false; // Student ID not found
}


bool StArray::setFactor(const int course_num, int factor)
{
	bool st_found = false;
	bool course_found = false;
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
	{
		if (NULL == pStArr_[i])
			continue;
		else
			st_found = true;

		if (-1 != pStArr_[i]->getEE_CourseInd(course_num))
		{
			pStArr_[i]->getEE_Course(course_num)->setFactor(factor);
			course_found = true;
		}
	}
	if (!st_found || !course_found)
		return false;
	return true;
}


bool StArray::printStudent(const int st_id) const
{
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
	{
		if (pStArr_[i]->getID() == st_id)
		{
			pStArr_[i]->print();
			return true;
		}
	}
	return false;
}


void StArray::printAll() const
{
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
		if (NULL != pStArr_[i])
			pStArr_[i]->print();
}


void StArray::resetStArray()
{
	for (int i = 0; i < MAX_STUDENT_NUM; i++)
		pStArr_[i]->~Student();
}
