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
void closest_neighbour(vector<Mat> video);
void genByCopy(vector<Mat> & original_video, vector<Mat> & new_frames, int frames_toAdd);
