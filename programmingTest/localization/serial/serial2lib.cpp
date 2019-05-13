#include "serial2lib.h"
#include "serialLibFuncdef.h"
#include "serial/serial.h"

void my_sleep(unsigned long milliseconds) {
#ifdef _WIN32
	Sleep(milliseconds); // 100 ms
#else
	usleep(milliseconds * 1000); // 100 ms
#endif
}

void TransportPosition(serial::Serial& my_serial, int positionInfor[]){
	unsigned char ToTty[13];
	getpositionInformationToTty(positionInfor, ToTty);

	unsigned short crcParity = usMBCRC16(ToTty, 11);
	ToTty[11] = (crcParity & 0xff00) >> 8;
	ToTty[12] = crcParity & 0xff;
	size_t bytes_wrote = my_serial.write(ToTty, 13);

}
void redaTty(serial::Serial& my_serial, string& readResults){
	 readResults = my_serial.read(2);
}

unsigned short usMBCRC16(unsigned char * pucFrame, unsigned short usLen)
{
	unsigned char ucCRCHi = 0xFF;
	unsigned char ucCRCLo = 0xFF;
	int iIndex;
	while (usLen--)
	{
		iIndex = ucCRCLo ^ *(pucFrame++);
		ucCRCLo = (unsigned char)(ucCRCHi ^ aucCRCHi[iIndex]);
		ucCRCHi = aucCRCLo[iIndex];
	}
	return (unsigned short)(ucCRCHi << 8 | ucCRCLo);

}

void getpositionInformationToTty(int positionInfor[], unsigned char positionInformationToTty[]){

	// 导入x信息
	positionInformationToTty[0] = positionInfor[0];

	// 导入y信息
	positionInformationToTty[1] = positionInfor[1];

	// 导入z信息
	positionInformationToTty[2] = (positionInfor[2] & 0xff00) >> 8;
	positionInformationToTty[3] = positionInfor[2] & 0xff;
	
	//  报错信息
	positionInformationToTty[4] = positionInfor[3];
	
	positionInformationToTty[5] = (positionInfor[4] & 0xff0000) >> 16;
	positionInformationToTty[6] = (positionInfor[4] & 0xff00) >> 8;
	positionInformationToTty[7] = positionInfor[4] & 0xff;
	
	positionInformationToTty[8] = (positionInfor[5]  & 0xff0000) >> 16;
	positionInformationToTty[9] = (positionInfor[5]  & 0xff00) >> 8;
	positionInformationToTty[10] = positionInfor[5] & 0xff;

	// 导入角度信息
	//positionInformationToTty[4] = (positionInfor[3] & 0x0fff) >> 4;
	//positionInformationToTty[5] = ((positionInfor[3] & 0x0fff) << 4 | (positionInfor[4] & 0x000f)) & 0x00ff;
	
	//  报错信息
	//positionInformationToTty[6] = positionInfor[4];
	//printf("????????%d   !!!!!!!!!!!!!%d\n", positionInfor[3], positionInformationToTty[4]);
}




