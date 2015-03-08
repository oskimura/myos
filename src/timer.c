#include "i386.h"

#define	DEF_PIT_CLOCK 1193181.67	


void set_pit_counter(int freq, unsigned char counter, unsigned char mode) 
{
  unsigned short count;
  unsigned char command;
  
  count = (unsigned short) (DEF_PIT_CLOCK/freq);
  command = mode | 0x30 |counter;
  outb(0x0043,command);

  outb(0x0040,(count & 0xff));
  outb(0x0040,((count>>8) & 0xff));
}

void init_pit()
{
  set_pit_counter(100,0x00,0x06);
}
