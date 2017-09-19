#ifndef PERSON_H_
#define PERSON_H_

#include <string>

using namespace std;

class Person{
protected:
	string name_;
	int id_; // unique per person

public:
	Person(string name, int id);
	~Person();
	int getID() const;
	string getName() const;
};


#endif
