#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "zbar.h"
#include <math.h>

#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;
using namespace zbar;

typedef struct PostionInfo
{
	float xPosition;
	float yPosition;
	float depth;
	float slopeAngle;
};

typedef struct BorderLine
{
	float avgAngle;//average angle
	float lastYValue;//Y direction Value
};

class QRLocation
{
public:
	QRLocation(){};
	~QRLocation(){};
	string inputCode;
	vector<Point> zbarScan(Mat& input, string& codeInfo);
	vector<string> getStringMunber(string& codeInfo);
};
