.thumb

.thumb

.macro blh to,reg=r4
	push {\reg}
	ldr \reg,=\to
	mov r14,\reg
	pop {\reg}
	.short 0xF800
.endm

.macro SET_FUNC name, value
	.global \name
	.type   \name, function
	.set    \name, \value
.endm
.macro SET_DATA name, value
	.global \name
	.type   \name, object
	.set    \name, \value
.endm






.align
.ltorg
.global	PromoDispMainLoopHackASM
.type 	PromoDispMainLoopHackASM, function

PromoDispMainLoopHackASM:
	@ ORG 80CD0A8
	mov		r0, r9
	blh		PromoDispMainLoopHackCore
	
	
	@ config r4: charId, and r6: classId
	ldr		r1, =gGenericBuffer
	ldrb	r4,[r1]
	ldrb	r6,[r1, #1]
	
	@ this is a palette index?
	ldr		r1, =#0xFFFF
	str		r1,[sp, #0x58]
	
	ldr		r1, =#0x80CD105
	bx		r1





