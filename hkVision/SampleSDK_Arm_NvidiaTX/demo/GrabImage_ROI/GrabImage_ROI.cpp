#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "MvCameraControl.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

#define ROI_WIDTH 640      //can modify ROI width
#define ROI_HEIGHT 480     //can modify ROI height

bool g_bExit = false;

// 等待用户输入enter键来结束取流或结束程序
// wait for user to input enter to stop grabbing or end the sample program
void PressEnterToExit(void)
{
	int c;
	while ( (c = getchar()) != '\n' && c != EOF );
    fprintf( stderr, "\nPress enter to exit.\n");
    while( getchar() != '\n');
	g_bExit = true;
	sleep(1);
}

bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
{
    if (NULL == pstMVDevInfo)
    {
        printf("%s\n" , "The Pointer of pstMVDevInfoList is NULL!");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
		// 打印当前相机ip和用户自定义名字
		// print current ip and user defined name
        printf("%s %x\n" , "nCurrentIp:" , pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp);                  
        printf("%s %s\n\n" , "chUserDefinedName:" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);     
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
    {
        printf("UserDefinedName:%s\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
    }
    else
    {
        printf("Not support.\n");
    }
    return true;
}

static void* WorkThread(void* pUser)
{
    int nRet = MV_OK;

    MV_FRAME_OUT_INFO_EX stImageInfo = {0};
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
	
	//
	MVCC_INTVALUE stIntvalue = {0};
    nRet = MV_CC_GetIntValue(pUser, "PayloadSize", &stIntvalue);
    if (nRet != MV_OK)
    {
        printf("Get PayloadSize failed! nRet [%x]\n", nRet);
    }
	
	unsigned int nDataSize = stIntvalue.nCurValue + 2048;  // 一帧数据大小 + 预留2048byte用于SDK内部处理
// (data for one frame + preserved 2048 byte) is used for internal processing //in SDK
    unsigned char * pData = (unsigned char *)malloc(sizeof(unsigned char) * nDataSize);
    
	
    while(1)
    {
        nRet = MV_CC_GetOneFrameTimeout(pUser, pData, nDataSize, &stImageInfo, 1000);
		
		unsigned char* a = pData;
		Mat img(stImageInfo.nHeight, stImageInfo.nWidth, CV_8U, Scalar(0));
		unsigned char* raw = img.data;
		
        if (nRet == MV_OK)
        {
			for (int i = 0; i < stImageInfo.nHeight; i++)
			{
				for (int j = 0; j < stImageInfo.nWidth; j++)
				{
					*(raw++) = *a;
					a++;
				}
				// << endl;
			}
			imshow("img", img);
			waitKey(20);
			printf("GetOneFrame, Width[%d], Height[%d], nFrameNum[%d]\n", 
				stImageInfo.nWidth, stImageInfo.nHeight, stImageInfo.nFrameNum);
			if(g_bExit)
			{
				break;
			}
		}
    }
	
	free(pData);
	return 0;
}

int main()
{
    int nRet = MV_OK;

    void* handle = NULL;

    MV_CC_DEVICE_INFO_LIST stDeviceList;
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

    // 枚举设备
	// enumerate device
    nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK != nRet)
    {
        printf("MV_CC_EnumDevices fail! nRet [%x]\n", nRet);
        return -1;
    }
    unsigned int nIndex = 0;
    if (stDeviceList.nDeviceNum > 0)
    {
        for (int i = 0; i < stDeviceList.nDeviceNum; i++)
        {
            printf("[device %d]:\n", i);
            MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
            if (NULL == pDeviceInfo)
            {
                break;
            } 
            PrintDeviceInfo(pDeviceInfo);            
        }  
    } 
    else
    {
        printf("Find No Devices!\n");
        return -1;
    }

    scanf("%d", &nIndex);

    // 选择设备并创建句柄
	// select device and create handle
    nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[nIndex]);
    if (MV_OK != nRet)
    {
        printf("MV_CC_CreateHandle fail! nRet [%x]\n", nRet);
        return -1;
    }

    // 打开设备
	// open device
    nRet = MV_CC_OpenDevice(handle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_OpenDevice fail! nRet [%x]\n", nRet);
        return -1;
    }
	
	// 设置触发模式为off
	// set trigger mode as off
	nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 0);
    if (MV_OK != nRet)
    {
        printf("MV_CC_SetTriggerMode fail! nRet [%x]\n", nRet);
        return -1;
    }
	
	 /* For GigE cameras, we recommend increasing the packet size for better
       performance. When the network adapter supports jumbo frames, set the packet
       size to a value > 1500, e.g., to 8164. In this sample, we only set the packet size
       to 1500. */
	nRet = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", 1500);
	if (MV_OK != nRet)
    {
        printf("Set GevSCPSPacketSize fail! nRet [%x]\n", nRet);
        return -1;
    }

	/*Set the delay (in timestamp counter units) to insert between each packet for this stream channel. 
	This can be used as a crude flow-control mechanism if the application or the network infrastructure cannot keep up with the packets coming from the device.
	*/
    nRet = MV_CC_SetIntValue(handle, "GevSCPD", 4000);
    if (MV_OK != nRet)
    {
        printf("Set GevSCPD fail! nRet [%x]\n", nRet);
        return -1;
    }

	// set width
    nRet = MV_CC_SetIntValue(handle, "Width", ROI_WIDTH);
    if (MV_OK != nRet)
    {
        printf("Set Width fail! nRet [%x]\n", nRet);
        return -1;
    }

	// set height
    nRet = MV_CC_SetIntValue(handle, "Height", ROI_HEIGHT);
    if (MV_OK != nRet)
    {
        printf("Set Width fail! nRet [%x]\n", nRet);
        return -1;
    }
	
    // 开始取流
	// start grabbing image
    nRet = MV_CC_StartGrabbing(handle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_StartGrabbing fail! nRet [%x]\n", nRet);
        return -1;
    }

	pthread_t nThreadID;
	nRet = pthread_create(&nThreadID, NULL ,WorkThread , handle);
	if (nRet != 0)
	{
		printf("thread create failed.ret = %d\n",nRet);
		return -1;
	}
		
	PressEnterToExit();
	
    // 停止取流
	// stop grabbing image
    nRet = MV_CC_StopGrabbing(handle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_StopGrabbing fail! nRet [%x]\n", nRet);
        return -1;
    }

    // 关闭设备
	// close device
    nRet = MV_CC_CloseDevice(handle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_CloseDevice fail! nRet [%x]\n", nRet);
        return -1;
    }

    // 销毁句柄
	// destroy handle
    nRet = MV_CC_DestroyHandle(handle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_DestroyHandle fail! nRet [%x]\n", nRet);
        return -1;
    }

	printf("exit\n");
    return 0;
}
