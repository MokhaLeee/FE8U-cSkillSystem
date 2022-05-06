.thumb

.macro blh to,reg=r4
	push {\reg}
	ldr \reg,=\to
	mov r14,\reg
	pop {\reg}
	.short 0xF800
.endm

.global AsmBksel_DrawMore
.type AsmBksel_DrawMore, function

@ ORG 8036D04
AsmBksel_DrawMore:
	
	mov		r0, r4
	blh		cBksel_DrawMore
	
	pop		{r4}
	pop		{r0}
	bx		r0
	