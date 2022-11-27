/*
 * File.h
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#ifndef INC_FILE_H_
#define INC_FILE_H_

class File {
private:
	 char _name[20];
public:
	File(char* name);
	void open();
	void read();
	void write();
};

#endif /* INC_FILE_H_ */
