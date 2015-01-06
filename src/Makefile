OBJS = ipl.o setup.o startup.o video.o

kernel: $(OBJS)
	ld -nostdlib --traditional-format -T ipl.ls -Map kernel.map -o kernel.exe ipl.o setup.o startup.o video.o interrupt.o
	objcopy  -O binary kernel.exe kernel.bin
	dd if=/dev/zero of=fd.img count=2880
	dd if=kernel.bin of=fd.img conv=notrunc
	
clean:
	rm -f fd.img ipl.bin ipl.exe $(OBJS)

%.o:%.S
	gcc -g -g3 -gdwarf-2 -ffreestanding -fno-common -fno-builtin -fomit-frame-pointer -c -o $@ $<

%.o:%.c
	gcc -g -g3 -gdwarf-2 -fno-stack-protector -pipe -ffreestanding -fno-common -fno-builtin -fomit-frame-pointer -o $@ -c $<

ipl.o: ipl.S
setup.o: setup.S
