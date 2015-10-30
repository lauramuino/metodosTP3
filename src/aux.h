#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include "mat.h"
using namespace std;


void show_video(vector<Mat> v);
void genByCopy(vector<Mat> & original_video, vector<Mat> & new_frames, int frames_toAdd);
void spline_method(vector<Mat> & original_video, vector<Mat> & new_frames, int frames_toAdd, int frame_rate, int numberOfFrames, int height, int width);