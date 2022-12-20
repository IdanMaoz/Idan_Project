/*
 * File.h
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#ifndef INC_FILE_H_
#define INC_FILE_H_

#include <cstddef>

class File {
private:
	 char _name[20];
public:
	File(const char* name);
	void clear();
	void read();
	void write(char* data,size_t size);
};

#endif /* INC_FILE_H_ */
