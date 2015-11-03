import numpy as np
import cv2
import sys
from subprocess import call
import os
#########################
# QUE HACE:
# Pasa el video original a txt, luego corre el ./tp y despues pasa el resultado a video
# COMO CORRER:
# python runner.py data/video.avi data/out_video.avi method framesToAdd
# EJEMPLO:
# python runner.py data/funnybaby.avi data/funnybaby_slow_.avi 0 1
#########################

if(len(sys.argv) < 3):
	print "Use:"
	print "runner.py <original_video.avi/mp4> <generated_video.avi/mp4> method framesToAdd"
	quit()


videoInFilename = sys.argv[1] # video original en .avi/.mp4
videoOutFilename = sys.argv[2] # video interpolado en .avi/.mp4
method = sys.argv[3]
framesToAdd = sys.argv[4]
videotxt = videoInFilename + "_.txt" # video original en txt
videoProctxt = videoOutFilename + "_.txt" # video procesado en txt


# si no tengo el video en txt ya, lo paso a txt. sino uso el q ya existe
if( not os.path.exists(videotxt) ):
	os.system("python tools-python-tp3/videoToTextfile.py " + videoInFilename + " " + videotxt )
# si method es 'all' corro para los tres metodos
if method=="all":
	for meth in xrange(0,3):
		os.system("./tp " + videotxt + " "+ videoProctxt+"_m_" + str(meth) + "_ " +  str(meth) + " " + framesToAdd )
		os.system("python tools-python-tp3/textfileToVideo.py " + videoProctxt+"_m_" + str(meth) + "_ " +  videoOutFilename + "_m_" + str(meth) + ".avi")
# sino corro con los params dados
else:
	os.system("./tp " + videotxt +" "+ videoProctxt + " " +  method + " " + framesToAdd )
	os.system("python tools-python-tp3/textfileToVideo.py " + videoProctxt + " " +  videoOutFilename)