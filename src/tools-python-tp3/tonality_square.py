import numpy as np
import sys

# Genera un video de un cuadrado todo el mismo colo
# y frame a frame va a cambiando de color

width = 240
height = 240
jump = 1 # 1 a 127

print 255/jump
print height, width
print 24

for x in xrange(0,256, jump):
	actualColor = str(x)
	actualFrame = [[actualColor for y in range(height)] for z in range(width)]
	for pr in xrange(0,width):
		print(' '.join(actualFrame[pr]))
