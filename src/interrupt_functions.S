.text
.code32

.global INTERRUPT_NOTHING
INTERRUPT_NOTHING:
	pusha
	push 	%ds
	push 	%es
	push 	%fs
	push 	%gs
	
	pop	%gs
	pop	%fs
	pop	%es
	pop	%ds
	popa
	iret

.global INTERRUPT_KEYBOARD
INTERRUPT_KEYBOARD:
	pusha
	push 	%ds
	push 	%es
	push 	%fs
	push 	%gs

	movb	'A',	%al
	movb	%al,	0xb8000

	movb	$0x20,%al	
	outb	%al,$0x20

	pop	%gs
	pop	%fs
	pop	%es
	pop	%ds
	popa
	iret
