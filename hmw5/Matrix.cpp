#include "Matrix.h"
#include "Scalar.h"
#include "ScriptExceptions.h"


Matrix::Matrix(int rows, int cols, int val)
{
	if ((rows < 0) || (cols < 0))
		throw BAD_INPUT;

	rows_ = rows;
	cols_ = cols;

	mat_ = new int[rows_* cols_];
	for (int i = 0; i < rows_; ++i)
		for (int j = 0; j < cols_; ++j)
			mat_[i * cols_ + j] = val;
}


Matrix::Matrix(int startVal, int endVal)
{
	if ((startVal < 0) || (endVal < 0) || (startVal > endVal))
		throw BAD_INPUT;

	rows_ = 1;
	cols_ = endVal - startVal + 1;

	mat_ = new int[rows_ * cols_];
	for (int j = 0; j < cols_; ++j)
		mat_[j] = startVal + j;
}


Matrix::Matrix(const Matrix& mat)
{
	rows_ = mat.rows_;
	cols_ = mat.cols_;

	mat_ = new int[rows_* cols_];
	for (int i = 0; i < rows_; ++i)
		for (int j = 0; j < cols_; ++j)
			mat_[i * cols_ + j] = mat.mat_[i * cols_ + j];
}


VarPtr Matrix::Copy() const
{
	Matrix* pMat = new Matrix(this->rows_, this->cols_, 0);
	for (int i = 0; i < rows_; ++i)
		for (int j = 0; j < cols_; ++j)
			pMat->mat_[i * cols_ + j] = this->mat_[i * cols_ + j];
	return VarPtr(pMat);
}


VarPtr Matrix::NumElems() const
{
	return VarPtr(new Scalar(rows_ * cols_));
}


VarPtr Matrix::Size() const
{
	Matrix* pMat = new Matrix(1, 2, 0);
	(*pMat)[1] = rows_;
	(*pMat)[2] = cols_;
	return (VarPtr(pMat));
}


VarPtr Matrix::Size(int dim) const
{
	if ((dim > 2) || (dim < 1))
		throw BAD_INPUT;

	int dimSize;
	dim == 1 ? (dimSize = rows_) : (dimSize = cols_);
	return VarPtr(new Scalar(dimSize));
}


VarPtr Matrix::Conv(VarPtr rhs) const
{
	if ((*NumElems())[1] == 0)
		return VarPtr(new Matrix(*this));
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Matrix(rows_, cols_, 0));

	VarPtr pRet = VarPtr(new Matrix(rows_, cols_, 0));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1,(rhsCols / 2) + 1 };
	int maxRowShift = rhsRows - rhsCenter[0];
	int minRowShift = 1 - rhsCenter[0];
	int maxColShift = rhsCols - rhsCenter[1];
	int minColShift = 1 - rhsCenter[1];
	for (int resRow = 1; resRow <= rows_; ++resRow)
		for (int resCol = 1; resCol <= cols_; ++resCol)
		{
			IdxVec resIdx = { resRow,resCol };
			for (int rowShift = minRowShift; rowShift <= maxRowShift; ++rowShift)
				for (int colShift = minColShift; colShift <= maxColShift; ++colShift)
				{
					try
					{
						(*pRet)[resIdx] += ((*this)[resIdx + IdxVec{ -rowShift,-colShift }] * (*rhs)[rhsCenter + IdxVec{rowShift,colShift}]);
					}
					catch (...)
					{
						// convolution is zero padded (no action required)
					}
				}
		}
	return pRet;
}


VarPtr Matrix::Transpose() const
{
	Matrix* pMat = new Matrix(this->cols_, this->rows_, 0);
	for (int i = 1; i <= pMat->rows_; ++i)
	{
		for (int j = 1; j <= pMat->cols_; ++j)
		{
			IdxVec v = { i, j };
			(*pMat)[v] = mat_[(j - 1) * cols_ + i - 1]; // left: 1-based, right: 0-based
		}
	}
	return VarPtr(pMat);
}


