#include "i386.h"
#include "video.h"
#include "interrupt.h"


extern void startup();
void startup() {
	unsigned short *video = (unsigned short *)0xb8000;
	unsigned char *str = "hello\r\n";
	unsigned char c;

	struct video_ v;
	init(&v);
	puts(&v,str);
	
	init_interrupts();
	puts(&v, "end\n");

	while(1) {
		hlt();
	}
}


void init_bss()
{


}
