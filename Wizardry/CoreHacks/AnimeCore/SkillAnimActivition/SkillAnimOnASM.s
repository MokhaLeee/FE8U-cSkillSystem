.thumb

.macro blh to,reg=r4
	push {\reg}
	ldr \reg,=\to
	mov r14,\reg
	pop {\reg}
	.short 0xF800
.endm

.global SkillActivationAnims
.type SkillActivationAnims, function

@ hack from 0x8059048
SkillActivationAnims:
	push  {r4-r7}
	
	@ r7 = struct Anim
	mov		r0, r7
	blh		cSkillActivationAnims
	
	lsl		r0, #2
	ldr		r1, =SkillActivationJumpTable
	add		r0, r1
	ldr		r0,[r0]
	bx		r0

	SkillActivationJumpTable:
		.word End + 1
		.word NoAnim + 1
		.word NoAnim2 + 1
	
	End:
	pop 	 {r4-r7}
	ldr 	r0, =0x8059141
	bx  	r0

	NoAnim:
	pop  	{r4-r7}
	ldr  	r0, =0x80590D3
	bx   	r0

	NoAnim2:
	pop  	{r4-r7}
	ldr 	 r0, =0x8059675
	bx  	r0
	