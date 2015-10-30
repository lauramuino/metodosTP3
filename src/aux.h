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