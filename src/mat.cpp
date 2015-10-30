#include "mat.h"


Matrix::Matrix(size_t n, size_t m) : rows_(n), cols_(m), data_((n) * (m))
{
}



unsigned char& Matrix::operator()(size_t i, size_t j)
{
    return data_[i * cols_ + j];
}



unsigned char Matrix::operator()(size_t i, size_t j) const
{
    return data_[i * cols_ + j];
} 



Matrix::Matrix(const Mat& anotherMat)
{
	this->rows_ = anotherMat.rows_;
	this->cols_ = anotherMat.cols_;
	this->data_ = anotherMat.data_;
}

Matrix Matrix::clone() const
{
	Matrix res(rows_, cols_);
	const Matrix& thisMat = *this;

	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			res(i, j) = thisMat(i, j);
		}
	}

	return res;
}
// Ojo, ahora es de char la matriz
/* 
Matrix* Matrix::operator*(double scalar)
{
	Matrix& thisMat = *this;
	Matrix* res = new Matrix(thisMat.cols(), thisMat.rows());

	for (int i = 0; i < thisMat.rows(); i++) {
		for (int j = 0; j < thisMat.cols(); j++) {
			res->operator()(i, j) = thisMat(i, j) * scalar;
		}
	}

	return res;
}
*/
/*
vector<double> Matrix::operator*(const vector<double>& x)
{
	vector<double> res(x.size());
	Matrix& thisMat = *this;
	
	assert(x.size() == cols_&& "Error al multiplicar matriz y vector de diferentes dimensiones");

	for (int i = 0; i < rows_; i++) {
		double mult = 0;
		for(int j = 0; j < cols_; j++) {
			mult += thisMat(i,j) * x[j];
		}
		res[i] = mult;
	}

	return res;
}
*/

size_t Matrix::rows() const
{
	return rows_;
}



size_t Matrix::cols() const
{
	return cols_;
}



void Matrix::ShowOctave()
{
	Matrix& thisMat = *this;
	cout << "[";
	for (int j = 0; j < rows_; j++) {
		for (int k = 0; k < cols_; k++) {
			cout << +thisMat(j,k) << " "; // el + es un casteo automatico
		}
		cout << ";";
	}
	cout << "]";
}



void Matrix::Show()
{
	Matrix& thisMat = *this;
	for (int j = 0; j < rows_; j++) {
		for (int k = 0; k < cols_; k++) {
			cout << +thisMat(j,k) << " "; // el + es un casteo automatico
		}
		cout << endl;
	}

}
