.thumb

.macro blr reg=r4
	mov r14,\reg
	.short 0xF800
.endm

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


@Bx'd to from 3003D28
@This function sets the Z flag if the moving unit can cross the other unit's tile, either because they're either both allied/npcs or enemies, or because the mover has Pass

.global	PassHackASM
.type 	PassHackASM, function

PassHackASM:
	push  	{r0-r6,r14}
	
	@r7 is allegiance byte of unit on tile we are looking at
	ldrb  	r4,[r3,#0xA]  @allegiance byte of current unit
	eor   	r4,r7     
	
	@if non-zero, then one character is an enemy and one is not. If zero, the z flag is set
	mov   	r0,#0x80
	tst   	r0,r4
	beq   	GoBack
	
	ldrb  	r0,[r3,#0xA]
	blh		GetUnit
	
	ldr   	r1, =SKILLID_Pass
	mov		r2, #0xFF
	AND		r1, r1, r2
	
	ldr   	r2, =SkillTester
	ldr		r2,[r2]
	blr		r2
	
	cmp   	r0,#0x1     @set z flag if unit has Pass
	GoBack:
	pop   	{r0-r6}
	pop   	{r4}
	mov   	r14,r4
	ldr   	r4,GoBackAddress
	bx    	r4

.align
GoBackAddress:
.long 0x03003D34    @note that we need to switch back to arm

