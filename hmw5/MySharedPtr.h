#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_

#include <iostream>
#include "ScriptExceptions.h"

using namespace std;

template <class T>
class MySharedPtr
{
private:
	T* pT_;
	int* counter_;

public: 
	MySharedPtr()
	{
		pT_ = NULL;
		counter_ = new int(1);
	};

	MySharedPtr(T* pT) // c'tor
	{
		pT_ = pT;
		counter_ = new int(1);
	};

	~MySharedPtr()
	{
		--(*counter_);
		if (*counter_ == 0)
		{
			delete pT_;
			delete counter_;
		}
	}

	MySharedPtr(const MySharedPtr<T>& ptr) // copy c'tor
	{
		pT_ = ptr.pT_; // Point to same memory
		(*(ptr.counter_))++;
		counter_ = ptr.counter_;
	};

	T& operator*()
	{
		return (*pT_);
	};

	T* operator->()
	{
		return pT_;
	};

	T* get()
	{
		return pT_;
	};

	MySharedPtr<T>& operator=(const MySharedPtr<T>& ptr_r)
	{
		if (this != &ptr_r)
		{
			(--(*counter_)); // decrement counter value
			if (*counter_ == 0) // delete pointed object and counter
			{
				delete pT_;
				delete counter_;
			}

			pT_ = ptr_r.pT_;
			++(*(ptr_r.counter_));
			counter_ = ptr_r.counter_;
		}
		return (*this);
	}
};

template <class T>
ostream& operator<<(ostream& ro, MySharedPtr<T>& ptr)
{
	ptr->print(ro);
	return ro;
};

#endif // _MY_SHARED_PTR_H_
