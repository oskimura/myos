#include "i386.h"
#include "mem.h"
#include "video.h"

void set_cur(video *v)
{
	outb(v->crt_port,15);
	outb(v->crt_port+1,v->cur_pos);
	outb(v->crt_port,14);
	outb(v->crt_port+1,v->cur_pos>>8);
}

void scroll_up(video *v) {
	memcpy((void*)(v->vram),
		(void*)(v->vram)+v->crt_width*2,
		v->crt_width*(v->crt_height-1)*2);
	memsetw((void*)(v->vram)+ v->crt_width*2*(v->crt_width-1),
		BLANK,
		v->crt_width);
	v->cur_pos -= v->crt_width;
	set_cur(v);
}

void clrscr(video *v)
{
	memsetw((void*)(v->vram),
		BLANK,
		v->crt_height * v->crt_width);
	v->cur_pos = 0;
	set_cur(v);
}

void putchar(video *v, char c)
{
	switch (c) {
	case '\r':
		v->cur_pos -= v->cur_pos % v->crt_width;
		break;
	case '\n':
		v->cur_pos += (v->crt_width - (v->cur_pos % v->crt_width));
		break;
	case '\b':
		if(v->cur_pos>0) {
			(v->vram)[--(v->cur_pos)] = ((0x0f)<<8)|0x20;
		}
	case 't':
		v->cur_pos += 8;
	default:
		(v->vram)[(v->cur_pos)++] = ((0x0f)<<8)|c;
	}
	if(v->cur_pos >= v->crt_width*v->crt_height) {
		scroll_up(v);
	}
	set_cur(v);
}

void init(video *v)
{
	v->crt_port = 0x3D4;
	v->crt_width = 80;
	v->crt_height = 25;
	v->vram = (unsigned short*)0xb8000;
	clrscr(v);	
}

void puts(video* v,const char *str) 
{
	while (*str) {
		putchar(v,*str++);
	}
}


char *uint_to_str(char *buf, unsigned src, int base) 
{
	char *p = buf;
	char *p1,*p2;

	do {
		*p++ = "0123456789ABCDEF"[src%base];
	} while(src/=base);
	*p = 0;
	for (p1=buf,p2=p-1; p1<p2; p++,p2--) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
	}
	return buf;
}


void printf(video* v, char *fmt,...)
{
	char **arg = (char**) &fmt;
	char c;
	arg++;

	while((c=*fmt++) != 0) {
		if (c != '%') {
			putchar(v, c);
		}
		else {
			char buf[64];
			char *p;
			c = *fmt++;
			switch (c) {
			case 'd' :
				if (0 > *((int*) arg)) {
					putchar(v,'-');
					*((int*)arg) = -1;
				}
				p = uint_to_str(buf,*((unsigned *) arg++),10);
				goto print_s;
			case 'x' :
				p = uint_to_str(buf,*((unsigned*) arg++), 16);
				goto print_s;
			case 's' :
				p = *arg++;
print_s:
				printf(v,p);
			default :
				putchar(v,c);
			}
		}
	}
}

