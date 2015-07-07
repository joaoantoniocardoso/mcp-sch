#include "task.h"
#include "stdlib.h"
extern int main(void);
uint8 num_tasks = 0;
uint32 running;
task_t task_list[11]; //main + 10 tasks

//configuracao
void task_init(void){
	uint32 i;
	for(i = 0; i<11 ; i++)
		task_list[i].status = 2;//mata o vetor
	num_tasks = 0;
	running = num_tasks;//num_tasks = 0
	task_list[num_tasks].status = 1;//running
	task_list[num_tasks].tid = num_tasks;
	num_tasks += 1;
}

//cria a tarefa e retorna o tid
uint32 	task_create(void(*entry)(void*), void *args){

	task_list[num_tasks].end_ctx = &task_list[num_tasks].task_ctx[242];//Aponta para o inicio da pilha mais o numero de registradores sem PC e SP
	task_list[num_tasks].task_ctx[255] = (uint32)args;          //salva o endereco dos argumentos no r0
	task_list[num_tasks].task_ctx[242] = (uint32)entry;//salva entry no registrador LR da pilha
	task_list[num_tasks].status = 0; //ready
	task_list[num_tasks].tid = num_tasks;
	num_tasks++;
	return task_list[num_tasks-1].tid;
}

//suspende a propria tarefa que chama
void	task_suspend(){
	task_list[running].status = 2;
	task_yield();
}

void	task_resume(uint32 tid){
	if (task_list[tid].status<2) //se nao estiver finishing(3) ou dead(2)
		task_list[tid].status = 0; //ready
}

uint32 	task_join(uint32 tid){
	task_list[tid].status= 2;
	return task_list[tid].ret_val;
}

//finaliza a tarefa retornando o
void 	task_finish(uint32 ret_val){
	task_list[running].status = 3; //finishing
	task_list[running].ret_val = ret_val;
	task_yield();
}

//tarefa libera o processador -> reescalonamento
void 	task_yield(void){
	uint32 i;
	for(i = running;i<11 && task_list[i].status != 0 ; i++)//varre o vetor a partir do running
		;
	if (i==11)
		for(i=0; task_list[i].status != 0 && i != running ;i++)//varre o vetor a partir do 0
			;
	if(i != running)
		task_pass(task_list[i].tid);
}

void	task_pass(uint32 tid){
	uint32 o_tid = running;
	if (task_list[running].status<2) //se nao estiver finishing(3) ou dead(2)
		task_list[running].status = 0; //ready
    running = tid; //atualiza o tid da running
    task_list[running].status = 1; //running
    switch_context((void**)&task_list[o_tid].end_ctx,(void*) task_list[running].end_ctx);
}

uint32 task_id(void){
	return running;
}

// Internal Functions
__asm__(".global switch_context	\n"
			"switch_context: \n"
			//"push {r0-r12,r14}\n"//move os registradores para a pilha
			"push {r0}\n"
			"push {r1}\n"
			"push {r2}\n"
			"push {r3}\n"
			"push {r4}\n"
			"push {r5}\n"
			"push {r6}\n"
			"push {r7}\n"
			"push {r8}\n"
			"push {r9}\n"
			"push {r10}\n"
			"push {r11}\n"
			"push {r12}\n"
			"push {r14}\n"
			"str  sp, [r0]\n"
			"mov  sp,r1\n"
			"pop {r14}\n"
			"pop {r12}\n"
			"pop {r11}\n"
			"pop {r10}\n"
			"pop {r9}\n"
			"pop {r8}\n"
			"pop {r7}\n"
			"pop {r6}\n"
			"pop {r5}\n"
			"pop {r4}\n"
			"pop {r3}\n"
			"pop {r2}\n"
			"pop {r1}\n"
			"pop {r0}\n"
			//"pop {r0-r12,r14}\n"//move os registradores da pilha
			"mov  pc,lr"
		);
