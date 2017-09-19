#ifndef EE_COURSE_H_
#define EE_COURSE_H_

#include "Course.h"

class EE_Course : public Course{
protected:
	int factor_;

public:
	EE_Course(int course_num, string course_name, int num_hws, float weight_hws);
	virtual ~EE_Course();
	int getFactor() const;
	bool setFactor(int factor);
	int getCourseGrade() const;
	//EE_Course* cloneEE_Course();
	void print();
};

#endif
