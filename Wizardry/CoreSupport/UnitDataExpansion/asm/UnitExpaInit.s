.thumb

.macro blh to,reg=r4
	push {\reg}
	ldr \reg,=\to
	mov r14,\reg
	pop {\reg}
	.short 0xF800
.endm

.type UnitExpaInit, function
.global UnitExpaInit

@ ORG $80A4178
UnitExpaInit:
	blh		ClearUnitsExpa
	add		sp, #4
	pop		{r3}
	mov		r8, r3
	pop		{r4- r7}
	pop		{r0}
	bx		r0
	
	
.align
.ltorg
	