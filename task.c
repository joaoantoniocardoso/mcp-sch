#include task.h

uint32 	task_init(void){
	//configuracao 
}

uint32 	task_create(void(*entry)(void*), void *args){
	//cria a tarefa e retorna o tid


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