#include "mat.h"

using namespace std;




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

int numberOfFrames;
int height;
int width;
int framerate;

int main(int argc, char* argv[])
{

	// Nota: trabaja con aritmetica de desborde. 
	Mat imgFrame = Mat(3, 3);
	imgFrame(0,0) = 126;
	imgFrame(0,1) = 127;
	imgFrame(0,2) = 128;
	imgFrame(1,0) = 129;
	imgFrame(1,1) = 130;
	imgFrame(1,2) = 131;
	imgFrame(1,2) += imgFrame(1,2) + 20;
	imgFrame.Show();
	imgFrame(0,2) += 128;
	imgFrame.Show();
	return 0;
}


