/*
 * Flash.c
 *
 *  Created on: 25 Oct 2022
 *      Author: student
 */

#include "Flash.h"
#include "main.h"

#include "stdio.h"
static uint32_t address = (0x08080000UL);

static uint32_t pageerror = 0;
static void pageSelect (FLASH_EraseInitTypeDef * flash)
{
	flash->TypeErase = FLASH_TYPEERASE_PAGES;
	flash->Banks = FLASH_BANK_2;
	flash->Page = 256;
	flash->NbPages = 1;
}

void Flash_erase()
{
	FLASH_EraseInitTypeDef page;
	pageSelect(&page);

	if (HAL_FLASHEx_Erase(&page, &pageerror) != HAL_OK) {
		printf("Erase failed\r\n");
	}
}

void Flash_program(uint64_t* array,uint32_t size)
{

	for (int i = 0 ; i<size/8; i++)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address+(i*8), *(array+i)) != HAL_OK) {
			printf("Program failed\r\n");
			break;
		}
	}
}
