/*
 * Flash.h
 *
 *  Created on: 4 Sep 2022
 *      Author: student
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_
#include "main.h"
#include "Dht.h"
typedef enum FlashState_
{
	FLASH_STATE_NONE,
	FLASH_STATE_ERASE,
	FLASH_STATE_PROGRAM

}FlashState;

typedef struct flashData_
{
	uint32_t temp;
	uint32_t counter;
}FlashData;

typedef struct flash_
{
	FlashState state;
	FlashData  data;
	uint32_t address;
	uint32_t isErase;


}Flash;

void Flash_init(Flash* flash);
void Flash_write(uint32_t flashAddr,void *data,uint32_t dataSize);
void Flash_myInterruptHandler();
void Flash_timerInterrupt();
void Flash_print(Flash* flash);
#endif /* INC_FLASH_H_ */
