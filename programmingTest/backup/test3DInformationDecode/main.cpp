#include "QRPosition.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>

using namespace zbar;
using namespace cv;
using namespace std;

#define ANGLE_DATA 0.0724
#define CODELENGTH 40

void localizeXYZ(vector<Point>& QR, ofstream& imageInformation, Mat& img);
int main(){

	for (int i = 0; i < 1; i++){
		string imagePath = "./many/c140/";
		string imagePathResults = imagePath + "localizationResults.txt";
		ofstream out(imagePathResults.c_str());
		
		string imagePathName = imagePath + "imageName.txt";
		ifstream imageNameTxt(imagePathName.c_str());
		string imageNum;
		imageNameTxt >> imageNum;
		for (int j = 0; j < atoi(imageNum.c_str()); j++)
		{
			string imageName;
			imageNameTxt >> imageName;
			Mat img = imread(imagePath + imageName, 0);
			QRLocation QRR;
			string codeInfo;
			QRR.inputCode = "8686886";
			double t1 = getTickCount();
			vector<Point> QR = QRR.zbarScan(img, codeInfo);

			if (QR.size() > 0)
			{
				cout << imageName << endl;
				localizeXYZ(QR, out, img);
				//PostionInfo result = QRR.calculatePoistionLeft2(QR);
			}
			double t2 = getTickCount();
			cout<< "time: "<<(t2-t1)*1000/getTickFrequency()<<endl<<endl;
		}
		out.close();
	}
return 0;
}

void localizeXYZ(vector<Point>& QR, ofstream& out, Mat& img){

	float length1Vertical = QR[1].y - QR[0].y;
	float length2Vertical = QR[2].y - QR[3].y;
	float singleLengthVertical = (length1Vertical + length2Vertical) / 2;

	float length1Horizontal = QR[3].x - QR[0].x;
	float length2Horizontal = QR[2].x - QR[1].x;
	float singleLengthHorizontal = (length1Horizontal + length2Horizontal) / 2;

	Point2f center;
	for (int i = 0; i < QR.size(); i++)
	{
		center.x += QR[i].x;
		center.y += QR[i].y;
	}
	center.x /= 4, center.y /= 4;  //根据四个点的坐标求出码中心点的位置
	//circle(img, center, 2, 255, -1);
	//imshow("windows", img);
	//imwrite("D:/test1.bmp", img);
	//waitKey(-1);

	float angle = ANGLE_DATA*(center.x - 400);  //根据标定的测量结果，x方向像素个数和夹角的关系，

	// 焦距的无量纲
	//float dSize1 = 744.6121;
	//float dSize1 = 755.5556;
	//float dSize1 = 760.06;
	float dSize = 760.736;  //标定所得，无量纲  x/d=pixesl/f;

	// 转成斜边的无量纲
	float dSize1 = dSize / cos(angle / 180 * 3.14);

	// 求斜边的长度
	float lSlop = CODELENGTH*dSize1 / singleLengthVertical;
	// 求深度
	float depth = lSlop*cos(angle / 180 * 3.14);
 
	// 求x的坐标
	//float x = (center.x - 400) *CODELENGTH / singleLengthHorizontal / sin(3.14 / 2 - initialAngle);
	//float x = (center.x - 400) *CODELENGTH / singleLengthHorizontal;
	float x = sin(angle / 180 * 3.14)*lSlop;   // 误差偏大

	// 求y的坐标
	float y = (center.y - 300) *CODELENGTH / singleLengthVertical;
	
	//计算初始倾斜角 通过左边的边计算
	float leftVerticalLength = cos(atan((QR[1].x - QR[0].x) / length1Vertical))*CODELENGTH;
	float leftVerticalangle = ANGLE_DATA*((QR[1].x + QR[0].x) / 2 - 400);
	float dSizeleftVertical = dSize / cos(leftVerticalangle / 180 * 3.14);
	float lSlopleftVertical = leftVerticalLength * dSizeleftVertical / length1Vertical;
	float depthleftVertical = lSlopleftVertical * cos(leftVerticalangle / 180 * 3.14);
	float xleftVertical = sin(leftVerticalangle / 180 * 3.14) * lSlopleftVertical;
	float angleInitialeftVertical = atan(abs(depthleftVertical - depth) / abs(xleftVertical - x)) / 3.14 * 180;
	
	//计算初始倾斜角 通过右边的边计算
	float rightVerticalLength = cos(atan((QR[2].x - QR[3].x) / length2Vertical))*CODELENGTH;
	float rightVerticalangle = ANGLE_DATA*((QR[2].x + QR[3].x) / 2 - 400);
	float dSizeRightVertical = dSize / cos(rightVerticalangle / 180 * 3.14);
	float lSlopRightVertical = rightVerticalLength * dSizeRightVertical / length2Vertical;
	float depthRightVertical = lSlopRightVertical * cos(rightVerticalangle / 180 * 3.14);
	float xRightVertical = sin(rightVerticalangle / 180 * 3.14) * lSlopRightVertical;
	float angleInitialRightVertical = atan(abs(depthRightVertical - depth) / abs(xRightVertical - x)) / 3.14 * 180;

	float angleInitial1 = (angleInitialRightVertical + angleInitialeftVertical)/2;
	float angleInitial2 = atan(abs(depthRightVertical - depthleftVertical) / abs(xRightVertical - xleftVertical)) / 3.14 * 180;

	out << x << endl;
	out << y << endl;
	out << depth << endl;
	out << angleInitial1 << endl;
	out << angleInitial2 << endl;
	out << angle << endl <<endl;

	cout << "x:  " << x << endl;
	cout << "y:  " << y << endl;
	cout << "depath:  " << depth << endl;
	cout << "angleInitial1:  " << angleInitial1 << endl;
	cout << "angleInitial2:  " << angleInitial2 << endl;
	cout << "angle:  " << angle << endl;

}
