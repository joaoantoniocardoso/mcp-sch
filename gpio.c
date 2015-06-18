#include "gpio.h"

gpioregs_t 	  * gpio_regs[] = {
		(gpioregs_t*)PORT_A_ADDR,
		(gpioregs_t*)PORT_B_ADDR,
		(gpioregs_t*)PORT_C_ADDR,
		(gpioregs_t*)PORT_D_ADDR,
		(gpioregs_t*)PORT_E_ADDR,
		(gpioregs_t*)PORT_F_ADDR,
		(gpioregs_t*)PORT_G_ADDR
};

gpiopadctrl_t * gpio_padctrl[] = {
		(gpiopadctrl_t *)(PORT_A_ADDR+PAD_OFFSET),
		(gpiopadctrl_t *)(PORT_B_ADDR+PAD_OFFSET),
		(gpiopadctrl_t *)(PORT_C_ADDR+PAD_OFFSET),
		(gpiopadctrl_t *)(PORT_D_ADDR+PAD_OFFSET),
		(gpiopadctrl_t *)(PORT_E_ADDR+PAD_OFFSET),
		(gpiopadctrl_t *)(PORT_F_ADDR+PAD_OFFSET),
		(gpiopadctrl_t *)(PORT_G_ADDR+PAD_OFFSET)
};

void gpio_enable(gpioport_t port){
	*(uint32*)(SYSCTRL_RCGC2) |= 0x01 << port;
	delay2(10);
}

void gpio_disable(gpioport_t port){
	*(uint32*)(SYSCTRL_RCGC2) &= ~(0x01 << port);
	delay(10);
}

void gpio_setPin(gpioport_t port, int pin){
	gpio_regs[port]->data[0x01<<pin]=0xFF;
}

void gpio_clearPin(gpioport_t port, int pin){
	gpio_regs[port]->data[0x01<<pin]=0x00;
}

uint8 gpio_readPort(gpioport_t port){
	return (uint8)gpio_regs[port]->data[0xFF];
}
void gpio_writePort(gpioport_t port, uint8 data){
	gpio_regs[port]->data[0xFF] = (uint32)data;
}

void gpio_setPinOutput(gpioport_t port, int pin){
	gpio_regs[port]->dir |= (0x01 << pin);
}

void gpio_setPinInput(gpioport_t port, int pin){
	gpio_regs[port]->dir &= ~(0x01 << pin);
}

void gpio_setPullUp(gpioport_t port, int pin, bool state){
	if(state)
		gpio_padctrl[port]->pullUp |= (0x01 << pin);
	else
		gpio_padctrl[port]->pullUp &= ~(0x01 << pin);
}

void gpio_setPullDown(gpioport_t port, int pin, bool state){
	if(state)
		gpio_padctrl[port]->pullDown |= (0x01 << pin);
	else
		gpio_padctrl[port]->pullDown &= ~(0x01 << pin);
}

void gpio_setIntSense(gpioport_t port, int pin, gpiosense_t sense){
	if(sense)
		gpio_regs[port]->intSense |= (0x01 << pin);
	else
		gpio_regs[port]->intSense &= ~(0x01 << pin);
}

void gpio_setIntEvent(gpioport_t port, int pin, gpioevent_t event){
	if(event)
		gpio_regs[port]->intEvent |= (0x01 << pin);
	else
		gpio_regs[port]->intEvent &= ~(0x01 << pin);
}

void gpio_setIntBothEdges(gpioport_t port, int pin, bool status){
	if(status)
		gpio_regs[port]->intBothEdges |= (0x01 << pin);
	else
		gpio_regs[port]->intBothEdges &= ~(0x01 << pin);

}

void gpio_enableInt(gpioport_t port, int pin){
	gpio_regs[port]->intMask |= (0x01 << pin);
}

void gpio_disableInt(gpioport_t port, int pin){
	gpio_regs[port]->intMask &= ~(0x01 << pin);
}

bool gpio_intStatus(gpioport_t port, int pin){
	return (bool)(gpio_regs[port]->intMskStatus & (0x01 << pin));
}
void gpio_clearInt(gpioport_t port, int pin){
	gpio_regs[port]->intClear |= (0x01<<pin);
}

void gpio_enableDigital(gpioport_t port, int pin){
	gpio_padctrl[port]->digitalEn |= (0x01<<pin);
}


void gpio_disableDigital(gpioport_t port, int pin){
	gpio_padctrl[port]->digitalEn &= ~(0x01<<pin);
}


