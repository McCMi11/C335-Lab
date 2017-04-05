	.text
	.syntax unified
	.thumb
	.global	ab	
	.type ab, %function
ab:
	push {r4-r7}
	movs r7, #0
	subs r6, r7, r0 // 0 - input = -input
	blt .END
	movs r0, r6
	.END:
	pop {r4-r7}
	bx	lr
