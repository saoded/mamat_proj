#ifndef ST_ARRAY_
#define ST_ARRAY_

#include "Student.h"

class StArray{
protected:
	Student* pStArr_[MAX_STUDENT_NUM];
	int numStudetns_; // MAX_STUDENT_NUM

public:
	StArray();
	~StArray();
	bool addStudent(const int st_id, const string st_name);
	bool addEE_Course(const int st_id, const int course_num, const string course_name, const int num_hws, const float weight_hws);
	bool addCS_Course(const int st_id, const int course_num, const string course_name, const int num_hws, const float weight_hws, const bool isTakef, const string courseBook);
	bool setHwGrade(const int st_id, const int course_num, const int hw_num, const int hw_grade);
	bool setExamGrade(const int st_id, const int course_num, const int exam_grade);
	bool setFactor(const int course_num, int factor);
	bool printStudent(const int st_id) const;
	void printAll() const;
	void resetStArray();
};


#endif
