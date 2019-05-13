#include "QRPosition.h"
#include "opencv2/calib3d/calib3d.hpp"
#include <stddef.h>
#include <time.h>
ImageScanner scanner;

static void collectCalibrationData(InputArrayOfArrays objectPoints,
	InputArrayOfArrays imagePoints1,
	InputArrayOfArrays imagePoints2,
	Mat& objPtMat, Mat& imgPtMat1, Mat* imgPtMat2,
	Mat& npoints);

/*********************************************************************************通用方法**********************************************************************/
vector<string> QRLocation::getStringMunber(string& codeInfo)//获得二维码信息中的数字信息
{
	vector<string> result;
	int a = codeInfo.find("_");
	int size = codeInfo.length();
	string searl = codeInfo.substr(0, a);
	result.push_back(searl);
	string position = codeInfo.substr(a + 1, size);
	result.push_back(position);
	return result;
}

vector<Point> QRLocation::zbarScan(Mat& input, string &codeInfo)//二维码扫描接口
{
	vector<Point> borders;
	scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);
	uchar *raw = (uchar *)input.data;
	int width = input.cols;
	int height = input.rows;
	Image imageZbar(width, height, "Y800", raw, width*height);
	//int data[300] = { 0 };
	//scanner.scan(imageZbar, data);
	int n = scanner.scan(imageZbar);
	imageZbar.set_data(NULL, 0);
	Image::SymbolIterator symbol = imageZbar.symbol_begin();
	if (imageZbar.symbol_begin() == imageZbar.symbol_end())
	{
		return borders;
	}
	//cout << "二维码信息：" << symbol->get_data() << endl;
	for (; symbol != imageZbar.symbol_end(); ++symbol)
	{
		string codeLocal = symbol->get_data();
		vector<string> searielNum = getStringMunber(codeLocal);
		Point rectPoint;
		for (int i = 0; i < 4; i++)
		{
			rectPoint.x = symbol->get_location_x(i);
			rectPoint.y = symbol->get_location_y(i);
			borders.push_back(rectPoint);
		}
		codeInfo = symbol->get_data();

	}
	return borders;
}

PostionInfo QRLocation::localizeXYZ(vector<Point>& QR, Mat& img){

	PostionInfo results;

	int width = img.rows;
	int height = img.cols;
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

	float angle = ANGLE_DATA*(center.x - width / 2);  //根据标定的测量结果，x方向像素个数和夹角的关系，

	// 焦距的无量纲
	//float dSize1 = 744.6121;
	//float dSize1 = 755.5556;
	//float dSize1 = 760.06;

	float dSize = fx;  //标定所得，无量纲  x/d=pixesl/f;

	// 转成斜边的无量纲
	float dSize1 = dSize / cos(angle / 180 * 3.14);

	// 求斜边的长度
	float lSlop = CODELENGTH*dSize1 / singleLengthVertical;
	// 求深度
	float depth = lSlop*cos(angle / 180 * 3.14);

	// 求x的坐标
	//float x = (center.x - width/2) *CODELENGTH / singleLengthHorizontal / sin(3.14 / 2 - initialAngle);
	//float x = (center.x - width/2) *CODELENGTH / singleLengthHorizontal;
	float x = sin(angle / 180 * 3.14)*lSlop;   // 误差偏大

	// 求y的坐标
	float y = (center.y - height / 2) *CODELENGTH / singleLengthVertical;

	//计算初始倾斜角 通过左边的边计算
	float leftVerticalLength = cos(atan((QR[1].x - QR[0].x) / length1Vertical))*CODELENGTH;
	float leftVerticalangle = ANGLE_DATA*((QR[1].x + QR[0].x) / 2 - width / 2);
	float dSizeleftVertical = dSize / cos(leftVerticalangle / 180 * 3.14);
	float lSlopleftVertical = leftVerticalLength * dSizeleftVertical / length1Vertical;
	float depthleftVertical = lSlopleftVertical * cos(leftVerticalangle / 180 * 3.14);
	float xleftVertical = sin(leftVerticalangle / 180 * 3.14) * lSlopleftVertical;
	//float angleInitialeftVertical = atan(abs(depthleftVertical - depth) / abs(xleftVertical - x)) / 3.14 * 180;

	//计算初始倾斜角 通过右边的边计算
	float rightVerticalLength = cos(atan((QR[2].x - QR[3].x) / length2Vertical))*CODELENGTH;
	float rightVerticalangle = ANGLE_DATA*((QR[2].x + QR[3].x) / 2 - width / 2);
	float dSizeRightVertical = dSize / cos(rightVerticalangle / 180 * 3.14);
	float lSlopRightVertical = rightVerticalLength * dSizeRightVertical / length2Vertical;
	float depthRightVertical = lSlopRightVertical * cos(rightVerticalangle / 180 * 3.14);
	float xRightVertical = sin(rightVerticalangle / 180 * 3.14) * lSlopRightVertical;
	//float angleInitialRightVertical = atan(abs(depthRightVertical - depth) / abs(xRightVertical - x)) / 3.14 * 180;

	// 根据左右边分别于中心的差  计算的角度
	//float angleInitial1 = (angleInitialRightVertical + angleInitialeftVertical) / 2;

	// 根据左右边的差  计算的角度
	float angleInitial = atan(abs(depthRightVertical - depthleftVertical) / abs(xRightVertical - xleftVertical)) / 3.14 * 180;

	cout << "By localizeXYZ" << endl;
	cout << "x:　" << x << endl;
	cout << "y:　" << y << endl;
	cout << "depath:　" << depth << endl;
	cout << "angleInitial:　" << angleInitial << endl << endl;

	results.xPosition = x;
	results.yPosition = y;
	results.depth = depth;
	results.slopeAngle = angleInitial;
	return results;

}

PostionInfo QRLocation::localizeXYZCalibXY(vector<Point>& QR, Mat& img){

	PostionInfo results;
	int width = img.rows;
	int height = img.cols;
	float length1Vertical = QR[1].y - QR[0].y;
	float length2Vertical = QR[2].y - QR[3].y;
	float singleLengthVertical = (length1Vertical + length2Vertical) / 2;

	float angle0 = ANGLE_DATA*(QR[0].x - width / 2);
	float angle1 = ANGLE_DATA*(QR[1].x - width / 2);
	float angle2 = ANGLE_DATA*(QR[2].x - width / 2);
	float angle3 = ANGLE_DATA*(QR[3].x - width / 2);

	float dSize0 = fx / cos(angle0 / 180 * 3.14);
	float dSize1 = fx / cos(angle1 / 180 * 3.14);
	float dSize2 = fx / cos(angle2 / 180 * 3.14);
	float dSize3 = fx / cos(angle3 / 180 * 3.14);

	float z0 = CODELENGTH*dSize0 / length1Vertical*cos(angle0 / 180 * 3.14);
	float z1 = CODELENGTH*dSize1 / length1Vertical*cos(angle1 / 180 * 3.14);
	float z2 = CODELENGTH*dSize2 / length2Vertical*cos(angle2 / 180 * 3.14);
	float z3 = CODELENGTH*dSize3 / length2Vertical*cos(angle3 / 180 * 3.14);

	float x0 = (QR[0].x - u0)*z0 / fx;
	float x1 = (QR[1].x - u0)*z1 / fx;
	float x2 = (QR[2].x - u0)*z2 / fx;
	float x3 = (QR[3].x - u0)*z3 / fx;

	float y0 = (QR[0].y - v0)*z0 / fy;
	float y1 = (QR[1].y - v0)*z1 / fy;
	float y2 = (QR[2].y - v0)*z2 / fy;
	float y3 = (QR[3].y - v0)*z3 / fy;

	cout << "By localizeXYZCalibXY" << endl;
	cout << "x:　" << (x0 + x1 + x2 + x3) / 4 << endl;
	cout << "y:　" << (y0 + y1 + y2 + y3) / 4 << endl;
	cout << "depath:　" << (z0 + z1 + z2 + z3) / 4 << endl;
	cout << "angleInitial:　" << atan((z2 - z1) / (x2 - x1)) / 3.14 * 180 << endl << endl;

	results.xPosition = (x0 + x1 + x2 + x3) / 4;
	results.yPosition = (y0 + y1 + y2 + y3) / 4;
	results.depth = (z0 + z1 + z2 + z3) / 4;
	results.slopeAngle = atan((z2 - z1) / (x2 - x1)) / 3.14 * 180;
	return results;
}

vector<float> QRLocation::getVerticalPixelsNumbers(vector<Point>& QR){
	float upLineK = float(QR[3].y - QR[0].y) / (QR[3].x - QR[0].x);
	float lowLineK = float(QR[2].y - QR[1].y) / (QR[2].x - QR[1].x);

	vector<float> pixelsNumbers(4, 0);
	//投影从左到右的顺序为0 1 3 2， 计算 0点和3点的竖直像素个数

	//float VerticalPixels0_1 = QR[1].y + lowLineK*(QR[0].x - QR[1].x) - QR[0].y;
	pixelsNumbers[0] = QR[1].y + lowLineK*(QR[0].x - QR[1].x) - QR[0].y;
	//float VerticalPixels3_1 = QR[1].y + lowLineK*(QR[3].x - QR[1].x) - QR[3].y;
	pixelsNumbers[1] = QR[1].y + lowLineK*(QR[3].x - QR[1].x) - QR[3].y;
	/*float VerticalPixels0_2 = QR[2].y + lowLineK*(QR[0].x - QR[2].x) - QR[0].y;
	float VerticalPixels3_2 = QR[2].y + lowLineK*(QR[3].x - QR[2].x) - QR[3].y;*/

	//float VerticalPixels1_0 = QR[1].y- (QR[0].y + upLineK*(QR[1].x - QR[0].x));
	pixelsNumbers[2] = QR[1].y - (QR[0].y + upLineK*(QR[1].x - QR[0].x));
	//float VerticalPixels2_0 = QR[2].y - (QR[0].y + upLineK*(QR[2].x - QR[0].x));
	pixelsNumbers[3] = QR[2].y - (QR[0].y + upLineK*(QR[2].x - QR[0].x));

	/*float VerticalPixels1_3 = QR[1].y - (QR[3].y + upLineK*(QR[1].x - QR[3].x));
	float VerticalPixels2_3 = QR[2].y - (QR[3].y + upLineK*(QR[2].x - QR[3].x));*/

	return pixelsNumbers;



	//投影从左到右的顺序为1 0 2 3， 计算 0点和2点的竖直像素个数




}

void QRLocation::getAngleByPixelsNumbers(vector<Point>& QR, ofstream& imageInformation, \
	Mat& img, vector<float>& PixelsNumbers){

	int width = img.rows;
	int height = img.cols;

	float dSize = fx;

	float angle0 = ANGLE_DATA*(QR[0].x - width / 2);  //根据标定的测量结果，x方向像素个数和夹角的关系，
	float angle1 = ANGLE_DATA*(QR[1].x - width / 2);
	float angle2 = ANGLE_DATA*(QR[2].x - width / 2);
	float angle3 = ANGLE_DATA*(QR[3].x - width / 2);
	float dSize0 = dSize / cos(angle0 / 180 * 3.14);
	float dSize1 = dSize / cos(angle1 / 180 * 3.14);
	float dSize2 = dSize / cos(angle2 / 180 * 3.14);
	float dSize3 = dSize / cos(angle3 / 180 * 3.14);

	float dDiff = 1 - (PixelsNumbers[3] * dSize0) / (PixelsNumbers[0] * dSize3);
	float xDiff = cos(angle3 / 180 * 3.14) - \
		(PixelsNumbers[3] * dSize0) / (PixelsNumbers[0] * dSize3)*cos(angle0 / 180 * 3.14);
	float Initangle1 = atan(dDiff / xDiff) / 3.14 * 180;

	float Initangle2 = atan(1 / ((cos(angle2 / 180 * 3.14) - (PixelsNumbers[2] * dSize1) / (PixelsNumbers[1] * dSize2)*cos(angle1 / 180 * 3.14)) \
		/ (1 - (PixelsNumbers[2] * dSize1) / (PixelsNumbers[1] * dSize2)))) / 3.14 * 180;

	float Initangle = atan((cos(angle2 / 180 * 3.14) - (PixelsNumbers[2] * dSize1) / (PixelsNumbers[1] * dSize2)*cos(angle1 / 180 * 3.14)) \
		/ (1 - (PixelsNumbers[2] * dSize1) / (PixelsNumbers[1] * dSize2))) / 3.14 * 180;
}

Rect QRLocation::getQRRegionRectangle(vector<Point>& AllQR, int& imgWidth, int& imgHeight){
	// get QR region
	//int RegionWidth = AllQR[2].x*3.2-AllQR[1].x*3.2+40;
	//int RegionHeight = AllQR[1].x*3.2-AllQR[0].x*3.2+40;
	int RegionWidth = 240;
	int RegionHeight = 200;
	Point regionCenter;
	for (int i = 0; i < 4; i++)
	{
		regionCenter.x += (AllQR[i].x*3.2);
		regionCenter.y += (AllQR[i].y*3.2);
	}
	regionCenter.x /= 4;
	regionCenter.y /= 4;
	int regionLeftUpX = regionCenter.x - RegionWidth / 2;
	int regionLeftUpy = regionCenter.y - RegionHeight / 2;
	int regionRightLowX = regionCenter.x + RegionWidth / 2;
	int regionRightLowy = regionCenter.y + RegionHeight / 2;

	if (regionLeftUpX < 0)
	{
		regionRightLowX -= regionLeftUpX;
		regionLeftUpX = 0;
	}

	if (regionLeftUpy<0)
	{
		regionRightLowy -= regionLeftUpy;
		regionLeftUpy = 0;
	}

	if (regionRightLowX>imgWidth - 1)
	{
		regionLeftUpX = regionLeftUpX - (regionRightLowX - (imgWidth - 1));
		regionRightLowX = imgWidth - 1;
	}

	if (regionRightLowy > imgHeight - 1)
	{
		regionLeftUpy = regionLeftUpy - (regionRightLowy - (imgHeight - 1));
		regionRightLowy = imgHeight - 1;
	}


	return Rect(regionLeftUpX, \
		regionLeftUpy, \
		regionRightLowX - regionLeftUpX, \
		regionRightLowy - regionLeftUpy);

}

