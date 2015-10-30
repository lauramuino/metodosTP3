//#include "mat.h"
#include "aux.h"
#include "video.h"

using namespace std;

//VARIABLES GLOBALES
int numberOfFrames;
int height;
int width;
int frame_rate;
int frames_toAdd;


/*
En la primera liınea esta la cantidad de cuadros que tiene el video (c)

En la segunda linea esta el tamaño del cuadro donde el primer numero es la cantidad
de filas y el segundo es la cantidad de columnas (height width).

En la tercera linea esta el framerate del video (f).

A partir de alli siguen las imagenes del video una despues de la otra en forma de matriz.

Las primeras height lineas son las filas de la primera imagen donde cada una tiene
width numeros correspondientes a los valores de cada pıxel en esa fila. Luego siguen las
filas de la siguiente imagen y asi sucesivamente.
*/




int main(int argc, char* argv[])
{
/*
	string input_file = argv[1];
	string output_file = argv[2];
	int method = stoi(argv[3]);
	int frames_toAdd = stoi(argv[4]);

	Video video(input_file);

	numberOfFrames = video.getFrames();
	height = video.getHeight();
	width = video.getWidth();
	frame_rate = video.getFrameRate();

	vector<Matrix> video_frames;

	for (int i = 0; i < numberOfFrames; ++i){
		video.siguienteFrame(video_frames[i]);
	}

	/*
	video_frames.reserve(numberOfFrames);
	vector<Matrix> generated_video_frames;
	generated_video_frames.reserve((numberOfFrames-1) * frames_toAdd);

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
	*/




	// show_video(video_frames);
	// genByCopy(video_frames, generated_video_frames, frames_toAdd);

	// show_video(generated_video_frames);




	return 0;
}

