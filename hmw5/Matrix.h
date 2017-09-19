#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"Variable.h"
#include"Scalar.h"
#include<iostream>
#include <typeinfo>

class Matrix : public Variable
{
public:
	Matrix(int rows, int cols, int val); // c'tor
	Matrix(int startVal, int endVal); // c'tor
	Matrix(const Matrix& mat); // copy c'tor
	virtual ~Matrix(){ delete[] mat_;}; // d'tor
	virtual VarPtr Copy() const;
	virtual VarPtr NumElems() const;
	virtual VarPtr Size() const;
	virtual VarPtr Size(int dim) const;
	virtual VarPtr Conv(VarPtr pVar) const;
	virtual VarPtr Transpose() const;

	virtual int& operator[](int);
	virtual const int& operator[](int) const;
	virtual int& operator[](IdxVec);
	virtual const int& operator[](IdxVec) const;

	virtual VarPtr operator+(const Variable&) const;
	virtual VarPtr operator+(const Scalar&) const;
	virtual VarPtr operator+(const Matrix&) const;

	virtual VarPtr operator*(const Variable&) const;
	virtual VarPtr operator*(const Scalar&) const;
	virtual VarPtr operator*(const Matrix&) const;

	virtual VarPtr operator<(const Variable&) const;
	virtual VarPtr operator<(const Scalar&) const;
	virtual VarPtr operator<(const Matrix&) const;

	virtual VarPtr operator>(const Variable&) const;
	virtual VarPtr operator>(const Scalar&) const;
	virtual VarPtr operator>(const Matrix&) const;

	virtual VarPtr operator==(const Variable&) const;
	virtual VarPtr operator==(const Scalar&) const;
	virtual VarPtr operator==(const Matrix&) const;

	virtual VarPtr operator&&(const Variable&) const;
	virtual VarPtr operator&&(const Scalar&) const;
	virtual VarPtr operator&&(const Matrix&) const;

	virtual VarPtr operator||(const Variable&) const;
	virtual VarPtr operator||(const Scalar&) const;
	virtual VarPtr operator||(const Matrix&) const;

	virtual void print(ostream& r) const;

private:
	int rows_, cols_;
	int* mat_;
};




#endif // _MATRIX_H_
