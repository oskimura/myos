.text
.code16

.globl reset_disk
.globl read_disk_sector


reset_disk:
	xor	%al,	%al
	xor	%ah,	%ah
	int	$0x13
	ret

# read disk sector
#	params:
#		es:di = dest buffer address
#		si = source sector no (0 - 2879)
#		dl = drive no
#	returns:
#		al = error code. 0 if succeeded.
read_disk_sector:
	# save drive no
	pushw	%dx
	xorw	%dx, %dx
	movw	%si, %ax
	
	# logical sector to track no
	movb	$fd_sector_per_track, %dl
	divb	%dl
	
	# track no
	movb	%al, %ch
	shrb	$0x01, %ch
	
	# head no
	jnc		head_0
	mov		$0x01, %dh
head_0:
	
	# sector no
	movb	%ah, %cl
	incb	%cl
	
	# dest buffer
	movw	%di, %bx
	
	# drive no
	popw	%ax
	movb	%al, %dl
	
	# sector count
	movb	$0x01, %al
	
	# read command
	movb	$0x02, %ah
	
	# execute
	int		$0x13
	
	ret