void* QRLocation::callLocalizationFunction(void* pImg){

	Mat imgOrg, img;
	(*((Mat*)pImg)).copyTo(imgOrg);

	resize(imgOrg, img, Size(imgOrg.cols / 3.2, imgOrg.rows / 3.2));

	int width = imgOrg.cols;
	int height = imgOrg.rows;
	Mat resultImg;
	cvtColor(imgOrg, resultImg, CV_GRAY2RGB);
	QRLocation QRR;
	string codeInfo;
	QRR.inputCode = "8686886";
	double t1 = clock();

	vector<Point> AllQR = zbarScan(img, codeInfo);
	if (AllQR.size() < 1){
		cout << "Image Without any QR code:" << endl;
		return 0;
	}
	Rect rect = getQRRegionRectangle(AllQR, width, height);
	Mat QRRegion;
	imgOrg(rect).copyTo(QRRegion);
	vector<Point> AllQRRegion = QRR.zbarScan(QRRegion, codeInfo);
	if (AllQRRegion.size() < 1){
		cout << "Image Without any QR code:" << endl;
		return 0;
	}

	for (int Qi = 0; Qi < AllQRRegion.size() / 4; Qi++)
	{
		AllQRRegion[0 + Qi * 4].x += rect.x;
		AllQRRegion[1 + Qi * 4].x += rect.x;
		AllQRRegion[2 + Qi * 4].x += rect.x;
		AllQRRegion[3 + Qi * 4].x += rect.x;

		AllQRRegion[0 + Qi * 4].y += rect.y;
		AllQRRegion[1 + Qi * 4].y += rect.y;
		AllQRRegion[2 + Qi * 4].y += rect.y;
		AllQRRegion[3 + Qi * 4].y += rect.y;

		vector<Point> QR(4);
		copy(AllQRRegion.begin() + Qi * 4, AllQRRegion.begin() + Qi * 4 + 4, QR.begin());

		localizeXYZ(QR, imgOrg);
		localizeXYZCalibXY(QR, imgOrg);
	}
	//namedWindow("DecodeAndLocResize", 1);
	//imwrite("resize.bmp", resultImg);
	//waitKey(-1);
	return 0;
}


