#ifndef CS_COURSE_H_
#define CS_COURSE_H_

#include "Course.h"

class CS_Course : public Course{
protected:
	bool isTakef_; // HWs Takef/Magen
	string courseBook_;

public:
	CS_Course(int course_num, string course_name, int num_hws, float weight_hws, bool isTakef, string courseBook);
	virtual ~CS_Course();
	bool isTakef() const;
	string getBook() const;
	bool setTakef(bool isTakef);
	bool setBook(const string& courseBook);
	int getCourseGrade() const;
	//CS_Course* cloneCS_Course();
	void print();
};

#endif
