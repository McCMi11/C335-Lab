	.text
	.syntax unified
	.thumb
	.global	fib	
	.type fib, %function
fib:
	push {r4-r7}
	// start my code
	movs r7, r0
	cmp r0, #0
	beq .END
	cmp r0, #1
	beq .END
	// set up vars
	// i = r3
	// prev1 = r6
	// prev2 = r5
	// val = r7
	movs r3, #0
	movs r6, #0
	movs r5, #1
	movs r7, #0
	// subtract 2 from num
	.ELSE:
	adds r7, r5, r6
	movs r6, r5
	movs r5, r7
	subs r0, #1
	cmp r0, #1
	beq .END
	bal .ELSE
	.END:
	movs r0, r7
	// end my code
	pop {r4-r7}
	bx      lr
