#ifndef __TASK_H
#define __TASK_H
#include "types.h"
#include "system.h"
#define TASK_STACK_SIZE	1024
#define MAX_TASKS		10

typedef struct task task_t; // 'process control block'

struct task {
	uint32 ret_val;
	uint32 tid;
	uint8 status; // [0]ready, [1]running;
	uint32 task_ctx[256];
	uint32 *end_ctx;
};
// tid uint32 ou como char?

task_t tasks[MAX_TASKS];

void 	task_init(void);									// configuracao
uint32 	task_create(void(*entry)(void*), void *args);		// cria a tarefa e retorna o tid
void	task_suspend(); 									// suspende a propria tarefa que chama
void	task_resume(uint32 tid);
uint32 	task_join(uint32 tid);
void 	task_finish(uint32 ret_val); 						// finaliza a tarefa retornando o
void 	task_yield(void); 									// tarefa libera o processador -> reescalonamento
void    task_pass(uint32 tid);
uint32 	task_id(void); 										// retorna o tid da tarefa atual

/* Internal Functions */
void    switch_context(void ** o_ctx, void * n_ctx);

#endif
