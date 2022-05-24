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






.global	CantoHackASM
.type 	CantoHackASM, function

CantoHackASM:
	@ ORG 801D248
	ldr		r4, =gActiveUnit
	
	@ r0 = ProcPtr, r1 = struct Unit*
	ldr		r1, [r4]
	blh		CantoHackCore
	
	cmp		r0, #1
	beq		canto
	
	b		no_canto

	canto:
	ldr		r1, =0x801D2A9
	bx		r1

	no_canto:
	ldr		r0, =0x801D299
	bx		r0
	
	