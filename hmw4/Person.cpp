#include "Person.h"

Person::Person(string name, int id) : name_(name), id_(id) {};


Person::~Person()
{
};


int Person::getID() const
{
	return id_;
}


string Person::getName() const
{
	return (name_);
}
