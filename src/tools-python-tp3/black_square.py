import numpy as np
import sys

def printCool(m, width, height):
	for x in xrange(0,width):
		for y in xrange(0,height):
			print m[width][height],
	print

width = 100
height = 100
white = '255'
black = '0'
jump = 10

print (height/jump)*(width/jump)
print height, width
print 16


whiteMatrix = [[white for x in range(height)] for x in range(width)]
actualFrame = whiteMatrix

for y in xrange(0,height,jump):
	for x in xrange(0,width,jump):
		for i in xrange(0,10):
			for j in xrange(0,10):
				actualFrame[x+i][y+j]=black
		#printCool( actualFrame, width, height )
		for pr in xrange(0,height):
			print ' '.join(actualFrame[pr])
		actualFrame = [[white for x in range(height)] for x in range(width)]



'''
whiteMatrix = [[]]
for i in range(0, height):
	for j in range(0,width):
		whiteMatrix[i][j] = white

print whiteMatrix
for n in range(desde,hasta, step):
	file = open('test_black_square','w')
	#file.write("# FromNodeId	ToNodeId \n")
		for i in range(0, height):
			for j in range(0,width):
'''
