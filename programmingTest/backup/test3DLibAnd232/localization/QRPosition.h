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

class QRLocation
{
public:
	QRLocation(){};
	~QRLocation(){};
	string inputCode;
	vector<Point> zbarScan(Mat& input, string &codeInfo);
	vector<string> getStringMunber(string& codeInfo);

	// 码的长度
	float CODELENGTH = 40;

	//标定参数
	float ANGLE_DATA = 0.0724;
	float fx = 760.8522;
	float fy = 760.9905;
	float u0 = 462.3623;
	float v0 = 329.8684;

	// 只是用中的fx，通过cos求x,y通过竖直像素个数建立相似三角形
	PostionInfo localizeXYZ(vector<Point>& QR, Mat& img);

	// 通过标定后的结果，变换矩阵是像素坐标到相机坐标的变换，x y都是通过z的变换矩阵求得
	PostionInfo localizeXYZCalibXY(vector<Point>& QR, Mat& img);

	//码不正的时候，计算竖直方向的像素格式
	vector<float> getVerticalPixelsNumbers(vector<Point>& QR);

	// 根据两条竖直的线求解相机倾斜角
	void getAngleByPixelsNumbers(vector<Point>& QR, ofstream& imageInformation, \
		Mat& img, vector<float>& PixelsNumbers);

	// 摄像头回调函数，调用localization函数
	void* callLocalizationFunction(void* pImg);

	// 将二维码区域单独截取出来
	Rect getQRRegionRectangle(vector<Point>& AllQR, int& imgWidth, int& imgHeight);

	// 标定的正向过程，拿到内参矩阵后，求解旋转矩阵和平移向量
	void localizationByRmatrix(vector<vector<Point2f> >& image_points_seq,
		float matrix[][3], float distortion[5]);
};
