#include "task.h"
#include "stdlib.h"

extern int main(void);
uint8 num_tasks = 0;
uint32 running;
task_t task_list[11]; //main + 10 tasks

//configuracao
void task_init(void){
	num_tasks = 0;
	running = num_tasks;//num_tasks = 0
	task_list[num_tasks].status = 1;//running
	task_list[num_tasks].tid = num_tasks++;

//////////////LEMBRAR DE TRABALHAR O CTX

}

//cria a tarefa e retorna o tid
uint32 	task_create(void(*entry)(void*), void *args){
	task_list[num_tasks].end_ctx = &task_list[num_tasks].task_ctx[13];//Aponta para o inicio da pilha mais o numero de registradores sem PC e SP
	task_list[num_tasks].task_ctx[0] = args;          //salva o endereco dos argumentos no r0 			
	task_list[num_tasks].task_ctx[13] = (uint32)entry;//salva entry no registrador LR da pilha
	task_list[num_tasks].status = 0; //ready
	task_list[num_tasks].tid = num_tasks;
	num_tasks++;
	return task_list[num_tasks].tid;
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
    switch_context(task_list[running].end_ctx, task_list[tid].end_ctx);
    task_list[running].status = 0; //ready
    running = tid; //atualiza o tid da running
    task_list[running].status = 1; //running
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
	return running;
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
			//"push {r0-r12,r14}\n"//move os registradores para a pilha
			"push r0\n"
			"push r1\n"
			"push r2\n"
			"push r3\n"
			"push r4\n"
			"push r5\n"
			"push r6\n"
			"push r7\n"
			"push r8\n"
			"push r9\n"
			"push r10\n"
			"push r11\n"
			"push r12\n"
			"push r14\n"
			"str  sp, [r0]\n"
			"mov  sp,r1\n"
			"pop r14\n"
			"pop r12\n"
			"pop r11\n"
			"pop r10\n"
			"pop r9\n"
			"pop r8\n"
			"pop r7\n"
			"pop r6\n"
			"pop r5\n"
			"pop r4\n"
			"pop r3\n"
			"pop r2\n"
			"pop r1\n"
			"pop r0\n"
			//"pop {r0-r12,r14}\n"//move os registradores da pilha
			"mov  pc,lr"
		);
