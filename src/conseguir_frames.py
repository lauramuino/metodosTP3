import numpy as np
import cv2
import sys
import os


video_file = sys.argv[1]
output_folder = sys.argv[2]


cap = cv2.VideoCapture(video_file)
i=0
ret = True
while(ret):
	ret, frame = cap.read()
	cv2.imwrite(output_folder+str(i)+".jpg",frame)
	i=i+1

cap.release()