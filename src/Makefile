OBJS = ipl.o setup.o startup.o video.o

kernel: $(OBJS)
	ld -T ipl.ls -o kernel.exe ipl.o setup.o startup.o video.o
	objcopy -S -O binary kernel.exe kernel.bin
	dd if=/dev/zero of=fd.img count=2880
	dd if=kernel.bin of=fd.img conv=notrunc
	
clean:
	-rm -f fd.img ipl.bin ipl.exe $(OBJS)

%.o:%s
	as -o $@ $<

%.o:%.c
	gcc -o $@ -c $<

ipl.o: ipl.s
setup.o: setup.s
