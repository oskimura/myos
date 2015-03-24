OBJS =  head.o startup.o video.o interrupt.o  segment.o timer.o interrupt_functions.o mm.o

kernel: $(OBJS)
	ld -nostdlib --traditional-format -T link.ls -Map kernel.map --oformat elf32-i386 -o kernel.exe   $(OBJS)

clean:
	rm -f fd.img ipl.bin ipl.exe $(OBJS)

%.o:%.S
	gcc -g -g3 -gdwarf-2 -ffreestanding -fno-common -fno-builtin -fomit-frame-pointer -c -o $@ $<

%.o:%.c
	gcc -g -g3 -gdwarf-2 -fno-stack-protector -pipe -ffreestanding -fno-common -fno-builtin -fomit-frame-pointer -o $@ -c $<

ipl.o: ipl.S
setup.o: setup.S
head.o: head.S