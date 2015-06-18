#ifndef __TASK_H
#define __TASK_H

#include "types.h"
#include "system.h"

#define TASK_STACK_SIZE	1024
#define MAX_TASKS		10

typedef struct task task_t; // 'process control block'
struct task {
	//TODO
};

uint32 	task_init(void);
uint32 	task_create(void(*entry)(void*), void *args);		//cria a tarefa e retorna o tid
void	task_suspend(); 									//suspende a propria tarefa que chama
void	task_resume(uint32 tid);
uint32 	task_join(uint32 tid, uint32 * ret_val);
void 	task_finish(uint32 ret_val); 						//finaliza a tarefa retornando o
void 	task_yield(void); 									//tarefa libera o processador -> reescalonamento
uint32 	task_id(void); 										//retorna o tid da tarefa atual

/* Internal Functions */
void 	reschedule(void);
void 	pauseScheduler(void);
void 	resumeScheduler(void);

#endif
