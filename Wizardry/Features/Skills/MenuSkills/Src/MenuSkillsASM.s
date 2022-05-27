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
.global	SummonUsabilityHackASM
.type 	SummonUsabilityHackASM, function

SummonUsabilityHackASM:

	@ hacked function, SummonCommandUsability
	@ ORG 80243DC
	
	blh		CheckSummonUsabilityCore
	cmp		r0, #1
	beq		.L0_Summon
	b		.L1_NoSummon

	.L0_Summon:
	ldr		r2,[r5]
	ldr		r0, =#0x80243FD
	bx		r0

	.L1_NoSummon:
	ldr		r0, =#0x802445B
	bx		r0



.align
.ltorg	
.global	StealUsabilityHackASM
.type 	StealUsabilityHackASM, function

StealUsabilityHackASM:
	@ hacked function, StealCommandUsability
	@ ORG 8024190
	
	blh		CheckStealUsabilityCore
	cmp		r0, #1
	beq		.L2_Steal
	b		.L3_NoSteal

	.L2_Steal:
	ldr		r2,[r4]
	ldr		r0, =#0x80241AF
	bx		r0

	.L3_NoSteal:
	ldr		r0, =#0x80241BD
	bx		r0
	


.align
.ltorg	
.global	PickUsabilityHackASM
.type 	PickUsabilityHackASM, function

PickUsabilityHackASM:
	@ hacked function, PickCommandUsability
	@ ORG 23E8C
	
	blh		CheckPickUsabilityCore
	cmp		r0, #1
	beq		.L4_Pick
	b		.L5_NoPick

	.L4_Pick:
	ldr		r2, =gActiveUnit
	ldr		r2,[r2]
	ldr		r0, =#0x8023E9D
	bx		r0

	.L5_NoPick:
	ldr		r0, =#0x8023E95
	bx		r0



.align
.ltorg	
.global	StealAiUsabilityHackASM
.type 	StealAiUsabilityHackASM, function

StealAiUsabilityHackASM:
	@ hacked function
	@ ORG 803D4C4
	
	push	{r3}
	blh		CheckStealUsabilityCore
	cmp		r0, #1
	beq		.L6_Steal
	b		.L7_NoSteal

	.L6_Steal:
	pop		{r3}
	ldr		r0, =#0x803D4D7
	bx		r0

	.L7_NoSteal:
	pop		{r3}
	ldr		r0, =#0x803D4FB
	bx		r0
		