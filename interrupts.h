#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"

#define NVIC_BASE		0xE000E000
#define NVICREG_EN		(NVIC_BASE+0x100)
#define NVICREG_DIS		(NVIC_BASE+0x180)
#define NVICREG_PEND	(NVIC_BASE+0x200)
#define NVICREG_UNPEND	(NVIC_BASE+0x280)
#define NVICREG_ACTIVE	(NVIC_BASE+0x300)
#define NVICREG_PRIO	(NVIC_BASE+0x400)
#define NVICREG_SWTRIG	(NVIC_BASE+0xF00)

void nvic_enable(uint32 IRQ);
void nvic_disable(uint32 IRQ);
void nvic_setPending(uint32 IRQ);
void nvic_clearPending(uint32 IRQ);
bool nvic_active(uint32 IRQ);
uint32 nvic_getPriority(uint32 IRQ);
void nvic_setPriority(uint32 IRQ, uint32 prio);

#endif
