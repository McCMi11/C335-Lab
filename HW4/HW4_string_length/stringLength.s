	.text
	.syntax unified
	.thumb
	.global	stringLength
	.type stringLength, %function
stringLength:
	push {r4-r7}
	movs r1, #0
	.LEN:
	ldrb r3, [r0, r1]
	cmp r3, #0
	beq .END
	adds r1, #1
	bal .LEN
	.END:
	mov r0, r1
	pop {r4-r7}
	bx	lr
