#include task.h

uint8 num_tasks = 0;

uint32 	task_init(void){
	//configuracao 
	task_create(main, )
}

uint32 	task_create(void(*entry)(void*), void *args){
	//cria a tarefa e retorna o tid
	task_t *n_task;
	*n_task = (task_t*) malloc(sizeof(task_t));
	n_task->task_ctx = malloc(TASK_STACK_SIZE);
	n_task->task_ctx += TASK_STACK_SIZE-14*sizeof(uint32);//Aponta para o inicio da pilha mais o numero de registradores sem PC
	*n_task = entry;//salva entry no registrador LR da pilha
	n_task->status = 0;//ready
	num_tasks++;
	n_task->tid = num_tasks;
	return n_task->tid;
}

void	task_suspend(){
	//suspende a propria tarefa que chama
}

void	task_resume(uint32 tid){

}

uint32 	task_join(uint32 tid, uint32 * ret_val){

}

void 	task_finish(uint32 ret_val){
	//finaliza a tarefa retornando o
}

void 	task_yield(void){
	//tarefa libera o processador -> reescalonamento
}

void	task_pass(uint32 tid){

}

uint32 	task_id(void){
	//retorna o tid da tarefa atual
}



/* Internal Functions */
void 	reschedule(void){

}

void 	pauseScheduler(void){

}

void 	resumeScheduler(void){

}

void	switch_context(**uint32 o_ctx, *uint32 n_ctx){

}