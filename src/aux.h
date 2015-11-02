#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include "mat.h"
//#include "video.h"

using namespace std;


void show_video(vector<Matrix> v);
void genByCopy(vector<Matrix>& original_video, vector<Matrix>& new_frames, int frames_toAdd);
void spline_method(vector<Matrix>& original_video, vector<Matrix>& new_frames, int frames_toAdd, int frame_rate, int numberOfFrames, int height, int width);
void linear_interpolation(vector<Matrix>& original_video, vector<Matrix>& new_frames, int frames_toAdd, int frame_rate, int numberOfFrames, int height, int width);
void convert_to_video_and_save(vector<Matrix>& generated_video_frames, string output_file, int frame_rate, int width, int height);
vector<Matrix> load_video(string input_file);
void save_video(string output_file, int numberOfFrames, int height, int width, int frame_rate, int frames_toAdd, vector<Matrix>& original_video, vector<Matrix>& new_video);
unsigned char evaluate_pol(unsigned char a, double b, double c, double d, double diff_x_xj);
double ECM(Matrix& frame1, Matrix& frame2);
double PSNR(Matrix& frame1, Matrix& frame2);
//Mat convert_to_opencv_frame(Matrix& frame, Size size);