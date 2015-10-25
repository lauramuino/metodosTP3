/***** A 2-D Matrix *****/
#ifndef MAT_H_
#define MAT_H_


#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;


class Mat {
	public:
	    Mat(size_t rows_, size_t cols_);
	    Mat(const Mat& anotherMat);
	    char& operator()(size_t i, size_t j);
	    char operator()(size_t i, size_t j) const;
	    size_t rows() const;
	    size_t cols() const;
		void Show();
		void ShowOctave();

		
	    //vector<double> operator*(const vector<double>& x);
	    //Mat* operator*(double scalar);
	    //Mat operator+(const Mat& anotherMat);
	    //Mat operator*(const Mat& anotherMat);
	    //Mat& operator=(const Mat& anotherMat);
	    //Mat clone() const;
		//void checkBandMat();

	private:

	    size_t rows_;
	    size_t cols_;
	    vector<char> data_;
	};
 




#endif
