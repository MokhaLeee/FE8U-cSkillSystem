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
.global	EkrSkill_BgConfigHackASM
.type 	EkrSkill_BgConfigHackASM, function

EkrSkill_BgConfigHackASM:
	blh		EkrSkill_BgConfigHack
	
	ldr		r0, =0x806E579
	bx		r0

.align
.ltorg

