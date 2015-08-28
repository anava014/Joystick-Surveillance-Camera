#! /bin/bash
fswebcam -d /dev/video0 -r 640x480 -S 20 test.jpeg
rm test.jpeg
export LD_LIBRARY_PATH=/usr/local/lib
usr/local/bin/mjpg_streamer -i "input_uvc.so -f 25 -r 640x480" -o "output_http.so -w /usr/local/www"  &
