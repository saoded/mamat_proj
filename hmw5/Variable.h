#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include<iostream>
#include<vector>
#include"MySharedPtr.h"

class Variable;
class Scalar;
class Matrix;

typedef MySharedPtr<Variable> VarPtr;
typedef vector<int> IdxVec;

IdxVec operator+(const IdxVec& lhs, const IdxVec& rhs);

class Variable
{
public:
	virtual ~Variable() {};

	virtual VarPtr Copy() const = 0;
	virtual VarPtr NumElems() const = 0;
	virtual VarPtr Size() const = 0;
	virtual VarPtr Size(int dim) const = 0;
	virtual VarPtr Conv(VarPtr pVar) const = 0;
	virtual VarPtr Transpose() const = 0;

	virtual int& operator[](int) = 0;
	virtual const int& operator[](int) const = 0;
	virtual int& operator[](IdxVec) = 0;
	virtual const int& operator[](IdxVec) const = 0;

	virtual VarPtr operator+(const Variable&) const = 0;
	virtual VarPtr operator+(const Scalar&) const = 0;
	virtual VarPtr operator+(const Matrix&) const = 0;

	virtual VarPtr operator*(const Variable&) const = 0;
	virtual VarPtr operator*(const Scalar&) const = 0;
	virtual VarPtr operator*(const Matrix&) const = 0;

	virtual VarPtr operator<(const Variable&) const = 0;
	virtual VarPtr operator<(const Scalar&) const = 0;
	virtual VarPtr operator<(const Matrix&) const = 0;

	virtual VarPtr operator>(const Variable&) const = 0;
	virtual VarPtr operator>(const Scalar&) const = 0;
	virtual VarPtr operator>(const Matrix&) const = 0;

	virtual VarPtr operator==(const Variable&) const = 0;
	virtual VarPtr operator==(const Scalar&) const = 0;
	virtual VarPtr operator==(const Matrix&) const = 0;

	virtual VarPtr operator&&(const Variable&) const = 0;
	virtual VarPtr operator&&(const Scalar&) const = 0;
	virtual VarPtr operator&&(const Matrix&) const = 0;

	virtual VarPtr operator||(const Variable&) const = 0;
	virtual VarPtr operator||(const Scalar&) const = 0;
	virtual VarPtr operator||(const Matrix&) const = 0;

	virtual void print(ostream& ro) const = 0;
};




#endif // _VARIABLE_H_
