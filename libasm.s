	.equ	  SYS_REGS,   0x400FE000
	.equ	  PORTF_BASE, 0x40025000
    .syntax unified
    .thumb
# -------------------------------------
# void delay(int n)
# -------------------------------------
.global delay
delay: 
	movw  r1, #2664
delay_l0:
	subs r1, r1, #1
	bne	delay_l0
	subs r0, r0, #1
	bne  delay
	mov pc, lr

# -------------------------------------
# void init_gpio()
# -------------------------------------
.global init_gpio
init_gpio:
	SUB sp, sp, #4 
	STR lr, [sp, #0]
	ldr  r0, =SYS_REGS
	mov  r1, #32
	str  r1, [r0, 0x108]
	mov	 r0, #1
	bl   delay
	ldr  r0, =PORTF_BASE
	mov  r1, #1
	str  r1, [r0, 0x400]
	str  r1, [r0, 0x51C]
	LDR lr, [sp,#0] 
    ADD sp, sp, #4
	mov pc, lr
	
# -------------------------------------
# void led_on()
# -------------------------------------
.global led_on
led_on:
	ldr  r1, =PORTF_BASE
	mov  r2, #1
	str  r2, [r1, 4]
	mov  pc, lr

# -------------------------------------
# void led_off()
# -------------------------------------
.global led_off
led_off:
	ldr  r1, =PORTF_BASE
	mov  r2, #0
	str  r2, [r1, 4]
	mov  pc, lr

	
# -------------------------------------
# long long mult(long a, long b)
# -------------------------------------
.global mult
mult:
	sub  	sp, #4
	str		r4, [sp, #0]
	movs  	r4, #1
	mov		r2, r1
	movs  	r1, #0
	movs  	r3, #32
mult_l0:
	lsrs  	r0, r0, #1
	it    	cs
	addscs 	r1, r1, r2
	rrxs  	r1, r1
	it    	cs
	addcs 	r0, r0, r4, LSL #31
	subs  	r3, r3, #1
	bne  	mult_l0
	ldr 	r4, [sp, #0]
	add  	sp, #4
	mov  	pc, lr
	
# -------------------------------------
# int invert_bits(int byte)
# 
# r6	   - 0
# r5       - 4
# r4       - 8
# lr	   - 12
# char     - 16
# ret_val  - 20
# -------------------------------------
.global invert_bits
invert_bits:
	push {lr}
	push {r4}
	push {r5}
	push {r6}
	mov  r4, #32
	mov  r5, #0
	ldr  r6, [sp, #16]
ib0:lsl  r5, #1
	cmp  r6, #0
	bmi  ib1
	add  r5, #1
ib1:lsl  r6, #1
	subs r4, #1
	bne	 ib0
	str  r5, [sp, #20]
	pop  {r6}
	pop  {r5}
	pop  {r4}
	pop  {pc}
	