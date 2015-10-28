#include "aux.h"

extern int numberOfFrames;
extern int height;
extern int width;
extern int frame_rate;
extern int frames_toAdd;




//muestra la data del video en formato texto
void show_video(vector<Mat> v){
	for(int i = 0; i < v.size(); i++){
		cout << "Frame " << i << endl;
		v[i].Show();
	}
	cout << endl;
} 


//metodo de vecino mas cercano
void closest_neighbour(vector<Mat> video, int frames_toAdd){
	
	for (int i = 0; i < video.size(); ++i)
	{
		/* code */
	}
}