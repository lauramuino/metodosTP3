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
				//new_frames.[i+j] = original_video[i].clone();
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
/*
cout << "numberOfFrames " << numberOfFrames << endl;
cout << "height " << height << endl;
cout << "width " << width << endl;
cout << "frame_rate " << frame_rate << endl;
cout << "frames_toAdd " << frames_toAdd << endl;
*/
	//defino los h_i = x_(i+1) - x_(i)
	vector<double> h(numberOfFrames);
	vector<double> b(numberOfFrames);
	vector<double> c(numberOfFrames);
	vector<double> d(numberOfFrames);
	//defino los alphas
	vector<double> alpha(numberOfFrames);
	vector<double> l(numberOfFrames);
	vector<double> mu(numberOfFrames);
	vector<double> z(numberOfFrames);


	for (int i = 0; i < height; ++i) //para cada posicion i,j del frame
	{
		for (int j = 0; j < width; ++j)
		{
			for (int frame = 0; frame < numberOfFrames-1; ++frame){ //para cada frame
				h[frame] = (double)(1.0/ (double) frame_rate); //consideramos los x como el tiempo
			} 
			for (int frame = 1; frame < numberOfFrames-2; ++frame){
				alpha[frame] = (3.0/h[frame]) * (original_video[frame+1](i,j) - original_video[frame](i,j)) - (3.0/h[frame-1]) * (original_video[frame](i,j) - original_video[frame-1](i,j));
			}
			l[0]=1;
			mu[0]=0;
			z[0]=0;
			for (int frame = 1; frame < numberOfFrames-1; ++frame)
			{
				l[frame]  = 2*(2.0/frame_rate) - h[frame-1]*mu[frame-1];
				mu[frame] = h[frame]/l[frame];
				z[frame]  = (alpha[frame]-h[frame-1]*z[frame-1])/l[frame];
			}

			l[numberOfFrames-1]=1;
			mu[numberOfFrames-1]=0;
			z[numberOfFrames-1]=0;			
			for (int frame = numberOfFrames-2; frame >= 0; frame--)
			{
				c[frame] = z[frame] - mu[frame]*c[frame+1];
				b[frame] = ((original_video[frame+1](i,j) - original_video[frame](i,j))/h[frame]  ) - ( h[frame] * (c[frame+1] + 2*c[frame]) /3 ) ;
				d[frame] = (c[frame+1] - c[frame]) / (3*h[frame]);
				//cout << "Polinomio para frame " << frame << " pixel (" << i << ", " << j << "): " << "a: " << +original_video[frame](i,j) << " b: " << b[frame] << " c: " << c[frame] << " d: " << d[frame] << endl;
			}

			for (int frame = 0; frame < numberOfFrames; ++frame)
			{
				for (int add = 0; add < frames_toAdd; ++add)
				{
					new_frames[frame*frames_toAdd+add](i, j) = evaluate_pol(original_video[frame](i,j), b[frame], c[frame], d[frame], (add+1)*(h[frame]/(frames_toAdd+1)) ); 
				}
			}
		}
	}
}

unsigned char evaluate_pol(unsigned char a, double b, double c, double d, double diff_x_xj){
	double res = a + b*(diff_x_xj) + c*pow(diff_x_xj,2) + d*pow(diff_x_xj, 3);
	if(res>255){
		return 255;
	}else if(res < 0){
		return 0;
	}else{
		return (unsigned char) res;
	}
} 

void linear_interpolation(vector<Matrix>& original_video, vector<Matrix>& new_frames, int frames_toAdd, int frame_rate, int numberOfFrames, int height, int width)
{
	double lambda;
	unsigned char new_pixel;
	//para cada pixel
	for (int frame = 0; frame < numberOfFrames-1; ++frame)
	{
		for (int p_i = 0; p_i < height; p_i++) {
			for (int p_j = 0; p_j < width; p_j++) {
				for (int add = 0; add < frames_toAdd; ++add)
				{
					lambda = (double)(add+1)*(1.0/(double)(frames_toAdd+1));
					
					unsigned char pixel0 = original_video[frame](p_i, p_j);
					unsigned char pixel1 = original_video[frame+1](p_i, p_j);
					
					if(pixel0 > pixel1) {
						//caso decreciente
						double new_pixel_f = pixel0 - lambda*(double)(pixel0-pixel1); 

						new_pixel = (unsigned char)new_pixel_f;
						
					} else {
						//caso creciente
						double new_pixel_f = pixel0 + lambda*(double)(pixel1-pixel0);
						new_pixel = (unsigned char)new_pixel_f;
					}

					new_frames[frame*frames_toAdd+add](p_i, p_j) = new_pixel; 
				}

			}
		}
	}
}


