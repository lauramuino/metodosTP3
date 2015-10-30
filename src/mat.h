/***** A 2-D Matrix *****/
#ifndef MATRIX_H_
#define MATRIX_H_


#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

// Nota: unsigned char trabaja con aritmetica de desborde. 
class Matrix {
	public:
	    Matrix(size_t rows_, size_t cols_);
	    Matrix(const Matrix& anotherMat);
	    unsigned char& operator()(size_t i, size_t j);
	    unsigned char operator()(size_t i, size_t j) const;
	    size_t rows() const;
	    size_t cols() const;
		void Show();
		void ShowOctave();
	    Matrix clone() const;

	    //vector<double> operator*(const vector<double>& x);
	    //Matrix* operator*(double scalar);
	    //Matrix operator+(const Matrix& anotherMat);
	    //Matrix operator*(const Matrix& anotherMat);
	    //Matrix& operator=(const Matrix& anotherMat);

		//void checkBandMat();

	private:

	    size_t rows_;
	    size_t cols_;
	    vector<unsigned char> data_;
	};
 




#endif
