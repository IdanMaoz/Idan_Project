/*
 * SDCard.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#include "SDCard.h"
#include "main.h"
#include "fatfs.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


void SDCard::openSystem()
{
	FATFS FatFs;
	FRESULT fres;
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
		printf("f_mount error (%i)\r\n", fres);
	while(1);
	}
}

