#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"

using namespace std;

VarPtr Scalar::Copy() const
{
	return VarPtr(new Scalar(this->val_));
}


VarPtr Scalar::NumElems() const
{
	return VarPtr(new Scalar(1));
}


VarPtr Scalar::Size() const
{
	Matrix* pMat = new Matrix(1, 2, 0);
	(*pMat)[1] = 1;
	(*pMat)[2] = 1;
	return VarPtr(pMat);
}


VarPtr Scalar::Size(int dim) const
{
	return VarPtr(new Scalar(1));
}


VarPtr Scalar::Conv(VarPtr rhs) const
{
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Scalar(0));
	VarPtr pRet = VarPtr(new Scalar(*this));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1, (rhsCols / 2) + 1 };
	(*pRet)[1] *= (*rhs)[rhsCenter];
	return pRet;
}


VarPtr Scalar::Transpose() const
{
	return Copy();
}


int& Scalar::operator[](int idx)
{
	if (idx != 1)
		throw INDEX_OUT_OF_RANGE;

	return (val_);
}


const int& Scalar::operator[](int idx) const
{
	if (idx != 1)
		throw INDEX_OUT_OF_RANGE;

	return (val_);
}


int& Scalar::operator[](IdxVec v) 
{
	if ((v.size() != 2) || (v[0] != 1) || (v[1] != 1))
		throw INDEX_OUT_OF_RANGE;

	return (this->val_);
}

const int& Scalar::operator[](IdxVec v) const
{
	if ((v.size() != 2) || (v[0] != 1) || (v[1] != 1))
		throw INDEX_OUT_OF_RANGE;

	return (this->val_);
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Scalar::operator+(const Variable& var) const
{
	return (var + (*this));
}

VarPtr Scalar::operator+(const Scalar& scl) const
{
	Scalar* pScl = new Scalar(*this);
	pScl->val_ += scl.val_;
	return VarPtr(pScl);
}

VarPtr Scalar::operator+(const Matrix& mat) const
{
	return (mat + *this);
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Scalar::operator*(const Variable& var) const
{
	return (var * (*this));
}

VarPtr Scalar::operator*(const Scalar& scl) const
{
	Scalar* pScl = new Scalar(*this);
	pScl->val_ *= scl.val_;
	return VarPtr(pScl);
}

VarPtr Scalar::operator*(const Matrix& mat) const
{
	return (mat * (*this));
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Scalar::operator<(const Variable& var) const
{
	return (var > (*this));
}

VarPtr Scalar::operator<(const Scalar& scl) const
{
	Scalar* pScl = new Scalar(0);
	if (this->val_ < scl.val_)
		pScl->val_ = 1;
	return VarPtr(pScl);
}

VarPtr Scalar::operator<(const Matrix& mat) const
{
	return (mat > (*this));
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Scalar::operator>(const Variable& var) const
{
	return (var < (*this));
}

VarPtr Scalar::operator>(const Scalar& scl) const
{
	Scalar* pScl = new Scalar(0);
	if (this->val_ > scl.val_)
		pScl->val_ = 1;
	return VarPtr(pScl);
}

VarPtr Scalar::operator>(const Matrix& mat) const
{
	return (mat < (*this));
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Scalar::operator==(const Variable& var) const
{
	return (var == (*this));
}

VarPtr Scalar::operator==(const Scalar& scl) const
{
	Scalar* pScl = new Scalar(0);
	if (this->val_ == scl.val_)
		pScl->val_ = 1;
	return VarPtr(pScl);
}

VarPtr Scalar::operator==(const Matrix& mat) const
{
	return (mat == (*this));
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Scalar::operator && (const Variable& var) const
{
	return (var && (*this));
}

VarPtr Scalar::operator && (const Scalar& scl) const
{
	Scalar* pScl = new Scalar(0);
	if ((this->val_ > 0) && (scl.val_ > 0))
		pScl->val_ = 1;
	return VarPtr(pScl);
}

VarPtr Scalar::operator && (const Matrix& mat) const
{
	throw BAD_INPUT;
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Scalar::operator||(const Variable& var) const
{
	return (var || (*this));
}

VarPtr Scalar::operator||(const Scalar& scl) const
{
	Scalar* pScl = new Scalar(0);
	if ((this->val_ > 0) || (scl.val_ > 0))
		pScl->val_ = 1;
	return VarPtr(pScl);
}

VarPtr Scalar::operator||(const Matrix& mat) const
{
	throw BAD_INPUT;
}

/////////////////////////////////////////////////////////////////////////////

void Scalar::print(ostream& ro) const
{
	ro << this->val_;
}
