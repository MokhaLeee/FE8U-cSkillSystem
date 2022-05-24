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






.global	PrePhaseRenewalHack
.type 	PrePhaseRenewalHack, function

PrePhaseRenewalHack:

	@ hacked function, MakeTerrainHealTargetList
	@ ORG 8025948
	
	ldrb	r6,[r0]

	@ r0 = struct Unit*, r1 = terrain type
	mov		r0, r5
	mov		r1, r6
	blh		JudgePrePhaseRenewal
	
	ldr		r0, =0x802598F
	bx		r0

