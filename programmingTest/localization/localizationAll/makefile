all: Demo1 Demo2 Demo3 Demo4 Demo5

# Demo1 没有使用多线程读取串口   Zbar输出7个点  只抓取一次图
Demo1: main.cpp callHik.cpp
	g++ -g -std=c++11 -o Demo1 main.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar/include \
	-L/home/firefly/Work/mylibs/zbar/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition -lserial2lib
	
# Demo2 没有使用多线程读取串口   Zbar输出19个点	  只抓取一次图
Demo2: main.cpp callHik.cpp
	g++ -g -std=c++11 -o Demo2 main.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar_19/include \
	-L/home/firefly/Work/mylibs/zbar_19/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar_19/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition_18 -lserial2lib -lpthread	

# Demo3 使用了多线程读取串口   Zbar输出7个点	抓一次图解一次码， 总共抓取3次
Demo3: main_thread.cpp callHik.cpp
	g++ -g -std=c++11 -o Demo3 main_thread.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar/include \
	-L/home/firefly/Work/mylibs/zbar/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition -lserial2lib -lpthread	

# Demo4 使用了多线程读取串口   Zbar输出19个点	抓一次图解一次码， 总共抓取3次
Demo4: main_thread.cpp callHik.cpp
	g++ -g -std=c++11 -o main main_thread.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar_19/include \
	-L/home/firefly/Work/mylibs/zbar_19/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar_19/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition_18 -lserial2lib -lpthread		

# Demo5 使用了多线程读取串口   Zbar输出7个点	先抓取5张图，然后用1 3 5进行定位
Demo5: main_5.cpp callHik.cpp
	g++ -g -std=c++11 -o Demo5 main_5.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar/include \
	-L/home/firefly/Work/mylibs/zbar/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition -lserial2lib -lpthread

# Demo6 使用了多线程读取串口   Zbar输出19个点	先抓取5张图，然后用1 3 5进行定位
Demo6: main_5.cpp callHik.cpp
	g++ -g -std=c++11 -o Demo6 main_5.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar_19/include \
	-L/home/firefly/Work/mylibs/zbar_19/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar_19/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition_18 -lserial2lib -lpthread		

	
Demo7: main_decode_mulitThread.cpp callHik.cpp
	g++ -g -std=c++11 -o Demo7 main_decode_mulitThread.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar/include \
	-L/home/firefly/Work/mylibs/zbar/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition -lserial2lib -lpthread
	
	
# Demo8 使用了多线程读取串口   Zbar输出7个点	先抓取5张图，然后用1 3 5进行定位
Demo8: main_5.cpp callHik.cpp
	g++ -g -std=c++11 -o Demo8 main_5.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar/include \
	-L/home/firefly/Work/mylibs/zbar/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition -lserial2lib -lpthread
	

# Demo8 使用了多线程读取串口   Zbar输出7个点	先抓取5张图，然后用1 3 5进行定位
Demo9: main_5_copy.cpp callHik.cpp
	g++ -g -std=c++11 -o Demo9 main_5_copy.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar/include \
	-L/home/firefly/Work/mylibs/zbar/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition -lserial2lib -lpthread
	
	
	
# Demo8 使用了多线程读取串口   Zbar输出7个点	先抓取5张图，然后用1 3 5进行定位
main: main.cpp callHik.cpp
	g++ -g -std=c++11 -o main main.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar/include \
	-L/home/firefly/Work/mylibs/zbar/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition -lserial2lib -lpthread
	
main_5: main_5.cpp callHik.cpp
	g++ -O3 -std=c++11 -o main_5 main_5.cpp callHik.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar/include \
	-L/home/firefly/Work/mylibs/zbar/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition -lserial2lib -lpthread
	
	
	
main_5_class: main_5_class.cpp callHik.cpp
	g++ -O3 -std=c++11 -o main_5_class main_5_class.cpp callHik.cpp callLocalization.cpp -Wl,-rpath=/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib \
	-I./ -I/home/firefly/Work/mylibs/opencv/include \
	-I/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/include \
	-I/home/firefly/Work/mylibs/serial/include \
	-I/home/firefly/Work/mylibs/zbar/include \
	-L/home/firefly/Work/mylibs/zbar/lib \
	-L/home/firefly/Work/mylibs/serial/lib \
	-L/home/firefly/Work/mylibs/opencv/lib \
	-L/home/firefly/Work/hkVision/SampleSDK_Arm_NvidiaTX/lib -L ./ \
	-Wl,-rpath=/home/firefly/Work/mylibs/opencv/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/serial/lib \
	-Wl,-rpath=/home/firefly/Work/mylibs/zbar/lib \
	-Wl,-rpath=./ \
	-lMvCameraControl -lopencv_core -lopencv_highgui -lopencv_imgproc -lserial -lzbar -lQRPosition -lserial2lib -lpthread	
	
clean:
	rm main -rf
