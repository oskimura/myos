#include "i386.h"
#include "video.h"

extern void startup();
void startup() {
	unsigned short *video = (unsigned short *)0xb8000;
	unsigned char *str = "hello\r\n";
	unsigned char c;

	struct video_ v;
	init(&v);
	puts(&v,str);
	
	while(1) {;}
}
