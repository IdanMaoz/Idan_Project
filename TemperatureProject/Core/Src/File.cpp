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

void File::clear()
{
	FRESULT fres;
	fres = f_unlink(_name);
	if(fres!=FR_OK){
		if(fres == 4){
			printf("Events log file already deleted\r\n");
		}
		else{
			printf("f_unlink error (%i)\r\n",fres);
		}
	}
	else{
		printf("Events log file deleted successfully\r\n");
	}
}

void File::read()
{
	FIL fil;
	BYTE readBuf[100];
	FRESULT fres;
	fres = f_open(&fil, _name, FA_READ);
	if (fres != FR_OK) {
		if(fres == 4){
			printf("Events log file doesn't exists\r\n");
		}
		else{
			printf("f_open error (%i)\r\n",fres);
		}
	}
	else{
		TCHAR* rres = f_gets((TCHAR*)readBuf, 100, &fil);
		while(rres != 0) {
			printf("%s\r", readBuf);
			rres = f_gets((TCHAR*)readBuf, 100, &fil);
		}
	}
	f_close(&fil);
}

void File::write(char* data,size_t size)
{
	FRESULT fres;
	FIL fil;
	BYTE writeBuf[150];
	fres = f_open(&fil, _name, FA_OPEN_APPEND | FA_WRITE);
	if(fres != FR_OK) {
		printf("f_open error (%i)\r\n", fres);
	}
	strncpy((char*)writeBuf, data, size);
	UINT bytesWrote;
	fres = f_write(&fil, writeBuf, size-1, &bytesWrote);
	if(fres != FR_OK) {
		printf("f_write error (%i)\r\n",fres);
	}
	f_write(&fil, "\r\n",2, &bytesWrote);
	f_close(&fil);
}
