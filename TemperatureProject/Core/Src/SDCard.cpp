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

/**
 * @brief  openSystem
 *         to open access to sd card
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void SDCard::openSystem()
{
	FATFS FatFs;
	FRESULT fres;
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
		if(fres == 3)
		{
			printf("The sd card isn't ready\r\n");
		}
		else{
			printf("f_mount error (%i)\r\n", fres);
		}

	while(1);
	}
}

