#include "QRPosition.h"
#include "localization.h"
#include "opencv2/calib3d/calib3d.hpp"
#include <stddef.h>
#include <time.h>
#include "zbar.h"

using namespace zbar;
ImageScanner scanner;

static void collectCalibrationData(InputArrayOfArrays objectPoints,
	InputArrayOfArrays imagePoints1,
	InputArrayOfArrays imagePoints2,
	Mat& objPtMat, Mat& imgPtMat1, Mat* imgPtMat2,
	Mat& npoints);

bool getQRPoistionInfo(int postionInfo[], void* img, float resizePara, bool isCalibrate){
	QRLocation QRR;
	bool isLocalization = false;
	if (isCalibrate){
		ofstream out("calibrate.txt", ios::app);
		QRR.outftxt = &out;
		isLocalization = QRR.callLocalizationByRmatrix(img, resizePara);}
	else{
		ofstream out("XYZcenter.txt", ios::app);
		QRR.outftxt = &out;
		isLocalization = QRR.callLocalizeXYZCenter(img, resizePara);
	}
	
	if (isLocalization){
		*postionInfo = QRR.results.xPosition;
		*(++postionInfo) = QRR.results.yPosition;
		*(++postionInfo) = QRR.results.depth;
		*(++postionInfo) = QRR.results.slopeAngle;

	}
	//return isLocalization && QRR.isSent;
	return isLocalization;
}

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

vector<Point> QRLocation::zbarScan(Mat& input, string &codeInfo, int centerPos[])//二维码扫描接口
{
	vector<Point> borders;
	scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);
	uchar *raw = (uchar *)input.data;
	int width = input.cols;
	int height = input.rows;
	Image imageZbar(width, height, "Y800", raw, width*height);
	//int data[300] = { 0 };
	//scanner.scan(imageZbar, data);
	int n = scanner.scan(imageZbar, centerPos);
	//printf("%d, %d, %d, %d, %d, %d\n", centerPos[0]/4, centerPos[1]/4, centerPos[2]/4, \
		centerPos[3]/4, centerPos[4]/4, centerPos[5]/4);
	imageZbar.set_data(NULL, 0);
	Image::SymbolIterator symbol = imageZbar.symbol_begin();
	if (imageZbar.symbol_begin() == imageZbar.symbol_end())
	{
		return borders;
	}
	cout << "codeInfo:   " << symbol->get_data() << endl;
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

