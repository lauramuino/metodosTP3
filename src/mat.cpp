#include "mat.h"


Mat::Mat(size_t n, size_t m) : rows_(n), cols_(m), data_((n) * (m))
{
}



unsigned char& Mat::operator()(size_t i, size_t j)
{
    return data_[i * cols_ + j];
}



unsigned char Mat::operator()(size_t i, size_t j) const
{
    return data_[i * cols_ + j];
} 



Mat::Mat(const Mat& anotherMat)
{
	this->rows_ = anotherMat.rows_;
	this->cols_ = anotherMat.cols_;
	this->data_ = anotherMat.data_;
}

Mat Mat::clone() const
{
	Mat res(rows_, cols_);
	const Mat& thisMat = *this;

	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			res(i, j) = thisMat(i, j);
		}
	}

	return res;
}
// Ojo, ahora es de char la matriz
/* 
Mat* Mat::operator*(double scalar)
{
	Mat& thisMat = *this;
	Mat* res = new Mat(thisMat.cols(), thisMat.rows());

	for (int i = 0; i < thisMat.rows(); i++) {
		for (int j = 0; j < thisMat.cols(); j++) {
			res->operator()(i, j) = thisMat(i, j) * scalar;
		}
	}

	return res;
}
*/
/*
vector<double> Mat::operator*(const vector<double>& x)
{
	vector<double> res(x.size());
	Mat& thisMat = *this;
	
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

size_t Mat::rows() const
{
	return rows_;
}



size_t Mat::cols() const
{
	return cols_;
}



void Mat::ShowOctave()
{
	Mat& thisMat = *this;
	cout << "[";
	for (int j = 0; j < rows_; j++) {
		for (int k = 0; k < cols_; k++) {
			cout << +thisMat(j,k) << " "; // el + es un casteo automatico
		}
		cout << ";";
	}
	cout << "]";
}



void Mat::Show()
{
	Mat& thisMat = *this;
	for (int j = 0; j < rows_; j++) {
		for (int k = 0; k < cols_; k++) {
			cout << +thisMat(j,k) << " "; // el + es un casteo automatico
		}
		cout << endl;
	}

}
