/*
 * Flash.cpp
 *
 *  Created on: 24 Nov 2022
 *      Author: student
 */

#include <Flash.h>
#include <iostream>


Flash::Flash()
{
	_address = 0x08080000;
}
void Flash::pageSelect(FLASH_EraseInitTypeDef* flash)
{
	flash->TypeErase = FLASH_TYPEERASE_PAGES;
	if(_address < 0x08080000){
		flash->Banks = FLASH_BANK_1;
	}
	else{
		flash->Banks = FLASH_BANK_2;
	}
	flash->Page = (_address - 0x80000000)/2048;
	flash->NbPages = 1;
}
uint32_t Flash::getAddres()
{
	return _address;

}

void Flash::erase()
{
	static uint32_t pageerror = 0;
	FLASH_EraseInitTypeDef flash;
	pageSelect(&flash);
	if(HAL_FLASHEx_Erase(&flash, &pageerror) != HAL_OK){
		printf("Erase failed\r\n");
	}
}
void Flash::program(uint64_t* array,uint32_t size)
{
	for (uint32_t i = 0 ; i<size/8; i++){
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (_address)+(i*8), *(array+i)) != HAL_OK){
			printf("Program failed\r\n");
			break;
		}
	}
}
