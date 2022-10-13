

#ifndef INC_MYMAIN_H_
#define INC_MYMAIN_H_

#include "main.h"
#include "Led.h"
#include "Buzzer.h"
#include "Dht.h"
#include "Flash.h"
void MyMain();
extern Led ledB;
extern Led ledR;
extern Buzzer bz1;
extern Dht dht;
extern Flash flash;
#endif /* INC_MYMAIN_H_ */
