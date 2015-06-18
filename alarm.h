#ifndef __ALARM_H
#define __ALARM_H

#include "types.h"
#include "system.h"

/* Definicao para um ponteiro para funcoes Handler */
typedef void (*alarmHandler_t)(void);

/* Estrutura para armazenamento das informacoes de um Alarm */
typedef struct alarm alarm_t;
struct alarm {
	//TODO
};

int setAlarm(uint32 milliseconds, alarmHandler_t handler, bool oneShoot);
void sleep(uint32 milli);

#endif
