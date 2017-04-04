	.text
	.syntax unified
	.thumb
	.global	gcd
	.type gcd, %function
gcd:
	push {r4-r7}
	movs r3, #0// stays 0
	movs r4, #1// stays 1
	movs r5, #0// int d
	.FWHILE: // while (!(a & 1) && !(b & 1))
	tst r0, r4
	bne .SWHILE
	tst r1, r4
	bne .SWHILE
	lsrs r0, #1
	lsrs r1, #1
	adds r5, #1
	bal .FWHILE
	.SWHILE: // while (a != b)
	cmp r0, r1
	beq .END
	// first if !(a & 1)
	tst r0, r4
	bne .SIF
	lsrs r0, #1
	bal .SWHILE
	.SIF: // if !(b & 1)
	tst r1, r4
	bne .TIF
	lsrs r1, #1
	bal .SWHILE
	.TIF: // if ( a > b)
	cmp r0, r1
	blt .ELSE
	subs r0, r0, r1
	lsrs r0, #1
	bal .SWHILE
	.ELSE: // ( a < b)
	subs r1, r1, r0
	lsrs r1, #1
	bal .SWHILE
	.END:
	lsls r0, r0, r5
	pop {r4-r7}
	bx	lr
