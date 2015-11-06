#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include "mat.h"


double ECM(Matrix& frame1, Matrix& frame2)
{
	assert(frame1.cols() == frame2.cols() && frame1.rows() == frame2.rows());

	int m = frame1.rows();
	int n = frame1.cols();
	double acum = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			acum += pow(abs(frame1(i,j) - frame2(i,j)), 2); 
		}
	}

	acum *= 1.0/(double)(n*m);

	return acum;
}



double PSNR(Matrix& frame1, Matrix& frame2)
{
	return 10*log10((255*255) / ECM(frame1, frame2));
}


vector<Matrix> load_video(string input_file){
	ifstream file(input_file.c_str());
	string data;
	int frames, height, width, frame_rate, numberOfFrames;
	unsigned char value;
	vector<Matrix> video_frames;

	//cargo los datos 
	file >> data;
	numberOfFrames = stoi(data);
	file >> data;
	height = stoi(data);
	file >> data;
	width = stoi(data);
	file >> data;
	frame_rate = stoi(data);

	//cargo las matrices
	for (int i = 0; i < numberOfFrames; ++i)
	{
		Matrix frame = Matrix(height, width);
		for (int j = 0; j < height; ++j)
		{
			for (int k = 0; k < width; ++k)
			{
				file >> data;
				//averiguar si esto sirve para pasarlo a unsigned char
				value = (unsigned char)stoi(data);
				frame(j,k) = value;
			}
		}
		//la guardo en el vector
		video_frames.push_back(frame);
	}
	return video_frames;
}

int main(int argc, char* argv[]){
	string input_video1 = argv[1];
	string input_video2 = argv[2];

	vector<Matrix> v1 = load_video(input_video1);
	vector<Matrix> v2 = load_video(input_video2);

	int frames_to_compare;
	if (v1.size() < v2.size() )
		frames_to_compare = v1.size();
	else
		frames_to_compare = v2.size();

	cout << "FRAME  - ECM    ----    PSNR" << endl;
	for (int i = 0; i < frames_to_compare; ++i){
		cout << i << ")   " << ECM(v1[i], v2[i]) << "  " << PSNR(v1[i], v2[i]) << endl;
	}

}