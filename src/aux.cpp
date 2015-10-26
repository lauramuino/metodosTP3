#include "aux.h"

//levanta archivo de video en formato texto y lo carga en array de matrices
vector<Mat> load_video(string input_file){
	ifstream file(input_file.c_str());
	string data;
	int frames, height, width, frame_rate;
	unsigned char value;
	vector<Mat> video_frames;

	//cargo los datos 
	file >> data;
	frames = stoi(data);
	file >> data;
	height = stoi(data);
	file >> data;
	width = stoi(data);
	file >> data;
	frame_rate = stoi(data);

	//cargo las matrices

	for (int i = 0; i < frames; ++i)
	{
		Mat frame = Mat(height, width);
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


//muestra la data del video en formato texto
void show_video(vector<Mat> v){
	for(int i = 0; i < v.size(); i++){
		cout << "Frame " << i << endl;
		v[i].Show();
	}
	cout << endl;
} 