/*
 * main.c
 *
 *
 */
#include "system.h"
#include "interrupts.h"
#include "gpio.h"


#define MS_DELAY 1000

int soma(int a, int b){
	int res;
	int res2;
	__asm__("add %0, %2, %3	\n"
			"add r4, %0, %0 \n"
			"add %2, r4, r4 \n"
			: "=r"(res), "=r"(res2)
			: "r"(a), "r"(b)
			: "r4"
		   );
	return res;
}

void task_soma(void){
	//pegar os parametros e passar para variaveis locais variavel1 e variavel2
	int soma(variavel1, variavel2);

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

	task_create(task_soma,/*struct*/);
	task_init();

	while(1){
		//gpio_setPin(PORT_F, 0);
		//delay(MS_DELAY);
		//gpio_clearPin(PORT_F, 0);
		//delay(MS_DELAY);
	}
}
