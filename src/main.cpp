//#include "mat.h"
#include "aux.h"
//#include "video.h"

using namespace std;

//VARIABLES GLOBALES
int numberOfFrames;
int height;
int width;
int frame_rate;
int frames_toAdd;

int generate_interval_method = 0;
double threshold = 200;
int block_size = 8;

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

//cargamos los parametros
	string input_file = argv[1];
	string output_file = argv[2];
	int method = stoi(argv[3]);
	int frames_toAdd = stoi(argv[4]);
	bool error_check = false;
	vector<Matrix> original_video_frames; // frames del video original
	vector<Matrix> video_frames; // frames del video a procesar


	// cargamos el video original
	// si vamos a comparar por ECM, tenemos que sacar frames
	if(argc > 5){
		error_check = true;
		original_video_frames = load_video(input_file);
		video_frames = copy_without_some_frames(original_video_frames, frames_toAdd);
		// ajusto los parametros globales
		numberOfFrames = video_frames.size();
		cout << "Checking ECM" << endl;
		// esto del frame rate no va, xq es un int y cuando da menor a 1 se rompe. Da igual
		//frame_rate =  ((double) original_video_frames.size() / frame_rate ) / (double) video_frames.size(); // con esto hago que el video con menos frames dure lo mismo que el original, bajandole el frame_rate
	}else{
		// si no procesamos el video original nada mas
		cout << "Not Checking ECM" << endl;
		video_frames = load_video(input_file);
	}


	cout << "Frames to Add: " << frames_toAdd << endl;

	// vector de indices de donde se divide el video a procesar
	vector<int> interval_divider_indexes;

	// guardo en interval_divider_indexes los indices donde termina un chunk de video, dependiendo de que usemos
	if(generate_interval_method == 0){
		// Dividimos el video en bloques de igual tamaño (excepto el ultimo si no es multiplo de la cantidad de frames)
		generate_even_interval_indexes(interval_divider_indexes, block_size, numberOfFrames);
	}else{
		// Dividimos el video de acuerdo a si encontramos una diferencia grande de ECM entre dos frames
		generate_ecm_interval_indexes(video_frames, interval_divider_indexes, threshold);
	}


	vector<vector<Matrix> > video_by_intervals; // Aca guardamos un vector de los chunks del videos a procesar (se guardan por copia)
	vector<vector<Matrix> > generated_video_by_intervals; // Aca guardamos un vector de los frames interpolados para cada chunk de video

	// divido mi video en fragmentos y lo guardo en video_by_intervals
	divide_video_in_intervals(video_frames, video_by_intervals, interval_divider_indexes); 


	//Para cada chunk de video, proceso ese pedazo
	for (int i = 0; i < video_by_intervals.size(); ++i){
		vector<Matrix> generated_video_frames; // frames generados (sin los originales)
		
		video_frames = video_by_intervals[i];
		numberOfFrames = video_frames.size();
//cout << "Iteracion " << i << " numberOfFrames: " << numberOfFrames << endl;
		// inicializamos el vector de los frames interpolados si el metodo es lineal o splines
		if(method != 0){
			// frame nulo para reservar espacio para los frames interpolados
			Matrix nullframe(height,width);
			for (int i = 0; i < (numberOfFrames-1)*frames_toAdd; i++){
				generated_video_frames.push_back(nullframe);
			}
		}

		switch (method) {
			case 0:	
					cout << "Metodo por Copia" << endl;
					genByCopy(video_frames, generated_video_frames, frames_toAdd);
					break;
			case 1: 
					cout << "Metodo Interpolacion Lineal" << endl;
					linear_interpolation(video_frames, generated_video_frames, frames_toAdd, frame_rate, numberOfFrames, height, width);
					break;
			case 2: 
					cout << "Metodo Interpolacion Splines" << endl;
					spline_method(video_frames, generated_video_frames, frames_toAdd, frame_rate, numberOfFrames, height, width);
					break;
			default: 
					cout << "Metodo incorrecto (se ingreso " << method << ")" << endl;
					exit(1);
		}


		// me guardo el video de los frames interpolados. Solo tiene los frames generados de forma contigua, despues hay que mergearlos con el original
		generated_video_by_intervals.push_back(generated_video_frames);
//cout << "Gen frames: " << generated_video_frames.size() << endl;
		// Si queremos, chequeamos el ECM y el PSNR de los frames interpolados contra los originales
		if(error_check){
			vector<double> ecms = ecm_interpolated_vs_original(original_video_frames, generated_video_frames, frames_toAdd);
			vector<double> psnrs = psnr_interpolated_vs_original(original_video_frames, generated_video_frames, frames_toAdd);
			for (int i = 0; i < ecms.size(); ++i)
				cout << "New Frame " << i << " - ECM: " << ecms[i] << endl;
			for (int i = 0; i < ecms.size(); ++i)
				cout << "New Frame " << i << " - PSNR: " << psnrs[i] << endl;
		}

	} //end for


	cout << "Saving to File" << endl;
	save_video(output_file, numberOfFrames, height, width, frame_rate, frames_toAdd, interval_divider_indexes, video_by_intervals, generated_video_by_intervals);

	//save_video(output_file, numberOfFrames, height, width, frame_rate, frames_toAdd, video_frames, generated_video_frames);



	return 0;
}

