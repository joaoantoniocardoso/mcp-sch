#include "interrupts.h"

void nvic_enable(uint32 IRQ){
	uint32 *regs = (uint32*)NVICREG_EN;
	regs[IRQ/32] = 0x01 << (IRQ%32);
}

void nvic_disable(uint32 IRQ){
	uint32 *regs = (uint32*)NVICREG_DIS;
	regs[IRQ/32] = 0x01 << (IRQ%32);
}

void nvic_setPending(uint32 IRQ){
	uint32 *regs = (uint32*)NVICREG_PEND;
	regs[IRQ/32] = 0x01 << (IRQ%32);
}

void nvic_clearPending(uint32 IRQ){
	uint32 *regs = (uint32*)NVICREG_UNPEND;
	regs[IRQ/32] = 0x01 << (IRQ%32);
}

bool nvic_active(uint32 IRQ){
	uint32 *regs = (uint32*)NVICREG_ACTIVE;
	if(regs[IRQ/32] & (0x01 << (IRQ%32))){
		return true;
	} else {
		return false;
	}
}

uint32 nvic_getPriority(uint32 IRQ){
	uint32 *regs = (uint32*)NVICREG_PRIO;
	return ((regs[IRQ/4] >> (((IRQ%4)*8)+5)) & 0x07);
}

void nvic_setPriority(uint32 IRQ, uint32 prio){
	uint32 *regs = (uint32*)NVICREG_PRIO;
	regs[IRQ/4] &= ((0x07) << (IRQ%4*8+5));
	regs[IRQ/4] |= ((prio & 0x07) << (IRQ%4*8+5));
}
