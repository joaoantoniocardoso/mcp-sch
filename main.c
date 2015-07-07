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

uint32 tid_ledoff, tid_ledon;

void task_ledon(void * args){
	while(1){
		gpio_setPin(PORT_F, 0);
		delay(500);
		//task_pass(tid_ledoff);
		task_yield();
	}
}

void task_ledoff(void * args){
	int i = 0;
	while(1){
		gpio_clearPin(PORT_F, 0);
		delay(500);
		//task_pass(0);
		task_yield();
		i++;
		if (i==4){
			i= 0;
			task_finish(0);
			//task_suspend();
		}
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
	int i = 0;
	int j;
	gpio_enable(PORT_F);
	gpio_setPinOutput(PORT_F, 0);
	gpio_enableDigital(PORT_F, 0);

//	gpio_setPinInput(PORT_F, 1);
//	gpio_setPullUp(PORT_F, 1, 1);
//	gpio_setIntSense(PORT_F, 1, SENSE_EDGE);
//	gpio_setIntEvent(PORT_F, 1, FALLING_EDGE);
//	gpio_enableInt(PORT_F, 1);
//	gpio_enableDigital(PORT_F, 1);

//	nvic_enable(PORTF_IRQ);

	task_init();

	tid_ledon = task_create(task_ledon,0);
	tid_ledoff = task_create(task_ledoff,0);
	
	while(1){
		i++;
		delay(1000);
		//task_pass(tid_ledon);
		task_yield();
		if (i==10){
			i= 0;
			task_resume(tid_ledoff);
		}
	}
	return 0;
}
