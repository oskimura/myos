.file "setup.s"
stack_begin = 0x1000
.code16
.text

begin:
	cli
	lgdt	gdtr
	movl	%cr0,	%eax
	orl	$0x01,	%eax
	movl	%eax,	%cr0

	jmp	reset_pipeline
reset_pipeline:
	ljmp	$0x08,	$set_cs
set_cs:

.code32
	movw	$0x10,	%ax
	movw	%ax,	%ds
	movw	%ax,	%es
	movw	%ax,	%ss
	
	movl	$stack_begin,	%esp

	#hlt
	call startup

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
