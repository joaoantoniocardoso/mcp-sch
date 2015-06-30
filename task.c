#include "task.h"
#include "stdlib.h"

extern int main(void);
uint8 num_tasks = 0;
task_t * running;

//configuracao
void task_init(void){
	running = (task_t*) malloc(sizeof(task_t));
	running->status = 1;//running
	running->tid = num_tasks++;
	running->t_next = running;
}

//cria a tarefa e retorna o tid
uint32 	task_create(void(*entry)(void*), void *args){
	task_t *n_task;
	n_task = (task_t*) malloc(sizeof(task_t));
	n_task->task_ctx =  malloc(TASK_STACK_SIZE) + TASK_STACK_SIZE;
	//n_task->task_ctx += TASK_STACK_SIZE;//Aponta para o inicio da pilha
	n_task->task_ctx = args;//salva o endereço dos argumentos no r0
	//n_task->task_ctx +=
	n_task->task_ctx -=13*sizeof(uint32);//Aponta para o inicio da pilha mais o numero de registradores sem PC e SP
	*(n_task->task_ctx) = entry;//salva entry no registrador LR da pilha
	n_task->status = 0;//ready
	n_task->tid = num_tasks;
	(busca(num_tasks-1))->t_next = n_task;
	n_task->t_next = Sch_pointer;
	num_tasks++;
	return n_task->tid;
}

//suspende a propria tarefa que chama
void	task_suspend(){
}

void	task_resume(uint32 tid){

}

uint32 	task_join(uint32 tid, uint32 * ret_val){
	return 0;
}

//finaliza a tarefa retornando o
void 	task_finish(uint32 ret_val){
}

//tarefa libera o processador -> reescalonamento
void 	task_yield(void){

}

void	task_pass(uint32 tid){
    //int i = task_id();
	//mudar pra running
	//mudar outras pra ready
	//switch_context();
}

//retorna o tid da tarefa atual
/*uint32 	task_id(void){
	task_t *t = Sch_pointer;
	uint8 i;
	for (i=num_tasks; i>0; i--){
		if (t->status == 1)//se running
			return t->tid;
		t=t->t_next;
	}
	return 0; // não achou o elemento no status running(não usou o task init)
}*/

uint32 task_id(void){
	return running->task_id;
}

//busca uma task na lista
task_t* busca (uint32 id) {
	task_t *t = Sch_pointer;
	uint8 i;
	for (i=num_tasks; i>0; i--){
		if (t->tid ==id)
			return t;
		t=t->t_next;
	}
	return NULL; // não achou o elemento
}

// Internal Functions
void 	reschedule(void){

}

void 	pauseScheduler(void){

}

void 	resumeScheduler(void){

}

//void	switch_context(**uint32 o_ctx, *uint32 n_ctx){}
