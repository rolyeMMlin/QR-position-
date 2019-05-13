#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "BitBuffer.hpp"
#include "QrCode.hpp"
#include <opencv2/opencv.hpp>

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;
using namespace cv;


// Function prototypes
static void doBasicDemo(const char* text, int edgeLength);
static void printQr(const QrCode &qr, int edgeLength, Mat& img);
void getOutputImgWithArrow(Mat& imgOutput, Mat QRimg);


// The main application program.
int main(int argc,   char* argv[]) {
	const char* text = argv[1];   //要编码的字符
	const char* edgeLengthChar = argv[2];
	int edgeLength = atoi(edgeLengthChar);
	doBasicDemo(text, edgeLength);
	return EXIT_SUCCESS;
}

// Creates a single QR Code, then prints it to the console.
static void doBasicDemo(const char* text, int edgeLength) {
	//const char *text = "S150101195";              // User-supplied text
	const QrCode::Ecc errCorLvl = QrCode::Ecc::MEDIUM;  // Error correction level
	
	// Make and print the QR Code symbol
	const QrCode qr = QrCode::encodeText(text, errCorLvl);
	Mat QRimg(edgeLength, edgeLength, CV_8U, Scalar(255));
	printQr(qr, edgeLength, QRimg);
	Mat imgOutput(edgeLength+100, edgeLength+100, CV_8U, Scalar(255));
	getOutputImgWithArrow(imgOutput, QRimg);
	
	//std::cout << qr.toSvgString(4) << std::endl;
}

// Prints the given QrCode object to the console.
static void printQr(const QrCode &qr, int edgeLength, Mat& img) {
	
	Mat imgWithQROnly(qr.getSize(), qr.getSize(), CV_8U, Scalar(255));
	int cols = imgWithQROnly.cols;
	for (int y = 0; y < qr.getSize(); y++) {
		for (int x = 0; x < qr.getSize(); x++) {
			
			if(qr.getModule(x, y))
			{
				*(imgWithQROnly.data+y*cols+x) = uint8_t(0);
			}
		}
	}
	
	resize(imgWithQROnly, img, Size(img.cols, img.rows), 0, 0, INTER_NEAREST );
}

void getOutputImgWithArrow(Mat& imgOutput, Mat QRimg){
	

	for (int ih = 0; ih< QRimg.rows; ih++)
	{
		memcpy(imgOutput.data + imgOutput.cols*(ih + 50) + 50, QRimg.data + ih*QRimg.cols, QRimg.cols);
	}
	
	//   上边界
	Point rookPoints[1][3];
	rookPoints[0][0] = Point(imgOutput.cols/2, 5);
	rookPoints[0][1] = Point(imgOutput.cols/2-5, 10);
	rookPoints[0][2] = Point(imgOutput.cols/2+5, 10);
	const Point* ppt[1] = { rookPoints[0] };
	int npt[]={3};
	fillPoly(imgOutput, ppt, npt, 1, Scalar(0), 0);
	line(imgOutput,Point(imgOutput.cols/2, 0),Point(imgOutput.cols/2, 5),Scalar(0),1,0);
	
	//    左边界
	rookPoints[0][0] = Point(5, imgOutput.rows/2);
	rookPoints[0][1] = Point(10, imgOutput.rows/2-5);
	rookPoints[0][2] = Point(10, imgOutput.rows/2+5);
	ppt[0] = { rookPoints[0] };
	fillPoly(imgOutput, ppt, npt, 1, Scalar(0), 0);
	line(imgOutput,Point(0, imgOutput.rows/2),Point(5, imgOutput.rows/2),Scalar(0),1,0);
	
	//    下边界
	rookPoints[0][0] = Point(imgOutput.cols/2, imgOutput.rows-6);
	rookPoints[0][1] = Point(imgOutput.cols/2-5, imgOutput.rows-11);
	rookPoints[0][2] = Point(imgOutput.cols/2+5, imgOutput.rows-11);
	ppt[0] = { rookPoints[0] };
	fillPoly(imgOutput, ppt, npt, 1, Scalar(0), 0);
	line(imgOutput,Point(imgOutput.cols/2, imgOutput.rows-1),Point(imgOutput.cols/2, imgOutput.rows-6),Scalar(0),1,0);
	
	//    右边界
	//    左边界
	rookPoints[0][0] = Point(imgOutput.rows-6, imgOutput.rows/2);
	rookPoints[0][1] = Point(imgOutput.rows-11, imgOutput.rows/2-5);
	rookPoints[0][2] = Point(imgOutput.rows-11, imgOutput.rows/2+5);
	ppt[0] = { rookPoints[0] };
	fillPoly(imgOutput, ppt, npt, 1, Scalar(0), 0);
	line(imgOutput,Point(imgOutput.cols-1, imgOutput.rows/2),Point(imgOutput.cols-6, imgOutput.rows/2),Scalar(0),1,0);
	rectangle(imgOutput, Point(0, 0), Point(imgOutput.cols-1, imgOutput.rows-1), Scalar(0), 1, 1, 0);
	imwrite("./testQR.bmp", imgOutput);
	
}




