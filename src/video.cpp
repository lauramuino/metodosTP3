#include "video.h"

void showFrame(Matrix frame){

	


}


Video::Video(std::string archivo){

	video.open(archivo);

}

bool Video::siguienteFrame(Matrix& frame) {

	Mat frame_cv, frame_cv_g;

	bool hay_siguiente = video.read(frame_cv);

	//imshow("frame",frame_cv);

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

int Video::getHeight(){
	return video.get(CV_CAP_PROP_FRAME_HEIGHT);
}

int Video::getWidth(){
	return video.get(CV_CAP_PROP_FRAME_WIDTH);
}

int Video::getFrames(){
	return video.get(CV_CAP_PROP_FRAME_COUNT);
}

int Video::getFrameRate(){
	return video.get(CV_CAP_PROP_FPS);
}

