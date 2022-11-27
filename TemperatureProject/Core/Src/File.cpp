/*
 * File.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#include <File.h>
#include <stdio.h>
#include <string.h>
#include "fatfs.h"
File::File(char* name) {
	memcpy(_name,name,sizeof(_name));
}

void File::open()
{
	FIL fil;
	FRESULT fres;
	fres = f_open(&fil, _name, FA_READ);
	if (fres != FR_OK) {
	printf("f_open error (%i)\r\n",fres);
	//while(1);
	}
}
void File::read()
{
	FIL fil;
	BYTE readBuf[30];
	TCHAR* rres = f_gets((TCHAR*)readBuf, 30, &fil);
	if(rres == 0) {
		printf("f_gets error (%i)\r\n", *rres);
	}
	f_close(&fil);
}

void File::write()
{
	FRESULT fres;
	FIL fil;
	BYTE writeBuf[30];
	fres = f_open(&fil, _name, FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if(fres != FR_OK) {
		printf("f_open error (%i)\r\n", fres);
	}

	strncpy((char*)writeBuf, "a new file is made!", 20);
	UINT bytesWrote;
	fres = f_write(&fil, writeBuf, 19, &bytesWrote);
	if(fres != FR_OK) {
		printf("f_write error (%i)\r\n",fres);
	}
	f_close(&fil);
}
