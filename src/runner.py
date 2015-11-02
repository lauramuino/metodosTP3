import numpy as np
import cv2
import sys
from subprocess import call
import os
#########################
# QUE HACE:
# Pasa el video original a txt, luego corre el ./tp y despues pasa el resultado a video
# COMO CORRER:
# python runner.py data/video.avi data/out_video.avi 
# EJEMPLO:
# python runner.py data/funnybaby.avi data/funnybaby_slow_.avi 0 1
#########################

if(len(sys.argv) < 2):
	print "Use:"
	print "runner.py <original_video.avi/mp4> <generated_video.avi/mp4> "
	quit()


videoInFilename = sys.argv[1]
videoOutFilename = sys.argv[2]
videoOuttxt = videoInFilename + "_.txt"
method = sys.argv[3]
framesToAdd = sys.argv[4]


#call(["python", "tools-python-tp3/videoToTextfile.py " + videoInFilename + " data/" + videoOuttxt ])
#call(["./tp", videoOuttxt +" "+ videoOutFilename + " data/" +  videoOutFilename ])
#call(["python", "tools-python-tp3/textfileToVideo.py " + videoOutFilename + " data/" +  videoOutFilename])

os.system("python tools-python-tp3/videoToTextfile.py " + videoInFilename + " " + videoOuttxt )
os.system("./tp " + videoOuttxt +" "+ videoOutFilename + " " +  method + " " + framesToAdd )
os.system("python tools-python-tp3/textfileToVideo.py " + videoOuttxt + " " +  videoOutFilename)