void QRLocation::localizationByRmatrix(vector<vector<Point2f> >& image_points_seq,
	float matrix[][3], float distortion[5]){


	vector<vector<Point3f> >object_points(1, vector<Point3f>(4));
	object_points[0][0].x = 0;
	object_points[0][0].y = 0;
	object_points[0][0].z = 0;

	object_points[0][1].x = 0;
	object_points[0][1].y = 40;
	object_points[0][1].z = 0;

	object_points[0][2].x = 40;
	object_points[0][2].y = 40;
	object_points[0][2].z = 0;

	object_points[0][3].x = 40;
	object_points[0][3].y = 0;
	object_points[0][3].z = 0;

	Mat objPt, imgPt, npoints;
	collectCalibrationData(object_points, image_points_seq, noArray(),
		objPt, imgPt, 0, npoints);

	// matrix = { { 530.0394109869766, 0, 338.8877250817052 }, \
	{ 0, 530.2174994598887, 232.3375650099054 }, \
	{0, 0, 1} };
	//float distortion[5] = { -0.2651714853411377, -0.06416630065798006, \
		0.0007277414703180894, -0.001017029027201303, 0.3324625316861573 };

	Mat mycameraMatrix(Size(3, 3), CV_32FC1, matrix);
	Mat mydistortion(Size(5, 1), CV_32FC1, distortion);
	CvMat c_objPt = objPt, c_imgPt = imgPt, c_npoints = npoints, \
		CVmycameraMatrix = mycameraMatrix, CVmydistortion = mydistortion;

	Mat rvecM(1, 3, CV_32FC1), tvecM(1, 3, CV_32FC1);
	CvMat c_rvecM = rvecM, c_tvecM = tvecM;
	cvFindExtrinsicCameraParams2(&c_objPt, &c_imgPt, &CVmycameraMatrix, &CVmydistortion, &c_rvecM, &c_tvecM);

	double R_matrix[9];
	CvMat pR_matrix;
	cvInitMatHeader(&pR_matrix, 3, 3, CV_32FC1, R_matrix, CV_AUTOSTEP);

	cvRodrigues2(&c_tvecM, &pR_matrix);

	Mat Rmatrix((&pR_matrix)->rows, (&pR_matrix)->cols, (&pR_matrix)->type, (&pR_matrix)->data.fl);
	Mat Tvector((&c_rvecM)->rows, (&c_rvecM)->cols, (&c_rvecM)->type, (&c_rvecM)->data.fl);
	cout << Rmatrix << endl << endl;
	cout << Tvector << endl << endl;

	float Position[3][4] = { { 0, 0, 40, 40 }, { 0, 40, 40, 0 }, \
	{ 0, 0, 0, 0 } };
	Mat wpConvexHull(Size(4, 3), CV_32FC1, Position);

	Mat PositionCamera = Rmatrix*wpConvexHull;// + //Tvector.t();
	cout << PositionCamera << endl << endl;
	cout << Tvector.t() << endl << endl;
	PositionCamera.col(0) += Tvector.t();
	PositionCamera.col(1) += Tvector.t();
	PositionCamera.col(2) += Tvector.t();
	PositionCamera.col(3) += Tvector.t();

	float theataX = atan2(Rmatrix.at<float>(2, 1), Rmatrix.at<float>(2, 2));
	float theataY = atan2(-1.0*Rmatrix.at<float>(2, 0), \
		sqrt(Rmatrix.at<float>(2, 2)*Rmatrix.at<float>(2, 2) + \
		Rmatrix.at<float>(2, 1)*Rmatrix.at<float>(2, 1)));
	float theataZ = atan2(Rmatrix.at<float>(1, 0), Rmatrix.at<float>(0, 0));
	cout << theataX << endl;
	cout << theataY << endl;
	cout << theataZ << endl;
	cout << PositionCamera << endl;
}

static void collectCalibrationData(InputArrayOfArrays objectPoints,
	InputArrayOfArrays imagePoints1,
	InputArrayOfArrays imagePoints2,
	Mat& objPtMat, Mat& imgPtMat1, Mat* imgPtMat2,
	Mat& npoints)
{
	int nimages = (int)objectPoints.total();
	int i, j = 0, ni = 0, total = 0;
	CV_Assert(nimages > 0 && nimages == (int)imagePoints1.total() &&
		(!imgPtMat2 || nimages == (int)imagePoints2.total()));

	for (i = 0; i < nimages; i++)
	{
		ni = objectPoints.getMat(i).checkVector(3, CV_32F);
		CV_Assert(ni >= 0);
		total += ni;
	}

	npoints.create(1, (int)nimages, CV_32S);
	objPtMat.create(1, (int)total, CV_32FC3);
	imgPtMat1.create(1, (int)total, CV_32FC2);
	Point2f* imgPtData2 = 0;

	if (imgPtMat2)
	{
		imgPtMat2->create(1, (int)total, CV_32FC2);
		imgPtData2 = imgPtMat2->ptr<Point2f>();
	}

	Point3f* objPtData = objPtMat.ptr<Point3f>();
	Point2f* imgPtData1 = imgPtMat1.ptr<Point2f>();

	for (i = 0; i < nimages; i++, j += ni)
	{
		Mat objpt = objectPoints.getMat(i);
		Mat imgpt1 = imagePoints1.getMat(i);
		ni = objpt.checkVector(3, CV_32F);
		int ni1 = imgpt1.checkVector(2, CV_32F);
		CV_Assert(ni > 0 && ni == ni1);
		npoints.at<int>(i) = ni;
		memcpy(objPtData + j, objpt.data, ni*sizeof(objPtData[0]));
		memcpy(imgPtData1 + j, imgpt1.data, ni*sizeof(imgPtData1[0]));

		if (imgPtData2)
		{
			Mat imgpt2 = imagePoints2.getMat(i);
			int ni2 = imgpt2.checkVector(2, CV_32F);
			CV_Assert(ni == ni2);
			memcpy(imgPtData2 + j, imgpt2.data, ni*sizeof(imgPtData2[0]));
		}
	}
}