#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

struct PostionInfo
{
	int xPosition;
	int yPosition;
	int depth;
	int theataX;
	int theataY;
	int theataZ;
};

class QRLocation
{
public:
	QRLocation(){
		
		CODELENGTH = 39.2;
		ANGLE_DATA = 0.0546;
		fx = 951.8508;
		fy = 951.9705;
		u0 = 650.7842;
		v0 = 536.4463;
		
		/*fx = 735.922;
		fy = 736.0184;
		u0 = 631.3601;
		v0 = 519.8215;*/
		
		outftxt=NULL;
		isSent = false;
		
		};
	~QRLocation(){};
	string inputCode;
	vector<string> codeInfo;
	vector<Point> zbarScan(Mat& input, int centerPos[]);

	// 码的长度
	float CODELENGTH;

	//标定参数
	float ANGLE_DATA ;
	float fx;
	float fy;
	float u0;
	float v0;

	//打印定位信息到文档中
	ofstream* outftxt;
	
	// 是否发送定位信息
	bool isSent;

	// 定位结果
	PostionInfo results;
	
	// 是否报错
	
	int isError;

	// 只是用中的fx，通过cos求x,y通过竖直像素个数建立相似三角形
	//void localizeXYZ(vector<Point>& QR, Mat& img);
	//void localizeXYZCenter(vector<Point>& QR, Mat& img);

	// 通过标定后的结果，变换矩阵是像素坐标到相机坐标的变换，x y都是通过z的变换矩阵求得
	//void localizeXYZCalibXY(vector<Point>& QR, Mat& img);

	//码不正的时候，计算竖直方向的像素格式
	//vector<float> getVerticalPixelsNumbers(vector<Point>& QR);

	// 根据两条竖直的线求解相机倾斜角
	//void getAngleByPixelsNumbers(vector<Point>& QR, ofstream& imageInformation, \
		Mat& img, vector<float>& PixelsNumbers);

	// 摄像头回调函数，调用localization函数
	//void* callLocalizationFunction(void* pImg, ofstream* outf, float resizePara);
	bool callLocalizationByRmatrix(void* pImg, float resizePara, \
									float codeLength, float upCenterX, \
									float lowerCenterY, bool isUp, int codeNumbers, int& isError);
	//bool callLocalizeXYZCenter(void* pImg, float resizePara);

	// 将二维码区域单独截取出来
	Rect getQRRegionRectangle(vector<Point>& AllQR, int& imgWidth, int& imgHeight, float resizePara);

	// 标定的正向过程，拿到内参矩阵后，求解旋转矩阵和平移向量
	//void localizationByRmatrix(vector<vector<Point2f> >& image_points_seq,
		//float matrix[][3], float distortion[5]);
		
	void localizationByRmatrix(vector<vector<Point2f> >&image_points_seq, vector<vector<Point3f> >&object_points);
};