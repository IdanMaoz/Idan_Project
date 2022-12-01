/*
 * Flash.h
 *
 *  Created on: 24 Nov 2022
 *      Author: student
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_
#include "main.h"
#include <stdint.h>
class Flash {
	uint32_t _address;
	static Flash* _instance;
public:
	static Flash* getInstance()
	{
		if(!_instance){
				_instance = new Flash;
			}
			return _instance;
	}
	void erase();
	void program(uint64_t* array,uint32_t size);
	uint32_t getAddres();
private:
	void pageSelect(FLASH_EraseInitTypeDef* page);
	Flash();

};

#endif /* INC_FLASH_H_ */
