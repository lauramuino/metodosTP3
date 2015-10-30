#include "aux.h"

extern int numberOfFrames;
extern int height;
extern int width;
extern int frame_rate;
extern int frames_toAdd;




//muestra la data del video en formato texto
void show_video(vector<Matrix> v){
	for(int i = 0; i < v.size(); i++){
		cout << "Frame " << i << endl;
		v[i].Show();
	}
	cout << endl;
} 


//metodo de vecino mas cercano
void genByCopy(vector<Matrix>& original_video, vector<Matrix>& new_frames, int frames_toAdd){
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


//metodo de interpolacion fragmentaria cubica (o splines) natural
//para mas informacion, leer el burden.pdf 150/151
void spline_method(vector<Matrix>& original_video, vector<Matrix>& new_frames, int frames_toAdd, int frame_rate, int numberOfFrames, int height, int width){

	//defino los h_i = x_(i+1) - x_(i)
	vector<double> h(numberOfFrames);
	//defino los alphas
	vector<double> alpha(numberOfFrames-1);
	vector<double> l(numberOfFrames);
	vector<double> mu(numberOfFrames);
	vector<double> z(numberOfFrames);

	for (int i = 0; i < height; ++i) //para cada posicion i,j del frame
	{
		for (int j = 0; j < width; ++j)
		{
			for (int frame = 0; frame < numberOfFrames-1; ++frame) //para cada frame
				h[i] = (double)(1.0/frame_rate); //consideramos los x como el tiempo

			for (int frame = 1; frame < numberOfFrames-1; ++i)
				alpha[frame] = (3.0/h[frame]) * (original_video[frame+1](i,j) - original_video[frame](i,j)) - (3.0/h[frame-1]) * (original_video[frame](i,j) - original_video[frame-1](i,j));
			
			l[0]=1;
			mu[0]=0;
			z[0]=0;

			for (int frame = 1; frame < numberOfFrames-1; ++frame)
			{
				l[frame]=2*(2.0/frame_rate) - h[frame-1]*mu[frame-1];
				mu[frame] = h[frame]/l[frame];	
			}

		}
	}
}