void QRLocation::localizeXYZ(vector<Point>& QR, Mat& img){

	int width = img.cols;
	int height = img.rows;
	float length1Vertical = QR[1].y - QR[0].y;
	float length2Vertical = QR[2].y - QR[3].y;

	float singleLengthVertical = (length1Vertical + length2Vertical) / 2;

	float length1Horizontal = QR[3].x - QR[0].x;
	float length2Horizontal = QR[2].x - QR[1].x;

	float singleLengthHorizontal = (length1Horizontal + length2Horizontal) / 2;

	Point2f center;
	for (int i = 0; i < 4; i++)
	{
		center.x += QR[i].x;
		center.y += QR[i].y;
	}
	center.x /= 4.0, center.y /= 4.0;  //根据四个点的坐标求出码中心点的位置

	float dSize = fx;  //标定所得，无量纲  x/d=pixesl/f;

	// 转成斜边的无量纲(码中心)
	//float angleCenter = ANGLE_DATA*(center.x - width / 2);  //根据标定的测量结果，x方向像素个数和夹角的关系，码中心
	float angleCenter = atan((center.x - width / 2) / fx) / 3.1416 * 180;
	float dSizeCenter = dSize / cos(angleCenter / 180 * 3.14);

	// 求码中心竖直，斜边的长度
	float lSlopCenter = CODELENGTH* dSizeCenter / singleLengthVertical;

	// 求码中心深度
	float depthCenter = lSlopCenter*cos(angleCenter / 180 * 3.14);

	// 求中心x的坐标
	//float xCenter = (center.x - width/2) *CODELENGTH / singleLengthHorizontal;
	float x = sin(angleCenter / 180 * 3.14)*lSlopCenter;

	// 求y的坐标
	float y = (height / 2 - center.y) *CODELENGTH / singleLengthVertical;

	//计算初始倾斜角 通过左边的边计算
	float leftVerticalLength = cos(atan((QR[1].x - QR[0].x) / length1Vertical))*CODELENGTH;
	//float leftVerticalangle = ANGLE_DATA*((QR[1].x + QR[0].x) / 2 - width / 2);
	float leftVerticalangle = atan(((QR[1].x + QR[0].x) / 2 - width / 2) / fx) / 3.1416 * 180;
	float dSizeleftVertical = dSize / cos(leftVerticalangle / 180 * 3.14);
	float lSlopleftVertical = leftVerticalLength * dSizeleftVertical / length1Vertical;
	float depthleftVertical = lSlopleftVertical * cos(leftVerticalangle / 180 * 3.14);
	float xleftVertical = sin(leftVerticalangle / 180 * 3.14) * lSlopleftVertical;
	float angleInitialeftVertical = atan(abs(depthleftVertical - depthCenter) / abs(xleftVertical - x)) / 3.14 * 180;
	//计算初始倾斜角 通过右边的边计算
	float rightVerticalLength = cos(atan((QR[2].x - QR[3].x) / length2Vertical))*CODELENGTH;
	//float rightVerticalangle = ANGLE_DATA*((QR[2].x + QR[3].x) / 2 - width / 2);
	float rightVerticalangle = atan(((QR[2].x + QR[3].x) / 2 - width / 2) / fx) / 3.1416 * 180;
	float dSizeRightVertical = dSize / cos(rightVerticalangle / 180 * 3.14);
	float lSlopRightVertical = rightVerticalLength * dSizeRightVertical / length2Vertical;
	float depthRightVertical = lSlopRightVertical * cos(rightVerticalangle / 180 * 3.14);
	float xRightVertical = sin(rightVerticalangle / 180 * 3.14) * lSlopRightVertical;
	float angleInitialRightVertical = atan(abs(depthRightVertical - depthCenter) / abs(xRightVertical - x)) / 3.14 * 180;
	// 根据左右边分别于中心的差  计算的角度
	float angleInitial = (angleInitialRightVertical + angleInitialeftVertical) / 2;

	// 按条件筛选定位结果
	float distance = sqrt((xleftVertical - xRightVertical)*(xleftVertical - xRightVertical) + \
		(depthRightVertical - depthleftVertical)*(depthRightVertical - depthleftVertical));
	cout << "distance: " << distance << endl;
	if (distance>39.4 && distance<39.8){
		results.xPosition = round(x);
		results.yPosition = round(y);
		results.depth = round(depthCenter);
		results.slopeAngle = round(angleInitial * 10);
		cout << "x:  " << x << endl;
		cout << "y:  " << y << endl;
		cout << "depath:  " << depthCenter << endl;
		cout << "angleInitial:  " << angleInitial << endl;
		cout << "length1Vertical:  " << length1Vertical << "   length2Vertical:  " << length2Vertical << endl << endl;

		if (NULL != outftxt){
			*outftxt << "By localizeXYZ" << endl;
			*outftxt << "x:  " << x << endl;
			*outftxt << "y:  " << y << endl;
			*outftxt << "depath:  " << depthCenter << endl;
			*outftxt << "angleInitial:  " << angleInitial << endl;
			*outftxt << length1Horizontal << "   " << length1Horizontal << endl;
			*outftxt << length1Vertical << "   " << length2Vertical << endl << endl;
		}
	}
}

