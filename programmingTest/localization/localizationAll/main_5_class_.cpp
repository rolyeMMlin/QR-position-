#include "callLocalization.h"
#include "callHik.h"
#include "QRPosition.h"
#include "serial2lib.h"

using namespace cv;
using namespace std;

string readResults;
bool isReadTty = true;
static void* getTTY(void* p_my_serial){
	while (isReadTty){
		redaTty(*((serial::Serial*) p_my_serial), readResults);
		//readResults = "C0";
	}
	printf("Read tty program is over!\n");
}


int main(){

	Mat img(1024, 1280, CV_8U, Scalar(0));

	// 串口初始化
	serial::Serial my_serial(string("/dev/ttyUSB0"), 115200, serial::Timeout::simpleTimeout(10));
	my_serial.flush();
	if (my_serial.isOpen())
		cout << "Serial open success!" << endl;
	else
	{
		cout << "Serial open failure!" << endl;
		return 0;
	}
	pthread_t nThreadID;
	serial::Serial* p_my_serial = &my_serial;
	int nReta = pthread_create(&nThreadID, NULL, getTTY, p_my_serial);
	sleep(1);


	// 相机初始化
	MV_CC_DEVICE_INFO_LIST stDeviceList;
	while (1){
		int listCode = listCamera(stDeviceList);
		if (1 <= stDeviceList.nDeviceNum && 1 == listCode){
			printf("%d cameras have been detected!\n", stDeviceList.nDeviceNum);
			break;
		}
		printf("%d cameras have been detected!\n", stDeviceList.nDeviceNum);
	}
	
	float codeLength, smallLength, bigLength;
	int resizeParam, codeNumbers, MaxNumberOfImgs, leastNumberOfCamptrueImage, xDiff_1, yDiff_1;
	int angleIndex, xIndex, yIndex, UpExposureTime, leftExposureTime, rightExposureTime, xDiff, yDiff;
	int leftCameraIndex, rightCameraIndex, upCameraIndex;
	
	// 通用参数
	ifstream fpw;
	fpw.open("./commonPara.txt");
	fpw >> MaxNumberOfImgs >> leastNumberOfCamptrueImage>>leftCameraIndex>>rightCameraIndex>>upCameraIndex;
	fpw.close();
	
	
	void* handle0 = NULL, *handle1 = NULL, *handle2 = NULL;
	handle0 = callHik(leftCameraIndex, stDeviceList, handle0);   ///////0
	handle1 = callHik(rightCameraIndex, stDeviceList, handle1);   ///////2
	handle2 = callHik(upCameraIndex, stDeviceList, handle2);   ///////1
	bool isTurnOn0 = true, isTurnOn1 = true, isTurnOn2 = true;
	
	
	
	// 上视摄像头
	fpw.open("./upCameraPara.txt");
	fpw >> codeLength >> smallLength >> bigLength >> resizeParam >> codeNumbers >>
		angleIndex >> xIndex >> yIndex >> UpExposureTime >> xDiff >> yDiff>> xDiff_1 >> yDiff_1;
	fpw.close();
	MV_CC_SetExposureTime(handle2, UpExposureTime);
	Detector upCamera(handle2, codeLength, smallLength, bigLength, \
		resizeParam, codeNumbers, MaxNumberOfImgs, leastNumberOfCamptrueImage, \
		angleIndex, xIndex, yIndex, xDiff, yDiff, xDiff_1, yDiff_1);

	// 左视摄像头
	fpw.open("./leftCamearPara.txt");
	fpw >> codeLength >> smallLength >> bigLength >> resizeParam >> codeNumbers >> 
		angleIndex >> xIndex >> yIndex >> leftExposureTime >> xDiff >> yDiff>> xDiff_1 >> yDiff_1;
	fpw.close();
	MV_CC_SetExposureTime(handle0, leftExposureTime);
	Detector leftCamera(handle0, codeLength, smallLength, bigLength, \
		resizeParam, codeNumbers, MaxNumberOfImgs, leastNumberOfCamptrueImage, \
		angleIndex, xIndex, yIndex, xDiff, yDiff, xDiff_1, yDiff_1);

	// 右视摄像头
	fpw.open("./rightCameraPara.txt");
	fpw >> codeLength >> smallLength >> bigLength >> resizeParam >> codeNumbers >> 
		angleIndex >> xIndex >> yIndex >> rightExposureTime >> xDiff >> yDiff>> xDiff_1 >> yDiff_1;
	fpw.close();
	MV_CC_SetExposureTime(handle1, rightExposureTime);
	Detector rightCamera(handle1, codeLength, smallLength, bigLength, \
		resizeParam, codeNumbers, MaxNumberOfImgs, leastNumberOfCamptrueImage, \
		angleIndex, xIndex, yIndex, xDiff, yDiff, xDiff_1, yDiff_1);
		
	int timesOfLeftCamera = 0, timesOfRightCamera = 0, timesOfUpCamera = 0;

	while (!kbhit()){
		if (readResults.size() == 0)
			continue;
		printf("receive command\n");
		int cameraIndex = int(readResults[0]);
		int codeNumbers = int(readResults[1]);
		//int codeNumbers = 1;
		printf("cameraIndex: %d\n", cameraIndex);
		printf("codeNumbers: %d\n", codeNumbers);
		int* postionInfoValues;
		char codeInfo[16];
		switch (cameraIndex){
		case 65:   // 0x41
			printf("Left camera starts capturing image:  %d\n", isTurnOn0);

			if (!isTurnOn0){
				handle0 = callHik(0, stDeviceList, handle0);
				isTurnOn0 = true;
			}

			leftCamera.codeNumbers = codeNumbers;
			leftCamera.leastNumberOfCamptrueImage = leastNumberOfCamptrueImage;
			leftCamera.MaxNumberOfImgs = MaxNumberOfImgs;
			postionInfoValues = leftCamera.locateQR(img);
			
			//纠正x y方向的偏移
			if(leftCamera.codeNumbers==0){
			postionInfoValues[0] = 0;
			cout<<"                            " <<postionInfoValues[1]<<endl;
			//postionInfoValues[0] += leftCamera.xDiff;
			postionInfoValues[1] += 22;
			postionInfoValues[1] += (-(postionInfoValues[6]*cos(abs(postionInfoValues[7]/1800.0*3.14))+270)*tan(postionInfoValues[2]/1800.0*3.14));
			//postionInfoValues[1] = -sin(postionInfoValues[2]/1800.0*3.14)*600;
			//postionInfoValues[1] =  postionInfoValues[1] - leftCamera.yDiff;
			//postionInfoValues[2] += 12;
			}
			else{
			postionInfoValues[0] += leftCamera.xDiff_1;
			postionInfoValues[1] =  postionInfoValues[1] - leftCamera.yDiff_1;
			//postionInfoValues[2] += 18;
			}
			
			TransportPosition(my_serial, postionInfoValues);
			printf("postionInfo:  %d, %d, %d, %d, %d, %d\n", postionInfoValues[0], \
				postionInfoValues[1], postionInfoValues[2], postionInfoValues[3], \
				postionInfoValues[4], postionInfoValues[5]);
			cout << endl << endl;
			
			++timesOfLeftCamera;
			imwrite("./leftCameraImgs/"+to_string(timesOfLeftCamera%5)+".bmp", img);
			imwrite("./leftCameraImgs/now.bmp", img);
			
			break;

		case 66:   // 0x42
			printf("Right camera starts capturing image:  %d\n", isTurnOn1);

			if (!isTurnOn1){
				handle1 = callHik(2, stDeviceList, handle1);
				isTurnOn1 = true;
			}

			rightCamera.codeNumbers = codeNumbers;
			rightCamera.leastNumberOfCamptrueImage = leastNumberOfCamptrueImage;
			rightCamera.MaxNumberOfImgs = MaxNumberOfImgs;
			postionInfoValues = rightCamera.locateQR(img);
			
			//纠正x y方向的偏移
			if(rightCamera.codeNumbers==0){
			postionInfoValues[0] += rightCamera.xDiff;
			postionInfoValues[1] = rightCamera.yDiff - postionInfoValues[1];}
			else{
			postionInfoValues[0] += rightCamera.xDiff_1;
			postionInfoValues[1] = rightCamera.yDiff_1 - postionInfoValues[1];}
			
			TransportPosition(my_serial, postionInfoValues);
			printf("postionInfo:  %d, %d, %d, %d, %d, %d\n", postionInfoValues[0], \
				postionInfoValues[1], postionInfoValues[2], postionInfoValues[3], \
				postionInfoValues[4], postionInfoValues[5]);
			cout << endl << endl;
			
			++timesOfRightCamera;
			imwrite("./rightCameraImgs/"+to_string(timesOfRightCamera%5)+".bmp", img);
			imwrite("./rightCameraImgs/now.bmp", img);
			
			break;

		case 67:   // 0x43
			printf("Up camera starts capturing image:  %d\n", isTurnOn2);
			if (!isTurnOn2){
				handle2 = callHik(1, stDeviceList, handle2); 
				isTurnOn2 = true;
			}
			upCamera.codeNumbers = codeNumbers;
			upCamera.leastNumberOfCamptrueImage = leastNumberOfCamptrueImage;
			upCamera.MaxNumberOfImgs = MaxNumberOfImgs;
			postionInfoValues = upCamera.locateQR(img);
			
			//纠正x y方向的偏移   纠正的时候，纠正的正方向和码对应的方向相反时，不需要对求取的位置值取反
			postionInfoValues[0] += upCamera.xDiff;
			postionInfoValues[1] = upCamera.yDiff - postionInfoValues[1];
			
			TransportPosition(my_serial, postionInfoValues);
			printf("postionInfo:  %d, %d, %d, %d, %d, %d\n", postionInfoValues[0], \
				postionInfoValues[1], postionInfoValues[2], postionInfoValues[3], \
				postionInfoValues[4], postionInfoValues[5]);
			cout << endl << endl;
			
			++timesOfUpCamera;
			imwrite("./upCameraImgs/"+to_string(timesOfUpCamera%5)+".bmp", img);
			imwrite("./upCameraImgs/now.bmp", img);
			
			break;

		case 193:   // 0xc1
			if (isTurnOn0){
				destoryCamera(handle0); isTurnOn0 = false;
			} break;

		case 194:   // 0xc2
			if (isTurnOn1){
				destoryCamera(handle1); isTurnOn1 = false;
			} break;

		case 195:   // 0xc3
			if (isTurnOn2){
				destoryCamera(handle2); isTurnOn2 = false;
			} break;

		case 202:   // 0xca
			if (isTurnOn0 && isTurnOn1 && isTurnOn2){
				destoryCamera(handle0);
				destoryCamera(handle1);
				destoryCamera(handle2);
				isTurnOn0 = false; isTurnOn1 = false; isTurnOn2 = false;
			} break;
		default:
			printf("!!!!No corresponding operation!!!!\n");
			break;
		}
	}
	isReadTty = false;
	destoryCamera(handle0);
	destoryCamera(handle1);
	destoryCamera(handle2);
	return 0;
}
