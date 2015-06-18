#ifndef __GPIO_H
#define __GPIO_H

#include "types.h"
#include "system.h"

#define PORTA_IRQ	0
#define PORTB_IRQ	1
#define PORTC_IRQ	2
#define PORTD_IRQ	3
#define PORTE_IRQ	4
#define PORTF_IRQ	30
#define PORTG_IRQ	31

typedef enum gpioport {
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_G
} gpioport_t;

typedef enum gpiosense {
	SENSE_EDGE  = 0,
	SENSE_LEVEL = 1
} gpiosense_t;

typedef enum gpioevent {
	FALLING_EDGE  = 0,
	RISING_EDGE   = 1,
	LOW_LEVEL     = 0,
	HIGH_LEVEL    = 1
} gpioevent_t;

typedef struct gpioregs {
	uint32 data[256];
	uint32 dir;
	uint32 intSense;
	uint32 intBothEdges;
	uint32 intEvent;
	uint32 intMask;
	uint32 intRawStatus;
	uint32 intMskStatus;
	uint32 intClear;
	uint32 afsel;
} gpioregs_t;

typedef struct gpiopadctrl {
	uint32	dr2r;
	uint32  dr4r;
	uint32  dr8r;
	uint32  openDrain;
	uint32  pullUp;
	uint32  pullDown;
	uint32  slewRate;
	uint32  digitalEn;
	uint32  lock;
	uint32  commit;
} gpiopadctrl_t;

#define SYSCTRL_RCGC2 0x400FE108
#define PORT_A_ADDR	  0x40004000
#define PORT_B_ADDR	  0x40005000
#define PORT_C_ADDR	  0x40006000
#define PORT_D_ADDR	  0x40007000
#define PORT_E_ADDR	  0x40024000
#define PORT_F_ADDR	  0x40025000
#define PORT_G_ADDR	  0x40026000
#define PAD_OFFSET       0x500

void gpio_enable(gpioport_t port);
void gpio_disable(gpioport_t port);

void gpio_setPin(gpioport_t port, int pin);
void gpio_clearPin(gpioport_t port, int pin);
uint8 gpio_readPort(gpioport_t port);
void gpio_writePort(gpioport_t port, uint8 data);

void gpio_setPinOutput(gpioport_t port, int pin);
void gpio_setPinInput(gpioport_t port, int pin);
void gpio_setPullUp(gpioport_t port, int pin, bool state);
void gpio_setPullDown(gpioport_t port, int pin, bool state);

void gpio_setIntSense(gpioport_t port, int pin, gpiosense_t sense);
void gpio_setIntEvent(gpioport_t port, int pin, gpioevent_t event);
void gpio_setIntBothEdges(gpioport_t port, int pin, bool status);
void gpio_enableInt(gpioport_t port, int pin);
void gpio_disableInt(gpioport_t port, int pin);
bool gpio_intStatus(gpioport_t port, int pin);
void gpio_clearInt(gpioport_t port, int pin);

void gpio_enableDigital(gpioport_t port, int pin);
void gpio_disableDigital(gpioport_t port, int pin);

#endif
