/*
 * main.c
 */
extern void delay(int milli);
extern void init_gpio();
extern void led_on();
extern void led_off();
extern long long mult(long a, long b);

int turn = 1;
void SysTick_INT(void){
	if(turn){
		led_on();
		turn = 0;
	} else {
		led_off();
		turn = 1;
	}
}

typedef struct SysTick {
	unsigned int ctrl_stat;
	unsigned int reload;
	unsigned int current;
	unsigned int calibration;
} tSysTick;

tSysTick * st_regs;

#define MS_DELAY 1000

int main(void) {

	init_gpio();
	st_regs = (tSysTick *)(0xE000E010);
	st_regs->ctrl_stat = 0;
	st_regs->reload = 8000000;
	st_regs->current = 0;
	st_regs->ctrl_stat = 0x07;

	while(1){

	}
	/*
	long long res;
	long a = 4;
	long b = 1000000000;
	res = mult(a,b);

	init_gpio();
	while(1){
		led_on();
		delay(MS_DELAY);
		led_off();
		delay(MS_DELAY);
	}

	return (int)res;
	*/
}


int hm_01(int a){
	return a+10;
}

int hm_02(int a, int b){
	return a + b;
}

long long hm_03(long a, long b){
	return a*b;
}

long long hm_04(long a, long b){
	return (long long)a*(long long)b;
}
