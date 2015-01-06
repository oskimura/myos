#include "types.h"
#include "i386.h"
#include "mem.h"
#include "interrupt.h"

idt_entry idt[IDT_ENTRIES];
idt_ptr ptr;

extern void INTERRUPT_KEYBOARD;
extern void INTERRUPT_NOTHING;


//void init_interrupt()
void init_interrupts()
{
	int i;
	disable();
	// reprogram PCI
	// initialize Command Word
	// ICW1 initilization for mask
	outb(0x20,0x11);
	outb(0xa0,0x11);
	// ICW2 specify interrupt numbers
	outb(0x21,0x20);//PIC1 : 0x20-27
	outb(0xa1,0x28);//PIC  : 0x28-2f
	// ICW3 setu pin wired to master/slaves
	outb(0x21,0x4);
	outb(0xa1,0x2);
	// ICW4 set addtional option
	outb(0x21,0x1);
	outb(0xa1,0x1);
	// Mask interrupts
	outb(0x21,0xfd);
	outb(0xa1,0xff);

	for (i=0;i<IDT_ENTRIES;i++) {
		idt[i].offset_low = (dword)&INTERRUPT_NOTHING;
		idt[i].offset_high = (dword) &INTERRUPT_NOTHING >> 16;
		idt[i].selector = KERNEL_CODE;
		idt[i].reserved = 0;
		idt[i].attribute = INT_GATE;
	}
	// set keybord
	idt[0x21].offset_low  = (dword)&INTERRUPT_KEYBOARD;
	idt[0x21].offset_high  = (dword)&INTERRUPT_KEYBOARD >> 16;
	idt[0x21].selector  = KERNEL_CODE;
	idt[0x21].reserved  = 0;
	idt[0x21].attribute = INT_GATE;


	ptr.limit = sizeof(idt_entry) * IDT_ENTRIES -1;	
	ptr.base = (dword)&idt[0];
	__asm__ __volatile__("lidt ptr");
	enable();
	return;
}
