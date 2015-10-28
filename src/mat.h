/***** A 2-D Matrix *****/
#ifndef MAT_H_
#define MAT_H_


#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

// Nota: unsigned char trabaja con aritmetica de desborde. 
class Mat {
	public:
	    Mat(size_t rows_, size_t cols_);
	    Mat(const Mat& anotherMat);
	    unsigned char& operator()(size_t i, size_t j);
	    unsigned char operator()(size_t i, size_t j) const;
	    size_t rows() const;
	    size_t cols() const;
		void Show();
		void ShowOctave();
	    Mat clone() const;

	    //vector<double> operator*(const vector<double>& x);
	    //Mat* operator*(double scalar);
	    //Mat operator+(const Mat& anotherMat);
	    //Mat operator*(const Mat& anotherMat);
	    //Mat& operator=(const Mat& anotherMat);

		//void checkBandMat();

	private:

	    size_t rows_;
	    size_t cols_;
	    vector<unsigned char> data_;
	};
 




#endif
