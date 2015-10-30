#ifndef VIDEOCV_H_
#define VIDEOCV_H_

// include

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "/usr/local/include/opencv2/core/core.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/video/video.hpp"

#include "mat.h"

using namespace cv;
using namespace std;

class Video {
	public:
	    Video(std::string archivo){

	    	video.open(archivo);

	    }

	    bool siguienteFrame(Matrix& frame) {

			Mat frame_cv, frame_cv_g;

			bool hay_siguiente = video.read(frame_cv);

			imshow("frame",frame_cv);

			if(hay_siguiente){
				cvtColor(frame_cv,frame_cv_g,CV_RGB2GRAY);

				imshow("frame g",frame_cv_g);

				for(int i = 0 ; i < frame_cv_g.rows ; i++){

					for(int j = 0 ; j < frame_cv_g.cols ; j++){
						double pixel = (double)frame_cv_g.at<unsigned char>(i,j);
						frame(j,i) = pixel;

					}
				}
			}

			waitKey(10);

			return hay_siguiente;
		}

		int getHeight(){
			return video.get(CV_CAP_PROP_FRAME_HEIGHT);
		}

		int getWidth(){
			return video.get(CV_CAP_PROP_FRAME_WIDTH);
		}

		int getFrames(){
			return video.get(CV_CAP_PROP_FRAME_COUNT);
		}

		int getFrameRate(){
			return video.get(CV_CAP_PROP_FPS);
		}

	private:
		VideoCapture video;
	};
 





#endif
