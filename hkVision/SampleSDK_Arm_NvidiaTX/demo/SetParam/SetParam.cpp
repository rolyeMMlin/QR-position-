#include <stdio.h>
#include <string.h>
#include "MvCameraControl.h"


bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
{
    if (NULL == pstMVDevInfo)
    {
        printf("%s\n" , "The Pointer of pstMVDevInfoList is NULL!");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        printf("%s %x\n" , "nCurrentIp:" , pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp);                   //当前IP current IP
        printf("%s %s\n\n" , "chUserDefinedName:" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);     //用户定义名 user defined name
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


int main()
{
    int nRet = MV_OK;

    void* handle = NULL;

    MV_CC_DEVICE_INFO_LIST stDeviceList;
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

    // 1. 枚举设备
    // 1. enumerate device
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

    // 2. 选择设备并创建句柄
    // 2. selective device and create handle
    nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[nIndex]);
    if (MV_OK != nRet)
    {
        printf("MV_CC_CreateHandle fail! nRet [%x]\n", nRet);
        return -1;
    }

    // 3.打开设备
    // 3. open device
    nRet = MV_CC_OpenDevice(handle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_OpenDevice fail! nRet [%x]\n", nRet);
        return -1;
    }

    // 4.设置宽
    // 4. set width
    unsigned int nWidthValue = 0;
    printf("please input the width to set:");
    scanf("%d", &nWidthValue);
    nRet = MV_CC_SetIntValue(handle, "Width", nWidthValue);
    if (MV_OK == nRet)
    {
        printf("set Width OK!\n");
    }
    else
    {
        printf("set Width failed! nRet [%x]\n", nRet);
    }


    // 5.设置高
    // 5. set height
    unsigned int nHeightValue = 0;
    printf("please input the height to set:");
    scanf("%d", &nHeightValue);
   
    nRet = MV_CC_SetIntValue(handle, "Height", nHeightValue);    //宽高设置时需考虑步进(16)，即设置宽高需16的倍数
// when setting width and height, the step is 16
    if (MV_OK == nRet)
    {
        printf("set height OK!\n");
    }
    else
    {
        printf("set height failed! nRet [%x]\n", nRet);
    }

    // 6.设置曝光时间
    // 6. set exposure time
    float fExposureTime = 0.0f;
    printf("please input the exposure time to set:");
    scanf("%f", &fExposureTime);

    nRet = MV_CC_SetFloatValue(handle, "ExposureTime", fExposureTime);
    if (MV_OK == nRet)
    {
        printf("set exposure time OK!\n");
    }
    else
    {
        printf("set exposure time failed! nRet [%x]\n", nRet);
    }


    // 7.设置触发模式
    // 7. set TriggerMode
    unsigned int nTriggerMode = 0;
    printf("please input the TriggerMode to set:");
    scanf("%d", &nTriggerMode);

    nRet = MV_CC_SetEnumValue(handle, "TriggerMode", nTriggerMode);
    if (MV_OK == nRet)
    {
        printf("set TriggerMode OK!\n");
    }
    else
    {
        printf("set TriggerMode failed! nRet [%x]\n", nRet);
    }

    // 8.使能水平镜像
    // 8. enable ReverseX
    int nSetBoolValue;
    bool bSetBoolValue;
    printf("please input the ReverseX to set(bool):");
    scanf("%d", &nSetBoolValue);
    if (0 != nSetBoolValue)
    {
        bSetBoolValue = true;
    }
    else
    {
        bSetBoolValue = false;
    }
    nRet = MV_CC_SetBoolValue(handle, "ReverseX", bSetBoolValue);
    if (MV_OK == nRet)
    {
        printf("Set ReverseX OK!\n");
    }
    else
    {
        printf("Set ReverseX Failed! nRet = [%x]\n", nRet);
    }

    // 9. 用户自定义名 
    // 9. user defined ID
    unsigned char strValue[16];
    printf("please input the DeviceUserID to set(string):");
    scanf("%s", strValue);
    nRet = MV_CC_SetStringValue(handle, "DeviceUserID", (char*)strValue);
    if (MV_OK == nRet)
    {
        printf("Set DeviceUserID OK!\n");
    }
    else
    {
        printf("Set DeviceUserID Failed! nRet = [%x]\n", nRet);
    }

    // 10.关闭设备
    // 10. close device
    nRet = MV_CC_CloseDevice(handle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_CloseDevice fail! nRet [%x]\n", nRet);
        return -1;
    }

    // 11.销毁句柄
    // 11. destroy handle
    nRet = MV_CC_DestroyHandle(handle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_DestroyHandle fail! nRet [%x]\n", nRet);
        return -1;
    }

    return 0;

}
