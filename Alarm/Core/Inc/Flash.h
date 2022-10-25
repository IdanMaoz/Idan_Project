/*
 * Flash.h
 *
 *  Created on: 25 Oct 2022
 *      Author: student
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_
#include <stdint.h>
void Flash_erase();
void Flash_program(uint64_t* aray,uint32_t size);
#endif /* INC_FLASH_H_ */
