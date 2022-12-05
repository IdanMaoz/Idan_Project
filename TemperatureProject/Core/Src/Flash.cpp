/*
 * Flash.cpp
 *
 *  Created on: 24 Nov 2022
 *      Author: student
 */

#include <Flash.h>
#include <iostream>

/**
 * @brief  Flash
 *         init the flash
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
Flash::Flash()
{
	_address = 0x08080000;
}

/**
 * @brief  pageSelect
 *         handle the flash page
 *         @note
 *
 *
 * @param  FLASH_EraseInitTypeDef* flash - the flash
 * @retval none
 */
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

/**
 * @brief  getAddress
 *         get the flash address
 *         @note
 *
 *
 * @param  none
 * @retval the adress
 */

uint32_t Flash::getAddress()
{
	return _address;

}

/**
 * @brief  erase
 *         erase the flash data
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void Flash::erase()
{
	static uint32_t pageerror = 0;
	FLASH_EraseInitTypeDef flash;
	pageSelect(&flash);
	if(HAL_FLASHEx_Erase(&flash, &pageerror) != HAL_OK){
		printf("Erase failed\r\n");
	}
}

/**
 * @brief  program
 *         write to the flash
 *         @note
 *
 *
 * @param  uint64_t* array - the data
 * @param  uint32_t size - the data size
 * @retval none
 */
void Flash::program(uint64_t* array,uint32_t size)
{
	for (uint32_t i = 0 ; i<size/8; i++){
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (_address)+(i*8), *(array+i)) != HAL_OK){
			printf("Program failed\r\n");
			break;
		}
	}
}
