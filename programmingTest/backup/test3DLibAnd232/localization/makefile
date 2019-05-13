project = 3DInforLib

CC = g++

CXXFLAGS = -c -g -fPIC
src = ./src/
CPPFLAGS = -I ./ -I /home/firefly/Work/mylibs/opencv/include -I /home/firefly/Work/mylibs/zbar/include/
LDFLAGS = -L /home/firefly/Work/mylibs/opencv/lib -L /home/firefly/Work/mylibs/zbar/lib/
LIBS = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_calib3d -lzbar

all:lib3DInforLib clean

lib3DInforLib:QRPosition.o
	$(CC) -shared -fPIC $^ -o lib3DInforLib.so $(LDFLAGS) $(LIBS)
	rm -f /home/firefly/Work/programmingTest/test3DLibAnd232/GrabImage_ROI/lib3DInforLib.so
	cp ./lib3DInforLib.so /home/firefly/Work/programmingTest/test3DLibAnd232/GrabImage_ROI/lib3DInforLib.so
%.o:$(src)%.cpp
	$(CC) $(CXXFLAGS) $< -o $@ $(CPPFLAGS) $(LDFLAGS) $(LIBS)
	
.PHONY:clean

clean:
	rm -f ./*.o
