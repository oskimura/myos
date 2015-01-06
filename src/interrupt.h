#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "types.h"

#define IDT_ENTRIES 256

typedef struct idt_entry_ 
{
	word offset_low;
	word selector;
	byte reserved;
	byte attribute;
	word offset_high;
} __attribute__((__packed__)) idt_entry;

typedef struct idt_ptr_
{
	word limit;
	dword base;
}__attribute__((__packed__)) idt_ptr;

void init_interrupts();

#endif
