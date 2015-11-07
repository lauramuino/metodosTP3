import numpy as np
import sys

# Genera todo un video en blanco. con eso variamos la cantidad de frames

width = 240
height = 240
n_of_frames = 100 # <-- variar
white = '255'

print n_of_frames
print height, width
print 24

for x in xrange(0,n_of_frames):
	actualFrame = [[white for y in range(height)] for z in range(width)]
	for pr in xrange(0,width):
		print(' '.join(actualFrame[pr]))
