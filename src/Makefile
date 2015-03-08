OBJS =  head.o startup.o video.o interrupt.o  segment.o timer.o

kernel: $(OBJS)
	ld -nostdlib --traditional-format -Ttext=0x100000 -Map kernel.map --oformat elf32-i386 -o kernel.exe   $(OBJS)

clean:
	rm -f fd.img ipl.bin ipl.exe $(OBJS)

%.o:%.S
	gcc -g -g3 -gdwarf-2 -ffreestanding -fno-common -fno-builtin -fomit-frame-pointer -c -o $@ $<

%.o:%.c
	gcc -g -g3 -gdwarf-2 -fno-stack-protector -pipe -ffreestanding -fno-common -fno-builtin -fomit-frame-pointer -o $@ -c $<

ipl.o: ipl.S
setup.o: setup.S
head.o: head.S