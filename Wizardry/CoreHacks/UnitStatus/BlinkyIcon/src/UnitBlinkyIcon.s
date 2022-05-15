.thumb

.macro blh to,reg=r4
	push {\reg}
	ldr \reg,=\to
	mov r14,\reg
	pop {\reg}
	.short 0xF800
.endm


.global	BlinkyUnitStatusIcons
.type 	BlinkyUnitStatusIcons, function

@ from 0x80276C0
BlinkyUnitStatusIcons:
	lsl		r6, r7, #0x18
	
	mov		r0, r4
	blh		GetUnitStatusIndex
	
	ldr		r1, =BlinkyStatusIconJumpTable
	lsl		r0, #2
	add		r0, r1
	ldr		r0, [r0]
	cmp		r0, #0
	beq		.L1_NoIcon
	bx		r0
	
	.L1_NoIcon:
	ldr		r0, =0x80278A7
	bx		r0
	
	


.align
.ltorg

.global	CostumBlankyIcon_BuffStatus
.type 	CostumBlankyIcon_BuffStatus, function

CostumBlankyIcon_BuffStatus:
	mov		r0, r4
	blh		PutUnitStatusBuffIcon
	ldr		r1, =#0x80278A7
	bx		r1

.align
.ltorg







.global	CostumBlankyIcon_DeBuffStatus
.type 	CostumBlankyIcon_DeBuffStatus, function

CostumBlankyIcon_DeBuffStatus:
	mov		r0, r4
	blh		PutUnitStatusDeBuffIcon
	ldr		r1, =#0x80278A7
	bx		r1
	