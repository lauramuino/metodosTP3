#ifndef VIDEOCV_H_
#define VIDEOCV_H_

// include

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>


//#include "/usr/local/include/opencv2/opencv.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#include "mat.h"

using namespace cv;
using namespace std;

class Video {
	public:
	    Video(std::string archivo);

	    bool siguienteFrame(Matrix& frame);

		int getHeight();

		int getWidth();
		int getFrames();

		int getFrameRate();

	private:
		VideoCapture video;
	};
 





#endif