/*
void convert_to_video_and_save(vector<Matrix>& generated_video_frames, string output_file, int frame_rate, int width, int height)
{
	VideoWriter output_video;
	Size size(width, height);
	//cout << "1" << endl;
	output_video.open(output_file, CV_FOURCC('M','J','P','G'), frame_rate, size, 0);
	//cout << "width: " << width << " height: " << height << endl;
	//cout << "2" << endl;
	for (Matrix& frame : generated_video_frames) {
		Mat opencv_frame = convert_to_opencv_frame(frame, size);
		//cout << "3" << endl;
		output_video.write(opencv_frame);
		//cout << "4" << endl;
	}
}



Mat convert_to_opencv_frame(Matrix& frame, Size size)
{
	Mat opencv_frame(size, CV_8U);
	//cout << "cols: " << opencv_frame.cols << " rows: " << opencv_frame.rows << endl;
	
	for (int i = 0; i < frame.rows(); i++) {
		for(int j = 0; j < frame.cols(); j++) {
			//double pixel = (double)frame_cv_g.at<unsigned char>(i,j);
			//cout << (double)frame(j, i) << " ";
			opencv_frame.at<unsigned char>(i, j) = frame(j, i);
		}
		cout << endl;
	}

	//imshow("asd", opencv_frame);
	//waitKey(0);
}
*/

vector<Matrix> load_video(string input_file){
	ifstream file(input_file.c_str());
	string data;
	//int frames, height, width, frame_rate;
	unsigned char value;
	vector<Matrix> video_frames;

	//cargo los datos 
	file >> data;
	numberOfFrames = stoi(data);
	file >> data;
	height = stoi(data);
	file >> data;
	width = stoi(data);
	file >> data;
	frame_rate = stoi(data);
/*
cout << "numberOfFrames " << numberOfFrames << endl;
cout << "height " << height << endl;
cout << "width " << width << endl;
cout << "frame_rate " << frame_rate << endl;
*/
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
	return video_frames;
}




void save_video(string output_file, int numberOfFrames, int height, int width, int frame_rate, int frames_toAdd, vector<Matrix>& original_video, vector<Matrix>& new_video)
{
	ofstream f(output_file);
/*
cout << "numberOfFrames " << numberOfFrames << endl;
cout << "height " << height << endl;
cout << "width " << width << endl;
cout << "frame_rate " << frame_rate << endl;
*/
	f << numberOfFrames + (numberOfFrames-1)*frames_toAdd << endl;
	f << height << "," << width << endl; //formato infesto
	f << frame_rate << endl;

	for (int frame = 0; frame < original_video.size(); ++frame){
		//escribo un frame original
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (j != width-1)
					f << (double)original_video[frame](i,j) << ", ";
				else
					f << (double)original_video[frame](i,j);	//si es la ultima linea
			}
		f << endl;
		}
		//escribo frames_toAdd frames (los interpolados)
		for (int add = 0; add < frames_toAdd && frame < original_video.size()-1; ++add)
		{
			//escribo un frame de los interpolados
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (j != width-1)
						f << (double)new_video[frame*frames_toAdd+add](i,j) << ", ";
					else
						f << (double)new_video[frame*frames_toAdd+add](i,j);	//si es la ultima linea
				}
			f << endl;
			}
		}
		
	}
}



double ECM(Matrix& frame1, Matrix& frame2)
{
	assert(frame1.cols() == frame2.cols() && frame1.rows() == frame2.rows());

	int m = frame1.rows();
	int n = frame1.cols();
	double acum = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			acum += pow(abs(frame1(i,j) - frame2(i,j)), 2); 
		}
	}

	acum *= 1.0/(double)(n*m);

	return acum;
}



double PSNR(Matrix& frame1, Matrix& frame2)
{
	return 10*log10((255*255) / ECM(frame1, frame2));
}
