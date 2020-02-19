#include "segment.h"

segment_descriptor gdt[NUM_GDT];
gdtr gdt_;

extern void init_gdtr();
void __inline__ init_gdtr()
{
  gdt[0].limit_low = 0;
  gdt[0].base_addr_low = 0;
  gdt[0].base_addr_mid = 0 ;
  gdt[0].flags = 0;
  gdt[0].base_addr_high = 0;

  gdt[1].limit_low = 0xffff;
  gdt[1].base_addr_low = 0x00;
  gdt[1].base_addr_mid = 0x00;
  gdt[1].flags = 0xcf9a;
  gdt[1].base_addr_high = 0x00;
  
  gdt[2].limit_low = 0xffff;
  gdt[2].base_addr_low = 0x00;
  gdt[2].base_addr_mid = 0x00;
  gdt[2].flags = 0xcf92;
  gdt[2].base_addr_high = 0x00;


  
  gdt_.base = gdt;
  gdt_.size = NUM_GDT * sizeof(segment_descriptor);


  __asm__ __volatile__ ("lgdt gdt_ \t\n"
			"ljmp	$0x08,	$reset_pipeline\t\n"
			"reset_pipeline:\t\n"
			"movw	$0x10,	%ax\t\n"
			"movw	%ax,	%ds\t\n"
			"movw	%ax,	%es\t\n"
			"movw	%ax,	%ss\t\n"
			);
}
