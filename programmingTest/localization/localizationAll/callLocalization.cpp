#include "callLocalization.h"

int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}


void filterResults(vector<int >& inputResults, vector<int >& outputResults, map<int, int>& outputResultsMap, \
	int filterSize, int strideSize){

	if (filterSize % 2 == 0){
		cout << "filterSize Error" << endl;
	}
	int inputSize = inputResults.size() - filterSize + 1;
	vector<int > subInputResultsSort(filterSize, 0.0);
	auto inputResultsBegin = inputResults.begin();
	for (int i = 0; i < inputSize; i = i + strideSize)
	{
		inputResultsBegin = inputResults.begin() + i;
		copy(inputResultsBegin, inputResultsBegin + filterSize, subInputResultsSort.begin());
		sort(subInputResultsSort.begin(), subInputResultsSort.end());
		outputResults.push_back(subInputResultsSort[filterSize / 2]);
		outputResultsMap[subInputResultsSort[filterSize / 2]]++;
	}
}


int* Detector::locateQR(Mat& img){

	int postionInfo[7] = { 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff, \
		0x0fffffff, 0x0fffffff, 0x0fffffff };

	postionInfoValues[0] = 0, postionInfoValues[1] = 0;
	postionInfoValues[2] = 0, postionInfoValues[3] = -1;
	postionInfoValues[4] = 0, postionInfoValues[5] = 0;

	while (!kbhit() && MaxNumberOfImgs > 0 && leastNumberOfCamptrueImage>0)
	{
		getImage(cameraHandle, img);// img = imread("./test.bmp");改
		codeInfo[0] = 0;
		codeInfo[1] = 0;
		//img = imread("./11.jpg", 0);
		bool islocalizationImg = getQRPoistionInfo(postionInfo, &img, resizeParam, \
			true, codeLength, smallLength, bigLength, true, codeNumbers, codeInfo);

		if (islocalizationImg)
		{
			//imwrite("./65.bmp", img);
			angleResults.push_back(postionInfo[angleIndex]);
			--leastNumberOfCamptrueImage;
			postionInfoValues[4] = codeInfo[1];
			postionInfoValues[5] = codeInfo[0];
		}
		
		--MaxNumberOfImgs;
	}

	cout << "leastNumberOfCamptrueImage:" << leastNumberOfCamptrueImage << endl;

	
	if (angleResults.size() > 0)
	{
		/*filterResults(angleResults, outputResults, outputResultsMap, 5, 1);
		
		int ans, count = 0, angle = 0;
		for (map<int, int>::iterator it = outputResultsMap.begin(); it != outputResultsMap.end(); it++)
		if (it->second > count) {
			count = it->second;
			ans = it->first;
		}

		if (outputResultsMap[ans] > outputResultsMap.size())
			angle = ans;
		else
		{
			int sum = 0;
			for (int oi = 0; oi < outputResults.size(); oi++)
				sum += outputResults[oi];
			angle = round(float(sum) / outputResults.size());
		}*/
		
		int ans, count = 0, angle = 0;
		int sum = 0;
		for (int oi = 0; oi < angleResults.size(); oi++)
			sum += angleResults[oi];
		
		angle = round(float(sum) / angleResults.size());
		
		postionInfoValues[0] = postionInfo[xIndex];
		postionInfoValues[1] = postionInfo[yIndex];
		postionInfoValues[2] = angle; 
		postionInfoValues[3] = 1;
		postionInfoValues[6] = postionInfo[2];
		postionInfoValues[7] = postionInfo[3];
		
		
	}
	
	angleResults.clear();
	outputResults.clear();
	outputResultsMap.clear();
	return postionInfoValues;
}