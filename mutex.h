#ifndef __MUTEX_H
#define __MUTEX_H

#include "types.h"
#include "system.h"

/* Estrutura para armazenamento das informacoes de um Alarm */
typedef struct mutex mutex_t;
struct mutex {
	//TODO
};

void lock(mutex_t mtx);
void unlock(mutex_t mtx);

#endif
