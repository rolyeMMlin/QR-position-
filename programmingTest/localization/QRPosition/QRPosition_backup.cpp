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

bool getQRPoistionInfo(int postionInfo[], void* img, float resizePara, bool isCalibrate, \
						float codeLength, float upCenterX, float lowerCenterY, bool isUp, int codeNumbers){
	QRLocation QRR;
	QRR.CODELENGTH = codeLength;
	bool isLocalization = false;
	QRR.isError = 0;
	isLocalization = QRR.callLocalizationByRmatrix(img, resizePara, codeLength, \
													upCenterX, lowerCenterY, isUp, codeNumbers, QRR.isError);
	if (isLocalization){
		*postionInfo = QRR.results.xPosition;
		*(++postionInfo) = QRR.results.yPosition;
		*(++postionInfo) = QRR.results.depth;
		*(++postionInfo) = QRR.results.theataX;
		*(++postionInfo) = QRR.results.theataY;
		*(++postionInfo) = QRR.results.theataZ;
		*(++postionInfo) = QRR.isError;

	}
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
	//cout << "codeInfo:   " << symbol->get_data() << endl;
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

	/* *outftxt << PositionCamera.at<float>(0, 0) << " ";
	*outftxt << PositionCamera.at<float>(1, 0) << " ";
	*outftxt << PositionCamera.at<float>(2, 0) << " ";
	*outftxt << theataX / 3.14 * 180<< " ";
	*outftxt << theataY / 3.14 * 180<< " ";
	*outftxt << theataZ / 3.14 * 180 << endl;*/

	//cout << "x:  " << PositionCamera.at<float>(1, 0) << endl;
	//cout << "y:  " << PositionCamera.at<float>(0, 0) << endl;
	//cout << "depath:  " << PositionCamera.at<float>(2, 0) << endl;
	//cout << "theataX:  " << theataX / 3.14 * 180 << endl;
	cout << "theataY:  " << theataY / 3.14 * 180 << endl;
	//cout << "theataZ:  " << theataZ / 3.14 * 180 + 90 << endl;
	
	results.xPosition = round(PositionCamera.at<float>(1, 0));
	results.yPosition = round(PositionCamera.at<float>(0, 0));
	results.depth = round(PositionCamera.at<float>(2, 0));
	results.theataX = round(theataX / 3.14 * 180 * 10);
	results.theataY = round(theataY / 3.14 * 180 * 10);
	results.theataZ = round( (theataZ / 3.14 * 180+90) * 10);
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

bool QRLocation::callLocalizationByRmatrix(void* pImg, float resizePara, \
											float codeLength, float upCenterX, \
											float lowerCenterY, bool isUp, int codeNumbers, int& isError){
	Mat imgOrg, img;
	(*((Mat*)pImg)).copyTo(imgOrg);

	resize(imgOrg, img, Size(imgOrg.cols / resizePara, imgOrg.rows / resizePara));

	int width = imgOrg.cols;
	int height = imgOrg.rows;
	string codeInfo;
	// 三个定位块的中心坐标
	int centerPos_first[12] = { 1, 1, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0};
	int centerPos[12] = { 1, 1, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0};
	
	double t1 = clock();
	vector<Point> AllQR = zbarScan(img, codeInfo, centerPos_first);
	//cout<< "The time of first zbarScan: "<< (clock()-t1)/1000.0<<"ms"<<endl;
	
	cout<< "Number of QR code:  "<<AllQR.size()/4<<endl;
	
	
	if (AllQR.size() < 1){
		cout << "Image Without any QR code:" << endl;
		return false;
	}
	
	
	
	// 判断是否漏检码
	if (codeNumbers == 0 && (AllQR.size()==4) ){
		isError = 1;
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
	
	Rect rect = getQRRegionRectangle(AllQRCopy, width, height, resizePara);
	
	//printf("ROI Info:  %d, %d, %d, %d\n", rect.x, rect.y, rect.width, rect.height);
	
	
	
	if (rect.x <0 || rect.y<0 || rect.width <=0 || rect.height <=0 )
		return false;
	
	Mat QRRegion(rect.height, rect.width, CV_8U, Scalar(0));

	for (int ih = 0; ih< rect.height; ih++)
	{

		memcpy(QRRegion.data + ih*rect.width, imgOrg.data + imgOrg.cols*(ih + rect.y) + rect.x, rect.width);

	}
	
	t1 = clock();
	vector<Point> AllQRRegion = zbarScan(QRRegion, codeInfo, centerPos);
	//cout<< "The time of second zbarScan: "<< (clock()-t1)/1000.0<<"ms"<<endl;
	
	if (AllQRRegion.size() < 1){
		cout << "Image(ROI region) Without any QR code" << endl;
		imwrite("./cameraImg/ROI.bmp", QRRegion);
		imwrite("./cameraImg/ROI_ORG.bmp", imgOrg);
		//
		/*AllQRRegion = AllQR;
		centerPos[0] = centerPos_first[0], centerPos[1] = centerPos_first[1], centerPos[2] = centerPos_first[2];
		centerPos[3] = centerPos_first[3], centerPos[4] = centerPos_first[4], centerPos[5] = centerPos_first[5];*/
		//
		return false;
	}
	
	//printf("ROI localization center:  %d, %d, %d, %d, %d, %d\n", centerPos[0], centerPos[1], centerPos[2], \
	centerPos[3], centerPos[4], centerPos[5]);
	
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
	
	//printf("center X: %d, %d, %d\n", x_Position[0], x_Position[1], x_Position[2]);
	//printf("center Y: %d, %d, %d\n", y_Position[0], y_Position[1], y_Position[2]);
	
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
	
	
	// 通过7个点的像素坐标和世界坐标求解旋转矩阵
	//printf("6 points X:  %d, %d, %d, %d, %d, %d, %d\n", QR[0].x, QR[1].x, QR[2].x, QR[3].x, QR[4].x, QR[5].x, QR[6].x);
	//printf("6 points Y:  %d, %d, %d, %d, %d, %d, %d\n", QR[0].y, QR[1].y, QR[2].y, QR[3].y, QR[4].y, QR[5].y, QR[6].y);
	
	// 7个点的像素坐标
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
	tempPointSet[0].x = 0, tempPointSet[0].y = 0, tempPointSet[0].z = 0;
	tempPointSet[1].x = 0, tempPointSet[1].y =codeLength, tempPointSet[1].z = 0;
	tempPointSet[2].x =codeLength, tempPointSet[2].y = 0, tempPointSet[2].z = 0;
	tempPointSet[3].x =codeLength, tempPointSet[3].y =codeLength, tempPointSet[3].z = 0;
	tempPointSet[4].x = upCenterX, tempPointSet[4].y = upCenterX, tempPointSet[4].z = 0;
	tempPointSet[5].x = upCenterX, tempPointSet[5].y = lowerCenterY, tempPointSet[5].z = 0;
	tempPointSet[6].x = lowerCenterY, tempPointSet[6].y = upCenterX, tempPointSet[6].z = 0;
	vector<vector<Point3f> > object_points(1, tempPointSet);
	
	
	localizationByRmatrix(image_points_seq, object_points);
	return true;
}