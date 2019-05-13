#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "MvCameraControl.h"
#include "callHik.h"
#include <time.h>
#include <iostream>

#define ROI_WIDTH 1280     //can modify ROI width
#define ROI_HEIGHT 1024     //can modify ROI height

bool g_bExit = false;

bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
{
	if (NULL == pstMVDevInfo)
	{
		printf("%s\n", "The Pointer of pstMVDevInfoList is NULL!");
		return false;
	}
	if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
	{
		// 打印当前相机ip和用户自定义名字
		// print current ip and user defined name
		printf("%s %x\n", "nCurrentIp:", pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp);
		printf("%s %s\n\n", "chUserDefinedName:", pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
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

int  WorkThread(void* pUser, Mat& img)
{
	//int nRet = MV_OK;
	MV_FRAME_OUT_INFO_EX stImageInfo = { 0 };
	memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));

	//
	MVCC_INTVALUE stIntvalue = { 0 };
	int nRet = MV_CC_GetIntValue(pUser, "PayloadSize", &stIntvalue);
	if (nRet != MV_OK)
	{
		printf("Get PayloadSize failed! nRet [%x]\n", nRet);
		return 0;
	}

	unsigned int nDataSize = stIntvalue.nCurValue + 2048;  // 一帧数据大小 + 预留2048byte用于SDK内部处理
	// (data for one frame + preserved 2048 byte) is used for internal processing //in SDK
	unsigned char * pData = (unsigned char *)malloc(sizeof(unsigned char)* nDataSize);

	//while (1)
	//{
		nRet = MV_CC_GetOneFrameTimeout(pUser, pData, nDataSize, &stImageInfo, 1000);
		unsigned char* a = pData;

		unsigned char* raw = img.data;

		if (nRet == MV_OK)
		{
			//double timeBegin = clock();
			//int copyWidthIndex = 0;
			memcpy(raw, a, stIntvalue.nCurValue);
			/*for (int i = 0; i < stImageInfo.nHeight; i++)
			{
				memcpy(raw+copyWidthIndex, a+copyWidthIndex, stImageInfo.nWidth);
				copyWidthIndex += stImageInfo.nWidth;
			}*/
			
			/*for (int i = 0; i < stImageInfo.nHeight; i++)
			{
				for (int j = 0; j < stImageInfo.nWidth; j++)
				{
					*(raw++) = *a;
					a++;
				}
				// << endl;
			}*/
			//std::cout<< "CaptureImageTime1 : " << (clock() - timeBegin) / 1000.0 << "ms" << std::endl;
			if (g_bExit)
			{
				return 0;
				//break;
			}
		}
	//}

	free(pData);
	return 1;
}

int listCamera(MV_CC_DEVICE_INFO_LIST& stDeviceList){

	int nRet;
	memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

	// 枚举设备
	// enumerate device
	nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
	if (MV_OK != nRet)
	{
		printf("MV_CC_EnumDevices fail! nRet [%x]\n", nRet);
		return -1;
	}
	
	if(stDeviceList.nDeviceNum > 0)
		return 1;
	else
		return -1;
}

void* callHik(unsigned int nIndex, MV_CC_DEVICE_INFO_LIST& stDeviceList, void* handle){
	
	//int nRet = MV_OK;
	if (stDeviceList.nDeviceNum <= 0)
	/*{
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
	else*/
	{
		printf("Find No Devices!\n");
		return handle;
	}

	// 选择设备并创建句柄
	// select device and create handle
	int nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[nIndex]);
	if (MV_OK != nRet)
	{
		printf("MV_CC_CreateHandle fail! nRet [%x]\n", nRet);
		return handle;
	}

	// 打开设备
	// open device
	nRet = MV_CC_OpenDevice(handle);
	if (MV_OK != nRet)
	{
		printf("MV_CC_OpenDevice fail! nRet [%x]\n", nRet);
		return handle;
	}

	// 设置触发模式为off
	// set trigger mode as off
	nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 0);
	if (MV_OK != nRet)
	{
		printf("MV_CC_SetTriggerMode fail! nRet [%x]\n", nRet);
		return handle;
	}

	/* For GigE cameras, we recommend increasing the packet size for better
	performance. When the network adapter supports jumbo frames, set the packet
	size to a value > 1500, e.g., to 8164. In this sample, we only set the packet size
	to 1500. */
	nRet = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", 1500);
	if (MV_OK != nRet)
	{
		printf("Set GevSCPSPacketSize fail! nRet [%x]\n", nRet);
		return handle;
	}

	/*Set the delay (in timestamp counter units) to insert between each packet for this stream channel.
	This can be used as a crude flow-control mechanism if the application or the network infrastructure cannot keep up with the packets coming from the device.
	*/
	nRet = MV_CC_SetIntValue(handle, "GevSCPD", 8000);
	if (MV_OK != nRet)
	{
		printf("Set GevSCPD fail! nRet [%x]\n", nRet);
		return handle;
	}

	// set width
	nRet = MV_CC_SetIntValue(handle, "Width", ROI_WIDTH);
	if (MV_OK != nRet)
	{
		printf("Set Width fail! nRet [%x]\n", nRet);
		return handle;
	}

	// set height
	nRet = MV_CC_SetIntValue(handle, "Height", ROI_HEIGHT);
	if (MV_OK != nRet)
	{
		printf("Set Width fail! nRet [%x]\n", nRet);
		return handle;
	}

	// 开始取流
	// start grabbing image
	nRet = MV_CC_StartGrabbing(handle);
	if (MV_OK != nRet)
	{
		printf("MV_CC_StartGrabbing fail! nRet [%x]\n", nRet);
		return handle;
	}
	return handle;
}

int getImage(void* handle, Mat& img){
	int getCode = WorkThread(handle, img);
	return getCode;
}

int destoryCamera(void* handle){
	int nRet = MV_OK;
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
