	.text
	.syntax unified
	.thumb
	.global	regName	
	.type regName, %function
regName:
	push {r4-r7}
	cmp r0, 15
	bgt .ERR
	ldr r1, .labA   @ load contents of memory at labA (address of global_name)
	lsls r0, #2
	ldr r0, [r1, r0]
	bal .END
.ERR:
	movs r0, #0

.END:
	pop {r4-r7}
	bx	lr
	.align 2
.labA:
    .word names
