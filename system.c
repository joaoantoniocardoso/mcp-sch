#include "system.h"

void delay(uint32 milli) __attribute__((naked));
void delay(uint32 milli) {
__asm__("	 movw  r1, #2664	\n"
        "delay_l0:				\n"
	    "    subs r1, r1, #1	\n"
	    "    bne  delay_l0		\n"
	    "    subs r0, r0, #1	\n"
	    "    bne  delay			\n"
	    "    mov  pc, lr		\n"
	   );
}
void delay2(uint32 milli) {
	uint32 tmp;
	while(milli--){
		tmp = 2664;
		while(tmp--);
	}
}