void QRLocation::localizeXYZCenter(vector<Point>& QR, Mat& img){

	float length1Vertical = QR[1].y - QR[0].y;
	float length2Vertical = QR[2].y - QR[3].y;
	float singleLengthVertical = (length1Vertical + length2Vertical) / 2;

	int width = img.cols;
	int height = img.rows;
	float dSize = fx;

	float angle0 = atan((QR[0].x - width / 2) / fx);
	float angle1 = atan((QR[1].x - width / 2) / fx);
	float angle2 = atan((QR[2].x - width / 2) / fx);
	float angle3 = atan((QR[3].x - width / 2) / fx);

	float dSize0 = dSize / cos(angle0);
	float dSize1 = dSize / cos(angle1);
	float dSize2 = dSize / cos(angle2);
	float dSize3 = dSize / cos(angle3);

	float z0 = CODELENGTH*dSize0 / length1Vertical*cos(angle0);
	float z1 = CODELENGTH*dSize1 / length1Vertical*cos(angle1);
	float z2 = CODELENGTH*dSize2 / length2Vertical*cos(angle2);
	float z3 = CODELENGTH*dSize3 / length2Vertical*cos(angle3);

	float x0 = CODELENGTH*dSize0 / length1Vertical*sin(angle0);
	float x1 = CODELENGTH*dSize1 / length1Vertical*sin(angle1);
	float x2 = CODELENGTH*dSize2 / length2Vertical*sin(angle2);
	float x3 = CODELENGTH*dSize3 / length2Vertical*sin(angle3);

	// 求y的坐标
	Point2f center;
	for (int i = 0; i < 4; i++)
	{
		center.x += QR[i].x;
		center.y += QR[i].y;
	}
	center.x /= 4, center.y /= 4;
	float y = (height / 2 - center.y) *CODELENGTH / singleLengthVertical;

	//float angleInitial1 = atan((z3 - z0) / abs(x0 - x3));
	//float angleInitial2 = atan((z2 - z1) / abs(x1 - x2));

	float angleInitial1 = atan((z3 - z0) / 40);
	float angleInitial2 = atan((z2 - z1) / 40);
	float angleInitial = (angleInitial1 + angleInitial2) / 2.0 / 3.1416 * 180;

	float distance1 = sqrt((z3 - z0)*(z3 - z0) + (x0 - x3)*(x0 - x3));
	float distance2 = sqrt((z2 - z1)*(z2 - z1) + (x1 - x2)*(x1 - x2));

	cout << "distance Center:  " << distance1 << "    " << distance2 << endl;

	//if (distance1<39.9 && distance2<39.9 && 39.1 <distance1 && 39.1<distance2){
	//if (( 60 < distance1 && distance2 < 60.3) || (distance1<60.3 && 60 < distance2)){
	isSent = true;
	cout << "By localizeXYZCenter" << endl;
	printf("z:   %f, %f, %f, %f\n", z0, z1, z2, z3);
	cout << "x Center:  " << (x0 + x1 + x2 + x3) / 4.0 << endl;
	cout << "y Center:  " << y << endl;
	cout << "depath Center:  " << (z0 + z1 + z2 + z3) / 4.0 << endl;
	cout << "angleInitial Center:  " << angleInitial << endl << endl;

	results.xPosition = round((x0 + x1 + x2 + x3) / 4.0);
	results.yPosition = round(y);
	results.depth = round((z0 + z1 + z2 + z3) / 4.0);
	results.slopeAngle = round(angleInitial);

	
	if (NULL != outftxt){
		*outftxt << (x0 + x1 + x2 + x3) / 4.0 << " ";
		*outftxt << y << " ";
		*outftxt << (z0 + z1 + z2 + z3) / 4.0 << " ";
		*outftxt << round(angleInitial * 1000) / 1000.0 << endl;
	//}
	}
}

