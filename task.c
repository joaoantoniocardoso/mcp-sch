#include "task.h"
#include "stdlib.h"

extern int main(void);
uint8 num_tasks = 0;
task_t * running;
task_t* task_list[11]; //main + 10 tasks

//configuracao
void task_init(void){
	num_tasks = 0;
	running = (task_t*) malloc(sizeof(task_t));
	running->status = 1;//running
	task_list[num_tasks] = running;
	running->tid = num_tasks++;
	running->t_next = running;
}

//cria a tarefa e retorna o tid
uint32 	task_create(void(*entry)(void*), void *args){
	task_t *n_task;
	n_task = (task_t*) malloc(sizeof(task_t));
	n_task->task_ctx =  malloc(TASK_STACK_SIZE) + TASK_STACK_SIZE;
	//n_task->task_ctx += TASK_STACK_SIZE;//Aponta para o inicio da pilha
	n_task->task_ctx = args; //salva o endereco dos argumentos no r0
	//n_task->task_ctx +=
	n_task->task_ctx -=13*sizeof(uint32); //Aponta para o inicio da pilha mais o numero de registradores sem PC e SP
	*((uint32*)n_task->task_ctx) = (uint32)entry; //salva entry no registrador LR da pilha

	n_task->status = 0; //ready
	n_task->tid = num_tasks;

	n_task->t_next = running->t_next;
	running->t_next = n_task;

	task_list[num_tasks] = n_task;
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
    task_t * n_task = task_list[tid];
    switch_context(&running->task_ctx, n_task->task_ctx);
    running->status = 0; //ready
    running = n_task; //atualiza o ponteiro
    running->status = 1; //running
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
	return running->tid;
}

////busca uma task na lista
//task_t* busca (uint32 id) {
//	task_t *t = running;
//	uint8 i;
//	for (i=num_tasks; i>0; i--){
//		if (t->tid ==id)
//			return t;
//		t=t->t_next;
//	}
//	return NULL; // não achou o elemento
//}

// Internal Functions
void 	reschedule(void){

}

void 	pauseScheduler(void){

}

void 	resumeScheduler(void){

}

__asm__(".global switch_context	\n"
			"switch_context: \n"
			"push {r0-r12,r14}\n"//move os registradores para a pilha
			"str  sp, [r0]\n"
			"mov  sp,r1\n"
			"pop {r0-r12,r14}\n"//move os registradores da pilha
			"mov  pc,lr"
		);
