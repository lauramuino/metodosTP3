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
params = "<method>                  (int) ===> 0 = copiar vecinos, 1 = lineal, 2 = splines \
<frames_to_add>           (int) \
<check_vs_original>       'true' 'false'  ===> saca frames del original y compara contra los interpolados \
<interval_method>         'block' 'ecm'   ===> divide el video por bloque o por un umbral diferenci de ECM entre 2 frames\
<block_size_or_threshold> (int) (float) ===> block_size - umbral para ecm"


if(len(sys.argv) < 6):
	print "Use:"
	print "runner.py <original_video.avi/mp4> <generated_video.avi/mp4> <method> <frames_to_add> <check_vs_original> <interval_method> <block_size_or_threshold>"
	print  params
	quit()


videoInFilename = sys.argv[1] # video original en .avi/.mp4
videoOutFilename = sys.argv[2] # video interpolado en .avi/.mp4
method = sys.argv[3]
framesToAdd = sys.argv[4]
check_vs_original = sys.argv[5]
interval_method = sys.argv[6]
block_size_or_threshold = sys.argv[7]

video_text_in = videoInFilename + "_IN_txt" # video original en txt
video_text_out = videoOutFilename + "_OUT_txt" # video procesado en txt

# si no tengo el video en txt ya, lo paso a txt. sino uso el q ya existe
if( not os.path.exists(video_text_in) ):
	os.system("python tools-python-tp3/videoToTextfile.py " + videoInFilename + " " + video_text_in )
# si method es 'all' corro para los tres metodos
if method=="all":
	for meth in xrange(0,3):
		video_text_out = videoOutFilename + "OUT_m_" + str(meth) + "_txt " 
		params = str(meth) + " " + framesToAdd + " " + check_vs_original + " " + interval_method + " " + block_size_or_threshold
		os.system("./tp " + video_text_in + " " + video_text_out + params )
		os.system("python tools-python-tp3/textfileToVideo.py "  +  video_text_out + " " + videoOutFilename +  str(meth) + ".avi" )
# sino corro con los params dados
else:
	p = method + " " + framesToAdd + " " + check_vs_original + " " + interval_method + " " + block_size_or_threshold
	os.system("./tp " + video_text_in +" "+ video_text_out + " " +  p )
	os.system("python tools-python-tp3/textfileToVideo.py " + video_text_out + " " +  videoOutFilename)