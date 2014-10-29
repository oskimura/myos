OBJS = ipl.o setup.o

kernel: ipl.o setup.o ipl.ls
	ld -T ipl.ls -o kernel.exe ipl.o setup.o
	objcopy -S -O binary kernel.exe kernel.bin
	dd if=/dev/zero of=fd.img count=2880
	dd if=kernel.bin of=fd.img conv=notrunc
	
clean:
	-rm -f fd.img ipl.bin ipl.exe $(OBJS)

.s.o:
	as -o $@ $^

ipl.o: ipl.s
setup.o: setup.s
