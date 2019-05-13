project=test3DInformation

GXX=g++
CXXFLAGS=-c -g
CPPFLAGS=-I /home/firefly/Work/mylibs/opencv/include/
LDFLAGS=-L /home/firefly/Work/mylibs/opencv/lib/
LIBS=-lopencv_core -lopencv_highgui -lopencv_imgproc -lzbar
all:main clean_O	
main: main.o QRPosition.o
	g++ -g -o main main.o QRPosition.o $(LDFLAGS) $(LIBS)
%.o:%.cpp
	$(GXX) $(CXXFLAGS) $< -o $@  $(CPPFLAGS) $(LDFLAGS) $(LIBS)
	
.PHONY:clean_O
clean_O:
	@rm ./*.o
clean:
	@rm ./main
