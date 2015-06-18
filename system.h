#ifndef __SYSTEM_H
#define __SYSTEM_H
#include "types.h"

typedef struct SysTick {
	unsigned int ctrl_stat;
	unsigned int reload;
	unsigned int current;
	unsigned int calibration;
} tSysTick;

tSysTick * st_regs;

void delay(uint32 milli);
void delay2(uint32 milli);

#endif
