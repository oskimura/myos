#define ASM  1
.file "setup.s"
.global setup
stack_begin = 0x1000
.code16
.text

setup:
	cli
	lgdt	gdtr
	movl	%cr0,	%eax
	orl	$0x01,	%eax
	movl	%eax,	%cr0

	jmp	reset_pipeline
reset_pipeline:
	ljmp	$0x08,	$set_cs1
set_cs1:

.code32
	movw	$0x10,	%ax
	movw	%ax,	%ds
	movw	%ax,	%es
	movw	%ax,	%ss
	
	movl	$stack_begin,	%esp
	jmp 	entry
#multiboot_header:
#	.align 4
#	.long MULTI_HEADER_MAGIC
#	.long MULTI_HEADER_FLAGS
#        .long MULTI_HEADER_CHECKSUM

entry:
	 call	startup
loop:
	hlt
	jmp 	loop

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

gdtr:
gdtr_limit: .word gdt_end - gdt -1
gdtr_base: .long gdt

.align 8
gdt:

gdt_null:
.word	0x00
.word	0x00
.byte	0x00
.byte	0x00
.byte	0x00
.byte	0x00

gdt_kernel_cs:
.word	0xffff
.word	0x00
.byte	0x00
.byte	0x98
.byte	0xdf
.byte 	0x00


gdt_kernel_ds:
.word	0xffff
.word	0x00
.byte	0x00
.byte 	0x92
.byte	0xdf
.byte 	0x00

gdt_end:
