.thumb

.macro blh to,reg=r4
	push {\reg}
	ldr \reg,=\to
	mov r14,\reg
	pop {\reg}
	.short 0xF800
.endm

.global	MMB_DrawStatusFix
.type 	MMB_DrawStatusFix, function

@ hack from 808C392
MMB_DrawStatusFix:
	mov		r6, r1
	
	mov		r0, r1
	blh		GetUnitStatusIndex
	
	cmp		r0, #0
	beq		.L0_Return
	
	
	blh		GetStatusMiniBoxGfx
	
	@ 0x808C421
	ldr		r1, =#0x6002DE0
	mov		r2, #0x28
	blh		CpuFastSet
	
	ldr		r4, =#0x16F
	strh	r4,[r5]
	
	add		r4, #1
	strh	r4,[r5, #2]
	
	add		r4, #1
	strh	r4,[r5, #4]
	
	add		r4, #1
	strh	r4,[r5, #6]
	
	add		r4, #1
	strh	r4,[r5, #8]
	
	mov		r0, #0
	strh	r0,[r5, #10]
	
	mov		r0, r6 @ unit
	blh		GetUnitStatusDura
	
	ldr		r1, =#0x1128
	add		r0, r1
	strh	r0,[r5, #0xC]
	

	.L0_Return:
	pop		{r4-r6, pc}

.align
.ltorg


