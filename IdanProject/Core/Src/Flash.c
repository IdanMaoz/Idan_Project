/*
 * Flash.c
 *
 *  Created on: 4 Sep 2022
 *      Author: student
 */

#include "Flash.h"
#include "MyMain.h"

#include <stdio.h>
#include <string.h>
#define SIZE_OF_TEXT 24
static char text[24];

//static uint32_t address = (0x08080000);
//static uint32_t ind = 0;
//static uint64_t temp;
//static FlashState flashState=FLASH_STATE_NONE;

void Flash_init(Flash* flash)
{
	flash->data.counter = 0;
	flash->state = FLASH_STATE_NONE;
	flash->isErase = 0;
	flash->address = 0x08080000;
	/*for(uint32_t i=0x08080000;i<0x08081000;i+=8){
		if(*(uint32_t *)(i) == 0xFFFFFFFFULL){
			flash->address = i;
			break;
		}
	}*/

}
void erase(FLASH_EraseInitTypeDef *pEraseInit)
{
	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase_IT(pEraseInit);
}


void Flash_print(Flash* flash)
{
	for(int i=0x08080000;i<flash->address;i+=8){
		uint32_t printTemp = *(uint32_t *)(i);
		uint32_t printTime = *(uint32_t *)(i+4);
		printf("The temperature is: %ld and the time is: %ld\r\n",printTemp,printTime);

	}



}

void Flash_write(uint32_t flashAddr,void *data,uint32_t dataSize)
{
	FLASH_EraseInitTypeDef flash;
	flash.TypeErase = FLASH_TYPEERASE_PAGES;
	if(flashAddr < 0x08080000){
		flash.Banks = FLASH_BANK_1;
	}
	else{
		flash.Banks = FLASH_BANK_2;
	}
	flash.Page = (flashAddr - 0x80000000)/2048;
	flash.NbPages = 1;
	memcpy(text,data,dataSize);
	erase(&flash);
}

void Flash_myInterruptHandler(Flash* flash)
{
	if(flash->state==FLASH_STATE_ERASE){
		/*HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, address, *(uint64_t *)(text));
		ind+=8;*/
		flash->state=FLASH_STATE_PROGRAM;
		flash->isErase = 0;

		flash->data.temp = (uint64_t)Dht_getTemperature(&dht);
		flash->data.counter = (uint64_t)HAL_GetTick();
		uint64_t data =  *(uint64_t *)&flash->data;
		HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, flash->address, (data));
		flash->address+=8;

	}
	else if(flash->state==FLASH_STATE_PROGRAM){

		/*if(ind<SIZE_OF_TEXT){
			//HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, address+ind, *(uint64_t *)(text+ind));
			ind+=8;
		}
		else{*/

		flash->state=FLASH_STATE_NONE;
		//printFlash();
		HAL_FLASH_Lock();


		//}
	}
}
void checkAddress(Flash* flash)
{
	FLASH_EraseInitTypeDef flashErase;
	flashErase.TypeErase = FLASH_TYPEERASE_PAGES;
	flashErase.Banks = FLASH_BANK_2;
	flashErase.NbPages = 1;
	if(flash->address == 0x08080000 || flash->address == 0x08081000)
	{
		flash->address = 0x08080000;
		flashErase.Page = 256;
		flash->isErase = 1;
		flash->state = FLASH_STATE_ERASE;
		erase(&flashErase);

	}
	else if(flash->address == 0x08080800)
	{
		flash->isErase = 1;
		flashErase.Page = 257;
		flash->state = FLASH_STATE_ERASE;
		erase(&flashErase);
	}
	if(!flash->isErase){
		HAL_FLASH_Unlock();

		flash->data.temp = (uint64_t)Dht_getTemperature(&dht);
		flash->data.counter = (uint64_t)HAL_GetTick();
		uint64_t data =  *(uint64_t *)&flash->data;
		HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, flash->address, (data));
		flash->address+=8;
	}

}
void Flash_timerInterrupt(Flash* flash)
{
	flash->data.counter++;
	if(flash->data.counter>=1000){
		checkAddress(flash);
		flash->data.counter = 0;
	}
}