Rect QRLocation::getQRRegionRectangle(vector<Point>& AllQR, int& imgWidth, int& imgHeight, float resizePara){
	// get QR region
	int RegionWidth = AllQR[2].x * resizePara - AllQR[1].x * resizePara + 20;
	int RegionHeight = AllQR[1].y * resizePara - AllQR[0].y * resizePara + 20;
	//int RegionWidth = 240;
	//int RegionHeight = 200;
	Point regionCenter;
	for (int i = 0; i < 4; i++)
	{
		regionCenter.x += (AllQR[i].x * resizePara);
		regionCenter.y += (AllQR[i].y * resizePara);
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

void QRLocation::localizationByRmatrix(vector<vector<Point2f> >&image_points_seq, vector<vector<Point3f> >&object_points){

	//计算旋转矩阵
	Mat objPt, imgPt, npoints;
	collectCalibrationData(object_points, image_points_seq, noArray(),
		objPt, imgPt, 0, npoints);

	float matrix[3][3] = { { 951.6612827077732, 0, 652.4532343040199 }, \
	{0, 951.5966925193334, 536.3781120475536}, \
	{0, 0, 1} };
	//float matrix[3][3] = {{735.9218242622756, 0, 631.3601291997825}, \
	{0, 736.0184025237319, 519.8214683510848}, \
	{0, 0, 1}};
	
	
	float distortion[1][5] = { 0.004765955590486268, -0.08154359089272163, \
		0.000323842378354986, 0.0007546445224335794, 0.1583932100400319 };
	//float distortion[1][5] = {-0.145093974066445, 0.1102843952139624, \
	-0.0006832208312817194, -0.0005016994787515799, -0.03810609409771405};
	
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

	cvRodrigues2(&c_rvecM, &pR_matrix);

	Mat Rmatrix((&pR_matrix)->rows, (&pR_matrix)->cols, (&pR_matrix)->type, (&pR_matrix)->data.fl);
	Mat Tvector((&c_tvecM)->rows, (&c_tvecM)->cols, (&c_tvecM)->type, (&c_tvecM)->data.fl);

	//cout << Rmatrix << endl << endl;
	//cout << Tvector << endl << endl;

	float Position[3][1] = { 20, 20, 0 };
	Mat wpConvexHull(Size(1, 3), CV_32FC1, Position);

	Mat PositionCamera = Rmatrix*wpConvexHull;
	PositionCamera.col(0) += Tvector.t();

	float theataX = atan2(Rmatrix.at<float>(2, 1), Rmatrix.at<float>(2, 2));
	float theataY = atan2(-1.0*Rmatrix.at<float>(2, 0), \
		sqrt(Rmatrix.at<float>(2, 2)*Rmatrix.at<float>(2, 2) + \
		Rmatrix.at<float>(2, 1)*Rmatrix.at<float>(2, 1)));
	float theataZ = atan2(Rmatrix.at<float>(1, 0), Rmatrix.at<float>(0, 0));

	cout << "localization by Rmatrix" << endl;

	/*cout << theataX / 3.14 * 180 << endl;
	cout << theataY / 3.14 * 180 << endl;
	cout << theataZ / 3.14 * 180 << endl;
	cout << PositionCamera << endl << endl;*/

	/* *outftxt << PositionCamera.at<float>(1, 0) << " ";
	*outftxt << PositionCamera.at<float>(0, 0) << " ";
	*outftxt << PositionCamera.at<float>(2, 0) << " ";
	*outftxt << theataX / 3.14 * 180 << endl;*/

	cout << "x:  " << PositionCamera.at<float>(1, 0) << endl;
	cout << "y:  " << PositionCamera.at<float>(0, 0) << endl;
	cout << "depath:  " << PositionCamera.at<float>(2, 0) << endl;
	cout << "angleInitial:  " << theataY / 3.14 * 180 << endl;
	
	results.xPosition = round(PositionCamera.at<float>(1, 0));
	results.yPosition = round(PositionCamera.at<float>(0, 0));
	results.depth = round(PositionCamera.at<float>(2, 0));
	results.slopeAngle = round(theataY / 3.14 * 180 * 10);
}

