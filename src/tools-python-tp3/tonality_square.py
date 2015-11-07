import numpy as np
import sys

def printCool(m, width, height):
	for x in xrange(0,width):
		for y in xrange(0,height):
			print m[width][height],
	print

width = 240
height = 240
jump = 24 # 1 a 127

if(jump == 1):
	print 255
else:
	print 255/jump

print height, width
print 24


for x in xrange(0,256, jump):
	actualColor = str(x)
	actualFrame = [[actualColor for y in range(height)] for z in range(width)]
	for pr in xrange(0,width):
		print(' '.join(actualFrame[pr]))
