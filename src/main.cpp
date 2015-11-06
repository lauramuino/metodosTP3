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

// input.avi, output.txt, method, frames to add, check_contra_original, interval_division_method, interval_div_param
if(argc < 6){
	cout << "uso:" << endl;
	cout << "./tp input.txt output.txt <method> <frames_to_add> <check_vs_original> <interval_method> <block_size_or_threshold>" << endl;
	cout << "<method>                  (int) ===> 0 = copiar vecinos, 1 = lineal, 2 = splines" << endl;
	cout << "<frames_to_add>           (int)" << endl;
	cout << "<check_vs_original>       'true' 'false'  ===> saca frames del original y compara contra los interpolados" << endl;
	cout << "<interval_method>         'block' 'ecm'   ===> divide el video por bloque o por un umbral diferenci de ECM entre 2 frames" << endl;
	cout << "<block_size_or_threshold> (int) (float) ===> block_size - umbral para ecm" << endl;
	return 0;
}
	string input_file = argv[1];
	string output_file = argv[2];
	int method = stoi(argv[3]);
	int frames_toAdd = stoi(argv[4]);
	string check_contra_original = argv[5];
	string generate_interval_method = argv[6];
	string block_size_or_treshhold = argv[7];
	

	vector<Matrix> original_video_frames; // frames del video original
	vector<Matrix> video_frames; // frames del video a procesar
	int original_number_of_frames;


	// cargamos el video original
	// si vamos a comparar los frames generados por ECM, tenemos que sacar frames del original
	if(check_contra_original == "true"){
		cout << "Check ECM" << endl;
		original_video_frames = load_video(input_file);
		original_number_of_frames = original_video_frames.size();
		video_frames = copy_without_some_frames(original_video_frames, frames_toAdd);
	}else{
		// si no procesamos el video original nada mas
		cout << "Not Check ECM" << endl;
		video_frames = load_video(input_file);
		original_number_of_frames = video_frames.size();
	}

	numberOfFrames = video_frames.size();
	cout << "Original number of frames: " << original_number_of_frames << endl;
	cout << "Number of frames to process: " << numberOfFrames << endl;

	// DIVIDIMOS EL VIDEO EN INTERVALOS

	// vector de indices de donde se divide el video a procesar. 
	// guardo en interval_divider_indexes los indices donde termina un chunk de video, dependiendo de que usemos
	// Si el bloque es de 4, seria <3,6,9...> porque un chunk va del frame 0 al 3, otro del 3 al 6, etc...
	vector<int> interval_divider_indexes;

	if(generate_interval_method == "block"){ //si el metodo es por bloques
		// Dividimos el video en bloques de igual tamaño (excepto el ultimo si no es multiplo de la cantidad de frames)
		int block_size;
		if(stoi(block_size_or_treshhold) < numberOfFrames){ // me fijo si el bloque es mas grande que el video en total
			block_size = stoi(block_size_or_treshhold); 
			cout << "Dividiendo en bloques de tamaño: " << block_size << endl;
		} else{
			block_size = numberOfFrames+1; // en este caso tomo el video entero en un solo bloque
			cout << "Dividiendo en un solo bloque" << endl;
		}
		generate_even_interval_indexes(interval_divider_indexes, block_size, numberOfFrames);

	}else{ 	// Sino dividimos el video de acuerdo a si encontramos una diferencia grande de ECM entre dos frames
		double threshold = stod(block_size_or_treshhold);
		generate_ecm_interval_indexes(video_frames, interval_divider_indexes, threshold);
	}

	vector<vector<Matrix> > video_by_intervals; // Aca guardamos un vector de los chunks del videos a procesar (se guardan por copia)
	vector<vector<Matrix> > generated_video_by_intervals; // Aca guardamos un vector de los frames interpolados para cada chunk de video

	// divido mi video en fragmentos y lo guardo en video_by_intervals
	divide_video_in_intervals(video_frames, video_by_intervals, interval_divider_indexes); 
	cout << "Video dividido en intervalos" << endl;

	//Para cada chunk de video, proceso ese pedazo
	for (int i = 0; i < video_by_intervals.size(); ++i){
		vector<Matrix> generated_video_frames; // frames generados (sin los originales)
		video_frames = video_by_intervals[i];
		//video_frames.size() = video_frames.size();

		// inicializamos el vector de los frames interpolados si el metodo es lineal o splines
		if(method != 0){
			// frame nulo para reservar espacio para los frames interpolados
			Matrix nullframe(height,width);
			for (int i = 0; i < (video_frames.size()-1)*frames_toAdd; i++){
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
					linear_interpolation(video_frames, generated_video_frames, frames_toAdd, frame_rate, video_frames.size(), height, width);
					break;
			case 2: 
					cout << "Metodo Interpolacion Splines" << endl;
					spline_method(video_frames, generated_video_frames, frames_toAdd, frame_rate, video_frames.size(), height, width);
					break;	
			default: 
					cout << "Metodo incorrecto (se ingreso " << method << ")" << endl;
					exit(1);
		}

		// me guardo el video de los frames interpolados. Solo tiene los frames generados de forma contigua, despues hay que mergearlos con el original
		generated_video_by_intervals.push_back(generated_video_frames);
	
	} //end for
	
	// Si queremos, chequeamos el ECM y el PSNR de los frames interpolados contra los originales
	if(check_contra_original == "true"){
		// mergeamos todos los frames interpolados en un solo vector de frames (sin los originales)
		vector<Matrix> generated_video_frames = merge_chunks(generated_video_by_intervals);
		vector<double> ecms = ecm_interpolated_vs_original(original_video_frames, generated_video_frames, frames_toAdd);
		vector<double> psnrs = psnr_interpolated_vs_original(original_video_frames, generated_video_frames, frames_toAdd);
		for (int i = 0; i < ecms.size(); ++i)
			cout << "New Frame " << i << " - ECM: " << ecms[i] << endl;
		for (int i = 0; i < ecms.size(); ++i)
			cout << "New Frame " << i << " - PSNR: " << psnrs[i] << endl;
	}

	save_video(output_file, numberOfFrames, height, width, frame_rate, frames_toAdd, interval_divider_indexes, video_by_intervals, generated_video_by_intervals);


	cout << "Saved to File" << endl;

	//save_video(output_file, numberOfFrames, height, width, frame_rate, frames_toAdd, video_frames, generated_video_frames);



	return 0;
}

