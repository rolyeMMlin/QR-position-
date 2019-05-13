#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include "callHik.h"
#include <pthread.h>
#include <time.h>
#include "QRPosition.h"
#include "serial2lib.h"

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void);
using namespace std;
class Detector{
	public:
	
	Detector(void* cameraHandle, float codeLength, float smallLength, float bigLength, \
	int resizeParam, int codeNumbers, int MaxNumberOfImgs, int leastNumberOfCamptrueImage, \
	int angleIndex, int xIndex, int yIndex, int xDiff, int yDiff, int xDiff_1, int yDiff_1) :\
	cameraHandle(cameraHandle), codeLength(codeLength), smallLength(smallLength), bigLength(bigLength), \
	resizeParam(resizeParam), codeNumbers(codeNumbers), MaxNumberOfImgs(MaxNumberOfImgs), \
	leastNumberOfCamptrueImage(leastNumberOfCamptrueImage), \
	angleIndex(angleIndex), xIndex(xIndex), yIndex(yIndex), xDiff(xDiff), yDiff(yDiff), xDiff_1(xDiff_1), yDiff_1(yDiff_1)
	{
		postionInfoValues[0] = 0, postionInfoValues[1] = 0, postionInfoValues[2] = 0, postionInfoValues[3] = -1; 
	};

	~Detector(){
	
	};

	// 抓图和定位
	void* cameraHandle;
	float codeLength, smallLength, bigLength;
	int resizeParam, MaxNumberOfImgs, leastNumberOfCamptrueImage;
	int postionInfoValues[8];
	
	// 定位结果滤波
	vector<int > angleResults;
	vector<int > outputResults;
	map<int, int> outputResultsMap;
	
	int codeInfo[2] = {0, 0};
	// 结果判定
	int angleIndex, xIndex, yIndex, xDiff, yDiff, xDiff_1, yDiff_1;

	int codeNumbers;
	int* locateQR(Mat& img);
	//void filterResults(vector<int >& inputResults, vector<int >& outputResults, \
		map<int, int>& outputResultsMap, int filterSize, int strideSize);


};