static void collectCalibrationData(InputArrayOfArrays objectPoints,
	InputArrayOfArrays imagePoints1,
	InputArrayOfArrays imagePoints2,
	Mat& objPtMat, Mat& imgPtMat1, Mat* imgPtMat2,
	Mat& npoints){
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

bool QRLocation::callLocalizationByRmatrix(void* pImg, float resizePara){
	Mat imgOrg, img;
	(*((Mat*)pImg)).copyTo(imgOrg);

	resize(imgOrg, img, Size(imgOrg.cols / resizePara, imgOrg.rows / resizePara));

	int width = imgOrg.cols;
	int height = imgOrg.rows;
	Mat resultImg;
	cvtColor(imgOrg, resultImg, CV_GRAY2RGB);
	QRLocation QRR;
	string codeInfo;
	QRR.inputCode = "8686886";

	// 三个定位块的中心坐标
	int centerPos_first[12] = { 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0};
	int centerPos[6] = { 0, 0, 0, 0, 0, 0};
	vector<Point> AllQR = zbarScan(img, codeInfo, centerPos_first);
	
	cout<< "Number of QR code:  "<<AllQR.size()/4<<endl;
	
	
	if (AllQR.size() < 1){
		cout << "Image Without any QR code:" << endl;
		return false;
	}
		
	vector<Point> NewAllQR(4);
	if ((AllQR.size()==4) || (AllQR[0].x > AllQR[4].x))
		copy(AllQR.begin(), AllQR.begin() + 4, NewAllQR.begin());
	else
		copy(AllQR.begin()+4, AllQR.begin() + 8, NewAllQR.begin());
	
	vector<Point> AllQRCopy(4, Point(0, 0));
	//AllQRCopy.clear();
	//模拟工况下，测试相机安装
	AllQRCopy[0] = NewAllQR[1];
	AllQRCopy[1] = NewAllQR[2];
	AllQRCopy[2] = NewAllQR[3];
	AllQRCopy[3] = NewAllQR[0];
	
	//实际工况下，相机实际安装
	/*AllQRCopy[0] = NewAllQR[3];
	AllQRCopy[1] = NewAllQR[0];
	AllQRCopy[2] = NewAllQR[1];
	AllQRCopy[3] = NewAllQR[2];*/
	
	//Rect rect = getQRRegionRectangle(AllQR, width, height, resizePara);
	Rect rect = getQRRegionRectangle(AllQRCopy, width, height, resizePara);
	
	printf("ROI Info:  %d, %d, %d, %d\n", rect.x, rect.y, rect.width, rect.height);
	
	Mat QRRegion;
	imgOrg(rect).copyTo(QRRegion);
	vector<Point> AllQRRegion = QRR.zbarScan(QRRegion, codeInfo, centerPos);
	
	printf("ROI localization center:  %d, %d, %d, %d, %d, %d\n", centerPos[0], centerPos[1], centerPos[2], \
	centerPos[3], centerPos[4], centerPos[5]);
	if (AllQRRegion.size() < 1){
		cout << "Image(ROI region) Without any QR code:" << endl;
		return false;
	}
	AllQRRegion[0].x += rect.x, AllQRRegion[0].y += rect.y;
	AllQRRegion[1].x += rect.x, AllQRRegion[1].y += rect.y;
	AllQRRegion[2].x += rect.x, AllQRRegion[2].y += rect.y;
	AllQRRegion[3].x += rect.x, AllQRRegion[3].y += rect.y;
	
	//把QR码定位坐标的第3个放到末尾，前三个用于匹配定位块的中心点
	Point tempPoint = AllQRRegion[2];
	AllQRRegion[2] = AllQRRegion[3], AllQRRegion[3] = tempPoint;
	
	vector<Point> QR(7);
	copy(AllQRRegion.begin(), AllQRRegion.begin() + 4, QR.begin());

	int x_Position[3] = { centerPos[0] / 4 + rect.x, centerPos[2] / 4 + rect.x, centerPos[4] / 4 + rect.x };
	//sort(x_Position, x_Position + 3);

	int y_Position[3] = { centerPos[1] / 4 + rect.y, centerPos[3] / 4 + rect.y, centerPos[5] / 4 + rect.y };
	//sort(y_Position, y_Position + 3);
	
	printf("center X: %d, %d, %d\n", x_Position[0], x_Position[1], x_Position[2]);
	printf("center Y: %d, %d, %d\n", y_Position[0], y_Position[1], y_Position[2]);
	
	for(int ii = 0; ii<3; ii++)
	{ 
		float distance_inf = 0xfffffff;
		for(int jj = 0; jj<3; jj++)
		{
			float distance = sqrt(powf((QR[ii].y - y_Position[jj]),2) + powf((QR[ii].x - x_Position[jj]),2));  
			if (distance<distance_inf)
			{
				distance_inf = distance;
				QR[ii+4].x = x_Position[jj];
				QR[ii+4].y = y_Position[jj];
			}
			
			
		}
	}

	//QR[4].x = x_Position[0], QR[5].x = x_Position[1], QR[6].x = x_Position[2];
	//QR[4].y = y_Position[0], QR[5].y = y_Position[2], QR[6].y = y_Position[1];

	printf("7 points X:  %d, %d, %d, %d, %d, %d, %d\n", QR[0].x, QR[1].x, QR[2].x, QR[3].x, QR[4].x, QR[5].x, QR[6].x);
	printf("7 points Y:  %d, %d, %d, %d, %d, %d, %d\n", QR[0].y, QR[1].y, QR[2].y, QR[3].y, QR[4].y, QR[5].y, QR[6].y);

	vector<Point2f> image_points_buf(7);  
	image_points_buf[0].x = QR[0].x, image_points_buf[0].y = QR[0].y;
	image_points_buf[1].x = QR[1].x, image_points_buf[1].y = QR[1].y;
	image_points_buf[2].x = QR[2].x, image_points_buf[2].y = QR[2].y;
	image_points_buf[3].x = QR[3].x, image_points_buf[3].y = QR[3].y;
	image_points_buf[4].x = QR[4].x, image_points_buf[4].y = QR[4].y;
	image_points_buf[5].x = QR[5].x, image_points_buf[5].y = QR[5].y;
	image_points_buf[6].x = QR[6].x, image_points_buf[6].y = QR[6].y;

	vector<vector<Point2f> > image_points_seq(1, image_points_buf); 

	vector<Point3f>tempPointSet(7);
	// 模拟工况下，7个点对应的世界坐标。
	/*tempPointSet[0].x = 39.2, tempPointSet[0].y = 0, tempPointSet[0].z = 0;
	tempPointSet[1].x = 0, tempPointSet[1].y = 0, tempPointSet[1].z = 0;
	tempPointSet[2].x = 39.2, tempPointSet[2].y = 39.2, tempPointSet[2].z = 0;
	tempPointSet[3].x = 0, tempPointSet[3].y = 39.2, tempPointSet[3].z = 0;
	tempPointSet[4].x = 32.7, tempPointSet[4].y = 5.8, tempPointSet[4].z = 0;
	tempPointSet[5].x = 5.8, tempPointSet[5].y = 5.8, tempPointSet[5].z = 0;
	tempPointSet[6].x = 32.7, tempPointSet[6].y = 32.7, tempPointSet[6].z = 0;*/

	//实际工况下，7个点对应的世界坐标。
	/*tempPointSet[0].x = 0, tempPointSet[0].y = 39.2, tempPointSet[0].z = 0;
	tempPointSet[1].x = 39.2, tempPointSet[1].y = 39.2, tempPointSet[1].z = 0;
	tempPointSet[2].x = 0, tempPointSet[2].y = 0, tempPointSet[2].z = 0;
	tempPointSet[3].x = 39.2, tempPointSet[3].y = 0, tempPointSet[3].z = 0;
	tempPointSet[4].x = 5.8, tempPointSet[4].y = 32.7, tempPointSet[4].z = 0;
	tempPointSet[5].x = 32.7, tempPointSet[5].y = 32.7, tempPointSet[5].z = 0;
	tempPointSet[6].x = 5.8, tempPointSet[6].y = 5.8, tempPointSet[6].z = 0;*/
	
	
	// 真实的世界坐标
	tempPointSet[0].x = 0, tempPointSet[0].y = 0, tempPointSet[0].z = 0;
	tempPointSet[1].x = 0, tempPointSet[1].y = 39.2, tempPointSet[1].z = 0;
	tempPointSet[2].x = 39.2, tempPointSet[2].y = 0, tempPointSet[2].z = 0;
	tempPointSet[3].x = 39.2, tempPointSet[3].y = 39.2, tempPointSet[3].z = 0;
	tempPointSet[4].x = 5.8, tempPointSet[4].y = 5.8, tempPointSet[4].z = 0;
	tempPointSet[5].x = 5.8, tempPointSet[5].y = 32.7, tempPointSet[5].z = 0;
	tempPointSet[6].x = 32.7, tempPointSet[6].y = 5.8, tempPointSet[6].z = 0;
	
	
	vector<vector<Point3f> > object_points(1, tempPointSet);
	localizationByRmatrix(image_points_seq, object_points);
	return true;
}

bool QRLocation::callLocalizeXYZCenter(void* pImg, float resizePara){
	Mat imgOrg, img, imgT, pImgValue;
	(*((Mat*)pImg)).copyTo(pImgValue);
	
	transpose(pImgValue, imgT);
	flip(imgT, imgOrg, 1);
	imwrite("./center.bmp", imgOrg);
	// imgOrg是翻转90度后的结果
	resize(imgOrg, img, Size(imgOrg.cols / resizePara, imgOrg.rows / resizePara));

	int width = imgOrg.cols;
	int height = imgOrg.rows;
	Mat resultImg;
	cvtColor(imgOrg, resultImg, CV_GRAY2RGB);
	QRLocation QRR;
	string codeInfo;
	QRR.inputCode = "8686886";

	// 三个定位块的中心坐标
	int centerPos[6] = { 0, 0, 0, 0, 0, 0 };
	vector<Point> AllQR = zbarScan(img, codeInfo, centerPos);
	if (AllQR.size() < 1){
		cout << "Image Without any QR code:" << endl;
		return false;
	}

	printf("%d, %d, %d, %d\n", AllQR[0].x, AllQR[1].x, AllQR[2].x, AllQR[3].x);
	printf("%d, %d, %d, %d\n", AllQR[0].y, AllQR[1].y, AllQR[2].y, AllQR[3].y);
	
	Rect rect = getQRRegionRectangle(AllQR, width, height, resizePara);
	printf("ROI Info:  %d, %d, %d, %d\n", rect.x, rect.y, rect.width, rect.height);
	
	Mat QRRegion;
	imgOrg(rect).copyTo(QRRegion);
	vector<Point> AllQRRegion = QRR.zbarScan(QRRegion, codeInfo, centerPos);
	imwrite("ROI.bmp", QRRegion);
	if (AllQRRegion.size() < 1){
		cout << "Image(ROI region) Without any QR code:" << endl;
		return false;
	}
	
	AllQRRegion[0].x += rect.x, AllQRRegion[0].y += rect.y;
	AllQRRegion[1].x += rect.x, AllQRRegion[1].y += rect.y;
	AllQRRegion[2].x += rect.x, AllQRRegion[2].y += rect.y;
	AllQRRegion[3].x += rect.x, AllQRRegion[3].y += rect.y;
	
	printf("%d, %d, %d, %d\n", AllQRRegion[0].x, AllQRRegion[1].x, AllQRRegion[2].x, AllQRRegion[3].x);
	printf("%d, %d, %d, %d\n", AllQRRegion[0].y, AllQRRegion[1].y, AllQRRegion[2].y, AllQRRegion[3].y);

	localizeXYZCenter(AllQRRegion, imgOrg);
	imwrite("./org_center.bmp", imgOrg);

	return true;
}

