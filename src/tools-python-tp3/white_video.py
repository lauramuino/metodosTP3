import numpy as np
import sys



# Genera todo un video en blanco. con eso variamos la cantidad de frames

height = 272
width = 464
n_of_frames = 8 # <-- variar
white = '255'

for a in xrange(1,12):
	n_of_frames = a*8
	for x in xrange(0,n_of_frames):
		actualFrame = [[white for y in range(height)] for z in range(width)]
		file = open("white_" + str(n_of_frames)+'.txt',"w")
		file.write(str(n_of_frames) + '\n')
		file.write(str(height) + ' ' + str(width) + '\n') 
		file.write('24 \n')
		for pr in xrange(0,width):
			file.write(' '.join(actualFrame[pr]) + '\n')