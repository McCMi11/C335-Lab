	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	movs r7, 0
	subs r6, r7, r4
	bgt .END
	movs r4, r6
	.END:
	movs r0, r4
	pop {r4-r7}	
	bx	lr
