#include "QRPosition.h"
#include <stddef.h>
ImageScanner scanner;

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

vector<Point> QRLocation::zbarScan(Mat& input, string& codeInfo)//二维码扫描接口
{
	vector<Point> borders;
	scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);
	uchar *raw = (uchar *)input.data;
	int width = input.cols;
	int height = input.rows;
	Image imageZbar(width, height, "Y800", raw, width*height);
	//int data[300] = { 0 };
	scanner.scan(imageZbar);
	//int n = scanner.scan(imageZbar);
	//cout<<n<<endl;
	imageZbar.set_data(NULL, 0);
	Image::SymbolIterator symbol = imageZbar.symbol_begin();
	if (imageZbar.symbol_begin() == imageZbar.symbol_end())
	{
		return borders;
	}
	cout << "CodeInformation:  " << symbol->get_data() << endl;
	for (; symbol != imageZbar.symbol_end(); ++symbol)
	{
		string codeLocal = symbol->get_data();
		vector<string> searielNum = getStringMunber(codeLocal);
		if (searielNum[0] == inputCode)
		{
			Point rectPoint;
			for (int i = 0; i<4; i++)
			{
				rectPoint.x = symbol->get_location_x(i);
				rectPoint.y = symbol->get_location_y(i);
				borders.push_back(rectPoint);
			}
			codeInfo = symbol->get_data();
		}

	}
	return borders;
}

