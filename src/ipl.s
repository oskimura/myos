# ipl.s

.globl fd_sector_per_track

boot_begin = 0x7c00
ipl_size = 0x200
fd_sector_per_track = 0x12

kernel_begin_sector = 0x01
read_kernel_es_offset = 0x1000

fd_sector_length = 512


# generate real mode code
.code16

    jmp begin
    nop

# BPB
name:           .ascii  "Name    "
sector_size:    .word   0x0200
cluster_size:   .byte   0x01
fat_pos:        .word   0x0001
fat_cnt:        .byte   0x02
root_size:      .word   0x00e0
sector_cnt:     .word   0x0b40
media_type:     .byte   0xf0
fat_size:       .word   0x0009
sector_cnt_pt:  .word   0x0012
head_cnt:       .word   0x0002
bpb_pos:        .long   0x0000
sector_cnt_l:   .long   0x00000b40
drive_no:       .byte   0x00
reserved:       .byte   0x00
ext_boot_code:  .byte   0x29
volume_serial:  .long   0xffffffff
disk_name:      .ascii  "DISK       "
fat_name:       .ascii  "FAT12   "

	# boot begin
begin:
	# infinite loop
	# deny interrupt
	cli

	# setup registers	
	cld
	xorw	%ax,	%ax
	movw	%ax, 	%ss
	movw	%ax,	%es
	movw	%ax,	%fs

	movb	%dl, 	boot_drive

	movw	$_kernel_begin,	%ax
	movw	%ax,	%sp
	xor	%ax,	%ax

	movw	%ax,	%ds
	movw	$boot_begin,	%si

	movw 	%ax,	%es
	movw	$_kernel_begin,	%di

	movw	$(ipl_size / 2),	%cx

	rep	movsw

	ljmp	$0x0000,	$set_cs
set_cs:
	#show message
	movw	$BOOT_MSG,	%si
	call print

	#reset disk drive
	movb	boot_drive, %dl
	call	reset_disk
	jc	error

	#sucesse
	movw	$DISK_RESET_MSG,	%si
	call	print
# read kernel image from disk
	pushw	$0x00
	popw	%es
	xorw	%di,	%di
	movw	$ipl_end, %di
	movb	boot_drive, %dl
	movw	$kernel_begin_sector, %si


read_kernel:
	call	read_disk_sector
	jc	error
	addw	$fd_sector_length, %di
	jnc 	advance_read_kernel_sector
	movw	%es,	%ax
	addw	$read_kernel_es_offset,	%ax
	movw	%ax,	%es
advance_read_kernel_sector:
	incw	%si
	cmpw	$_kernel_end_sector, %si
	jb	read_kernel

#success
	movw	$DISK_READ_MSG,	%si
	call print
#jump to setup
	jmp	ipl_end
error:
	movw	$ERROR_MSG, %si
	call	print
error_end:
	jmp	error_end

end:
    jmp end
print:
	xorw	%bx,	%bx
	movb	$0x0e,	%ah
print_char:
	lodsb
	orb	%al,	%al
	jz	print_end
	int	$0x10
	jmp	print_char
print_end:
	ret

boot_drive:	.byte	0x00
BOOT_MSG: .string "Hello,World!\r\n"
DISK_RESET_MSG: .string "Succes reset!\r\n"
DISK_READ_MSG: .string "Succes read disk!\r\n"
ERROR_MSG: .string "Disk error!\r\n"


# boot signature.
. = 510
.short 0xaa55
ipl_end:
