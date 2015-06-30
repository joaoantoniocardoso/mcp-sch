/*
 * main.c
 *
 *
 */
#include "system.h"
#include "interrupts.h"
#include "gpio.h"
#include "task.h"


#define MS_DELAY 1000

 uint32 t_ledoff, t_ledon;

//int soma(int a, int b){
//	int res;
//	int res2;
//	__asm__("add %0, %2, %3	\n"
//			"add r4, %0, %0 \n"
//			"add %2, r4, r4 \n"
//			: "=r"(res), "=r"(res2)
//			: "r"(a), "r"(b)
//			: "r4"
//		   );
//	return res;
//}

//void task_soma(void){
//	while(1){
//		//pegar os parametros e passar para variaveis locais variavel1 e variavel2
//		//uint32 *i;
//		int var1, var2;
//		__asm__("ldr r4,[sp,0]		\n"
//				"add sp,0x04		\n"
//				"ldr %0, [r4,0x00]	\n"
//				"ldr %1, [r4,0x04] 	\n"
////				: "r4"
//				: "=r"(var1), "=r"(var2)
//				);
//
//		int essa_somas = soma(var1, var2);
//	//	task_join
//	// buscar proxima task ready
//	//task_pass();
//	}

//}

void task_ledon(void * args){
	while(1){
		gpio_setPin(PORT_F, 0);
		delay(500);
		task_pass(t_ledoff);
	}
}

void task_ledoff(void * args){
	while(1){
		gpio_clearPin(PORT_F, 0);
		delay(500);
		task_pass(t_ledon);
	}
}

int turn = 0;
void PortF_INT(){
	delay(1000 );
	nvic_clearPending(PORTF_IRQ);
	gpio_clearInt(PORT_F, 1);
	if(turn){
		gpio_clearPin(PORT_F, 0);
		turn = 0;
	} else {
		gpio_setPin(PORT_F, 0);
		turn = 1;
	}
}

int main(void) {
	gpio_enable(PORT_F);
	gpio_setPinOutput(PORT_F, 0);
	gpio_enableDigital(PORT_F, 0);

	gpio_setPinInput(PORT_F, 1);
	gpio_setPullUp(PORT_F, 1, 1);
	gpio_setIntSense(PORT_F, 1, SENSE_EDGE);
	gpio_setIntEvent(PORT_F, 1, FALLING_EDGE);
	gpio_enableInt(PORT_F, 1);
	gpio_enableDigital(PORT_F, 1);

	nvic_enable(PORTF_IRQ);

	//
	//int i[2];
	//i[0] = 3;
	//i[1]= 5;

	task_init();

	tid_ledon = task_create(task_ledon,0);
	tid_ledoff = task_create(task_ledoff,0);
	task_pass(tid_ledon);
	
	//uint32 soma1 = task_create(task_soma,i);
	//uint32 soma2 = task_create(task_soma,0);
	//task_pass(soma1);

	while(1){
		//gpio_setPin(PORT_F, 0);
		//delay(MS_DELAY);
		//gpio_clearPin(PORT_F, 0);
		//delay(MS_DELAY);
	}
}
