project = QRPosition

CC = g++

CXXFLAGS = -c -O3 -fPIC
CPPFLAGS = -I ./ -I /home/firefly/Work/mylibs/opencv/include -I /home/firefly/Work/mylibs/zbar/include/
LDFLAGS = -L /home/firefly/Work/mylibs/opencv/lib -L /home/firefly/Work/mylibs/zbar/lib/

CPPFLAGSS = -I ./ -I /home/firefly/Work/mylibs/opencv/include 
LDFLAGSS = -L /home/firefly/Work/mylibs/opencv/lib

LIBS = -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab  -lzbar

all:libQRPosition clean

libQRPosition:QRPosition.so
	$(CC) -shared -fPIC $^ -o libQRPosition.so $(LDFLAGS) $(LIBS)
	rm -f /home/firefly/Work/programmingTest/localization/localizationAll/libQRPosition.so
	cp ./libQRPosition.so /home/firefly/Work/programmingTest/localization/localizationAll/libQRPosition.so
QRPosition.so:QRPosition.cpp
	$(CC) $(CXXFLAGS) $< -o $@ $(CPPFLAGS) $(LDFLAGS) $(LIBS)
	

	
.PHONY:clean

clean:
	rm -f ./*.ro
