#ifndef _SCALAR_H_
#define _SCALAR_H_

#include"Variable.h"

class Scalar : public Variable
{
public:
	Scalar(int val) { val_ = val; }; // c'tor
	Scalar(const Scalar& scalar) { val_ = scalar.val_; }; // copy c'tor
	virtual ~Scalar(){};
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
	int val_;
};

#endif // _SCALAR_H_
