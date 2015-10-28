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

void genByCopy(vector<Mat> & original_video, vector<Mat> & new_frames, int frames_toAdd){
	for (int i = 0; i < original_video.size() ; ++i)
	{
		if(i>0 && i< original_video.size()-1 ){ // soy un frame del medio
			for (int j = 0; j < frames_toAdd; ++j)
				new_frames.push_back(original_video[i].clone());
		}else if(i==0){ // soy el primer frame
			for (int j = 0; j < frames_toAdd/2; ++j)
				new_frames.push_back(original_video[i].clone());
		}else if(i == original_video.size()-1){ //soy el ultimo frame
			for (int j = frames_toAdd/2; j < frames_toAdd; ++j) // agrego cantidad de frames faltantes
				new_frames.push_back(original_video[i].clone());
		}
	}
}