int& Matrix::operator[](int idx) 
{
	if ((idx < 1) || (idx > rows_ * cols_))
		throw INDEX_OUT_OF_RANGE;

	int idx_0 = idx - 1; // 0-based indexing
	int idx_col = idx_0 / rows_;
	int idx_row = idx_0 % rows_;
	return (mat_[idx_row * cols_ + idx_col]);
}


const int& Matrix::operator[](int idx) const
{
	if ((idx < 1) || (idx > rows_ * cols_))
		throw INDEX_OUT_OF_RANGE;

	int idx_0 = idx - 1; // 0-based indexing
	int idx_col = idx_0 / rows_;
	int idx_row = idx_0 % rows_;
	return (mat_[idx_row * cols_ + idx_col]);
}


int& Matrix::operator[](IdxVec v)
{
	if ((v.size() != 2) || (v[0] < 1) || (v[0] > rows_) || (v[1] < 1) || (v[1] > cols_))
		throw INDEX_OUT_OF_RANGE;

	int i0 = v[0] - 1; // rows - 0-based indexing
	int j0 = v[1] - 1; // cols - 0-based indexing
	return (mat_[i0 * cols_ + j0]);
}


const int& Matrix::operator[](IdxVec v) const
{
	if ((v.size() != 2) || (v[0] < 1) || (v[0] > rows_) || (v[1] < 1) || (v[1] > cols_))
		throw INDEX_OUT_OF_RANGE;

	int i0 = v[0] - 1; // rows - 0-based indexing
	int j0 = v[1] - 1; // cols - 0-based indexing
	return (mat_[i0 * cols_ + j0]);
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Matrix::operator+(const Variable& var) const
{
	return (var + *this);
}

VarPtr Matrix::operator+(const Scalar& scl) const
{
	Matrix* pMat = new Matrix(*this);
	int numElem = rows_ * cols_;
	for (int i = 1; i <= numElem; ++i)
		(*pMat)[i] += scl[1];

	return VarPtr(pMat);
}

VarPtr Matrix::operator+(const Matrix& mat) const
{
	if ((this->cols_ != mat.cols_) || (this->rows_ != mat.rows_))
		throw BAD_MAT_DIMS("+");

	Matrix* pMat = new Matrix(*this);
	int numElem = rows_ * cols_;
	for (int i = 1; i <= numElem; ++i)
		(*pMat)[i] += mat[i];

	return VarPtr(pMat);
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Matrix::operator*(const Variable& var) const
{
	// Matrix multiplication is NOT commutative
	if (strcmp(typeid(var).name(), "6Matrix") == 0)
		return ((*this) * (dynamic_cast<const Matrix&> (var)));
	else 
		return ((*this) * (dynamic_cast<const Scalar&> (var)));
}

VarPtr Matrix::operator*(const Scalar& scl) const
{
	Matrix* pMat = new Matrix(*this);
	int numElem = rows_ * cols_;
	for (int i = 1; i <= numElem; ++i)
		(*pMat)[i] *= scl[1];

	return VarPtr(pMat);
}

VarPtr Matrix::operator*(const Matrix& mat) const
{
	if (this->cols_ != mat.rows_)
		throw BAD_MAT_PROD;

	// Mat_A * Mat_B = Mat_C
	// (MxN) * (NxK) = (MxK)
	int rowsRes = this->rows_;
	int colsRes = mat.cols_;
	int N = this->cols_; // intermediate dim

	Matrix* pMatRes = new Matrix(rowsRes, colsRes, 0);
	for (int resRow = 1; resRow <= rowsRes; ++resRow)
		for (int resCol = 1; resCol <= colsRes; ++resCol)
		{
			IdxVec resIdx = { resRow, resCol };
			for (int n = 1; n <= N; ++n)
			{	
				IdxVec idxA = { resRow, n };
				IdxVec idxB = { n, resCol };
				(*pMatRes)[resIdx] += (*this)[idxA] * mat[idxB];
			}
		}

	return VarPtr(pMatRes);
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Matrix::operator<(const Variable& var) const
{
	return (var > (*this));
}

VarPtr Matrix::operator<(const Scalar& scl) const
{
	Matrix* pMatRes = new Matrix(this->rows_, this->cols_, 0);
	int numElem = rows_ * cols_;
	for (int i = 1; i <= numElem; ++i)
		if ((*this)[i] < scl[1])
			(*pMatRes)[i] = 1;

	return VarPtr(pMatRes);
}

VarPtr Matrix::operator<(const Matrix& mat) const
{
	if ((this->cols_ != mat.cols_) || (this->rows_ != mat.rows_))
		throw BAD_MAT_DIMS(">/<");

	Matrix* pMatRes = new Matrix(this->rows_, this->cols_, 0);
	int numElem = rows_ * cols_;
	for (int i = 1; i <= numElem; ++i)
		if ((*this)[i] < mat[i])
			(*pMatRes)[i] = 1;

	return VarPtr(pMatRes);
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Matrix::operator>(const Variable& var) const
{
	return (var < (*this));
}

VarPtr Matrix::operator>(const Scalar& scl) const
{
	Matrix* pMatRes = new Matrix(this->rows_, this->cols_, 0);
	int numElem = rows_ * cols_;
	for (int i = 1; i <= numElem; ++i)
		if ((*this)[i] > scl[1])
			(*pMatRes)[i] = 1;

	return VarPtr(pMatRes);
}

VarPtr Matrix::operator>(const Matrix& mat) const
{
	if ((this->cols_ != mat.cols_) || (this->rows_ != mat.rows_))
		throw BAD_MAT_DIMS(">/<");

	Matrix* pMatRes = new Matrix(this->rows_, this->cols_, 0);
	int numElem = rows_ * cols_;
	for (int i = 1; i <= numElem; ++i)
		if ((*this)[i] > mat[i])
			(*pMatRes)[i] = 1;

	return VarPtr(pMatRes);
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Matrix::operator==(const Variable& var) const
{
	return (var == (*this));
}

VarPtr Matrix::operator==(const Scalar& scl) const
{
	Matrix* pMatRes = new Matrix(this->rows_, this->cols_, 0);
	int numElem = rows_ * cols_;
	for (int i = 1; i <= numElem; ++i)
		if ((*this)[i] == scl[1])
			(*pMatRes)[i] = 1;

	return VarPtr(pMatRes);
}

VarPtr Matrix::operator==(const Matrix& mat) const
{
	if ((this->cols_ != mat.cols_) || (this->rows_ != mat.rows_))
		throw BAD_MAT_DIMS("==");

	Matrix* pMatRes = new Matrix(this->rows_, this->cols_, 0);
	int numElem = rows_ * cols_;
	for (int i = 1; i <= numElem; ++i)
		if ((*this)[i] == mat[i])
			(*pMatRes)[i] = 1;

	return VarPtr(pMatRes);
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Matrix::operator&&(const Variable& var) const
{
	throw BAD_INPUT;
}

VarPtr Matrix::operator&&(const Scalar& scl) const
{
	throw BAD_INPUT;
}

VarPtr Matrix::operator&&(const Matrix& mat) const
{
	throw BAD_INPUT;
}

/////////////////////////////////////////////////////////////////////////////

VarPtr Matrix::operator||(const Variable& var) const
{
	throw BAD_INPUT;
}

VarPtr Matrix::operator||(const Scalar& scl) const
{
	throw BAD_INPUT;
}

VarPtr Matrix::operator||(const Matrix& mat) const
{
	throw BAD_INPUT;
}

/////////////////////////////////////////////////////////////////////////////

void Matrix::print(ostream& ro) const
{
	for (int r = 1; r <= rows_; ++r)
	{
		for (int c = 1; c <= cols_; ++c)
		{
			IdxVec resIdx = { r, c };
			ro << (*this)[resIdx];
			ro << "\t";
		}
		if (r < rows_)
			ro << endl; // skip to next line every row, except last row
	}		
}
